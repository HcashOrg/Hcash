#pragma once

#include <blockchain/Operations.hpp>

namespace hsrcore {
    namespace blockchain {

        struct DefineSlateOperation
        {
            static const OperationTypeEnum type;

            vector<signed_int> slate;

            void evaluate(TransactionEvaluationState& eval_state)const;
        };

    }
} // hsrcore::blockchain

FC_REFLECT(hsrcore::blockchain::DefineSlateOperation, (slate))
