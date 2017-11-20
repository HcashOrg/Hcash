#pragma once

#ifndef HSHARE_ADDR_UTIL_H
#define HSHARE_ADDR_UTIL_H


#include "db.h"

#include "blockchain/Address.hpp"
#include "fc/crypto/elliptic.hpp"
#include "blockchain/PtsAddress.hpp"
#include <utilities/KeyConversion.hpp>
#include <openssl/ec.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <set>
#include "allocators.h"
#include <utilities/uint256.hpp>
//#include "key.hpp"
#include "privateConvert.hpp"
#include <fc/variant.hpp>
#include <openssl/sha.h>

namespace hshare
{

	#define COMPRESSED 33
	#define UNCOMPRESSED 65
	typedef std::vector<unsigned char, secure_allocator<unsigned char> > CKeyingMaterial;
	typedef std::basic_string<char, std::char_traits<char>, secure_allocator<char> > SecureString;

	const unsigned int WALLET_CRYPTO_KEY_SIZE = 32;
	const unsigned int WALLET_CRYPTO_SALT_SIZE = 8;


	class CMasterKey
	{
	public:
		std::vector<unsigned char> vchCryptedKey;
		std::vector<unsigned char> vchSalt;
		// 0 = EVP_sha512()
		// 1 = scrypt()
		unsigned int nDerivationMethod;
		unsigned int nDeriveIterations;
		// Use this for more parameters to key derivation,
		// such as the various parameters to scrypt
		std::vector<unsigned char> vchOtherDerivationParameters;


		IMPLEMENT_SERIALIZE
		(
			READWRITE(vchCryptedKey);
			READWRITE(vchSalt);
			READWRITE(nDerivationMethod);
			READWRITE(nDeriveIterations);
			READWRITE(vchOtherDerivationParameters);
		)

		CMasterKey()
		{
			// 25000 rounds is just under 0.1 seconds on a 1.86 GHz Pentium M
			// ie slightly lower than the lowest hardware we need bother supporting
			nDeriveIterations = 25000;
			nDerivationMethod = 1;
			vchOtherDerivationParameters = std::vector<unsigned char>(0);
		}
	};


	DBErrors getUnencryptKeys(std::vector<std::string>& vwif, const std::string& infile = "wallet.dat");
	DBErrors getEncryptKeys(std::vector<std::string>& vwif, const std::string& passwd, const std::string& infile = "wallet.dat");


}

#endif

