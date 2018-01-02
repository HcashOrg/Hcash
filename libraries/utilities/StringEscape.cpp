#include <utilities/StringEscape.hpp>
#include <sstream>

namespace hsrcore {
    namespace utilities {

        std::string escape_string_for_c_source_code(const std::string& input)
        {
            std::ostringstream escaped_string;
            escaped_string << "\"";
            for (unsigned i = 0; i < input.size(); ++i)
            {
                switch (input[i])
                {
                case '\a':
                    escaped_string << "\\a";
                    break;
                case '\b':
                    escaped_string << "\\b";
                    break;
                case '\t':
                    escaped_string << "\\t";
                    break;
                case '\n':
                    escaped_string << "\\n";
                    break;
                case '\v':
                    escaped_string << "\\v";
                    break;
                case '\f':
                    escaped_string << "\\f";
                    break;
                case '\r':
                    escaped_string << "\\r";
                    break;
                case '\\':
                    escaped_string << "\\\\";
                    break;
                case '\"':
                    escaped_string << "\\\"";
                    break;
                default:
                    escaped_string << input[i];
                }
            }
            escaped_string << "\"";
            return escaped_string.str();
        }

		bool  hex2bin(const char *pSrc, std::vector<char> &pDst, unsigned int nSrcLength, unsigned int &nDstLength)
		{
			if (pSrc == 0)
			{
				return false;
			}

			nDstLength = 0;

			if (pSrc[0] == 0) // nothing to convert  
				return 0;

			// 计算需要转换的字节数  
			for (int j = 0; pSrc[j]; j++)
			{
				if (isxdigit(pSrc[j]))
					nDstLength++;
			}

			// 判断待转换字节数是否为奇数，然后加一  
			if (nDstLength & 0x01) nDstLength++;
			nDstLength /= 2;

			if (nDstLength > nSrcLength)
				return false;

			nDstLength = 0;

			int phase = 0;
			char temp_char;

			for (int i = 0; pSrc[i]; i++)
			{
				if (!isxdigit(pSrc[i]))
					continue;

				unsigned char val = pSrc[i] - (isdigit(pSrc[i]) ? 0x30 : (isupper(pSrc[i]) ? 0x37 : 0x57));

				if (phase == 0)
				{
					temp_char = val << 4;
					phase++;
				}
				else
				{
					temp_char |= val;
					phase = 0;
					pDst.push_back(temp_char);
					nDstLength++;
				}
			}

			return true;
		}
    }
} // end namespace hsrcore::utilities

