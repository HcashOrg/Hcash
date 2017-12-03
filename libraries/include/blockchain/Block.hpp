#pragma once

#include <blockchain/Transaction.hpp>
#include <utilities/uint256.hpp>
namespace hsrcore {
    namespace blockchain {

        struct BlockHeader
        {
            DigestType  digest()const;

            BlockIdType        previous;
            uint32_t             block_num = 0;
            
            DigestType          transaction_digest;
            /** used for random number generation on the blockchain */
           /* SecretHashType     next_secret_hash;
            SecretHashType     previous_secret;*/
			Address	  coin_base;

			uint32_t is_coinstake = 0;
			uint32_t is_multisig_account = 0;
			fc::array<char, 27> reserver_data;
			uint32_t nbits;
			uint32_t sbits;
			fc::array<char, 12> reserver_data1;
			fc::time_point_sec   timestamp;
			uint64_t nNonce;
			uint64_t extra_nonce;
			fc::array<char, 24> reserver_data2;
			//fc::array<char, 12> end_data;
			
			
			uint256 GetPoWHash() const;
			uint256 GetNoNonceHash() const;
        };

        struct SignedBlockHeader : public BlockHeader
        {
            BlockIdType    id()const;
            bool             validate_signee(const fc::ecc::public_key& expected_signee, bool enforce_canonical = false)const;
            PublicKeyType  signee(bool enforce_canonical = false)const;
            void             sign(const fc::ecc::private_key& signer);

            SignatureType delegate_signature;
        };

        struct FullBlock : public SignedBlockHeader
        {
            size_t               block_size()const;

            signed_transactions  user_transactions;
        };

        struct DigestBlock : public SignedBlockHeader
        {
            DigestBlock(){}
            DigestBlock(const FullBlock& block_data);

            DigestType                      calculate_transaction_digest()const;
            bool                             validate_digest()const;
            bool                             validate_unique()const;

            std::vector<TransactionIdType> user_transaction_ids;
        };

    }
} // hsrcore::blockchain

FC_REFLECT(hsrcore::blockchain::BlockHeader,
    (previous)(block_num)(transaction_digest)(coin_base)(is_coinstake)(is_multisig_account)(reserver_data)(nbits)(sbits)(reserver_data1)(timestamp)(nNonce)(extra_nonce)(reserver_data2))
    FC_REFLECT_DERIVED(hsrcore::blockchain::SignedBlockHeader, (hsrcore::blockchain::BlockHeader), (delegate_signature))
    FC_REFLECT_DERIVED(hsrcore::blockchain::FullBlock, (hsrcore::blockchain::SignedBlockHeader), (user_transactions))
    FC_REFLECT_DERIVED(hsrcore::blockchain::DigestBlock, (hsrcore::blockchain::SignedBlockHeader), (user_transaction_ids))
