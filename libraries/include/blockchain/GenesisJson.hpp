#pragma once
#include <blockchain/GenesisState.hpp>
#include <sstream>

namespace hsrcore {
    namespace blockchain {

        GenesisState get_builtin_genesis_block_config();
        fc::sha256 get_builtin_genesis_block_state_hash();

    }
} // hsrcore::blockchain
