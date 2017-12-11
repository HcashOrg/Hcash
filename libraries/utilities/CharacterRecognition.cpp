
#include <stdio.h>

namespace hsrcore {
	namespace utilities {

		inline bool inRange(char input, char range_start, char range_end)
		{
			if (input >= range_start&&input <= range_end)
				return true;
			return false;
		}
		bool isGBK(const char* input)
		{
			if (input == NULL)
				return false;
			const char* p = input;
			while (*p != '\0')
			{
				char c = *p;
				if (inRange(c, 0, 0x7f))
				{
					++p;
					continue;
				}
				else if (*(++p) != '\0')
				{
					if ((inRange(c, 0xa1, 0xa9) && inRange(*p, 0xa1, 0xfe))
						|| (inRange(c, 0xb0, 0xf7) && inRange(*p, 0xa1, 0xfe))
						|| (inRange(c, 0x81, 0xb0) && (*p != 0x7f) && inRange(*p, 0x40, 0xfe))
						|| (inRange(c, 0xaa, 0xfe) && (*p != 0x7f) && inRange(*p, 0x40, 0xa0))
						|| (inRange(c, 0xa8, 0xa9) && (*p != 0x7f) && inRange(*p, 0x40, 0xa0))
						|| (inRange(c, 0xaa, 0xaf) && inRange(*p, 0xa1, 0xfe))
						|| (inRange(c, 0xf8, 0xfe) && inRange(*p, 0xa1, 0xfe))
						|| (inRange(c, 0xa1, 0xa7) && (*p != 0x7f) && inRange(*p, 0x40, 0xa0)))
					{
						++p;
					}
					else
					{
						return false;
					}
				}
				else
					return false;
			}
			return true;
		}
		bool isContinousByteOfUTF_8(char c)
		{
			if ((c & 0xc0) == 0x80)
				return true;
			return false;
		}
		bool isUTF_8(const char* input)
		{
			if (input == NULL)
				return false;
			const char* p = input;
			while (*p != '\0')
			{
				char c = *p;
				int width = 1;
				if (c & 0x80 == 0)
				{
					//字节最高位为0，为单字节
					++p;
					continue;
				}
				else if ((c & 0xe0) == 0xc0)
				{
					//字节前三位为110
					if (p[1] != '\0'&&isContinousByteOfUTF_8(p[1]))
					{
						p = p + 2;
						continue;
					}
					return false;
				}
				else if ((c & 0xf0) == 0xe0)
				{
					if (p[1] != '\0'&&isContinousByteOfUTF_8(p[1])
						&& p[2] != '\0' && isContinousByteOfUTF_8(p[2]))
					{
						p = p + 3;
						continue;
					}
					return false;
				}
				else if ((c & 0xf8) == 0xf0)
				{
					if (p[1] != '\0'&&isContinousByteOfUTF_8(p[1])
						&& p[2] != '\0' && isContinousByteOfUTF_8(p[2])
						&& p[3] != '\0' && isContinousByteOfUTF_8(p[3]))
					{
						p = p + 3;
						continue;
					}
					return false;
				}
				return false;
			}
			return true;
		}
	}
}