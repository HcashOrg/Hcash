#pragma once
#include <locale.h>
#include <iostream>
#include <string>  
#include <fstream>  
#ifdef WIN32
#include <windows.h> 
#endif
#ifdef __linux__

#define CSET_GBK    "GBK"
#define CSET_UTF8   "UTF-8"

#define LC_NAME_zh_CN   "zh_CN"

#elif defined(__APPLE__)
#define CSET_GBK    "GBK"
#define CSET_UTF8   "UTF-8"

#define LC_NAME_zh_CN   "zh_CN"
#elif defined( WIN32)

#define CSET_GBK    "936"
#define CSET_UTF8   "65001"

#define LC_NAME_zh_CN   "Chinese_People's Republic of China"

#define sprintf sprintf_s

// ifdef _MSC_VER
#endif

#define LC_NAME_zh_CN_GBK       LC_NAME_zh_CN "." CSET_GBK
#define LC_NAME_zh_CN_UTF8      LC_NAME_zh_CN "." CSET_UTF8
#define LC_NAME_zh_CN_DEFAULT   LC_NAME_zh_CN_GBK


static bool setCNlocale()
{
    char* locname = NULL;
#ifdef WIN32
    system("chcp 936");
    return true;
    //locname = setlocale(LC_ALL, LC_NAME_zh_CN_GBK);

#else

    locname = setlocale(LC_ALL, LC_NAME_zh_CN_UTF8);
#endif
    if (NULL == locname)
  	    {
            return false;
  	    }
    else
  	    {
            return true;
  	    }
}

static bool resetCNlocale()
{
    char* locname = NULL;
    locname = setlocale(LC_ALL,"");
    if (NULL == locname)
    {
        return false;
    }
    else
    {
        return true;
    }
}

#ifdef WIN32

static std::string GBKToUTF8(const std::string& strGBK)
{
    std::string strOutUTF8 = "";
    WCHAR * str1;
    int n = MultiByteToWideChar(CP_ACP, 0, strGBK.c_str(), -1, NULL, 0);
    str1 = new WCHAR[n];
    MultiByteToWideChar(CP_ACP, 0, strGBK.c_str(), -1, str1, n);
    n = WideCharToMultiByte(CP_UTF8, 0, str1, -1, NULL, 0, NULL, NULL);
    char * str2 = new char[n];
    WideCharToMultiByte(CP_UTF8, 0, str1, -1, str2, n, NULL, NULL);
    strOutUTF8 = str2;
    delete[]str1;
    str1 = NULL;
    delete[]str2;
    str2 = NULL;
    return strOutUTF8;
}

static std::string UTF8ToGBK(const std::string& strUTF8)
{
    int len = MultiByteToWideChar(CP_UTF8, 0, strUTF8.c_str(), -1, NULL, 0);
    unsigned short * wszGBK = new unsigned short[len + 1];
    memset(wszGBK, 0, len * 2 + 2);
    MultiByteToWideChar(CP_UTF8, 0, (LPCTSTR)strUTF8.c_str(), -1, (LPWSTR)wszGBK, len);

    len = WideCharToMultiByte(CP_ACP, 0, (LPWSTR)wszGBK, -1, NULL, 0, NULL, NULL);
    char *szGBK = new char[len + 1];
    memset(szGBK, 0, len + 1);
    WideCharToMultiByte(CP_ACP, 0, (LPWSTR)wszGBK, -1, szGBK, len, NULL, NULL);
    //strUTF8 = szGBK;  
    std::string strTemp(szGBK);
    delete[]szGBK;
    delete[]wszGBK;
    return strTemp;
}




#elif __linux__
#include <iconv.h>  

static int code_convert(char *from_charset, char *to_charset, char *inbuf, int inlen, char *outbuf, int outlen)
{
	iconv_t cd;
	int rc;
	char **pin = &inbuf;
	char **pout = &outbuf;
	size_t temp_out = outlen;
	size_t temp_in = inlen;

	cd = iconv_open(to_charset, from_charset);
	if (cd == 0)
		return -1;
	memset(outbuf, 0, outlen);
	if (iconv(cd, pin, &temp_in, pout, &temp_out) == -1)
		return -1;
	outlen = temp_out;
	iconv_close(cd);
	return 0;
}

static int u2g(char *inbuf, int inlen, char *outbuf, int outlen)
{
	return code_convert("utf-8", "gb2312", inbuf, inlen, outbuf, outlen);
}
static int g2u(char *inbuf, size_t inlen, char *outbuf, size_t outlen)
{
	return code_convert("gb2312", "utf-8", inbuf, inlen, outbuf, outlen);
}
static std::string GBKToUTF8(const std::string& strGBK)
{
	int len = strGBK.size();
	char* str1 = new char[len * 2 + 1];
	int outlen = len * 2 + 1;
	if (g2u((char*)strGBK.data(), len, str1, outlen) == 0)
	{
		std::string strTemp(str1);
		return strTemp;
	}
	return "";
}
static std::string UTF8ToGBK(const std::string& strUTF8)
{
	int len = strUTF8.size();
	char* str1 = new char[len * 2 + 1];
	int outlen = len * 2 + 1;
	if (u2g((char*)strUTF8.data(), len, str1, outlen) == 0)
	{
		std::string strTemp(str1);
		return strTemp;
	}
	return "";
}

#else

#endif
