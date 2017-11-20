#pragma once

#include <fc/array.hpp>
#include <string>

namespace fc { namespace ecc { class public_key; } }

namespace hsrcore {
    namespace blockchain {

        /**
         *  Implements address stringification and validation from PTS
         */
        struct PtsAddress
        {
            PtsAddress(); ///< constructs empty / null address
            PtsAddress(const std::string& base58str);   ///< converts to binary, validates checksum
            PtsAddress(const fc::ecc::public_key& pub, bool compressed = true, uint8_t version = 56); ///< converts to binary

            uint8_t version()const { return addr.at(0); }
            bool is_valid()const;

            operator std::string()const; ///< converts to base58 + checksum

            fc::array<char, 25> addr; ///< binary representation of address
        };

        inline bool operator == (const PtsAddress& a, const PtsAddress& b) { return a.addr == b.addr; }
        inline bool operator != (const PtsAddress& a, const PtsAddress& b) { return a.addr != b.addr; }
        inline bool operator <  (const PtsAddress& a, const PtsAddress& b) { return a.addr < b.addr; }

    }
} // namespace hsrcore::blockchain

namespace std
{
    template<>
    struct hash < hsrcore::blockchain::PtsAddress >
    {
    public:
        size_t operator()(const hsrcore::blockchain::PtsAddress &a) const
        {
            size_t s;
            memcpy((char*)&s, &a.addr.data[sizeof(a) - sizeof(s)], sizeof(s));
            return s;
        }
    };
}

#include <fc/reflect/reflect.hpp>
FC_REFLECT(hsrcore::blockchain::PtsAddress, (addr))

namespace fc
{
    void to_variant(const hsrcore::blockchain::PtsAddress& var, fc::variant& vo);
    void from_variant(const fc::variant& var, hsrcore::blockchain::PtsAddress& vo);
}
