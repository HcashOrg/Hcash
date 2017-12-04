#include <fc/crypto/sms4.h>

namespace fc
{
	std::vector<char> sms4_encrypt(const fc::sha512& key, const std::vector<char>& plain_text,bool isEncrypt)
	{
		std::vector<char> cipher_text(plain_text.size()+16);
		std::vector<char> temp(16);
		sms4_key_t sms4key;
		if (isEncrypt)
		{
			sms4_set_encrypt_key(&sms4key, ((unsigned char*)&key));
		}
		else
		{
			sms4_set_decrypt_key(&sms4key, ((unsigned char*)&key));
		}
		int len = plain_text.size();
		int has = 0;
		while (len >= 16)
		{
			temp.assign(plain_text.begin() + has, plain_text.begin() + has+16);
			sms4_encrypt((const unsigned char*)temp.data(), (unsigned char*)cipher_text.data()+has, &sms4key);
			has += 16;
			len -= 16;
		}
		if (has != len)
		{
			temp.assign(plain_text.begin() + has, plain_text.end());
			sms4_encrypt((const unsigned char*)temp.data(), (unsigned char*)cipher_text.data()+has, &sms4key);
		}
		
		return cipher_text;
	}

	std::vector<char> sms4_decrypt(const fc::sha512& key, const std::vector<char>& cipher_text)
	{
		return sms4_encrypt(key,cipher_text,false);
	}

}