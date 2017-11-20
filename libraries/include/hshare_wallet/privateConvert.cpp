#pragma once
#include <openssl/bn.h>
#include <openssl/ecdsa.h>
#include <openssl/rand.h>
#include <openssl/obj_mac.h>
#include "privateConvert.hpp"
#include <string.h>


bool GetSecretBytes(EC_KEY* pkey,unsigned char vch[32]) {
	const BIGNUM *bn = EC_KEY_get0_private_key(pkey);
	if (bn == NULL)
		return false;
	int nBytes = BN_num_bytes(bn);
	int n = BN_bn2bin(bn, &vch[32 - nBytes]);
	if (n != nBytes)
		return false;
	memset(vch, 0, 32 - nBytes);
	return true;
}

bool convert_key(std::vector<unsigned char> privkey, unsigned char vch[32],bool fSkipCheck)
{
	EC_KEY* pkey = EC_KEY_new_by_curve_name(NID_secp256k1);
	const unsigned char* pbegin = &privkey[0];
	if (d2i_ECPrivateKey(&pkey, &pbegin, privkey.size())) {
		if (fSkipCheck)
		{
			if (GetSecretBytes(pkey, vch))
			{
				return true;
			}
			else
				return false;
		}

		// d2i_ECPrivateKey returns true if parsing succeeds.
		// This doesn't necessarily mean the key is valid.
		if (EC_KEY_check_key(pkey))
			if (GetSecretBytes(pkey, vch))
			{
				return true;
			}
			else
				return false;
	}
	return false;
}
