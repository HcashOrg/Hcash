#pragma once

namespace hsrcore {
    namespace client {

#ifndef HSR_TEST_NETWORK
        static const std::vector<std::string> SeedNodes
        {
			"47.74.176.222:50666",
			"47.74.144.24:50666",
			"47.74.144.184:50666"
        };
#else
        static const std::vector<std::string> SeedNodes
        {
			"47.96.41.39:50766"
        };
#endif

    }
} // hsrcore::client
