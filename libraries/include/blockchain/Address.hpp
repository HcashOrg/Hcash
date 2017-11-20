#pragma once

#include <blockchain/Config.hpp>
#include <blockchain/PtsAddress.hpp>

#include <fc/array.hpp>
#include <fc/crypto/ripemd160.hpp>
#include <fc/crypto/elliptic.hpp>
#include <fc/crypto/base58.hpp>


namespace fc {
    namespace ecc {
        class public_key;
        typedef fc::array<char, 33>  public_key_data;
    }
} // fc::ecc

namespace hsrcore {
    namespace blockchain {

        enum AddressType
        {
            hsr_address = 0,
            contract_address = 1,
            script_id = 2
        };

        struct WithdrawCondition;
        struct PublicKeyType;

        /**
         *  @brief a 160 bit hash of a public key
         *
         *  An address can be converted to or from a base58 string with 32 bit checksum.
         *
         *  An address is calculated as ripemd160( sha512( compressed_ecc_public_key ) )
         *
         *  When converted to a string, checksum calculated as the first 4 bytes ripemd160( address ) is
         *  appended to the binary address before converting to base58.
         */
        class Address
        {
        public:
            Address(); ///< constructs empty / null address

			explicit Address(const std::string& base58str, const AddressType& address_type = AddressType::hsr_address);   ///< converts to binary, validates checksum
            Address(const fc::ecc::public_key& pub, const AddressType& address_type = AddressType::hsr_address); ///< converts to binary
			explicit Address(const fc::ecc::public_key_data& pub, const AddressType& address_type = AddressType::hsr_address); ///< converts to binary

            Address(const PtsAddress& pub); ///< converts to binary
            Address(const WithdrawCondition& condition, const AddressType& address_type = AddressType::hsr_address);
            Address(const PublicKeyType& pubkey, const AddressType& address_type = AddressType::hsr_address);
            //Address(const PublicKeyType& pubkey, const fc::ripemd160& trxid);//用于合约地址

            /**
            * Validate address
            * @param base58str address string
            * @param to_account prefix of string
            * @return bool
            */

			static bool is_valid(const std::string& base58str, const std::string& prefix = HSR_ADDRESS_PREFIX);

			std::string AddressToString(const AddressType& address_type = AddressType::hsr_address)const;

			int judge_addr_type(const std::string& base58str);

			explicit operator std::string()const; ///< converts to base58 + checksum

			fc::array<char, 25> addr; ///< binary representation of address

        private:
			void AddressHelper(const fc::ecc::public_key& pub, bool compressed = true, uint8_t version = 40);


        };
        inline bool operator == (const Address& a, const Address& b) { return a.addr == b.addr; }
        inline bool operator != (const Address& a, const Address& b) { return a.addr != b.addr; }
        inline bool operator <  (const Address& a, const Address& b) { return a.addr < b.addr; }

    }
} // namespace hsrcore::blockchain

namespace fc
{
    void to_variant(const hsrcore::blockchain::Address& var, fc::variant& vo);
    void from_variant(const fc::variant& var, hsrcore::blockchain::Address& vo);
}

namespace std
{
    template<>
    struct hash < hsrcore::blockchain::Address >
    {
    public:
        size_t operator()(const hsrcore::blockchain::Address &a) const
        {
			size_t s;
			memcpy((char*)&s, &a.addr.data[sizeof(a) - sizeof(s)], sizeof(s));
			return s;
        }
    };

}

#include <fc/reflect/reflect.hpp>

FC_REFLECT_ENUM(hsrcore::blockchain::AddressType,
    (hsr_address)
    (contract_address)
    (script_id)
    )

    FC_REFLECT(hsrcore::blockchain::Address, (addr))
