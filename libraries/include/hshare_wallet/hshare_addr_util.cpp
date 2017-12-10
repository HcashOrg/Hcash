#include "hshare_addr_util.h"
#include <fc/io/sstream.hpp>
#include "client/ClientImpl.hpp"


#include <openssl/aes.h>
#include <openssl/rand.h>


LockedPageManager LockedPageManager::instance;

namespace hshare
{

	int EC_KEY_regenerate_key(EC_KEY *eckey, BIGNUM *priv_key)
	{
		int ok = 0;
		BN_CTX *ctx = NULL;
		EC_POINT *pub_key = NULL;

		if (!eckey) return 0;

		const EC_GROUP *group = EC_KEY_get0_group(eckey);

		if ((ctx = BN_CTX_new()) == NULL)
			goto err;

		pub_key = EC_POINT_new(group);

		if (pub_key == NULL)
			goto err;

		if (!EC_POINT_mul(group, pub_key, priv_key, NULL, NULL, ctx))
			goto err;

		EC_KEY_set_private_key(eckey, priv_key);
		EC_KEY_set_public_key(eckey, pub_key);

		ok = 1;

	err:

		if (pub_key)
			EC_POINT_free(pub_key);
		if (ctx != NULL)
			BN_CTX_free(ctx);

		return(ok);
	}

	bool SetSecretBytes(const unsigned char vch[32], EC_KEY* pkey)
	{
		bool ret;
		BIGNUM bn;
		BN_init(&bn);
		ret = BN_bin2bn(vch, 32, &bn);
		assert(ret);
		ret = EC_KEY_regenerate_key(pkey, &bn);

		BN_clear_free(&bn);
		return ret;
	}


	template<typename T1>
	inline uint256 Hash(const T1 pbegin, const T1 pend)
	{
		static unsigned char pblank[1];
		uint256 hash1;
		SHA256((pbegin == pend ? pblank : (unsigned char*)&pbegin[0]), (pend - pbegin) * sizeof(pbegin[0]), (unsigned char*)&hash1);
		uint256 hash2;
		SHA256((unsigned char*)&hash1, sizeof(hash1), (unsigned char*)&hash2);
		return hash2;
	}

	bool isHsharePubkeyCompressed(const std::vector<unsigned char>& hshare_pubkey)
	{
		int len = hshare_pubkey.size();
		if (len == COMPRESSED)
			return true;
		else
			return false;
	}

	fc::ecc::public_key changeHsharePubkey(std::vector<unsigned char> hshare_pubkey)
	{
		int len = hshare_pubkey.size();
		if (isHsharePubkeyCompressed(hshare_pubkey))
		{
			fc::ecc::public_key_data pubkeydata;
			memcpy(&pubkeydata, &hshare_pubkey[0], COMPRESSED);
			fc::ecc::public_key pubkey(pubkeydata);
			return pubkey;
		}
		else
		{
			fc::ecc::public_key_point_data  pubkeydata;
			memcpy(&pubkeydata, &hshare_pubkey[0], UNCOMPRESSED);
			fc::ecc::public_key pubkey(pubkeydata);
			return pubkey;
		}

	}


	std::string getHshareAddr(std::vector<unsigned char> hshare_pubkey)
	{

		fc::ecc::public_key pubkey = changeHsharePubkey(hshare_pubkey);

		hsrcore::blockchain::PtsAddress ptsaddr(pubkey, true, 40);
		std::string str = ptsaddr;

		return str;

	}

	fc::ecc::private_key changeHsharePrivkey(std::vector<unsigned char> hshare_privkey, bool isCompressed)
	{
		unsigned char vch[32];
		std::vector<char> temp_vch;
		temp_vch.reserve(32);
		convert_key(hshare_privkey, vch);
		temp_vch.assign(vch, vch + 32);
		

		fc::ecc::private_key final_key = fc::variant(temp_vch).as<fc::ecc::private_key>();

		return final_key;
	}


	bool ReadKeyValue(CDataStream& ssKey, CDataStream& ssValue, std::string& strType, std::string& strErr, std::vector<std::string>& vwif, set<std::string>& vKeyPool)
	{
		try
		{

			// Unserialize
			// Taking advantage of the fact that pair serialization
			// is just the two items serialized one after the other


			ssKey >> strType;

			if (strType == "pool")
			{
				int64_t temp_time;
				int nversion;
				std::vector<unsigned char> tempvchPubKey;
				ssValue >> nversion;
				ssValue >> temp_time;
				ssValue >> tempvchPubKey;
				fc::ecc::public_key vchPubKey;
				vchPubKey = changeHsharePubkey(tempvchPubKey);
				if (!vchPubKey.valid())
				{
					strErr = "Error reading wallet database: CPubKey corrupt";
					return false;
				}
				vKeyPool.emplace(vchPubKey.to_base58());

			}


			if (strType == "key")
			{
				std::vector<unsigned char> tempvchPubKey;
				ssKey >> tempvchPubKey;
				//tempvchPubKey.assign(ssKey.begin() + ssKey.nReadPos+1, ssKey.begin() + ssKey.nReadPos + 1+ (int)*(ssKey.begin() + ssKey.nReadPos));
				fc::ecc::public_key vchPubKey;
				vchPubKey = changeHsharePubkey(tempvchPubKey);
				if (!vchPubKey.valid())
				{
					strErr = "Error reading wallet database: CPubKey corrupt";
					return false;
				}

//				printf("address : %s ", getHshareAddr(tempvchPubKey).c_str());
				fc::ecc::private_key pkey;

				uint256 hash;

				std::vector<unsigned char> temppkey;
				ssValue >> temppkey;

				pkey = changeHsharePrivkey(temppkey, false);
				vwif.emplace_back(hsrcore::utilities::key_to_wif(pkey));

//				printf("private : %s ", hsrcore::utilities::key_to_wif(pkey).c_str());
				auto ttee = pkey.get_public_key();
				hsrcore::blockchain::PtsAddress ptsaddr(pkey.get_public_key(), true, 40);
				std::string str = ptsaddr;
//				printf("my address : %s \n", str.c_str());
				// Old wallets store keys as "key" [pubkey] => [privkey]
				// ... which was slow for wallets with lots of keys, because the public key is re-derived from the private key
				// using EC operations as a checksum.
				// Newer wallets store keys as "key"[pubkey] => [privkey][hash(pubkey,privkey)], which is much faster while
				// remaining backwards-compatible.
				try
				{
					ssValue >> hash;
				}
				catch (...) {}


				bool fSkipCheck = false;

				if (hash != 0)
				{
					// hash pubkey/privkey to accelerate wallet load
					std::vector<unsigned char> vchKey;
					vchKey.reserve(tempvchPubKey.size() + temppkey.size());
					vchKey.insert(vchKey.end(), tempvchPubKey.begin(), tempvchPubKey.end());
					vchKey.insert(vchKey.end(), temppkey.begin(), temppkey.end());
					std::string ss1 = Hash(vchKey.begin(), vchKey.end()).GetHex();
					std::string ss2 = hash.GetHex();
					if (Hash(vchKey.begin(), vchKey.end()) != hash)
					{
						strErr = "Error reading wallet database: CPubKey/CPrivKey corrupt";
						return false;
					}

					fSkipCheck = true;
				}

				// 			if (!key.Load(pkey, vchPubKey, fSkipCheck))
				// 			{
				// 				strErr = "Error reading wallet database: CPrivKey corrupt";
				// 				return false;
				// 			}

			}


		}
		catch (...)
		{
			return false;
		}
		return true;
	}

	DBErrors getUnencryptKeys( std::vector<std::string>& vwif, const std::string& infile)
	{

		DBErrors result = DB_LOAD_OK;
		CDB walletdb(infile, "r+");


		int nMinVersion = 0;
		if (walletdb.Read((std::string)"minversion", nMinVersion))
		{
			if (nMinVersion > CLIENT_VERSION)
				return DB_TOO_NEW;
		}

		// Get cursor
		Dbc* pcursor = walletdb.GetCursor();
		if (!pcursor)
		{
			printf("Error getting wallet database cursor\n");
			return DB_CORRUPT;
		}
		set<std::string> vKeyPool;
		std::vector<std::string> vAllWif;
		while (true)
		{
			// Read next record
			CDataStream ssKey(SER_DISK, CLIENT_VERSION);
			CDataStream ssValue(SER_DISK, CLIENT_VERSION);
			int ret = walletdb.ReadAtCursor(pcursor, ssKey, ssValue);
			
			if (ret == DB_NOTFOUND)
				break;
			else if (ret != 0)
			{
				printf("Error reading next record from wallet database\n");
				return DB_CORRUPT;
			}

			// Try to be tolerant of single corrupt records:
			std::string strType, strErr;

			if (!ReadKeyValue(ssKey, ssValue, strType, strErr, vAllWif, vKeyPool))
			{
				
				// losing keys is considered a catastrophic error, anything else
				// we assume the user can live with:
				result = DB_CORRUPT;

			}
			if (!strErr.empty())
				printf("%s\n", strErr.c_str());

		}
		pcursor->close();
		for (auto temp_str : vAllWif)
		{
			auto pkey = hsrcore::utilities::wif_to_key(temp_str);
			if (pkey)
			{
				auto pPub = pkey->get_public_key();
				if (!vKeyPool.count(pPub.to_base58()))
				{
					vwif.emplace_back(temp_str);
				}
			}
			
		}


		return result;


	}




	bool ReadCryptKeyValue(CDataStream& ssKey, CDataStream& ssValue, std::string& strType, std::string& strErr,
		                   vector<CMasterKey>& vmkey, std::vector<vector<unsigned char>>& vpubkey, std::vector<vector<unsigned char>>& vcryptsecret)
	{
		try
		{

			// Unserialize
			// Taking advantage of the fact that pair serialization
			// is just the two items serialized one after the other


			ssKey >> strType;

			if (strType == "mkey")
			{
				unsigned int nId;
				ssKey >> nId;

				CMasterKey tmp;
				ssValue >> tmp;

				vmkey.emplace_back(tmp);
				
			}
			else if (strType == "ckey")
			{
				
				vector<unsigned char> vchPubKey;
				ssKey >> vchPubKey;
				vector<unsigned char> vchCryptedSecret;
				ssValue >> vchCryptedSecret;
				
				vpubkey.emplace_back(vchPubKey);
				vcryptsecret.emplace_back(vchCryptedSecret);
			}

		}
		catch (...)
		{
			return false;
		}
		return true;
	}


	DBErrors dumpCryptKeys(vector<CMasterKey>& vmkey, std::vector<vector<unsigned char>>& vpubkey, std::vector<vector<unsigned char>>& vsecret, const std::string& infile)
	{

		//clear contents
		vmkey.clear();
		vpubkey.clear();
		vsecret.clear();


		DBErrors result = DB_LOAD_OK;
		CDB walletdb(infile, "r+");


		int nMinVersion = 0;
		if (walletdb.Read((std::string)"minversion", nMinVersion))
		{
			if (nMinVersion > CLIENT_VERSION)
				return DB_TOO_NEW;
		}

		// Get cursor
		Dbc* pcursor = walletdb.GetCursor();
		if (!pcursor)
		{
			printf("Error getting wallet database cursor\n");
			return DB_CORRUPT;
		}

		while (true)
		{
			// Read next record
			CDataStream ssKey(SER_DISK, CLIENT_VERSION);
			CDataStream ssValue(SER_DISK, CLIENT_VERSION);
			int ret = walletdb.ReadAtCursor(pcursor, ssKey, ssValue);
			if (ret == DB_NOTFOUND)
				break;
			else if (ret != 0)
			{
				printf("Error reading next record from wallet database\n");
				return DB_CORRUPT;
			}

			// Try to be tolerant of single corrupt records:
			std::string strType, strErr;

			if (!ReadCryptKeyValue(ssKey, ssValue, strType, strErr, vmkey, vpubkey, vsecret))
			{
				// losing keys is considered a catastrophic error, anything else
				// we assume the user can live with:
				result = DB_CORRUPT;

			}
			if (!strErr.empty())
				printf("%s\n", strErr.c_str());
		}
		pcursor->close();

		return result;


	}



/*	int testEncyptLen(std::vector<unsigned char>& src, std::vector<unsigned char>& des)
	{
		int nLen = src.size();
		int nCLen = nLen + AES_BLOCK_SIZE, nFLen = 0;
		des = std::vector<unsigned char>(nCLen);

		unsigned char chKey[32];
		unsigned char chIV[32];
		RAND_bytes(&chKey[0], 32);
		RAND_bytes(&chIV[0], 32);

		EVP_CIPHER_CTX ctx;

		bool fOk = true;

		EVP_CIPHER_CTX_init(&ctx);
		if (fOk) fOk = EVP_EncryptInit_ex(&ctx, EVP_aes_256_cbc(), NULL, chKey, chIV);
		if (fOk) fOk = EVP_EncryptUpdate(&ctx, &des[0], &nCLen, &des[0], nLen);
		if (fOk) fOk = EVP_EncryptFinal_ex(&ctx, (&des[0]) + nCLen, &nFLen);
		EVP_CIPHER_CTX_cleanup(&ctx);

		if (!fOk) printf("encryt error!");

		return nCLen + nFLen;
	}*/


	unsigned char chKey[WALLET_CRYPTO_KEY_SIZE];
	unsigned char chIV[WALLET_CRYPTO_KEY_SIZE];

	bool setKeyFromPassphrase(const std::string& strKeyData, const std::vector<unsigned char>& chSalt, const unsigned int nRounds, const unsigned int nDerivationMethod)
	{
		if (nRounds < 1 || chSalt.size() != WALLET_CRYPTO_SALT_SIZE)
			return false;

		int i = 0;
		
	
		i = EVP_BytesToKey(EVP_aes_256_cbc(), EVP_sha512(), &chSalt[0],
				(unsigned char *)&strKeyData[0], strKeyData.size(), nRounds, chKey, chIV);
		
		if (i != WALLET_CRYPTO_KEY_SIZE)
			return false;
		
		return true;
	}




	bool descrpt(const std::vector<unsigned char>& vchCiphertext, CKeyingMaterial& vchPlaintext)
	{
		// plaintext will always be equal to or lesser than length of ciphertext
		int nLen = vchCiphertext.size();
		int nPLen = nLen, nFLen = 0;

		vchPlaintext = CKeyingMaterial(nPLen);

		EVP_CIPHER_CTX ctx;

		bool fOk = true;

		EVP_CIPHER_CTX_init(&ctx);
		if (fOk) fOk = EVP_DecryptInit_ex(&ctx, EVP_aes_256_cbc(), NULL, chKey, chIV);
		if (fOk) fOk = EVP_DecryptUpdate(&ctx, &vchPlaintext[0], &nPLen, &vchCiphertext[0], nLen);
		if (fOk) fOk = EVP_DecryptFinal_ex(&ctx, (&vchPlaintext[0]) + nPLen, &nFLen);
		EVP_CIPHER_CTX_cleanup(&ctx);

		if (!fOk) return false;

		vchPlaintext.resize(nPLen + nFLen);
		return true;
	}

	bool decryptSecret(const CKeyingMaterial& vMasterKey, const std::vector<unsigned char>& vchCiphertext, const uint256& nIV, CKeyingMaterial& vchPlaintext)
	{
		memcpy(&chIV[0], &nIV, WALLET_CRYPTO_KEY_SIZE);
		memcpy(&chKey[0], &vMasterKey[0], sizeof chKey);
	
		return descrpt(vchCiphertext, *((CKeyingMaterial*)&vchPlaintext));
	}

	void getHsharePrivKey(std::vector<unsigned char>& hshare_privkey, const hshare::CKeyingMaterial& vchSecret)
	{
		EC_KEY *pkey = EC_KEY_new_by_curve_name(NID_secp256k1);
		assert(pkey != NULL);
		unsigned char vch[32];
		for (int i = 0; i < vchSecret.size(); ++i)
			vch[i] = vchSecret[i];

		if (!SetSecretBytes(vch, pkey))
			printf("SetSecretBytes failed!");

		EC_KEY_set_conv_form(pkey, POINT_CONVERSION_UNCOMPRESSED);
		int nSize = i2d_ECPrivateKey(pkey, NULL);
		assert(nSize);
		hshare_privkey.resize(nSize);

		unsigned char* pbegin = &hshare_privkey[0];
		int nSize2 = i2d_ECPrivateKey(pkey, &pbegin);
		assert(nSize == nSize2);
	}


	DBErrors getEncryptKeys(std::vector<std::string>& vwif, const std::string& passwd, const std::string& infile)
	{

		DBErrors res = DB_LOAD_OK;

		std::vector<hshare::CMasterKey> vmkey;
		std::vector<vector<unsigned char>> vpubkey;
		std::vector<vector<unsigned char>> vcryptsecret;
		hshare::dumpCryptKeys(vmkey, vpubkey, vcryptsecret, infile);

		for (int i = 0; i < vpubkey.size(); ++i)
		{
//			printf("pubkey addr: %s\n", hshare::getHshareAddr(vpubkey[i]).c_str());

			auto h = hshare::Hash(vpubkey[i].begin(), vpubkey[i].end());
			
			if (!hshare::setKeyFromPassphrase(passwd, vmkey[0].vchSalt, vmkey[0].nDeriveIterations, vmkey[0].nDerivationMethod))
			{
				printf("setKeyFromPassphrase error!");
				res = DB_CORRUPT;
				break;
			}

			hshare::CKeyingMaterial vMasterKey;
			if (!hshare::descrpt(vmkey[0].vchCryptedKey, vMasterKey))
			{
				printf("descrpt function, get vMasterKey error!");
				res = DB_CORRUPT;
				continue;
			}


			hshare::CKeyingMaterial vchSecret;

			hshare::decryptSecret(vMasterKey, vcryptsecret[i], h, vchSecret);
			if (vchSecret.size() != 32)
			{
				printf("size = %d, get secret error!\n", vchSecret.size());

				continue;
			}


			vector<unsigned char> privKey;
			hshare::getHsharePrivKey(privKey, vchSecret);

			fc::ecc::private_key pkey;

			pkey = hshare::changeHsharePrivkey(privKey, false);
			vwif.emplace_back(hsrcore::utilities::key_to_wif(pkey));

//			printf("private : %s ", hsrcore::utilities::key_to_wif(pkey).c_str());
//			auto ttee = pkey.get_public_key();
//			hsrcore::blockchain::PtsAddress ptsaddr(pkey.get_public_key(), true, 40);
//			std::string str = ptsaddr;
//			printf("my address : %s \n", str.c_str());

		}

		return res;

	}



	
}



/*
int main()
{
//	hshare::dumpKeys("C:\\Users\\wensw\\Desktop\\wallet.dat");


//	std::vector<unsigned char> src(32, 0), dst;	
//	RAND_bytes(&src[0], 32);
//	printf("%d\n", hshare::testEncyptLen(src, dst));

	std::vector<std::string> vwif;
/*
	std::vector<hshare::CMasterKey> vmkey;
	std::vector<vector<unsigned char>> vpubkey;
	std::vector<vector<unsigned char>> vcryptsecret;
	hshare::dumpCryptKeys(vmkey, vpubkey, vcryptsecret, "C:\\Users\\wensw\\Desktop\\wallet_out.dat");

	printf("%d\n", vmkey.size());
	printf("%d\n", vpubkey.size());
	printf("%d\n", vcryptsecret.size());

	for (auto tmp : vpubkey)
	{
		printf("%s\n", hshare::getHshareAddr(tmp).c_str());
	}

	for (int i = 0; i < vpubkey.size(); ++i)
	{
		printf("pubkey addr: %s\n", hshare::getHshareAddr(vpubkey[i]).c_str());

		auto h = hshare::Hash(vpubkey[i].begin(), vpubkey[i].end());
		hshare::SecureString passphase("123456789");
		if (!hshare::setKeyFromPassphrase(passphase, vmkey[0].vchSalt, vmkey[0].nDeriveIterations, vmkey[0].nDerivationMethod))
		{
			printf("setKeyFromPassphrase error!");
			break;
		}

		hshare::CKeyingMaterial vMasterKey;
		if (!hshare::descrpt(vmkey[0].vchCryptedKey, vMasterKey))
		{
			printf("descrpt function, get vMasterKey error!");
			continue;
		}


		hshare::CKeyingMaterial vchSecret;

		hshare::decryptSecret(vMasterKey, vcryptsecret[i], h, vchSecret);
		if (vchSecret.size() != 32)
		{
			printf("size = %d, get secret error!\n", vchSecret.size());

			continue;
		}
			

		vector<unsigned char> privKey;
		hshare::getHsharePrivKey(privKey, vchSecret);
		
		fc::ecc::private_key pkey;

		pkey = hshare::changeHsharePrivkey(privKey, false);
		vwif.emplace_back(hsrcore::utilities::key_to_wif(pkey));

		printf("private : %s ", hsrcore::utilities::key_to_wif(pkey).c_str());
		auto ttee = pkey.get_public_key();
		hsrcore::blockchain::PtsAddress ptsaddr(pkey.get_public_key(), true, 40);
		std::string str = ptsaddr;
		printf("my address : %s \n", str.c_str());

	}
#1#
	std::string passwd = "123456789";
	hshare::getEncryptKeys(vwif, passwd, "C:\\Users\\wensw\\Desktop\\wallet_out.dat");

	getchar();

}

*/
