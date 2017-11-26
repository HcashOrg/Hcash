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
			"39.108.111.162:40988",
			"39.108.83.28:40988",
			"47.104.111.111:40988",
			"47.94.152.170:40988",
			"47.96.182.36:40988",
			"47.100.110.221:40988",
			"39.104.49.39:40988",
			"47.74.153.100:40988",
			"47.91.41.134:40988",
			"47.74.17.190:40988",
			"47.90.212.56:40988"
        };
#endif

    }
} // hsrcore::client
