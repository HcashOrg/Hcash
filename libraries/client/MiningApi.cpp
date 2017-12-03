#include <client/Client.hpp>
#include <client/ClientImpl.hpp>
#include <client/Messages.hpp>
#include <fc/reflect/variant.hpp>

#include <fc/thread/non_preemptable_scope_check.hpp>
#include "cli/locale.hpp"

#include <blockchain/ChainDatabase.hpp>
#include <blockchain/Time.hpp>
#include <glua/hsrcore_lua_api.h>
#include <glua/hsrcore_lua_lib.h>
#include <glua/glua_lutil.h>
#include <fc/exception/exception.hpp>
#include <fc/thread/mutex.hpp>
#include <fc/thread/unique_lock.hpp>

#include <boost/uuid/sha1.hpp>
#include "blockchain/ContractOperations.hpp"
#include <utilities/CommonApi.hpp>

#include <utilities/bignum.hpp>
#include <boost/random.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/thread/locks.hpp>
#include <utilities/util.hpp>

namespace hsrcore {
	namespace client {
		namespace detail {
			/**
			* get mining info!.
			*
			* @return MiningInfo
			*/
			MiningInfo ClientImpl::get_mining_info()
			{
				MiningInfo miningdata;
				miningdata.blocks = _chain_db->get_head_block_num();
				miningdata.chain = "main";
				miningdata.currentblocksize = nBlockSize;
				miningdata.currentblocktx = nBlockTx;
				auto blockheader = _chain_db->get_head_block();

				miningdata.proof_of_work = GetDiffculty(blockheader,0);
				miningdata.proof_of_stake = GetDiffculty(blockheader,1);
				miningdata.errors = "";
				miningdata.generate = fgenerate;
				miningdata.genproclimit = nThread;
				miningdata.hashespersec = dHashesPerSec;
				miningdata.networkhashps = dHashesPerSec;
				miningdata.pooledtx = _chain_db->get_pending_transactions().size();


				return miningdata;
			}
			/**
			* get difficulty info!.
			*
			* @return float
			*/
			MiningDifficulty ClientImpl::get_difficulty()
			{
				MiningDifficulty diff;
				auto blockheader = _chain_db->get_head_block();
				diff.proof_of_work = GetDiffculty(blockheader,0);
				diff.proof_of_stake = GetDiffculty(blockheader,1);
				return diff;
			}
			/**
			* set generate!.
			*
			* @param fGenerate is start generate? (bool, required)
			* @param nThreads generate block thread count (filename, required)
			*
			* @return bool
			*/
			bool ClientImpl::set_generate(bool fGenerate, uint32_t nThreads )
			{
				GenerateBitcoins(fGenerate, nThreads);
				return true;
			}

			bool ClientImpl::set_pos_generate()
			{
				GenerateStakes();
				return true;
			}

			/**
			* get work for mining.
			*
			* @return MiningWorkPackage
			*/
			MiningWorkPackage ClientImpl::get_work()
			{
				MiningWorkPackage mining_work;
				const auto now = blockchain::now();
				_delegate_config.validate();
				if (coinbase == PublicKeyType())
				{
					auto& all_accounts = _wallet->get_wallet_db().get_accounts();
					FC_ASSERT(all_accounts.size() > 0,"please create account first");
					coinbase = all_accounts.begin()->second.owner_key;

				}
				FC_ASSERT(coinbase != PublicKeyType(),"please set coinbase first");
				FullBlock pblock(_chain_db->generate_block(now, coinbase,_delegate_config));
				uint256 hashTarget = CBigNum().SetCompact(pblock.nbits).getuint256();
				
				mining_work.data = fc::raw::pack ((BlockHeader)pblock);
				mining_work.hashnoNonce = pblock.GetNoNonceHash().GetHex();
				mining_work.target = hashTarget.GetHex();
				mapNewBlock[mining_work.hashnoNonce] = pblock;
				return mining_work;
			}
			/**
			* submit block!.
			*
			* @param HashNoNonce blockchain no nonce hash (std::string, required)
			* @param block blockchain data (std::string, required)
			*
			* @return bool
			*/
			bool ClientImpl::submit_block(const std::string& HashNoNonce, uint64_t Nonce,uint64_t Extra_Nonce)
			{
				BlockHeader temp_block;

				if (mapNewBlock.count(HashNoNonce))
				{
					auto pblock = mapNewBlock[HashNoNonce];
					pblock.nNonce = Nonce;
					pblock.extra_nonce = Extra_Nonce;
					_wallet->CheckWork(pblock);
					_wallet->pow_sign_block(pblock);
					auto temp_block = on_new_block(pblock, pblock.id(), false);
					if (!temp_block.is_included)
						return false;
					_p2p_node->broadcast(BlockMessage(pblock));
					return true;
				}
				


				return false;
			}

			bool  hex2bin(const char *pSrc, vector<char> &pDst, unsigned int nSrcLength, unsigned int &nDstLength)
			{
				if (pSrc == 0)
				{
					return false;
				}

				nDstLength = 0;

				if (pSrc[0] == 0) // nothing to convert  
					return 0;

				// 计算需要转换的字节数  
				for (int j = 0; pSrc[j]; j++)
				{
					if (isxdigit(pSrc[j]))
						nDstLength++;
				}

				// 判断待转换字节数是否为奇数，然后加一  
				if (nDstLength & 0x01) nDstLength++;
				nDstLength /= 2;

				if (nDstLength > nSrcLength)
					return false;

				nDstLength = 0;

				int phase = 0;
				char temp_char;

				for (int i = 0; pSrc[i]; i++)
				{
					if (!isxdigit(pSrc[i]))
						continue;

					unsigned char val = pSrc[i] - (isdigit(pSrc[i]) ? 0x30 : (isupper(pSrc[i]) ? 0x37 : 0x57));

					if (phase == 0)
					{
						temp_char = val << 4;
						phase++;
					}
					else
					{
						temp_char |= val;
						phase = 0;
						pDst.push_back(temp_char);
						nDstLength++;
					}
				}

				return true;
			}

			bool ClientImpl::submit_blockex(const std::string& data)
			{
				BlockHeader temp_block;
				std::vector<char> all_data;
				all_data.reserve(data.size() / 2);
				unsigned int nDstLength;
				hex2bin(data.c_str(), all_data, data.size(), nDstLength);
				temp_block = fc::raw::unpack<BlockHeader>(all_data);

				auto HashNoNonce = temp_block.GetNoNonceHash().GetHex();
				if (mapNewBlock.count(HashNoNonce))
				{
					auto pblock = mapNewBlock[HashNoNonce];
					pblock.nNonce = temp_block.nNonce;
					pblock.extra_nonce = temp_block.extra_nonce;
					pblock.reserver_data2 = temp_block.reserver_data2;
					_wallet->CheckWork(pblock);
					_wallet->pow_sign_block(pblock);
					on_new_block(pblock, pblock.id(), false);
					_p2p_node->broadcast(BlockMessage(pblock));
					return true;
				}



				return false;
			}


			bool  ClientImpl::set_coinbase(const std::string& account_name)
			{
				try
				{
					if (_wallet->is_valid_account_name(account_name))
					{
						coinbase = _wallet->get_account(account_name).owner_key;
					}
					else
					{
						Address temp(account_name);
						auto accountentry = _wallet->get_account_for_address(temp);
						if (accountentry.valid())
						{
							coinbase = accountentry->owner_key;
						}
					}
					return true;
				}
				FC_CAPTURE_AND_LOG(("set coinbase invalid address"));


				return false;
			}

			StakingInfo ClientImpl::get_staking_info()
			{
				StakingInfo stakeinfo;

				uint64_t nWeight = 0;
				if (_wallet->is_open())
					nWeight = _wallet->GetStakeWeight();

				uint64_t nNetworkWeight = GetPoSKernelPS();

				uint64_t nExpectedTime = fposgenerate&&nWeight>0 ? (HSR_PRODUCTE_BLOCK_INTERAL * nNetworkWeight / nWeight) : 0;
				stakeinfo.enabled = fposgenerate;
				stakeinfo.currentblocksize = nBlockSize;
				stakeinfo.currentblocktx = nBlockTx;
				auto block_header = _chain_db->get_head_block();
				stakeinfo.difficulty = GetDiffculty(block_header,1);
				stakeinfo.weight = nWeight;
				stakeinfo.netstakeweight = nNetworkWeight;
				stakeinfo.nExpectedTime = nExpectedTime;
				return stakeinfo;
			}
			/**
			* compile script source code to byte code, and store to binary file.
			*
			* @param filename script source file name (filename, required)
			*
			* @return filename
			*/
			inline void MilliSleep(int64_t n)
			{
#if BOOST_VERSION >= 105000
				boost::this_thread::sleep_for(boost::chrono::milliseconds(n));
#else
				boost::this_thread::sleep(boost::posix_time::milliseconds(n));
#endif
			}

			static void BitcoinMiner(ClientImpl * _client)
			{
				wlog("BRAINHasher Miner started\n");
				SetThreadPriority(THREAD_PRIORITY_LOWEST);
				RenameThread("brain-miner");

				// Each thread has its own key and counter


				try {
					while (_client->exit_miner_thread) {
						const auto now = fc::time_point_sec(fc::time_point::now());
						_client->_delegate_config.validate();
						{

							// Busy-wait for the network to come online so we don't waste time mining
							// on an obsolete chain. In regtest mode we expect to fly solo.
							//        while (vNodes.empty())
							//            MilliSleep(1000);


							//
							// Create new block
							//

							//int64_t nFees;

							while (!_client->_wallet->is_open())
							{
								MilliSleep(1000);
							}
							while (_client->_wallet->is_locked())
							{
								MilliSleep(1000);
							}

							if (_client->coinbase == PublicKeyType())
							{
								auto& all_accounts = _client->_wallet->get_wallet_db().get_accounts();
								FC_ASSERT(all_accounts.size() > 0, "please create account first");
								_client->coinbase = all_accounts.begin()->second.owner_key;

							}
							FC_ASSERT(_client->coinbase != PublicKeyType(), "please set coinbase first");

							FullBlock pblock(_client->_chain_db->generate_block(now, (Address)_client->coinbase,_client->_delegate_config));

							_client->nBlockSize = pblock.block_size();
							_client->nBlockTx = pblock.user_transactions.size();
							


							uint256 hashTarget = CBigNum().SetCompact(pblock.nbits).getuint256();
							fc::time_point_sec nStart = fc::time_point::now();
							uint256 hash;
							unsigned int nHashesDone = 0;
							boost::rand48 ran;
							pblock.nNonce = ran();
							while (_client->exit_miner_thread)
							{
								hash = pblock.GetPoWHash();
								++nHashesDone;
								try {


									if (hash <= hashTarget)
									{
										// Found a solution
										SetThreadPriority(THREAD_PRIORITY_NORMAL);
										_client->_wallet->CheckWork(pblock);
										_client->_wallet->pow_sign_block(pblock);
										_client->on_new_block(pblock, pblock.id(), false);
										_client->_p2p_node->broadcast(BlockMessage(pblock));
										SetThreadPriority(THREAD_PRIORITY_LOWEST);
										break;
									}
									++pblock.nNonce;

									// Meter hashes/sec
									static int64_t nHashCounter;
									if (_client->nHPSTimerStart == fc::time_point_sec(0))
									{
										_client->nHPSTimerStart = fc::time_point::now();
										nHashCounter = 0;
									}
									else
										++nHashCounter;// += nHashesDone;
									if ((fc::time_point::now() - _client->nHPSTimerStart).to_seconds() % 4 == 0)
									{
										static boost::mutex _update_speed;
										{
											_update_speed.lock();
											pblock.timestamp = fc::time_point::now();
											int64_t nLimiter = 1;
											int64_t nDelta = (fc::time_point::now() - _client->nHPSTimerStart).to_seconds();
											if (nDelta > 0 && nLimiter <= 10 + 1)
												_client->dHashesPerSec = 32768 * nHashCounter / (fc::time_point::now() - _client->nHPSTimerStart).to_seconds();
											//nHPSTimerStart = GetTimeMillis();
											//nHashCounter = 0;
											//nHashesDone = 0;
											// LogPrintf("BRAINHash CPU Hashing Rate: %6.0f hash/s\n", dHashesPerSec);
											// Avoid Debug Log Pollution
											nLimiter++; // Increment by 1
											if (nLimiter >= 5000 + 1) {
												nLimiter = 1;
											}
											_update_speed.unlock();
										}
									}
								}
								catch (...)
								{
								}
								// Check for stop or if block needs to be rebuilt
								boost::this_thread::interruption_point();

								if (pblock.nNonce >= 0xffffffffffff0000)
									break;

								if (pblock.previous != _client->get_head_block_id())
									break;


							}
						}
					}
				}
				catch (boost::thread_interrupted)
				{
					wlog("BRAINHash Miner terminated\n");
					throw;
				}
				catch (...)
				{
				}
			}

			void ThreadStakeMiner(ClientImpl * _client)
			{

				SetThreadPriority(THREAD_PRIORITY_LOWEST);
				_client->fposgenerate = true;
				// Make this thread recognisable as the mining thread
				RenameThread("hshare-miner");

				bool fTryToSync = true;

				while (true)
				{
					while (!_client->_wallet->is_open())
					{
						_client->nLastCoinStakeSearchInterval = 0;
						MilliSleep(1000);
					}
					while (_client->_wallet->is_locked())
					{
						_client->nLastCoinStakeSearchInterval = 0;
						MilliSleep(1000);
					}
					while (!_client->blockchain_is_synced())
					{
						_client->nLastCoinStakeSearchInterval = 0;
						fTryToSync = true;
						MilliSleep(1000);
					}

					if (fTryToSync)
					{
						fTryToSync = false;
						if (_client->_p2p_node->get_connection_count() < NETWORK_MIN_CONNECTION_COUNT_DEFAULT || _client->_chain_db->get_head_block_timestamp() < fc::time_point_sec(fc::time_point::now()) - 100 * 60)
						{
							MilliSleep(60000);
							continue;
						}
					}

					//
					// Create new block
					//


					
					try {
						auto all_account_entrys = _client->_wallet->get_spendable_account_balance_entrys();
						for (auto iter = all_account_entrys.begin(); iter != all_account_entrys.end(); ++iter)
						{
							try {

								Address tempcoinbase;
								int flag = 0;
								for (auto entry : iter->second)
								{
									if (entry.balance > 0)
									{
										tempcoinbase = (Address)_client->_wallet->get_owner_public_key(iter->first);
										flag = 1;
										break;
									}
								}
								if (flag)
								{
									const auto now = fc::time_point_sec(fc::time_point::now());
									int64_t nFees;
									FullBlock pblock(_client->_chain_db->generate_block(now, tempcoinbase, _client->_delegate_config,0, true));
									_client->nBlockSize = pblock.block_size();
									_client->nBlockTx = pblock.user_transactions.size();

									if (_client->_chain_db->CheckStake(pblock))
									{
										_client->_wallet->pow_sign_block(pblock);
										_client->on_new_block(pblock, pblock.id(), false);
										_client->_p2p_node->broadcast(BlockMessage(pblock));

									}
								}

							}
						
						catch (...)
						{
						}
						}
						auto all_multisig_account_entrys = _client->_wallet->get_all_multisig();
						for (auto iter = all_multisig_account_entrys.begin(); iter != all_multisig_account_entrys.end(); ++iter)
						{
							try
							{
								Address tempcoinbase;
								auto entry = _client->_chain_db->get_balance_entry(*iter);
								if (entry.valid()&&entry->balance > 0)
								{
									tempcoinbase = *iter;
									auto tempprivate_key = _client->_wallet->get_private_key(*entry->owners().begin());

									const auto now = fc::time_point_sec(fc::time_point::now());
									int64_t nFees;
									FullBlock pblock(_client->_chain_db->generate_block(now, tempcoinbase, _client->_delegate_config, 1, true));
									_client->nBlockSize = pblock.block_size();
									_client->nBlockTx = pblock.user_transactions.size();

									if (_client->_chain_db->CheckStake(pblock))
									{
										_client->_wallet->pow_sign_block(pblock);
										_client->on_new_block(pblock, pblock.id(), false);
										_client->_p2p_node->broadcast(BlockMessage(pblock));

									}
									

									
								}
								
							}
							catch (...)
							{
								
							}
							
						}

						MilliSleep(500);
						
					}
					catch (boost::thread_interrupted)
					{
						wlog("BRAINHash Miner terminated\n");
						throw;
					}
					FC_CAPTURE_AND_LOG(("pos miner exception"));
					


				}


			}

			
			void ClientImpl::GenerateBitcoins(bool fGenerate, int nThreads)
			{

				static boost::thread_group* minerThreads = NULL;
				if (nThreads == -1)
					nThreads = boost::thread::hardware_concurrency();
				fgenerate = fGenerate;
				nThread = nThreads;
				if (!fgenerate)
				{
					nHPSTimerStart = fc::time_point_sec(0);
					dHashesPerSec = 0.0;
					nThread = 0;
				}
				if (minerThreads != NULL)
				{
					exit_miner_thread = 0;
					minerThreads->join_all();
					delete minerThreads;
					minerThreads = NULL;
				}
				if (nThreads == 0 || !fGenerate)
					return;
				exit_miner_thread = 1;
				minerThreads = new boost::thread_group();
				for (int i = 0; i < nThreads; i++)
					minerThreads->create_thread(boost::bind(&BitcoinMiner, this));
			}

			

			void ClientImpl::GenerateStakes()
			{
				static boost::thread_group* minerStakeThread = NULL;
				if (minerStakeThread != NULL)
				{
					minerStakeThread->interrupt_all();
					delete minerStakeThread;
					minerStakeThread = NULL;
				}
				minerStakeThread = new boost::thread_group();
				minerStakeThread->create_thread(boost::bind(&ThreadStakeMiner,this));
			}

			float ClientImpl::GetDiffculty(SignedBlockHeader& block_header,bool is_coinstake)
			{
				if (block_header.block_num == 0)
					return 1.0;

				if (block_header.previous == BlockIdType())
					return 1.0;
				uint32_t tempbits;
				if (is_coinstake)
					tempbits = block_header.sbits;
				else
					tempbits = block_header.nbits;

				int nShift = (tempbits >> 24) & 0xff;
				
				double dDiff =
					(double)0x0000ffff / (double)(tempbits & 0x00ffffff);

				while (nShift < 29)
				{
					dDiff *= 256.0;
					nShift++;
				}
				while (nShift > 29)
				{
					dDiff /= 256.0;
					nShift--;
				}

				return dDiff;
			}

			double ClientImpl::GetPoSKernelPS()
			{
				int nPoSInterval = 72;
				double dStakeKernelsTriedAvg = 0;
				int nStakesHandled = 0, nStakesTime = 0;

				auto block_header = _chain_db->get_head_block();
				SignedBlockHeader pindexPrevStake;


				while (block_header.block_num>0 && nStakesHandled < nPoSInterval && block_header.previous!=BlockIdType())
				{
					if (block_header.is_coinstake)
					{
						if (pindexPrevStake.block_num)
						{
							dStakeKernelsTriedAvg += GetDiffculty(pindexPrevStake,1) * 4294967296.0;
							nStakesTime += (pindexPrevStake.timestamp - block_header.timestamp).to_seconds();
							nStakesHandled++;
						}
						pindexPrevStake = block_header;
					}

					block_header = _chain_db->get_block_header(block_header.previous);
				}

				double result = 0;

				if (nStakesTime)
					result = dStakeKernelsTriedAvg / (double)nStakesTime;
				result *= HSR_STAKE_TIMESTAMP_MASK + 1;

				return result;
			}
			

		}
	}
}
