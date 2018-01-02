#pragma once

#include <string>
#include <vector>
namespace hsrcore {
    namespace utilities {

        std::string escape_string_for_c_source_code(const std::string& input);
		bool  hex2bin(const char *pSrc, std::vector<char> &pDst, unsigned int nSrcLength, unsigned int &nDstLength);
    }
} // end namespace hsrcore::utilities
