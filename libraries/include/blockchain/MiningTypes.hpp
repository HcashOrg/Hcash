#pragma once
#include <fc/variant.hpp>


namespace hsrcore {
	namespace blockchain {

		struct MiningInfo {
			uint32_t blocks;
			uint32_t currentblocksize;
			uint32_t currentblocktx;
			double proof_of_work;
			double proof_of_stake;
			std::string errors;
			uint32_t genproclimit;
			double networkhashps;
			uint32_t pooledtx;
			std::string chain;
			bool generate;
			double hashespersec;

		};
		struct MiningWorkPackage {
			std::string hashnoNonce;
			fc::variant data;
			std::string target;
		};

		struct MiningDifficulty {
			float proof_of_work;
			float proof_of_stake;
		};
		struct StakingInfo
		{
			bool enabled;
			int currentblocksize;
			int currentblocktx;
			float difficulty;
			uint64_t weight;
			uint64_t netstakeweight;
			uint64_t nExpectedTime;
		};



	}
}

#include <fc/reflect/reflect.hpp>

FC_REFLECT(hsrcore::blockchain::MiningInfo,
(blocks)
(currentblocksize)
(currentblocktx)
(proof_of_work)
(proof_of_stake)
(errors)
(genproclimit)
(networkhashps)
(pooledtx)
(chain)
(generate)
(hashespersec))

FC_REFLECT(hsrcore::blockchain::MiningWorkPackage, (hashnoNonce)(data)(target))

FC_REFLECT(hsrcore::blockchain::MiningDifficulty, (proof_of_work)(proof_of_stake))
FC_REFLECT(hsrcore::blockchain::StakingInfo, 
(enabled)
(currentblocksize)
(currentblocktx)
(difficulty)
(weight)
(netstakeweight)
(nExpectedTime)
)
