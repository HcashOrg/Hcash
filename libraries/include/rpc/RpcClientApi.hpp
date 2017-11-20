#pragma once

#include <net/Node.hpp>
#include <wallet/Wallet.hpp>

#include <fc/filesystem.hpp>
#include <fc/network/ip.hpp>

#include <memory>

namespace hsrcore {
    namespace rpc {
        namespace detail { class RpcClientImpl; }

        using namespace hsrcore::blockchain;
        using namespace hsrcore::wallet;

        typedef vector<std::pair<ShareType, string> > Balances;

        enum GenerateTransactionFlag
        {
            sign_and_broadcast = 0,
            do_not_broadcast = 1,
            do_not_sign = 2
        };

    }
} // hsrcore::rpc
FC_REFLECT_ENUM(hsrcore::rpc::GenerateTransactionFlag, (do_not_broadcast)(do_not_sign)(sign_and_broadcast))
