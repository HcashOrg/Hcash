// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-2012 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.
#ifndef BITCOIN_HASH_H
#define BITCOIN_HASH_H

#include <utilities/uint256.hpp>


#include <openssl/sha.h>
#include <openssl/ripemd.h>


#include <utilities/blake.hpp>


template<typename T1>
inline uint256 HashR14(const T1 pbegin, const T1 pend)
{
	uint8_t out[32];
	uint64_t res[4];
	uint256 result;
	static unsigned char pblank[1];
	blake256_hash(out, (pbegin == pend ? pblank : (const uint8_t*)(&pbegin[0])),(pend - pbegin) * sizeof(pbegin[0]));
	
// 	U8TO64_BIG(res+0, out+0);
// 	U8TO64_BIG(res+1, out+8);
// 	U8TO64_BIG(res+2, out+16);
// 	U8TO64_BIG(res+3, out+24);
// 	
// 	for (int i = 3; i>=0; --i)
// 	{
// 		uint256 temp(res[i]);
// 		result << 64;
// 		result += temp;
// 	}
	memcpy(&result,out,sizeof(result));
 	//printf("%s\n", result.GetHex().c_str());
	return result;
}


#endif
