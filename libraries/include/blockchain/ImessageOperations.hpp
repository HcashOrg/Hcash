#pragma once


#include <blockchain/Operations.hpp>
#include <blockchain/Types.hpp>

namespace hsrcore {
    namespace blockchain {
        struct ImessageMemoOperation
        {
            static const OperationTypeEnum type;
            string imessage;
            ImessageMemoOperation(){}
            ImessageMemoOperation(std::string imess) :imessage(imess){}
            void evaluate(TransactionEvaluationState& eval_state)const;
        };
    }
}
FC_REFLECT(hsrcore::blockchain::ImessageMemoOperation, (imessage))
