#include <blockchain/Block.hpp>
#include <algorithm>
#include<utilities/uint256.hpp>
#include <utilities/hash.hpp>

namespace hsrcore {
    namespace blockchain {

        DigestType BlockHeader::digest()const
        {
            fc::sha256::encoder enc;
            fc::raw::pack(enc, *this);
            return enc.result();
        }

        BlockIdType SignedBlockHeader::id()const
        {
            fc::sha512::encoder enc;
            fc::raw::pack(enc, *this);
            return fc::ripemd160::hash(enc.result());
        }

		uint256 BlockHeader::GetPoWHash() const
		{

			auto rec = fc::raw::pack(*this);
			
			//return HashX14(rec.begin(),rec.end());
			return HashR14(rec.begin(), rec.end());

		}
		uint256 BlockHeader::GetNoNonceHash() const
		{
			auto rec = fc::raw::pack(*this);
			//return HashX14(rec.begin(),rec.end());
			memset(&rec[140],0,sizeof(uint64_t)*2);
			return HashR14(rec.begin(), rec.end());
		}



        bool SignedBlockHeader::validate_signee(const fc::ecc::public_key& expected_signee, bool enforce_canonical)const
        {
            return fc::ecc::public_key(delegate_signature, digest(), enforce_canonical) == expected_signee;
        }

        PublicKeyType SignedBlockHeader::signee(bool enforce_canonical)const
        {
            return fc::ecc::public_key(delegate_signature, digest(), enforce_canonical);
        }

        void SignedBlockHeader::sign(const fc::ecc::private_key& signer)
        {
            try {
                delegate_signature = signer.sign_compact(digest());
            } FC_RETHROW_EXCEPTIONS(warn, "")
        }

        size_t FullBlock::block_size()const
        {
            fc::datastream<size_t> ds;
            fc::raw::pack(ds, *this);
            return ds.tellp();
        }

        DigestBlock::DigestBlock(const FullBlock& block_data)
        {
            (SignedBlockHeader&)*this = block_data;
            user_transaction_ids.reserve(block_data.user_transactions.size());
            for (const auto& item : block_data.user_transactions)
                user_transaction_ids.push_back(item.id());
        }

        DigestType DigestBlock::calculate_transaction_digest()const
        {
            fc::sha512::encoder enc;
            fc::raw::pack(enc, user_transaction_ids);
            return fc::sha256::hash(enc.result());
        }

        bool DigestBlock::validate_digest()const
        {
            return calculate_transaction_digest() == transaction_digest;
        }

        bool DigestBlock::validate_unique()const
        {
            std::unordered_set<TransactionIdType> trx_ids;
            for (const auto& id : user_transaction_ids)
                if (!trx_ids.insert(id).second) return false;
            return true;
        }

    }
} // hsrcore::blockchain
