#pragma once
#include <blockchain/Block.hpp>
#include <client/Client.hpp>

namespace hsrcore {
    namespace client {

        enum MessageTypeEnum
        {
            trx_message_type = 1000,
            block_message_type = 1001,
            batch_trx_message_type = 1002
        };

        struct TrxMessage
        {
            static const MessageTypeEnum type;

            hsrcore::blockchain::SignedTransaction trx;
            TrxMessage() {}
            TrxMessage(hsrcore::blockchain::SignedTransaction transaction) :
                trx(std::move(transaction))
            {}
        };

        struct BatchTrxMessage
        {
            static const MessageTypeEnum type;
            std::vector<hsrcore::blockchain::SignedTransaction> trx_vec;
            BatchTrxMessage() {}
            BatchTrxMessage(std::vector<hsrcore::blockchain::SignedTransaction> transactions) :
                trx_vec(std::move(transactions))
            {}
        };

        struct BlockMessage
        {
            static const MessageTypeEnum type;

            BlockMessage(){}
            BlockMessage(const hsrcore::blockchain::FullBlock& blk)
                :block(blk), block_id(blk.id()){}

            hsrcore::blockchain::FullBlock    block;
            hsrcore::blockchain::BlockIdType block_id;

        };

    }
} // hsrcore::client

FC_REFLECT_ENUM(hsrcore::client::MessageTypeEnum, (trx_message_type)(block_message_type)(batch_trx_message_type))
FC_REFLECT(hsrcore::client::TrxMessage, (trx))
FC_REFLECT(hsrcore::client::BatchTrxMessage, (trx_vec))
FC_REFLECT(hsrcore::client::BlockMessage, (block)(block_id))
