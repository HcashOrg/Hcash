#pragma once
#include <blockchain/GenesisState.hpp>
#include <sstream>

namespace hsrcore {
    namespace blockchain {

        GenesisState get_builtin_genesis_block_config(bool is_test_net);
        fc::sha256 get_builtin_genesis_block_state_hash(bool is_test_net);

    }
} // hsrcore::blockchain
