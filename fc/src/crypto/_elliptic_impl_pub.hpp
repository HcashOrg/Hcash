#pragma once
#include <fc/crypto/elliptic.hpp>
#include <boost/config.hpp>

/* public_key_impl implementation based on openssl
 * used by mixed + openssl
 */
#define SM2_DEFAULT_POINT_CONVERSION_FORM POINT_CONVERSION_UNCOMPRESSED
#define P "FFFFFFFEFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF00000000FFFFFFFFFFFFFFFF"
#define A "FFFFFFFEFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF00000000FFFFFFFFFFFFFFFC"
#define B "28E9FA9E9D9F5E344D5A9E4BCF6509A7F39789F515AB8F92DDBCBD414D940E93"
#define GX "32C4AE2C1F1981195F9904466A39C9948FE30BBFF2660BE1715A4589334C74C7"
#define GY "BC3736A2F4F6779C59BDCEE36B692153D0A9877CC62A474002DF32E52139F0A0"
#define N "FFFFFFFEFFFFFFFFFFFFFFFFFFFFFFFF7203DF6B21C6052B53BBF40939D54123"
#define H "1"

namespace fc { namespace ecc { namespace detail {

void _init_lib();

class public_key_impl
{
    public:
        public_key_impl() BOOST_NOEXCEPT;
        public_key_impl( const public_key_impl& cpy ) BOOST_NOEXCEPT;
        public_key_impl( public_key_impl&& cpy ) BOOST_NOEXCEPT;
        ~public_key_impl() BOOST_NOEXCEPT;

        public_key_impl& operator=( const public_key_impl& pk ) BOOST_NOEXCEPT;

        public_key_impl& operator=( public_key_impl&& pk ) BOOST_NOEXCEPT;

        static int ECDSA_SIG_recover_key_GFp(EC_KEY *eckey, ECDSA_SIG *ecsig, const unsigned char *msg, int msglen, int recid, int check);

        EC_KEY* _key = nullptr;

    private:
        void free_key() BOOST_NOEXCEPT;
};

}}}
