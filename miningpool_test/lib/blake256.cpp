#include <ntdef.h>
#include <blake.hpp>


void blake256_compress( state256 *S, const uint8_t *block )
{
  uint32_t v[16], m[16], i;
#define ROT(x,n) (((x)<<(32-n))|( (x)>>(n)))
#define G(a,b,c,d,e)          \
  v[a] += (m[sigma[i][e]] ^ u256[sigma[i][e+1]]) + v[b]; \
  v[d] = ROT( v[d] ^ v[a],16);        \
  v[c] += v[d];           \
  v[b] = ROT( v[b] ^ v[c],12);        \
  v[a] += (m[sigma[i][e+1]] ^ u256[sigma[i][e]])+v[b]; \
  v[d] = ROT( v[d] ^ v[a], 8);        \
  v[c] += v[d];           \
  v[b] = ROT( v[b] ^ v[c], 7);

  for( i = 0; i < 16; ++i )  m[i] = U8TO32_BIG( block + i * 4 );

  for( i = 0; i < 8; ++i )  v[i] = S->h[i];

  v[ 8] = S->s[0] ^ u256[0];
  v[ 9] = S->s[1] ^ u256[1];
  v[10] = S->s[2] ^ u256[2];
  v[11] = S->s[3] ^ u256[3];
  v[12] = u256[4];
  v[13] = u256[5];
  v[14] = u256[6];
  v[15] = u256[7];

  /* don't xor t when the block is only padding */
  if ( !S->nullt )
  {
    v[12] ^= S->t[0];
    v[13] ^= S->t[0];
    v[14] ^= S->t[1];
    v[15] ^= S->t[1];
  }

  for( i = 0; i < 14; ++i )
  {
    /* column step */
    G( 0,  4,  8, 12,  0 );
    G( 1,  5,  9, 13,  2 );
    G( 2,  6, 10, 14,  4 );
    G( 3,  7, 11, 15,  6 );
    /* diagonal step */
    G( 0,  5, 10, 15,  8 );
    G( 1,  6, 11, 12, 10 );
    G( 2,  7,  8, 13, 12 );
    G( 3,  4,  9, 14, 14 );
  }

  for( i = 0; i < 16; ++i )  S->h[i % 8] ^= v[i];

  for( i = 0; i < 8 ; ++i )  S->h[i] ^= S->s[i % 4];
}


void blake256_init( state256 *S )
{
  S->h[0] = 0x6a09e667;
  S->h[1] = 0xbb67ae85;
  S->h[2] = 0x3c6ef372;
  S->h[3] = 0xa54ff53a;
  S->h[4] = 0x510e527f;
  S->h[5] = 0x9b05688c;
  S->h[6] = 0x1f83d9ab;
  S->h[7] = 0x5be0cd19;
  S->t[0] = S->t[1] = S->buflen = S->nullt = 0;
  S->s[0] = S->s[1] = S->s[2] = S->s[3] = 0;
}


void blake256_update( state256 *S, const uint8_t *in, uint64_t inlen )
{
  int left = S->buflen;
  int fill = 64 - left;

  /* data left and data received fill a block  */
  if( left && ( inlen >= fill ) )
  {
    memcpy( ( void * ) ( S->buf + left ), ( void * ) in, fill );
    S->t[0] += 512;

    if ( S->t[0] == 0 ) S->t[1]++;

    blake256_compress( S, S->buf );
    in += fill;
    inlen  -= fill;
    left = 0;
  }

  /* compress blocks of data received */
  while( inlen >= 64 )
  {
    S->t[0] += 512;

    if ( S->t[0] == 0 ) S->t[1]++;

    blake256_compress( S, in );
    in += 64;
    inlen -= 64;
  }

  /* store any data left */
  if( inlen > 0 )
  {
    memcpy( ( void * ) ( S->buf + left ),   \
            ( void * ) in, ( size_t ) inlen );
    S->buflen = left + ( int )inlen;
  }
  else S->buflen = 0;
}


void blake256_final( state256 *S, uint8_t *out )
{
  uint8_t msglen[8], zo = 0x01, oo = 0x81;
  uint32_t lo = S->t[0] + ( S->buflen << 3 ), hi = S->t[1];

  /* support for hashing more than 2^32 bits */
  if ( lo < ( S->buflen << 3 ) ) hi++;

  U32TO8_BIG(  msglen + 0, hi );
  U32TO8_BIG(  msglen + 4, lo );

  if ( S->buflen == 55 )   /* one padding byte */
  {
    S->t[0] -= 8;
    blake256_update( S, &oo, 1 );
  }
  else
  {
    if ( S->buflen < 55 )   /* enough space to fill the block  */
    {
      if ( !S->buflen ) S->nullt = 1;

      S->t[0] -= 440 - ( S->buflen << 3 );
      blake256_update( S, padding, 55 - S->buflen );
    }
    else   /* need 2 compressions */
    {
      S->t[0] -= 512 - ( S->buflen << 3 );
      blake256_update( S, padding, 64 - S->buflen );
      S->t[0] -= 440;
      blake256_update( S, padding + 1, 55 );
      S->nullt = 1;
    }

    blake256_update( S, &zo, 1 );
    S->t[0] -= 8;
  }

  S->t[0] -= 64;
  blake256_update( S, msglen, 8 );
  U32TO8_BIG( out + 0, S->h[0] );
  U32TO8_BIG( out + 4, S->h[1] );
  U32TO8_BIG( out + 8, S->h[2] );
  U32TO8_BIG( out + 12, S->h[3] );
  U32TO8_BIG( out + 16, S->h[4] );
  U32TO8_BIG( out + 20, S->h[5] );
  U32TO8_BIG( out + 24, S->h[6] );
  U32TO8_BIG( out + 28, S->h[7] );
}


void blake256_hash(const uint8_t *in, uint64_t inlen, uint8_t *out)
{
  state256 S;
  blake256_init( &S );
  blake256_update( &S, in, inlen );
  blake256_final( &S, out );
}

static inline unsigned char num_to_hex(uint8_t n, bool is_capital)
{
	if (n < 10)
		return (unsigned char)(n + 48);
	else if (n < 16)
	{
		if(is_capital)
			return (unsigned char)(n + 55);
		else
			return (unsigned char)(n + 87);
	}
}

void blake256_hash_hexdigest(const uint8_t *in, uint64_t inlen, unsigned char *outstr, bool is_capital)
{
    uint8_t out[32];
	unsigned char *p = outstr;
    blake256_hash(in, inlen, out);
	for(int i = 31; i >=0; --i)
	{
        uint8_t h,l;
		h = out[i] / 16;
		l = out[i] % 16;
		*p++ = num_to_hex(h, is_capital);
		*p++ = num_to_hex(l, is_capital);
	}
    *p = 0x0;
}

void blake256_stateCopy(state256 *dst, state256 *src)
{
	int i;
	memcpy(dst->buf, src->buf, 64);
	dst->buflen = src->buflen;
	for(i=0;i<8;i++)
	dst->h[i] = src->h[i];
	for (i = 0;i < 4;i++)
		dst->s[i] = src->s[i];
	dst->t[0] = src->t[0];
	dst->t[1] = src->t[1];
	dst->nullt = src->nullt;
}

/*
void blake256_test()
{
  uint8_t BlockOneTwo[] =
  { 0x04,0x00,0x00,0x00,0xf2,0x3d,0xe5,0xae,0xb3,0x46,0x0d,0xda,0xfe,0x4a,0x3e,0xe6,0x5e,0xaf,0xea,0x2a,0x26,0xe5,0x39,0x6a,0x61,0x28,0x59,0xc0,0x44,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0xcc,0x9f,0x4b,0x57,0xcf,0xfd,0x91,0xaa,0xf5,0xfd,0x28,0x42,0x1a,0xca,0x1e,0x7b,0x43,0xf3,0x16,0x7a,0x21,0xd1,0x1d,0x01,0x99,0xad,0x49,0x8e,0x49,0xaf,0x41,0xf9,0x6a,0x6f,0xdf,0xc1,0xeb,0xca,0xfb,0x32,0xa0,0xd0,0x74,0xcd,0x0c,0xda,0x40,0x0a,0xd0,0x6c,0x65,0xb2,0x7c,0x85,0xa4,0x37,0x22,0x00,0x2e,0x9c,0xdb,0xc3,0x81,0x1f,0x01,0x00,0xa9,0xe4,0x57,0x56,0x4f,0x86,0x05,0x00,0x14,0x00,0x1b,0xab,0x00,0x00,0x09,0xda,0x01,0x1a,0x66,0x6f,0xf5,0x02,0x01,0x00,0x00,0x00 };
  uint8_t Data[] =
  { 0x7a,0x39,0x02,0x00,0xaf,0x60,0x00,0x00,0xaf,0x48,0x52,0x59,0x00,0x03,0x90,0x75,0x32,0x22,0x00,0x00,0x2c,0x00,0x00,0x00,0xe3,0x00,0x30,0x7a,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x04,0x00,0x00,0x00 };
  uint8_t out[32];
  state256 S,IV;
  uint32_t i,temp,j,k;

  for (k = 0;k < 100000000;k++)
  {


	  printf("get new work %d\n", k);
	  BlockOneTwo[5] += 1;
	  blake256_init(&S);
	  blake256_update(&S, BlockOneTwo, 128);

	  for (i = 0;i < 100000000;i++)
	  {
		  temp = i;
		  Data[12] = (uint8_t)(temp >> 24);
		  Data[13] = (uint8_t)((temp & 0x00FF0000) >> 16);
		  Data[14] = (uint8_t)((temp & 0x0000FF00) >> 8);
		  Data[15] = (uint8_t)((temp & 0x000000FF) >> 0);

		  blake256_stateCopy(&IV, &S);
		  blake256_update(&IV, Data, 52);
		  blake256_final(&IV, out);

		  if ((out[31] | out[30] | out[29]|(out[28]&0xF0) ) == 0)
		  {
			  printf("found nonce is %02X\n", i);
			  for (j = 0;j < 32;j++)
				  printf("%02X", out[31 - j]);
		  }
	  }

	  printf("\nwork %d over\n", k);
  }
}
*/

void blake256_test()
{
    char* ptr = "The cryptographic hash function BLAKE2 is an improved version of the SHA-3 finalist BLAKE";
    uint8_t out[32];
    unsigned char outstr[65];
    //state256 S;
    //blake256_init(&S);
    //blake256_update(&S, ptr, strlen(ptr));
    //blake256_final(&S, out);
    
    blake256_hash((uint8_t*)ptr, strlen(ptr), out);
    for (int i = 0; i < 32; ++i)
        printf("%x ", out[i]);

    blake256_hash_hexdigest((uint8_t*)ptr, strlen(ptr), outstr, false);
	outstr[64] = '\0';
    printf("\n%s", outstr);

    blake256_hash_hexdigest((uint8_t*)ptr, strlen(ptr), outstr, true);
	outstr[64] = '\0';
    printf("\n%s", outstr);
}

#include <iostream>
#include <vector>

extern "C" {
	__declspec (dllexport) char * blake256_hash_hex(char* data,int size)
	{
		unsigned char outstr[65];
		//state256 S;
		//blake256_init(&S);
		//blake256_update(&S, ptr, strlen(ptr));
		//blake256_final(&S, out);
		std::cout << size << std::endl;

		blake256_hash_hexdigest((const uint8_t*)&data[0], size, outstr, false);
		return (char*)outstr;
	}
}
//
//int main(int argc, char *argv[])
//{
//	std::string str = argv[1];
//	std::vector<char> data;
//	data.insert(data.begin(), str.begin(), str.end());
//	blake256_hash_hex(data);
//	getchar();
//  
//	return 0;
//}
