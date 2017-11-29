//                                   _           _    __ _ _      
//                                  | |         | |  / _(_) |     
//    __ _  ___ _ __   ___ _ __ __ _| |_ ___  __| | | |_ _| | ___ 
//   / _` |/ _ \ '_ \ / _ \ '__/ _` | __/ _ \/ _` | |  _| | |/ _ \`
//  | (_| |  __/ | | |  __/ | | (_| | ||  __/ (_| | | | | | |  __/
//   \__, |\___|_| |_|\___|_|  \__,_|\__\___|\__,_| |_| |_|_|\___|
//    __/ |                                                       
//   |___/                                                        
//
//
// Warning: this is a generated file, any changes made here will be
//          overwritten by the build process.  If you need to change what is
//          generated here, you should either modify the input json files
//          (network_api.json, wallet_api.json, etc) or modify the code
//          generator (hsrcore_api_generator.cpp) itself
//
#define DEFAULT_LOGGER "rpc"
#include <rpc_stubs/CommonApiRpcClient.hpp>
#include <api/ConversionFunctions.hpp>

namespace hsrcore {
    namespace rpc_stubs {

        fc::variant_object CommonApiRpcClient::blockchain_get_info() const
        {
            fc::variant result = get_json_connection()->async_call("blockchain_get_info", std::vector<fc::variant>{}).wait();
            return result.as<fc::variant_object>();
        }
        void CommonApiRpcClient::blockchain_generate_snapshot(const std::string& filename) const
        {
            fc::variant result = get_json_connection()->async_call("blockchain_generate_snapshot", std::vector<fc::variant>{fc::variant(filename)}).wait();
        }
        std::vector<hsrcore::blockchain::HSRTrxidBalance> CommonApiRpcClient::blockchain_get_hsr_account_balance_entry(uint32_t block_num)
        {
            fc::variant result = get_json_connection()->async_call("blockchain_get_hsr_account_balance_entry", std::vector<fc::variant>{fc::variant(block_num)}).wait();
            return result.as<std::vector<hsrcore::blockchain::HSRTrxidBalance>>();
        }
        void CommonApiRpcClient::blockchain_generate_issuance_map(const std::string& symbol, const std::string& filename) const
        {
            fc::variant result = get_json_connection()->async_call("blockchain_generate_issuance_map", std::vector<fc::variant>{fc::variant(symbol), fc::variant(filename)}).wait();
        }
        hsrcore::blockchain::Asset CommonApiRpcClient::blockchain_calculate_supply(const std::string& asset) const
        {
            fc::variant result = get_json_connection()->async_call("blockchain_calculate_supply", std::vector<fc::variant>{fc::variant(asset)}).wait();
            return result.as<hsrcore::blockchain::Asset>();
        }
        bool CommonApiRpcClient::blockchain_is_synced() const
        {
            fc::variant result = get_json_connection()->async_call("blockchain_is_synced", std::vector<fc::variant>{}).wait();
            return result.as<bool>();
        }
        uint32_t CommonApiRpcClient::blockchain_get_block_count() const
        {
            fc::variant result = get_json_connection()->async_call("blockchain_get_block_count", std::vector<fc::variant>{}).wait();
            return result.as<uint32_t>();
        }
        hsrcore::blockchain::BlockchainSecurityState CommonApiRpcClient::blockchain_get_security_state() const
        {
            fc::variant result = get_json_connection()->async_call("blockchain_get_security_state", std::vector<fc::variant>{}).wait();
            return result.as<hsrcore::blockchain::BlockchainSecurityState>();
        }
        std::vector<hsrcore::blockchain::AccountEntry> CommonApiRpcClient::blockchain_list_accounts(const std::string& first_account_name /* = fc::json::from_string("\"\"").as<std::string>() */, uint32_t limit /* = fc::json::from_string("20").as<uint32_t>() */) const
        {
            fc::variant result = get_json_connection()->async_call("blockchain_list_accounts", std::vector<fc::variant>{fc::variant(first_account_name), fc::variant(limit)}).wait();
            return result.as<std::vector<hsrcore::blockchain::AccountEntry>>();
        }
        std::vector<hsrcore::blockchain::AccountEntry> CommonApiRpcClient::blockchain_list_recently_updated_accounts() const
        {
            fc::variant result = get_json_connection()->async_call("blockchain_list_recently_updated_accounts", std::vector<fc::variant>{}).wait();
            return result.as<std::vector<hsrcore::blockchain::AccountEntry>>();
        }
        std::vector<hsrcore::blockchain::AccountEntry> CommonApiRpcClient::blockchain_list_recently_registered_accounts() const
        {
            fc::variant result = get_json_connection()->async_call("blockchain_list_recently_registered_accounts", std::vector<fc::variant>{}).wait();
            return result.as<std::vector<hsrcore::blockchain::AccountEntry>>();
        }
        std::vector<hsrcore::blockchain::AssetEntry> CommonApiRpcClient::blockchain_list_assets(const std::string& first_symbol /* = fc::json::from_string("\"\"").as<std::string>() */, uint32_t limit /* = fc::json::from_string("20").as<uint32_t>() */) const
        {
            fc::variant result = get_json_connection()->async_call("blockchain_list_assets", std::vector<fc::variant>{fc::variant(first_symbol), fc::variant(limit)}).wait();
            return result.as<std::vector<hsrcore::blockchain::AssetEntry>>();
        }
        std::vector<std::pair<hsrcore::blockchain::TransactionIdType, hsrcore::blockchain::SignedTransaction>> CommonApiRpcClient::blockchain_list_pending_transactions() const
        {
            fc::variant result = get_json_connection()->async_call("blockchain_list_pending_transactions", std::vector<fc::variant>{}).wait();
            return result.as<std::vector<std::pair<hsrcore::blockchain::TransactionIdType, hsrcore::blockchain::SignedTransaction>>>();
        }
        std::pair<hsrcore::blockchain::TransactionIdType, hsrcore::blockchain::TransactionEntry> CommonApiRpcClient::blockchain_get_transaction(const std::string& transaction_id_prefix, bool exact /* = fc::json::from_string("false").as<bool>() */) const
        {
            fc::variant result = get_json_connection()->async_call("blockchain_get_transaction", std::vector<fc::variant>{fc::variant(transaction_id_prefix), fc::variant(exact)}).wait();
            return result.as<std::pair<hsrcore::blockchain::TransactionIdType, hsrcore::blockchain::TransactionEntry>>();
        }
        hsrcore::wallet::PrettyTransaction CommonApiRpcClient::blockchain_get_pretty_transaction(const std::string& transaction_id_prefix, bool exact /* = fc::json::from_string("false").as<bool>() */) const
        {
            fc::variant result = get_json_connection()->async_call("blockchain_get_pretty_transaction", std::vector<fc::variant>{fc::variant(transaction_id_prefix), fc::variant(exact)}).wait();
            return result.as<hsrcore::wallet::PrettyTransaction>();
        }
        hsrcore::wallet::PrettyContractTransaction CommonApiRpcClient::blockchain_get_pretty_contract_transaction(const std::string& transaction_id_prefix, bool exact /* = fc::json::from_string("false").as<bool>() */) const
        {
            fc::variant result = get_json_connection()->async_call("blockchain_get_pretty_contract_transaction", std::vector<fc::variant>{fc::variant(transaction_id_prefix), fc::variant(exact)}).wait();
            return result.as<hsrcore::wallet::PrettyContractTransaction>();
        }
        fc::optional<hsrcore::blockchain::BlockEntry> CommonApiRpcClient::blockchain_get_block(const std::string& block) const
        {
            fc::variant result = get_json_connection()->async_call("blockchain_get_block", std::vector<fc::variant>{fc::variant(block)}).wait();
            return result.as<fc::optional<hsrcore::blockchain::BlockEntry>>();
        }
        std::map<hsrcore::blockchain::TransactionIdType, hsrcore::blockchain::TransactionEntry> CommonApiRpcClient::blockchain_get_block_transactions(const std::string& block) const
        {
            fc::variant result = get_json_connection()->async_call("blockchain_get_block_transactions", std::vector<fc::variant>{fc::variant(block)}).wait();
            return result.as<std::map<hsrcore::blockchain::TransactionIdType, hsrcore::blockchain::TransactionEntry>>();
        }
        fc::optional<hsrcore::blockchain::AccountEntry> CommonApiRpcClient::blockchain_get_account(const std::string& account) const
        {
            fc::variant result = get_json_connection()->async_call("blockchain_get_account", std::vector<fc::variant>{fc::variant(account)}).wait();
            return result.as<fc::optional<hsrcore::blockchain::AccountEntry>>();
        }
        std::map<hsrcore::blockchain::AccountIdType, std::string> CommonApiRpcClient::blockchain_get_slate(const std::string& slate) const
        {
            fc::variant result = get_json_connection()->async_call("blockchain_get_slate", std::vector<fc::variant>{fc::variant(slate)}).wait();
            return result.as<std::map<hsrcore::blockchain::AccountIdType, std::string>>();
        }
        hsrcore::blockchain::BalanceEntry CommonApiRpcClient::blockchain_get_balance(const hsrcore::blockchain::Address& balance_id) const
        {
            fc::variant result = get_json_connection()->async_call("blockchain_get_balance", std::vector<fc::variant>{fc::variant(balance_id)}).wait();
            return result.as<hsrcore::blockchain::BalanceEntry>();
        }
        std::unordered_map<hsrcore::blockchain::BalanceIdType, hsrcore::blockchain::BalanceEntry> CommonApiRpcClient::blockchain_list_balances(const std::string& first_balance_id /* = fc::json::from_string("\"\"").as<std::string>() */, uint32_t limit /* = fc::json::from_string("20").as<uint32_t>() */) const
        {
            fc::variant result = get_json_connection()->async_call("blockchain_list_balances", std::vector<fc::variant>{fc::variant(first_balance_id), fc::variant(limit)}).wait();
            return result.as<std::unordered_map<hsrcore::blockchain::BalanceIdType, hsrcore::blockchain::BalanceEntry>>();
        }
        std::unordered_map<hsrcore::blockchain::BalanceIdType, hsrcore::blockchain::BalanceEntry> CommonApiRpcClient::blockchain_list_address_balances(const std::string& addr, const fc::time_point& chanced_since /* = fc::json::from_string("\"1970-1-1T00:00:01\"").as<fc::time_point>() */) const
        {
            fc::variant result = get_json_connection()->async_call("blockchain_list_address_balances", std::vector<fc::variant>{fc::variant(addr), fc::variant(chanced_since)}).wait();
            return result.as<std::unordered_map<hsrcore::blockchain::BalanceIdType, hsrcore::blockchain::BalanceEntry>>();
        }
        fc::variant_object CommonApiRpcClient::blockchain_list_address_transactions(const std::string& addr, uint32_t filter_before /* = fc::json::from_string("\"0\"").as<uint32_t>() */) const
        {
            fc::variant result = get_json_connection()->async_call("blockchain_list_address_transactions", std::vector<fc::variant>{fc::variant(addr), fc::variant(filter_before)}).wait();
            return result.as<fc::variant_object>();
        }
        hsrcore::wallet::AccountBalanceSummaryType CommonApiRpcClient::blockchain_get_account_public_balance(const std::string& account_name) const
        {
            fc::variant result = get_json_connection()->async_call("blockchain_get_account_public_balance", std::vector<fc::variant>{fc::variant(account_name)}).wait();
            return result.as<hsrcore::wallet::AccountBalanceSummaryType>();
        }
        std::unordered_map<hsrcore::blockchain::BalanceIdType, hsrcore::blockchain::BalanceEntry> CommonApiRpcClient::blockchain_list_key_balances(const hsrcore::blockchain::PublicKeyType& key) const
        {
            fc::variant result = get_json_connection()->async_call("blockchain_list_key_balances", std::vector<fc::variant>{fc::variant(key)}).wait();
            return result.as<std::unordered_map<hsrcore::blockchain::BalanceIdType, hsrcore::blockchain::BalanceEntry>>();
        }
        fc::optional<hsrcore::blockchain::AssetEntry> CommonApiRpcClient::blockchain_get_asset(const std::string& asset) const
        {
            fc::variant result = get_json_connection()->async_call("blockchain_get_asset", std::vector<fc::variant>{fc::variant(asset)}).wait();
            return result.as<fc::optional<hsrcore::blockchain::AssetEntry>>();
        }
        std::vector<hsrcore::blockchain::AccountEntry> CommonApiRpcClient::blockchain_list_active_delegates(uint32_t first /* = fc::json::from_string("0").as<uint32_t>() */, uint32_t count /* = fc::json::from_string("20").as<uint32_t>() */) const
        {
            fc::variant result = get_json_connection()->async_call("blockchain_list_active_delegates", std::vector<fc::variant>{fc::variant(first), fc::variant(count)}).wait();
            return result.as<std::vector<hsrcore::blockchain::AccountEntry>>();
        }
        std::vector<hsrcore::blockchain::AccountEntry> CommonApiRpcClient::blockchain_list_delegates(uint32_t first /* = fc::json::from_string("0").as<uint32_t>() */, uint32_t count /* = fc::json::from_string("20").as<uint32_t>() */) const
        {
            fc::variant result = get_json_connection()->async_call("blockchain_list_delegates", std::vector<fc::variant>{fc::variant(first), fc::variant(count)}).wait();
            return result.as<std::vector<hsrcore::blockchain::AccountEntry>>();
        }
        std::vector<hsrcore::blockchain::BlockEntry> CommonApiRpcClient::blockchain_list_blocks(uint32_t max_block_num /* = fc::json::from_string("-1").as<uint32_t>() */, uint32_t limit /* = fc::json::from_string("20").as<uint32_t>() */)
        {
            fc::variant result = get_json_connection()->async_call("blockchain_list_blocks", std::vector<fc::variant>{fc::variant(max_block_num), fc::variant(limit)}).wait();
            return result.as<std::vector<hsrcore::blockchain::BlockEntry>>();
        }
        std::vector<std::string> CommonApiRpcClient::blockchain_list_missing_block_delegates(uint32_t block_number)
        {
            fc::variant result = get_json_connection()->async_call("blockchain_list_missing_block_delegates", std::vector<fc::variant>{fc::variant(block_number)}).wait();
            return result.as<std::vector<std::string>>();
        }
        std::string CommonApiRpcClient::blockchain_export_fork_graph(uint32_t start_block /* = fc::json::from_string("1").as<uint32_t>() */, uint32_t end_block /* = fc::json::from_string("-1").as<uint32_t>() */, const hsrcore::blockchain::FilePath& filename /* = fc::json::from_string("\"\"").as<hsrcore::blockchain::FilePath>() */) const
        {
            fc::variant result = get_json_connection()->async_call("blockchain_export_fork_graph", std::vector<fc::variant>{fc::variant(start_block), fc::variant(end_block), fc::variant(filename)}).wait();
            return result.as<std::string>();
        }
        std::map<uint32_t, std::vector<hsrcore::blockchain::ForkEntry>> CommonApiRpcClient::blockchain_list_forks() const
        {
            fc::variant result = get_json_connection()->async_call("blockchain_list_forks", std::vector<fc::variant>{}).wait();
            return result.as<std::map<uint32_t, std::vector<hsrcore::blockchain::ForkEntry>>>();
        }
        std::vector<hsrcore::blockchain::SlotEntry> CommonApiRpcClient::blockchain_get_delegate_slot_entrys(const std::string& delegate_name, uint32_t limit /* = fc::json::from_string("\"10\"").as<uint32_t>() */) const
        {
            fc::variant result = get_json_connection()->async_call("blockchain_get_delegate_slot_entrys", std::vector<fc::variant>{fc::variant(delegate_name), fc::variant(limit)}).wait();
            return result.as<std::vector<hsrcore::blockchain::SlotEntry>>();
        }
        std::string CommonApiRpcClient::blockchain_get_block_signee(const std::string& block) const
        {
            fc::variant result = get_json_connection()->async_call("blockchain_get_block_signee", std::vector<fc::variant>{fc::variant(block)}).wait();
            return result.as<std::string>();
        }
        hsrcore::blockchain::Asset CommonApiRpcClient::blockchain_unclaimed_genesis() const
        {
            fc::variant result = get_json_connection()->async_call("blockchain_unclaimed_genesis", std::vector<fc::variant>{}).wait();
            return result.as<hsrcore::blockchain::Asset>();
        }
        bool CommonApiRpcClient::blockchain_verify_signature(const std::string& signer, const fc::sha256& hash, const fc::ecc::compact_signature& signature) const
        {
            fc::variant result = get_json_connection()->async_call("blockchain_verify_signature", std::vector<fc::variant>{fc::variant(signer), fc::variant(hash), fc::variant(signature)}).wait();
            return result.as<bool>();
        }
        void CommonApiRpcClient::blockchain_dump_state(const std::string& path) const
        {
            fc::variant result = get_json_connection()->async_call("blockchain_dump_state", std::vector<fc::variant>{fc::variant(path)}).wait();
        }
        void CommonApiRpcClient::blockchain_broadcast_transaction(const hsrcore::blockchain::SignedTransaction& trx)
        {
            fc::variant result = get_json_connection()->async_call("blockchain_broadcast_transaction", std::vector<fc::variant>{fc::variant(trx)}).wait();
        }
        void CommonApiRpcClient::blockchain_btc_address_convert(const std::string& path) const
        {
            fc::variant result = get_json_connection()->async_call("blockchain_btc_address_convert", std::vector<fc::variant>{fc::variant(path)}).wait();
        }
        std::string CommonApiRpcClient::blockchain_get_transaction_rpc(const std::string& transaction_id_prefix, bool exact /* = fc::json::from_string("false").as<bool>() */) const
        {
            fc::variant result = get_json_connection()->async_call("blockchain_get_transaction_rpc", std::vector<fc::variant>{fc::variant(transaction_id_prefix), fc::variant(exact)}).wait();
            return result.as<std::string>();
        }
        void CommonApiRpcClient::blockchain_set_node_vm_enabled(bool enabled)
        {
            fc::variant result = get_json_connection()->async_call("blockchain_set_node_vm_enabled", std::vector<fc::variant>{fc::variant(enabled)}).wait();
        }
        bool CommonApiRpcClient::blockchain_get_node_vm_enabled() const
        {
            fc::variant result = get_json_connection()->async_call("blockchain_get_node_vm_enabled", std::vector<fc::variant>{}).wait();
            return result.as<bool>();
        }
        vector<string> CommonApiRpcClient::blockchain_get_all_contracts() const
        {
            fc::variant result = get_json_connection()->async_call("blockchain_get_all_contracts", std::vector<fc::variant>{}).wait();
            return result.as<vector<string>>();
        }
        unordered_map<string, string> CommonApiRpcClient::blockchain_get_forever_contracts() const
        {
            fc::variant result = get_json_connection()->async_call("blockchain_get_forever_contracts", std::vector<fc::variant>{}).wait();
            return result.as<unordered_map<string, string>>();
        }
		std::vector<std::string> CommonApiRpcClient::blockchain_list_pub_all_address(const std::string& pub_key) const
		{
			fc::variant result = get_json_connection()->async_call("blockchain_list_pub_all_address", std::vector<fc::variant>{fc::variant(pub_key)}).wait();
			return result.as<std::vector<std::string>>();
		}
        std::vector<hsrcore::wallet::ContractTransactionSummary> CommonApiRpcClient::blockchain_list_contract_transaction_history(uint32_t from_block_num, uint32_t block_count, const std::string& contract_id /* = fc::json::from_string("\"\"").as<std::string>() */, uint32_t trx_type /* = fc::json::from_string("\"99\"").as<uint32_t>() */, const std::string& call_method /* = fc::json::from_string("\"\"").as<std::string>() */) const
        {
            fc::variant result = get_json_connection()->async_call("blockchain_list_contract_transaction_history", std::vector<fc::variant>{fc::variant(from_block_num), fc::variant(block_count), fc::variant(contract_id), fc::variant(trx_type), fc::variant(call_method)}).wait();
            return result.as<std::vector<hsrcore::wallet::ContractTransactionSummary>>();
        }
        void CommonApiRpcClient::network_add_node(const std::string& node, const std::string& command /* = fc::json::from_string("\"add\"").as<std::string>() */)
        {
            fc::variant result = get_json_connection()->async_call("network_add_node", std::vector<fc::variant>{fc::variant(node), fc::variant(command)}).wait();
        }
        uint32_t CommonApiRpcClient::network_get_connection_count() const
        {
            fc::variant result = get_json_connection()->async_call("network_get_connection_count", std::vector<fc::variant>{}).wait();
            return result.as<uint32_t>();
        }
        std::vector<fc::variant_object> CommonApiRpcClient::network_get_peer_info(bool not_firewalled /* = fc::json::from_string("false").as<bool>() */) const
        {
            fc::variant result = get_json_connection()->async_call("network_get_peer_info", std::vector<fc::variant>{fc::variant(not_firewalled)}).wait();
            return result.as<std::vector<fc::variant_object>>();
        }
        hsrcore::blockchain::TransactionIdType CommonApiRpcClient::network_broadcast_transaction(const hsrcore::blockchain::SignedTransaction& transaction_to_broadcast)
        {
            fc::variant result = get_json_connection()->async_call("network_broadcast_transaction", std::vector<fc::variant>{fc::variant(transaction_to_broadcast)}).wait();
            return result.as<hsrcore::blockchain::TransactionIdType>();
        }
        void CommonApiRpcClient::network_set_advanced_node_parameters(const fc::variant_object& params)
        {
            fc::variant result = get_json_connection()->async_call("network_set_advanced_node_parameters", std::vector<fc::variant>{fc::variant(params)}).wait();
        }
        fc::variant_object CommonApiRpcClient::network_get_advanced_node_parameters() const
        {
            fc::variant result = get_json_connection()->async_call("network_get_advanced_node_parameters", std::vector<fc::variant>{}).wait();
            return result.as<fc::variant_object>();
        }
        hsrcore::net::MessagePropagationData CommonApiRpcClient::network_get_transaction_propagation_data(const hsrcore::blockchain::TransactionIdType& transaction_id)
        {
            fc::variant result = get_json_connection()->async_call("network_get_transaction_propagation_data", std::vector<fc::variant>{fc::variant(transaction_id)}).wait();
            return result.as<hsrcore::net::MessagePropagationData>();
        }
        hsrcore::net::MessagePropagationData CommonApiRpcClient::network_get_block_propagation_data(const hsrcore::blockchain::BlockIdType& block_hash)
        {
            fc::variant result = get_json_connection()->async_call("network_get_block_propagation_data", std::vector<fc::variant>{fc::variant(block_hash)}).wait();
            return result.as<hsrcore::net::MessagePropagationData>();
        }
        fc::variant_object CommonApiRpcClient::network_get_info() const
        {
            fc::variant result = get_json_connection()->async_call("network_get_info", std::vector<fc::variant>{}).wait();
            return result.as<fc::variant_object>();
        }
        std::vector<hsrcore::net::PotentialPeerEntry> CommonApiRpcClient::network_list_potential_peers() const
        {
            fc::variant result = get_json_connection()->async_call("network_list_potential_peers", std::vector<fc::variant>{}).wait();
            return result.as<std::vector<hsrcore::net::PotentialPeerEntry>>();
        }
        fc::variant_object CommonApiRpcClient::network_get_upnp_info() const
        {
            fc::variant result = get_json_connection()->async_call("network_get_upnp_info", std::vector<fc::variant>{}).wait();
            return result.as<fc::variant_object>();
        }
        std::vector<std::string> CommonApiRpcClient::network_get_blocked_ips() const
        {
            fc::variant result = get_json_connection()->async_call("network_get_blocked_ips", std::vector<fc::variant>{}).wait();
            return result.as<std::vector<std::string>>();
        }
        std::string CommonApiRpcClient::debug_get_client_name() const
        {
            fc::variant result = get_json_connection()->async_call("debug_get_client_name", std::vector<fc::variant>{}).wait();
            return result.as<std::string>();
        }
        fc::variant CommonApiRpcClient::delegate_get_config() const
        {
            fc::variant result = get_json_connection()->async_call("delegate_get_config", std::vector<fc::variant>{}).wait();
            return result.as<fc::variant>();
        }
        void CommonApiRpcClient::delegate_set_network_min_connection_count(uint32_t count)
        {
            fc::variant result = get_json_connection()->async_call("delegate_set_network_min_connection_count", std::vector<fc::variant>{fc::variant(count)}).wait();
        }
        void CommonApiRpcClient::delegate_set_block_max_transaction_count(uint32_t count)
        {
            fc::variant result = get_json_connection()->async_call("delegate_set_block_max_transaction_count", std::vector<fc::variant>{fc::variant(count)}).wait();
        }
        void CommonApiRpcClient::delegate_set_soft_max_imessage_length(int64_t soft_length)
        {
            fc::variant result = get_json_connection()->async_call("delegate_set_soft_max_imessage_length", std::vector<fc::variant>{fc::variant(soft_length)}).wait();
        }
        void CommonApiRpcClient::delegate_set_imessage_fee_coe(const std::string& fee_coe)
        {
            fc::variant result = get_json_connection()->async_call("delegate_set_imessage_fee_coe", std::vector<fc::variant>{fc::variant(fee_coe)}).wait();
        }
        void CommonApiRpcClient::delegate_set_block_max_size(uint32_t size)
        {
            fc::variant result = get_json_connection()->async_call("delegate_set_block_max_size", std::vector<fc::variant>{fc::variant(size)}).wait();
        }
        void CommonApiRpcClient::delegate_set_transaction_max_size(uint32_t size)
        {
            fc::variant result = get_json_connection()->async_call("delegate_set_transaction_max_size", std::vector<fc::variant>{fc::variant(size)}).wait();
        }
        void CommonApiRpcClient::delegate_set_transaction_canonical_signatures_required(bool required)
        {
            fc::variant result = get_json_connection()->async_call("delegate_set_transaction_canonical_signatures_required", std::vector<fc::variant>{fc::variant(required)}).wait();
        }
        void CommonApiRpcClient::delegate_set_transaction_min_fee(const std::string& fee)
        {
            fc::variant result = get_json_connection()->async_call("delegate_set_transaction_min_fee", std::vector<fc::variant>{fc::variant(fee)}).wait();
        }
        void CommonApiRpcClient::delegate_blacklist_add_transaction(const hsrcore::blockchain::TransactionIdType& id)
        {
            fc::variant result = get_json_connection()->async_call("delegate_blacklist_add_transaction", std::vector<fc::variant>{fc::variant(id)}).wait();
        }
        void CommonApiRpcClient::delegate_blacklist_remove_transaction(const hsrcore::blockchain::TransactionIdType& id)
        {
            fc::variant result = get_json_connection()->async_call("delegate_blacklist_remove_transaction", std::vector<fc::variant>{fc::variant(id)}).wait();
        }
        void CommonApiRpcClient::delegate_blacklist_add_operation(const hsrcore::blockchain::OperationTypeEnum& id)
        {
            fc::variant result = get_json_connection()->async_call("delegate_blacklist_add_operation", std::vector<fc::variant>{fc::variant(id)}).wait();
        }
        void CommonApiRpcClient::delegate_blacklist_remove_operation(const hsrcore::blockchain::OperationTypeEnum& id)
        {
            fc::variant result = get_json_connection()->async_call("delegate_blacklist_remove_operation", std::vector<fc::variant>{fc::variant(id)}).wait();
        }
        fc::variant_object CommonApiRpcClient::wallet_get_info()
        {
            fc::variant result = get_json_connection()->async_call("wallet_get_info", std::vector<fc::variant>{}).wait();
            return result.as<fc::variant_object>();
        }
        void CommonApiRpcClient::wallet_open(const std::string& wallet_name)
        {
            fc::variant result = get_json_connection()->async_call("wallet_open", std::vector<fc::variant>{fc::variant(wallet_name)}).wait();
        }
        void CommonApiRpcClient::wallet_create(const std::string& wallet_name, const std::string& new_passphrase, const std::string& brain_key /* = fc::json::from_string("\"\"").as<std::string>() */)
        {
            fc::variant result = get_json_connection()->async_call("wallet_create", std::vector<fc::variant>{fc::variant(wallet_name), fc::variant(new_passphrase), fc::variant(brain_key)}).wait();
        }
        fc::optional<std::string> CommonApiRpcClient::wallet_get_name() const
        {
            fc::variant result = get_json_connection()->async_call("wallet_get_name", std::vector<fc::variant>{}).wait();
            return result.as<fc::optional<std::string>>();
        }
        std::string CommonApiRpcClient::wallet_import_private_key(const std::string& wif_key, const std::string& account_name /* = fc::json::from_string("null").as<std::string>() */, bool create_new_account /* = fc::json::from_string("false").as<bool>() */, bool rescan /* = fc::json::from_string("false").as<bool>() */)
        {
            fc::variant result = get_json_connection()->async_call("wallet_import_private_key", std::vector<fc::variant>{fc::variant(wif_key), fc::variant(account_name), fc::variant(create_new_account), fc::variant(rescan)}).wait();
            return result.as<std::string>();
        }
        void CommonApiRpcClient::wallet_close()
        {
            fc::variant result = get_json_connection()->async_call("wallet_close", std::vector<fc::variant>{}).wait();
        }
        void CommonApiRpcClient::wallet_backup_create(const fc::path& json_filename) const
        {
            fc::variant result = get_json_connection()->async_call("wallet_backup_create", std::vector<fc::variant>{fc::variant(json_filename)}).wait();
        }
        void CommonApiRpcClient::wallet_backup_restore(const fc::path& json_filename, const std::string& wallet_name, const std::string& imported_wallet_passphrase)
        {
            fc::variant result = get_json_connection()->async_call("wallet_backup_restore", std::vector<fc::variant>{fc::variant(json_filename), fc::variant(wallet_name), fc::variant(imported_wallet_passphrase)}).wait();
        }
        bool CommonApiRpcClient::wallet_set_automatic_backups(bool enabled)
        {
            fc::variant result = get_json_connection()->async_call("wallet_set_automatic_backups", std::vector<fc::variant>{fc::variant(enabled)}).wait();
            return result.as<bool>();
        }
        uint32_t CommonApiRpcClient::wallet_set_transaction_expiration_time(uint32_t seconds)
        {
            fc::variant result = get_json_connection()->async_call("wallet_set_transaction_expiration_time", std::vector<fc::variant>{fc::variant(seconds)}).wait();
            return result.as<uint32_t>();
        }
        std::vector<hsrcore::wallet::PrettyTransaction> CommonApiRpcClient::wallet_account_transaction_history(const std::string& account_name /* = fc::json::from_string("\"\"").as<std::string>() */, const std::string& asset_symbol /* = fc::json::from_string("\"\"").as<std::string>() */, int32_t limit /* = fc::json::from_string("0").as<int32_t>() */, uint32_t start_block_num /* = fc::json::from_string("0").as<uint32_t>() */, uint32_t end_block_num /* = fc::json::from_string("-1").as<uint32_t>() */) const
        {
            fc::variant result = get_json_connection()->async_call("wallet_account_transaction_history", std::vector<fc::variant>{fc::variant(account_name), fc::variant(asset_symbol), fc::variant(limit), fc::variant(start_block_num), fc::variant(end_block_num)}).wait();
            return result.as<std::vector<hsrcore::wallet::PrettyTransaction>>();
        }
        std::vector<hsrcore::wallet::PrettyTransaction> CommonApiRpcClient::wallet_transaction_history_splite(const std::string& account_name /* = fc::json::from_string("\"\"").as<std::string>() */, const std::string& asset_symbol /* = fc::json::from_string("\"\"").as<std::string>() */, int32_t limit /* = fc::json::from_string("0").as<int32_t>() */, int32_t transaction_type /* = fc::json::from_string("\"2\"").as<int32_t>() */) const
        {
            fc::variant result = get_json_connection()->async_call("wallet_transaction_history_splite", std::vector<fc::variant>{fc::variant(account_name), fc::variant(asset_symbol), fc::variant(limit), fc::variant(transaction_type)}).wait();
            return result.as<std::vector<hsrcore::wallet::PrettyTransaction>>();
        }
        hsrcore::wallet::AccountBalanceSummaryType CommonApiRpcClient::wallet_account_historic_balance(const fc::time_point& time, const std::string& account_name /* = fc::json::from_string("\"\"").as<std::string>() */) const
        {
            fc::variant result = get_json_connection()->async_call("wallet_account_historic_balance", std::vector<fc::variant>{fc::variant(time), fc::variant(account_name)}).wait();
            return result.as<hsrcore::wallet::AccountBalanceSummaryType>();
        }
        void CommonApiRpcClient::wallet_remove_transaction(const std::string& transaction_id)
        {
            fc::variant result = get_json_connection()->async_call("wallet_remove_transaction", std::vector<fc::variant>{fc::variant(transaction_id)}).wait();
        }
        std::map<hsrcore::blockchain::TransactionIdType, fc::exception> CommonApiRpcClient::wallet_get_pending_transaction_errors(const hsrcore::blockchain::FilePath& filename /* = fc::json::from_string("\"\"").as<hsrcore::blockchain::FilePath>() */) const
        {
            fc::variant result = get_json_connection()->async_call("wallet_get_pending_transaction_errors", std::vector<fc::variant>{fc::variant(filename)}).wait();
            return result.as<std::map<hsrcore::blockchain::TransactionIdType, fc::exception>>();
        }
        void CommonApiRpcClient::wallet_lock()
        {
            fc::variant result = get_json_connection()->async_call("wallet_lock", std::vector<fc::variant>{}).wait();
        }
        void CommonApiRpcClient::wallet_unlock(uint32_t timeout, const std::string& passphrase)
        {
            fc::variant result = get_json_connection()->async_call("wallet_unlock", std::vector<fc::variant>{fc::variant(timeout), fc::variant(passphrase)}).wait();
        }
        void CommonApiRpcClient::wallet_change_passphrase(const std::string& old_passphrase, const std::string& passphrase)
        {
            fc::variant result = get_json_connection()->async_call("wallet_change_passphrase", std::vector<fc::variant>{fc::variant(old_passphrase), fc::variant(passphrase)}).wait();
        }
        bool CommonApiRpcClient::wallet_check_passphrase(const std::string& passphrase)
        {
            fc::variant result = get_json_connection()->async_call("wallet_check_passphrase", std::vector<fc::variant>{fc::variant(passphrase)}).wait();
            return result.as<bool>();
        }
        bool CommonApiRpcClient::wallet_check_address(const std::string& address, int8_t address_type /* = fc::json::from_string("0").as<int8_t>() */)
        {
            fc::variant result = get_json_connection()->async_call("wallet_check_address", std::vector<fc::variant>{fc::variant(address), fc::variant(address_type)}).wait();
            return result.as<bool>();
        }
        std::vector<std::string> CommonApiRpcClient::wallet_list() const
        {
            fc::variant result = get_json_connection()->async_call("wallet_list", std::vector<fc::variant>{}).wait();
            return result.as<std::vector<std::string>>();
        }
        hsrcore::blockchain::Address CommonApiRpcClient::wallet_account_create(const std::string& account_name, const fc::variant& private_data /* = fc::json::from_string("null").as<fc::variant>() */)
        {
            fc::variant result = get_json_connection()->async_call("wallet_account_create", std::vector<fc::variant>{fc::variant(account_name), fc::variant(private_data)}).wait();
            return result.as<hsrcore::blockchain::Address>();
        }
        int8_t CommonApiRpcClient::wallet_account_set_approval(const std::string& account_name, int8_t approval /* = fc::json::from_string("1").as<int8_t>() */)
        {
            fc::variant result = get_json_connection()->async_call("wallet_account_set_approval", std::vector<fc::variant>{fc::variant(account_name), fc::variant(approval)}).wait();
            return result.as<int8_t>();
        }
        std::vector<hsrcore::blockchain::AccountEntry> CommonApiRpcClient::wallet_get_all_approved_accounts(int8_t approval /* = fc::json::from_string("1").as<int8_t>() */)
        {
            fc::variant result = get_json_connection()->async_call("wallet_get_all_approved_accounts", std::vector<fc::variant>{fc::variant(approval)}).wait();
            return result.as<std::vector<hsrcore::blockchain::AccountEntry>>();
        }
        std::string CommonApiRpcClient::wallet_address_create(const std::string& account_name, const std::string& label /* = fc::json::from_string("\"\"").as<std::string>() */, int32_t legacy_network_byte /* = fc::json::from_string("-1").as<int32_t>() */)
        {
            fc::variant result = get_json_connection()->async_call("wallet_address_create", std::vector<fc::variant>{fc::variant(account_name), fc::variant(label), fc::variant(legacy_network_byte)}).wait();
            return result.as<std::string>();
        }
        hsrcore::wallet::WalletTransactionEntry CommonApiRpcClient::wallet_transfer_to_address(const std::string& amount_to_transfer, const std::string& asset_symbol, const std::string& from_account_name, const std::string& to_address, const hsrcore::blockchain::Imessage& memo_message /* = fc::json::from_string("\"\"").as<hsrcore::blockchain::Imessage>() */, const hsrcore::wallet::VoteStrategy& strategy /* = fc::json::from_string("\"vote_recommended\"").as<hsrcore::wallet::VoteStrategy>() */)
        {
            fc::variant result = get_json_connection()->async_call("wallet_transfer_to_address", std::vector<fc::variant>{fc::variant(amount_to_transfer), fc::variant(asset_symbol), fc::variant(from_account_name), fc::variant(to_address), fc::variant(memo_message), fc::variant(strategy)}).wait();
            return result.as<hsrcore::wallet::WalletTransactionEntry>();
        }
        hsrcore::wallet::WalletTransactionEntry CommonApiRpcClient::wallet_transfer_to_address_build(const std::string& amount_to_transfer, const std::string& asset_symbol, const std::string& from_account_public_key, const std::string& to_address, const hsrcore::blockchain::Imessage& memo_message /* = fc::json::from_string("\"\"").as<hsrcore::blockchain::Imessage>() */, const hsrcore::wallet::VoteStrategy& strategy /* = fc::json::from_string("\"vote_none\"").as<hsrcore::wallet::VoteStrategy>() */)
        {
            fc::variant result = get_json_connection()->async_call("wallet_transfer_to_address_build", std::vector<fc::variant>{fc::variant(amount_to_transfer), fc::variant(asset_symbol), fc::variant(from_account_public_key), fc::variant(to_address), fc::variant(memo_message), fc::variant(strategy)}).wait();
            return result.as<hsrcore::wallet::WalletTransactionEntry>();
        }
        hsrcore::wallet::WalletTransactionEntry CommonApiRpcClient::wallet_transfer_to_public_account(const std::string& amount_to_transfer, const std::string& asset_symbol, const std::string& from_account_name, const std::string& to_account_name, const hsrcore::blockchain::Imessage& memo_message /* = fc::json::from_string("\"\"").as<hsrcore::blockchain::Imessage>() */, const hsrcore::wallet::VoteStrategy& strategy /* = fc::json::from_string("\"vote_recommended\"").as<hsrcore::wallet::VoteStrategy>() */)
        {
            fc::variant result = get_json_connection()->async_call("wallet_transfer_to_public_account", std::vector<fc::variant>{fc::variant(amount_to_transfer), fc::variant(asset_symbol), fc::variant(from_account_name), fc::variant(to_account_name), fc::variant(memo_message), fc::variant(strategy)}).wait();
            return result.as<hsrcore::wallet::WalletTransactionEntry>();
        }
        hsrcore::wallet::TransactionBuilder CommonApiRpcClient::wallet_withdraw_from_address(const std::string& amount, const std::string& symbol, const hsrcore::blockchain::Address& from_address, const std::string& to, const hsrcore::wallet::VoteStrategy& strategy /* = fc::json::from_string("\"vote_none\"").as<hsrcore::wallet::VoteStrategy>() */, bool sign_and_broadcast /* = fc::json::from_string("true").as<bool>() */, const std::string& builder_path /* = fc::json::from_string("\"\"").as<std::string>() */)
        {
            fc::variant result = get_json_connection()->async_call("wallet_withdraw_from_address", std::vector<fc::variant>{fc::variant(amount), fc::variant(symbol), fc::variant(from_address), fc::variant(to), fc::variant(strategy), fc::variant(sign_and_broadcast), fc::variant(builder_path)}).wait();
            return result.as<hsrcore::wallet::TransactionBuilder>();
        }
        void CommonApiRpcClient::wallet_rescan_blockchain(uint32_t start_block_num /* = fc::json::from_string("0").as<uint32_t>() */, uint32_t limit /* = fc::json::from_string("-1").as<uint32_t>() */)
        {
            fc::variant result = get_json_connection()->async_call("wallet_rescan_blockchain", std::vector<fc::variant>{fc::variant(start_block_num), fc::variant(limit)}).wait();
        }
        void CommonApiRpcClient::wallet_cancel_scan()
        {
            fc::variant result = get_json_connection()->async_call("wallet_cancel_scan", std::vector<fc::variant>{}).wait();
        }
        hsrcore::wallet::WalletTransactionEntry CommonApiRpcClient::wallet_get_transaction(const std::string& transaction_id)
        {
            fc::variant result = get_json_connection()->async_call("wallet_get_transaction", std::vector<fc::variant>{fc::variant(transaction_id)}).wait();
            return result.as<hsrcore::wallet::WalletTransactionEntry>();
        }
        hsrcore::wallet::WalletTransactionEntry CommonApiRpcClient::wallet_scan_transaction(const std::string& transaction_id, bool overwrite_existing /* = fc::json::from_string("false").as<bool>() */)
        {
            fc::variant result = get_json_connection()->async_call("wallet_scan_transaction", std::vector<fc::variant>{fc::variant(transaction_id), fc::variant(overwrite_existing)}).wait();
            return result.as<hsrcore::wallet::WalletTransactionEntry>();
        }
        void CommonApiRpcClient::wallet_rebroadcast_transaction(const std::string& transaction_id)
        {
            fc::variant result = get_json_connection()->async_call("wallet_rebroadcast_transaction", std::vector<fc::variant>{fc::variant(transaction_id)}).wait();
        }
        hsrcore::wallet::WalletTransactionEntry CommonApiRpcClient::wallet_account_register(const std::string& account_name, const std::string& pay_from_account, const fc::variant& public_data /* = fc::json::from_string("null").as<fc::variant>() */, uint8_t delegate_pay_rate /* = fc::json::from_string("-1").as<uint8_t>() */, const std::string& account_type /* = fc::json::from_string("\"titan_account\"").as<std::string>() */)
        {
            fc::variant result = get_json_connection()->async_call("wallet_account_register", std::vector<fc::variant>{fc::variant(account_name), fc::variant(pay_from_account), fc::variant(public_data), fc::variant(delegate_pay_rate), fc::variant(account_type)}).wait();
            return result.as<hsrcore::wallet::WalletTransactionEntry>();
        }
        void CommonApiRpcClient::wallet_account_update_private_data(const std::string& account_name, const fc::variant& private_data /* = fc::json::from_string("null").as<fc::variant>() */)
        {
            fc::variant result = get_json_connection()->async_call("wallet_account_update_private_data", std::vector<fc::variant>{fc::variant(account_name), fc::variant(private_data)}).wait();
        }
        hsrcore::wallet::WalletTransactionEntry CommonApiRpcClient::wallet_account_update_registration(const std::string& account_name, const std::string& pay_from_account, const fc::variant& public_data /* = fc::json::from_string("null").as<fc::variant>() */, uint8_t delegate_pay_rate /* = fc::json::from_string("-1").as<uint8_t>() */)
        {
            fc::variant result = get_json_connection()->async_call("wallet_account_update_registration", std::vector<fc::variant>{fc::variant(account_name), fc::variant(pay_from_account), fc::variant(public_data), fc::variant(delegate_pay_rate)}).wait();
            return result.as<hsrcore::wallet::WalletTransactionEntry>();
        }
        hsrcore::wallet::WalletTransactionEntry CommonApiRpcClient::wallet_account_update_active_key(const std::string& account_to_update, const std::string& pay_from_account, const std::string& new_active_key /* = fc::json::from_string("\"\"").as<std::string>() */)
        {
            fc::variant result = get_json_connection()->async_call("wallet_account_update_active_key", std::vector<fc::variant>{fc::variant(account_to_update), fc::variant(pay_from_account), fc::variant(new_active_key)}).wait();
            return result.as<hsrcore::wallet::WalletTransactionEntry>();
        }
        std::vector<hsrcore::wallet::WalletAccountEntry> CommonApiRpcClient::wallet_list_accounts() const
        {
            fc::variant result = get_json_connection()->async_call("wallet_list_accounts", std::vector<fc::variant>{}).wait();
            return result.as<std::vector<hsrcore::wallet::WalletAccountEntry>>();
        }
        std::vector<hsrcore::wallet::WalletAccountEntry> CommonApiRpcClient::wallet_list_unregistered_accounts() const
        {
            fc::variant result = get_json_connection()->async_call("wallet_list_unregistered_accounts", std::vector<fc::variant>{}).wait();
            return result.as<std::vector<hsrcore::wallet::WalletAccountEntry>>();
        }
        std::vector<hsrcore::wallet::WalletAccountEntry> CommonApiRpcClient::wallet_list_my_accounts() const
        {
            fc::variant result = get_json_connection()->async_call("wallet_list_my_accounts", std::vector<fc::variant>{}).wait();
            return result.as<std::vector<hsrcore::wallet::WalletAccountEntry>>();
        }
        std::vector<hsrcore::wallet::AccountAddressData> CommonApiRpcClient::wallet_list_my_addresses() const
        {
            fc::variant result = get_json_connection()->async_call("wallet_list_my_addresses", std::vector<fc::variant>{}).wait();
            return result.as<std::vector<hsrcore::wallet::AccountAddressData>>();
        }
        hsrcore::wallet::WalletAccountEntry CommonApiRpcClient::wallet_get_account(const std::string& account_name) const
        {
            fc::variant result = get_json_connection()->async_call("wallet_get_account", std::vector<fc::variant>{fc::variant(account_name)}).wait();
            return result.as<hsrcore::wallet::WalletAccountEntry>();
        }
        std::string CommonApiRpcClient::wallet_get_account_public_address(const std::string& account_name) const
        {
            fc::variant result = get_json_connection()->async_call("wallet_get_account_public_address", std::vector<fc::variant>{fc::variant(account_name)}).wait();
            return result.as<std::string>();
        }
        void CommonApiRpcClient::wallet_remove_contact_account(const std::string& account_name)
        {
            fc::variant result = get_json_connection()->async_call("wallet_remove_contact_account", std::vector<fc::variant>{fc::variant(account_name)}).wait();
        }
        void CommonApiRpcClient::wallet_account_rename(const std::string& current_account_name, const std::string& new_account_name)
        {
            fc::variant result = get_json_connection()->async_call("wallet_account_rename", std::vector<fc::variant>{fc::variant(current_account_name), fc::variant(new_account_name)}).wait();
        }
        hsrcore::wallet::WalletTransactionEntry CommonApiRpcClient::wallet_asset_create(const std::string& symbol, const std::string& asset_name, const std::string& issuer_name, const std::string& description, const std::string& maximum_share_supply, uint64_t precision, const fc::variant& public_data /* = fc::json::from_string("null").as<fc::variant>() */, bool is_market_issued /* = fc::json::from_string("false").as<bool>() */)
        {
            fc::variant result = get_json_connection()->async_call("wallet_asset_create", std::vector<fc::variant>{fc::variant(symbol), fc::variant(asset_name), fc::variant(issuer_name), fc::variant(description), fc::variant(maximum_share_supply), fc::variant(precision), fc::variant(public_data), fc::variant(is_market_issued)}).wait();
            return result.as<hsrcore::wallet::WalletTransactionEntry>();
        }
        hsrcore::wallet::WalletTransactionEntry CommonApiRpcClient::wallet_asset_issue(const std::string& amount, const std::string& symbol, const std::string& to_account_name, const hsrcore::blockchain::Imessage& memo_message /* = fc::json::from_string("\"\"").as<hsrcore::blockchain::Imessage>() */)
        {
            fc::variant result = get_json_connection()->async_call("wallet_asset_issue", std::vector<fc::variant>{fc::variant(amount), fc::variant(symbol), fc::variant(to_account_name), fc::variant(memo_message)}).wait();
            return result.as<hsrcore::wallet::WalletTransactionEntry>();
        }
        hsrcore::wallet::WalletTransactionEntry CommonApiRpcClient::wallet_asset_issue_to_addresses(const std::string& symbol, const std::map<std::string, hsrcore::blockchain::ShareType>& addresses)
        {
            fc::variant result = get_json_connection()->async_call("wallet_asset_issue_to_addresses", std::vector<fc::variant>{fc::variant(symbol), fc::variant(addresses)}).wait();
            return result.as<hsrcore::wallet::WalletTransactionEntry>();
        }
        hsrcore::wallet::AccountBalanceSummaryType CommonApiRpcClient::wallet_account_balance(const std::string& account_name /* = fc::json::from_string("\"\"").as<std::string>() */) const
        {
            fc::variant result = get_json_connection()->async_call("wallet_account_balance", std::vector<fc::variant>{fc::variant(account_name)}).wait();
            return result.as<hsrcore::wallet::AccountBalanceSummaryType>();
        }
        hsrcore::wallet::AccountBalanceIdSummaryType CommonApiRpcClient::wallet_account_balance_ids(const std::string& account_name /* = fc::json::from_string("\"\"").as<std::string>() */) const
        {
            fc::variant result = get_json_connection()->async_call("wallet_account_balance_ids", std::vector<fc::variant>{fc::variant(account_name)}).wait();
            return result.as<hsrcore::wallet::AccountBalanceIdSummaryType>();
        }
        std::vector<hsrcore::wallet::PublicKeySummary> CommonApiRpcClient::wallet_account_list_public_keys(const std::string& account_name)
        {
            fc::variant result = get_json_connection()->async_call("wallet_account_list_public_keys", std::vector<fc::variant>{fc::variant(account_name)}).wait();
            return result.as<std::vector<hsrcore::wallet::PublicKeySummary>>();
        }
        hsrcore::wallet::WalletTransactionEntry CommonApiRpcClient::wallet_delegate_withdraw_pay(const std::string& delegate_name, const std::string& to_account_name, const std::string& amount_to_withdraw)
        {
            fc::variant result = get_json_connection()->async_call("wallet_delegate_withdraw_pay", std::vector<fc::variant>{fc::variant(delegate_name), fc::variant(to_account_name), fc::variant(amount_to_withdraw)}).wait();
            return result.as<hsrcore::wallet::WalletTransactionEntry>();
        }
        hsrcore::blockchain::DelegatePaySalary CommonApiRpcClient::wallet_delegate_pay_balance_query(const std::string& delegate_name)
        {
            fc::variant result = get_json_connection()->async_call("wallet_delegate_pay_balance_query", std::vector<fc::variant>{fc::variant(delegate_name)}).wait();
            return result.as<hsrcore::blockchain::DelegatePaySalary>();
        }
        std::map<std::string,hsrcore::blockchain::DelegatePaySalary> CommonApiRpcClient::wallet_active_delegate_salary()
        {
            fc::variant result = get_json_connection()->async_call("wallet_active_delegate_salary", std::vector<fc::variant>{}).wait();
            return result.as<std::map<std::string,hsrcore::blockchain::DelegatePaySalary>>();
        }
        bool CommonApiRpcClient::wallet_get_delegate_statue(const std::string& account_name)
        {
            fc::variant result = get_json_connection()->async_call("wallet_get_delegate_statue", std::vector<fc::variant>{fc::variant(account_name)}).wait();
            return result.as<bool>();
        }
        void CommonApiRpcClient::wallet_set_transaction_imessage_fee_coe(const std::string& fee_coe)
        {
            fc::variant result = get_json_connection()->async_call("wallet_set_transaction_imessage_fee_coe", std::vector<fc::variant>{fc::variant(fee_coe)}).wait();
        }
        double CommonApiRpcClient::wallet_get_transaction_imessage_fee_coe()
        {
            fc::variant result = get_json_connection()->async_call("wallet_get_transaction_imessage_fee_coe", std::vector<fc::variant>{}).wait();
            return result.as<double>();
        }
        void CommonApiRpcClient::wallet_set_transaction_imessage_soft_max_length(int64_t soft_length)
        {
            fc::variant result = get_json_connection()->async_call("wallet_set_transaction_imessage_soft_max_length", std::vector<fc::variant>{fc::variant(soft_length)}).wait();
        }
        int64_t CommonApiRpcClient::wallet_get_transaction_imessage_soft_max_length()
        {
            fc::variant result = get_json_connection()->async_call("wallet_get_transaction_imessage_soft_max_length", std::vector<fc::variant>{}).wait();
            return result.as<int64_t>();
        }
        hsrcore::blockchain::Asset CommonApiRpcClient::wallet_set_transaction_fee(const std::string& fee)
        {
            fc::variant result = get_json_connection()->async_call("wallet_set_transaction_fee", std::vector<fc::variant>{fc::variant(fee)}).wait();
            return result.as<hsrcore::blockchain::Asset>();
        }
        hsrcore::blockchain::Asset CommonApiRpcClient::wallet_get_transaction_fee(const std::string& symbol /* = fc::json::from_string("\"\"").as<std::string>() */)
        {
            fc::variant result = get_json_connection()->async_call("wallet_get_transaction_fee", std::vector<fc::variant>{fc::variant(symbol)}).wait();
            return result.as<hsrcore::blockchain::Asset>();
        }
        fc::optional<std::string> CommonApiRpcClient::wallet_dump_private_key(const std::string& input) const
        {
            fc::variant result = get_json_connection()->async_call("wallet_dump_private_key", std::vector<fc::variant>{fc::variant(input)}).wait();
            return result.as<fc::optional<std::string>>();
        }
        fc::optional<std::string> CommonApiRpcClient::wallet_dump_account_private_key(const std::string& account_name, const hsrcore::wallet::AccountKeyType& key_type) const
        {
            fc::variant result = get_json_connection()->async_call("wallet_dump_account_private_key", std::vector<fc::variant>{fc::variant(account_name), fc::variant(key_type)}).wait();
            return result.as<fc::optional<std::string>>();
        }
        hsrcore::wallet::AccountVoteSummaryType CommonApiRpcClient::wallet_account_vote_summary(const std::string& account_name /* = fc::json::from_string("\"\"").as<std::string>() */) const
        {
            fc::variant result = get_json_connection()->async_call("wallet_account_vote_summary", std::vector<fc::variant>{fc::variant(account_name)}).wait();
            return result.as<hsrcore::wallet::AccountVoteSummaryType>();
        }
        hsrcore::wallet::VoteSummary CommonApiRpcClient::wallet_check_vote_status(const std::string& account)
        {
            fc::variant result = get_json_connection()->async_call("wallet_check_vote_status", std::vector<fc::variant>{fc::variant(account)}).wait();
            return result.as<hsrcore::wallet::VoteSummary>();
        }
        void CommonApiRpcClient::wallet_set_setting(const std::string& name, const fc::variant& value)
        {
            fc::variant result = get_json_connection()->async_call("wallet_set_setting", std::vector<fc::variant>{fc::variant(name), fc::variant(value)}).wait();
        }
        fc::optional<fc::variant> CommonApiRpcClient::wallet_get_setting(const std::string& name)
        {
            fc::variant result = get_json_connection()->async_call("wallet_get_setting", std::vector<fc::variant>{fc::variant(name)}).wait();
            return result.as<fc::optional<fc::variant>>();
        }
        void CommonApiRpcClient::wallet_delegate_set_block_production(const std::string& delegate_name, bool enabled)
        {
            fc::variant result = get_json_connection()->async_call("wallet_delegate_set_block_production", std::vector<fc::variant>{fc::variant(delegate_name), fc::variant(enabled)}).wait();
        }
        bool CommonApiRpcClient::wallet_set_transaction_scanning(bool enabled)
        {
            fc::variant result = get_json_connection()->async_call("wallet_set_transaction_scanning", std::vector<fc::variant>{fc::variant(enabled)}).wait();
            return result.as<bool>();
        }
        fc::ecc::compact_signature CommonApiRpcClient::wallet_sign_hash(const std::string& signer, const fc::sha256& hash)
        {
            fc::variant result = get_json_connection()->async_call("wallet_sign_hash", std::vector<fc::variant>{fc::variant(signer), fc::variant(hash)}).wait();
            return result.as<fc::ecc::compact_signature>();
        }
        std::string CommonApiRpcClient::wallet_login_start(const std::string& server_account)
        {
            fc::variant result = get_json_connection()->async_call("wallet_login_start", std::vector<fc::variant>{fc::variant(server_account)}).wait();
            return result.as<std::string>();
        }
        fc::variant CommonApiRpcClient::wallet_login_finish(const hsrcore::blockchain::PublicKeyType& server_key, const hsrcore::blockchain::PublicKeyType& client_key, const fc::ecc::compact_signature& client_signature)
        {
            fc::variant result = get_json_connection()->async_call("wallet_login_finish", std::vector<fc::variant>{fc::variant(server_key), fc::variant(client_key), fc::variant(client_signature)}).wait();
            return result.as<fc::variant>();
        }
        hsrcore::wallet::TransactionBuilder CommonApiRpcClient::wallet_balance_set_vote_info(const hsrcore::blockchain::Address& balance_id, const std::string& voter_address /* = fc::json::from_string("\"\"").as<std::string>() */, const hsrcore::wallet::VoteStrategy& strategy /* = fc::json::from_string("\"vote_all\"").as<hsrcore::wallet::VoteStrategy>() */, bool sign_and_broadcast /* = fc::json::from_string("\"true\"").as<bool>() */, const std::string& builder_path /* = fc::json::from_string("\"\"").as<std::string>() */)
        {
            fc::variant result = get_json_connection()->async_call("wallet_balance_set_vote_info", std::vector<fc::variant>{fc::variant(balance_id), fc::variant(voter_address), fc::variant(strategy), fc::variant(sign_and_broadcast), fc::variant(builder_path)}).wait();
            return result.as<hsrcore::wallet::TransactionBuilder>();
        }
        hsrcore::wallet::WalletTransactionEntry CommonApiRpcClient::wallet_publish_slate(const std::string& publishing_account_name, const std::string& paying_account_name /* = fc::json::from_string("\"\"").as<std::string>() */)
        {
            fc::variant result = get_json_connection()->async_call("wallet_publish_slate", std::vector<fc::variant>{fc::variant(publishing_account_name), fc::variant(paying_account_name)}).wait();
            return result.as<hsrcore::wallet::WalletTransactionEntry>();
        }
        hsrcore::wallet::WalletTransactionEntry CommonApiRpcClient::wallet_publish_version(const std::string& publishing_account_name, const std::string& paying_account_name /* = fc::json::from_string("\"\"").as<std::string>() */)
        {
            fc::variant result = get_json_connection()->async_call("wallet_publish_version", std::vector<fc::variant>{fc::variant(publishing_account_name), fc::variant(paying_account_name)}).wait();
            return result.as<hsrcore::wallet::WalletTransactionEntry>();
        }
        hsrcore::wallet::WalletTransactionEntry CommonApiRpcClient::wallet_collect_genesis_balances(const std::string& account_name)
        {
            fc::variant result = get_json_connection()->async_call("wallet_collect_genesis_balances", std::vector<fc::variant>{fc::variant(account_name)}).wait();
            return result.as<hsrcore::wallet::WalletTransactionEntry>();
        }
        int32_t CommonApiRpcClient::wallet_recover_accounts(int32_t accounts_to_recover, int32_t maximum_number_of_attempts /* = fc::json::from_string("1000").as<int32_t>() */)
        {
            fc::variant result = get_json_connection()->async_call("wallet_recover_accounts", std::vector<fc::variant>{fc::variant(accounts_to_recover), fc::variant(maximum_number_of_attempts)}).wait();
            return result.as<int32_t>();
        }
        fc::optional<fc::variant_object> CommonApiRpcClient::wallet_verify_titan_deposit(const std::string& transaction_id_prefix)
        {
            fc::variant result = get_json_connection()->async_call("wallet_verify_titan_deposit", std::vector<fc::variant>{fc::variant(transaction_id_prefix)}).wait();
            return result.as<fc::optional<fc::variant_object>>();
        }
        void CommonApiRpcClient::wallet_repair_entrys(const std::string& collecting_account_name /* = fc::json::from_string("\"\"").as<std::string>() */)
        {
            fc::variant result = get_json_connection()->async_call("wallet_repair_entrys", std::vector<fc::variant>{fc::variant(collecting_account_name)}).wait();
        }
        int32_t CommonApiRpcClient::wallet_regenerate_keys(const std::string& account_name, uint32_t max_key_number)
        {
            fc::variant result = get_json_connection()->async_call("wallet_regenerate_keys", std::vector<fc::variant>{fc::variant(account_name), fc::variant(max_key_number)}).wait();
            return result.as<int32_t>();
        }
        hsrcore::wallet::WalletTransactionEntry CommonApiRpcClient::wallet_account_retract(const std::string& account_to_retract, const std::string& pay_from_account)
        {
            fc::variant result = get_json_connection()->async_call("wallet_account_retract", std::vector<fc::variant>{fc::variant(account_to_retract), fc::variant(pay_from_account)}).wait();
            return result.as<hsrcore::wallet::WalletTransactionEntry>();
        }
        bool CommonApiRpcClient::wallet_account_delete(const std::string& account_name)
        {
            fc::variant result = get_json_connection()->async_call("wallet_account_delete", std::vector<fc::variant>{fc::variant(account_name)}).wait();
            return result.as<bool>();
        }
        std::string CommonApiRpcClient::wallet_transfer_to_address_rpc(const std::string& amount_to_transfer, const std::string& asset_symbol, const std::string& from_account_name, const std::string& to_address, const hsrcore::blockchain::Imessage& memo_message /* = fc::json::from_string("\"\"").as<hsrcore::blockchain::Imessage>() */, const hsrcore::wallet::VoteStrategy& strategy /* = fc::json::from_string("\"vote_recommended\"").as<hsrcore::wallet::VoteStrategy>() */)
        {
            fc::variant result = get_json_connection()->async_call("wallet_transfer_to_address_rpc", std::vector<fc::variant>{fc::variant(amount_to_transfer), fc::variant(asset_symbol), fc::variant(from_account_name), fc::variant(to_address), fc::variant(memo_message), fc::variant(strategy)}).wait();
            return result.as<std::string>();
        }
        std::string CommonApiRpcClient::wallet_account_balance_rpc(const std::string& account_name /* = fc::json::from_string("\"\"").as<std::string>() */) const
        {
            fc::variant result = get_json_connection()->async_call("wallet_account_balance_rpc", std::vector<fc::variant>{fc::variant(account_name)}).wait();
            return result.as<std::string>();
        }
        std::string CommonApiRpcClient::wallet_transfer_to_public_account_rpc(const std::string& amount_to_transfer, const std::string& asset_symbol, const std::string& from_account_name, const std::string& to_account_name, const hsrcore::blockchain::Imessage& memo_message /* = fc::json::from_string("\"\"").as<hsrcore::blockchain::Imessage>() */, const hsrcore::wallet::VoteStrategy& strategy /* = fc::json::from_string("\"vote_recommended\"").as<hsrcore::wallet::VoteStrategy>() */)
        {
            fc::variant result = get_json_connection()->async_call("wallet_transfer_to_public_account_rpc", std::vector<fc::variant>{fc::variant(amount_to_transfer), fc::variant(asset_symbol), fc::variant(from_account_name), fc::variant(to_account_name), fc::variant(memo_message), fc::variant(strategy)}).wait();
            return result.as<std::string>();
        }
        hsrcore::blockchain::PublicKeyType CommonApiRpcClient::wallet_get_account_owner_publickey(const std::string& account_name)
        {
            fc::variant result = get_json_connection()->async_call("wallet_get_account_owner_publickey", std::vector<fc::variant>{fc::variant(account_name)}).wait();
            return result.as<hsrcore::blockchain::PublicKeyType>();
        }
        hsrcore::wallet::WalletTransactionEntry CommonApiRpcClient::wallet_transfer_to_contract(double amount_to_transfer, const std::string& asset_symbol, const std::string& from_account_name, const std::string& to_contract, double amount_for_exec)
        {
            fc::variant result = get_json_connection()->async_call("wallet_transfer_to_contract", std::vector<fc::variant>{fc::variant(amount_to_transfer), fc::variant(asset_symbol), fc::variant(from_account_name), fc::variant(to_contract), fc::variant(amount_for_exec)}).wait();
            return result.as<hsrcore::wallet::WalletTransactionEntry>();
        }
        hsrcore::wallet::WalletTransactionEntry CommonApiRpcClient::sign_build_transaction(const hsrcore::wallet::WalletTransactionEntry& trasaction_building)
        {
            fc::variant result = get_json_connection()->async_call("sign_build_transaction", std::vector<fc::variant>{fc::variant(trasaction_building)}).wait();
            return result.as<hsrcore::wallet::WalletTransactionEntry>();
        }
        bool CommonApiRpcClient::broadcast_building_transaction(const hsrcore::wallet::WalletTransactionEntry& trasaction_building)
        {
            fc::variant result = get_json_connection()->async_call("broadcast_building_transaction", std::vector<fc::variant>{fc::variant(trasaction_building)}).wait();
            return result.as<bool>();
        }
        hsrcore::wallet::WalletTransactionEntry CommonApiRpcClient::wallet_transfer_to_contract_build(double amount_to_transfer, const std::string& asset_symbol, const std::string& from_account_public_key, const std::string& to_contract, double amount_for_exec)
        {
            fc::variant result = get_json_connection()->async_call("wallet_transfer_to_contract_build", std::vector<fc::variant>{fc::variant(amount_to_transfer), fc::variant(asset_symbol), fc::variant(from_account_public_key), fc::variant(to_contract), fc::variant(amount_for_exec)}).wait();
            return result.as<hsrcore::wallet::WalletTransactionEntry>();
        }
        std::vector<hsrcore::blockchain::Asset> CommonApiRpcClient::wallet_transfer_to_contract_testing(double amount_to_transfer, const std::string& asset_symbol, const std::string& from_account_name, const std::string& to_contract)
        {
            fc::variant result = get_json_connection()->async_call("wallet_transfer_to_contract_testing", std::vector<fc::variant>{fc::variant(amount_to_transfer), fc::variant(asset_symbol), fc::variant(from_account_name), fc::variant(to_contract)}).wait();
            return result.as<std::vector<hsrcore::blockchain::Asset>>();
        }
        vector<string> CommonApiRpcClient::wallet_get_contracts(const std::string& account_name /* = fc::json::from_string("\"\"").as<std::string>() */)
        {
            fc::variant result = get_json_connection()->async_call("wallet_get_contracts", std::vector<fc::variant>{fc::variant(account_name)}).wait();
            return result.as<vector<string>>();
        }
        void CommonApiRpcClient::wallet_scan_contracts()
        {
            fc::variant result = get_json_connection()->async_call("wallet_scan_contracts", std::vector<fc::variant>{}).wait();
        }
        bool CommonApiRpcClient::wallet_import_hshare_private_key(const std::string& acc_name, const hsrcore::blockchain::FilePath& infile)
        {
            fc::variant result = get_json_connection()->async_call("wallet_import_hshare_private_key", std::vector<fc::variant>{fc::variant(acc_name), fc::variant(infile)}).wait();
            return result.as<bool>();
        }
        bool CommonApiRpcClient::wallet_import_hshare_encrypted_private_key(const std::string& passwd, const std::string& acc_name, const hsrcore::blockchain::FilePath& infile)
        {
            fc::variant result = get_json_connection()->async_call("wallet_import_hshare_encrypted_private_key", std::vector<fc::variant>{fc::variant(passwd), fc::variant(acc_name), fc::variant(infile)}).wait();
            return result.as<bool>();
        }
        hsrcore::wallet::TransactionBuilder CommonApiRpcClient::wallet_builder_add_signature(const hsrcore::wallet::TransactionBuilder& builder, bool broadcast /* = fc::json::from_string("false").as<bool>() */)
        {
            fc::variant result = get_json_connection()->async_call("wallet_builder_add_signature", std::vector<fc::variant>{fc::variant(builder), fc::variant(broadcast)}).wait();
            return result.as<hsrcore::wallet::TransactionBuilder>();
        }
        hsrcore::wallet::TransactionBuilder CommonApiRpcClient::wallet_builder_file_add_signature(const hsrcore::blockchain::FilePath& builder_path, bool broadcast /* = fc::json::from_string("false").as<bool>() */)
        {
            fc::variant result = get_json_connection()->async_call("wallet_builder_file_add_signature", std::vector<fc::variant>{fc::variant(builder_path), fc::variant(broadcast)}).wait();
            return result.as<hsrcore::wallet::TransactionBuilder>();
        }
        hsrcore::wallet::WalletTransactionEntry CommonApiRpcClient::wallet_multisig_deposit(const std::string& amount, const std::string& asset_symbol, const std::string& from_account, const std::string& to_account, const hsrcore::blockchain::Imessage& memo_message /* = fc::json::from_string("\"\"").as<hsrcore::blockchain::Imessage>() */)
        {
            fc::variant result = get_json_connection()->async_call("wallet_multisig_deposit", std::vector<fc::variant>{fc::variant(amount), fc::variant(asset_symbol), fc::variant(from_account), fc::variant(to_account), fc::variant(memo_message)}).wait();
            return result.as<hsrcore::wallet::WalletTransactionEntry>();
        }
        fc::variant_object CommonApiRpcClient::wallet_import_multisig_account(const hsrcore::blockchain::Address& multisig_address)
        {
            fc::variant result = get_json_connection()->async_call("wallet_import_multisig_account", std::vector<fc::variant>{fc::variant(multisig_address)}).wait();
            return result.as<fc::variant_object>();
        }
        hsrcore::blockchain::Address CommonApiRpcClient::wallet_import_multisig_account_by_detail(const std::string& asset_symbol, uint32_t m, const std::vector<hsrcore::blockchain::Address>& addresses)
        {
            fc::variant result = get_json_connection()->async_call("wallet_import_multisig_account_by_detail", std::vector<fc::variant>{fc::variant(asset_symbol), fc::variant(m), fc::variant(addresses)}).wait();
            return result.as<hsrcore::blockchain::Address>();
        }
        hsrcore::wallet::TransactionBuilder CommonApiRpcClient::wallet_multisig_withdraw_start(const std::string& amount, const std::string& asset_symbol, const hsrcore::blockchain::Address& from, const hsrcore::blockchain::Address& to_address, const hsrcore::blockchain::Imessage& memo_message /* = fc::json::from_string("\"\"").as<hsrcore::blockchain::Imessage>() */, const hsrcore::blockchain::FilePath& builder_path /* = fc::json::from_string("\"\"").as<hsrcore::blockchain::FilePath>() */)
        {
            fc::variant result = get_json_connection()->async_call("wallet_multisig_withdraw_start", std::vector<fc::variant>{fc::variant(amount), fc::variant(asset_symbol), fc::variant(from), fc::variant(to_address), fc::variant(memo_message), fc::variant(builder_path)}).wait();
            return result.as<hsrcore::wallet::TransactionBuilder>();
        }
        std::pair<std::string, hsrcore::wallet::WalletTransactionEntry> CommonApiRpcClient::wallet_create_multisig_account(const std::string& amount, const std::string& asset_symbol, const std::string& from_account, uint32_t m, const std::vector<hsrcore::blockchain::Address>& addresses, const hsrcore::blockchain::Imessage& memo_message /* = fc::json::from_string("\"\"").as<hsrcore::blockchain::Imessage>() */)
        {
            fc::variant result = get_json_connection()->async_call("wallet_create_multisig_account", std::vector<fc::variant>{fc::variant(amount), fc::variant(asset_symbol), fc::variant(from_account), fc::variant(m), fc::variant(addresses), fc::variant(memo_message)}).wait();
            return result.as<std::pair<std::string, hsrcore::wallet::WalletTransactionEntry>>();
        }
        std::vector<hsrcore::wallet::PrettyTransaction> CommonApiRpcClient::wallet_multisig_account_history(const std::string& account_address, const std::string& asset_symbol /* = fc::json::from_string("\"\"").as<std::string>() */, int32_t limit /* = fc::json::from_string("0").as<int32_t>() */, uint32_t start_block_num /* = fc::json::from_string("0").as<uint32_t>() */, uint32_t end_block_num /* = fc::json::from_string("-1").as<uint32_t>() */) const
        {
            fc::variant result = get_json_connection()->async_call("wallet_multisig_account_history", std::vector<fc::variant>{fc::variant(account_address), fc::variant(asset_symbol), fc::variant(limit), fc::variant(start_block_num), fc::variant(end_block_num)}).wait();
            return result.as<std::vector<hsrcore::wallet::PrettyTransaction>>();
        }
        hsrcore::wallet::AccountBalanceSummaryType CommonApiRpcClient::wallet_multisig_account_balance(const std::string& account_address /* = fc::json::from_string("\"\"").as<std::string>() */) const
        {
            fc::variant result = get_json_connection()->async_call("wallet_multisig_account_balance", std::vector<fc::variant>{fc::variant(account_address)}).wait();
            return result.as<hsrcore::wallet::AccountBalanceSummaryType>();
        }
        fc::variant_object CommonApiRpcClient::wallet_builder_get_multisig_detail(const hsrcore::wallet::TransactionBuilder& transaction_builder) const
        {
            fc::variant result = get_json_connection()->async_call("wallet_builder_get_multisig_detail", std::vector<fc::variant>{fc::variant(transaction_builder)}).wait();
            return result.as<fc::variant_object>();
        }
        fc::variant_object CommonApiRpcClient::wallet_builder_file_get_multisig_detail(const hsrcore::blockchain::FilePath& builder_path) const
        {
            fc::variant result = get_json_connection()->async_call("wallet_builder_file_get_multisig_detail", std::vector<fc::variant>{fc::variant(builder_path)}).wait();
            return result.as<fc::variant_object>();
        }
        bool CommonApiRpcClient::set_pos_generate() 
        {
            fc::variant result = get_json_connection()->async_call("set_pos_generate", std::vector<fc::variant>{}).wait();
            return result.as<bool>();
        }
        fc::variant_object CommonApiRpcClient::about() const
        {
            fc::variant result = get_json_connection()->async_call("about", std::vector<fc::variant>{}).wait();
            return result.as<fc::variant_object>();
        }
        fc::variant_object CommonApiRpcClient::get_info() const
        {
            fc::variant result = get_json_connection()->async_call("get_info", std::vector<fc::variant>{}).wait();
            return result.as<fc::variant_object>();
        }
        void CommonApiRpcClient::stop()
        {
            fc::variant result = get_json_connection()->async_call("stop", std::vector<fc::variant>{}).wait();
        }
        std::string CommonApiRpcClient::help(const std::string& command_name /* = fc::json::from_string("\"\"").as<std::string>() */) const
        {
            fc::variant result = get_json_connection()->async_call("help", std::vector<fc::variant>{fc::variant(command_name)}).wait();
            return result.as<std::string>();
        }
        fc::variant_object CommonApiRpcClient::validate_address(const std::string& address) const
        {
            fc::variant result = get_json_connection()->async_call("validate_address", std::vector<fc::variant>{fc::variant(address)}).wait();
            return result.as<fc::variant_object>();
        }
        std::string CommonApiRpcClient::execute_command_line(const std::string& input) const
        {
            fc::variant result = get_json_connection()->async_call("execute_command_line", std::vector<fc::variant>{fc::variant(input)}).wait();
            return result.as<std::string>();
        }
        void CommonApiRpcClient::execute_script(const fc::path& script) const
        {
            fc::variant result = get_json_connection()->async_call("execute_script", std::vector<fc::variant>{fc::variant(script)}).wait();
        }
        fc::variants CommonApiRpcClient::batch(const std::string& method_name, const std::vector<fc::variants>& parameters_list) const
        {
            fc::variant result = get_json_connection()->async_call("batch", std::vector<fc::variant>{fc::variant(method_name), fc::variant(parameters_list)}).wait();
            return result.as<fc::variants>();
        }
        fc::variants CommonApiRpcClient::batch_authenticated(const std::string& method_name, const std::vector<fc::variants>& parameters_list) const
        {
            fc::variant result = get_json_connection()->async_call("batch_authenticated", std::vector<fc::variant>{fc::variant(method_name), fc::variant(parameters_list)}).wait();
            return result.as<fc::variants>();
        }
        hsrcore::wallet::WalletTransactionEntry CommonApiRpcClient::builder_finalize_and_sign(const hsrcore::wallet::TransactionBuilder& builder) const
        {
            fc::variant result = get_json_connection()->async_call("builder_finalize_and_sign", std::vector<fc::variant>{fc::variant(builder)}).wait();
            return result.as<hsrcore::wallet::WalletTransactionEntry>();
        }
        std::map<std::string, hsrcore::api::MethodData> CommonApiRpcClient::meta_help() const
        {
            fc::variant result = get_json_connection()->async_call("meta_help", std::vector<fc::variant>{}).wait();
            return result.as<std::map<std::string, hsrcore::api::MethodData>>();
        }
        void CommonApiRpcClient::rpc_set_username(const std::string& username /* = fc::json::from_string("\"\"").as<std::string>() */)
        {
            fc::variant result = get_json_connection()->async_call("rpc_set_username", std::vector<fc::variant>{fc::variant(username)}).wait();
        }
        void CommonApiRpcClient::rpc_set_password(const std::string& password /* = fc::json::from_string("\"\"").as<std::string>() */)
        {
            fc::variant result = get_json_connection()->async_call("rpc_set_password", std::vector<fc::variant>{fc::variant(password)}).wait();
        }
        void CommonApiRpcClient::rpc_start_server(uint32_t port /* = fc::json::from_string("\"65065\"").as<uint32_t>() */)
        {
            fc::variant result = get_json_connection()->async_call("rpc_start_server", std::vector<fc::variant>{fc::variant(port)}).wait();
        }
        void CommonApiRpcClient::http_start_server(uint32_t port /* = fc::json::from_string("\"65066\"").as<uint32_t>() */)
        {
            fc::variant result = get_json_connection()->async_call("http_start_server", std::vector<fc::variant>{fc::variant(port)}).wait();
        }
        void CommonApiRpcClient::ntp_update_time()
        {
            fc::variant result = get_json_connection()->async_call("ntp_update_time", std::vector<fc::variant>{}).wait();
        }
        fc::variant CommonApiRpcClient::disk_usage() const
        {
            fc::variant result = get_json_connection()->async_call("disk_usage", std::vector<fc::variant>{}).wait();
            return result.as<fc::variant>();
        }
        fc::path CommonApiRpcClient::compile_contract(const fc::path& filename) const
        {
            fc::variant result = get_json_connection()->async_call("compile_contract", std::vector<fc::variant>{fc::variant(filename)}).wait();
            return result.as<fc::path>();
        }
        std::string CommonApiRpcClient::register_contract(const std::string& owner, const fc::path& codefile, const std::string& asset_symbol, const fc::optional<double>& init_limit)
        {
            fc::variant result = get_json_connection()->async_call("register_contract", std::vector<fc::variant>{fc::variant(owner), fc::variant(codefile), fc::variant(asset_symbol), fc::variant(init_limit)}).wait();
            return result.as<std::string>();
        }
        hsrcore::wallet::WalletTransactionEntry CommonApiRpcClient::register_contract_build(const std::string& owner_public_key, const fc::path& codefile, const std::string& asset_symbol, const fc::optional<double>& init_limit)
        {
            fc::variant result = get_json_connection()->async_call("register_contract_build", std::vector<fc::variant>{fc::variant(owner_public_key), fc::variant(codefile), fc::variant(asset_symbol), fc::variant(init_limit)}).wait();
            return result.as<hsrcore::wallet::WalletTransactionEntry>();
        }
        std::vector<hsrcore::blockchain::Asset> CommonApiRpcClient::register_contract_testing(const std::string& owner, const fc::path& codefile)
        {
            fc::variant result = get_json_connection()->async_call("register_contract_testing", std::vector<fc::variant>{fc::variant(owner), fc::variant(codefile)}).wait();
            return result.as<std::vector<hsrcore::blockchain::Asset>>();
        }
        hsrcore::wallet::WalletTransactionEntry CommonApiRpcClient::upgrade_contract(const std::string& contract_address, const std::string& upgrader_name, const std::string& new_contract_name, const hsrcore::blockchain::Imessage& new_contract_desc, const std::string& asset_symbol, const fc::optional<double>& exec_limit)
        {
            fc::variant result = get_json_connection()->async_call("upgrade_contract", std::vector<fc::variant>{fc::variant(contract_address), fc::variant(upgrader_name), fc::variant(new_contract_name), fc::variant(new_contract_desc), fc::variant(asset_symbol), fc::variant(exec_limit)}).wait();
            return result.as<hsrcore::wallet::WalletTransactionEntry>();
        }
        hsrcore::wallet::WalletTransactionEntry CommonApiRpcClient::upgrade_contract_build(const std::string& contract_address, const std::string& upgrader_public_key, const std::string& new_contract_name, const hsrcore::blockchain::Imessage& new_contract_desc, const std::string& asset_symbol, const fc::optional<double>& exec_limit)
        {
            fc::variant result = get_json_connection()->async_call("upgrade_contract_build", std::vector<fc::variant>{fc::variant(contract_address), fc::variant(upgrader_public_key), fc::variant(new_contract_name), fc::variant(new_contract_desc), fc::variant(asset_symbol), fc::variant(exec_limit)}).wait();
            return result.as<hsrcore::wallet::WalletTransactionEntry>();
        }
        std::vector<hsrcore::blockchain::Asset> CommonApiRpcClient::upgrade_contract_testing(const std::string& contract_address, const std::string& upgrader_name, const std::string& new_contract_name, const hsrcore::blockchain::Imessage& new_contract_desc)
        {
            fc::variant result = get_json_connection()->async_call("upgrade_contract_testing", std::vector<fc::variant>{fc::variant(contract_address), fc::variant(upgrader_name), fc::variant(new_contract_name), fc::variant(new_contract_desc)}).wait();
            return result.as<std::vector<hsrcore::blockchain::Asset>>();
        }
        hsrcore::wallet::WalletTransactionEntry CommonApiRpcClient::destroy_contract(const std::string& contract_address, const std::string& destroyer_name, const std::string& asset_symbol, const fc::optional<double>& exec_limit)
        {
            fc::variant result = get_json_connection()->async_call("destroy_contract", std::vector<fc::variant>{fc::variant(contract_address), fc::variant(destroyer_name), fc::variant(asset_symbol), fc::variant(exec_limit)}).wait();
            return result.as<hsrcore::wallet::WalletTransactionEntry>();
        }
        hsrcore::wallet::WalletTransactionEntry CommonApiRpcClient::destroy_contract_build(const std::string& contract_address, const std::string& destroyer_public_key, const std::string& asset_symbol, const fc::optional<double>& exec_limit)
        {
            fc::variant result = get_json_connection()->async_call("destroy_contract_build", std::vector<fc::variant>{fc::variant(contract_address), fc::variant(destroyer_public_key), fc::variant(asset_symbol), fc::variant(exec_limit)}).wait();
            return result.as<hsrcore::wallet::WalletTransactionEntry>();
        }
        std::vector<hsrcore::blockchain::Asset> CommonApiRpcClient::destroy_contract_testing(const std::string& contract_address, const std::string& destroyer_name)
        {
            fc::variant result = get_json_connection()->async_call("destroy_contract_testing", std::vector<fc::variant>{fc::variant(contract_address), fc::variant(destroyer_name)}).wait();
            return result.as<std::vector<hsrcore::blockchain::Asset>>();
        }
        hsrcore::wallet::WalletTransactionEntry CommonApiRpcClient::call_contract(const std::string& contract, const std::string& caller_name, const std::string& function_name, const std::string& params, const std::string& asset_symbol, const fc::optional<double>& call_limit)
        {
            fc::variant result = get_json_connection()->async_call("call_contract", std::vector<fc::variant>{fc::variant(contract), fc::variant(caller_name), fc::variant(function_name), fc::variant(params), fc::variant(asset_symbol), fc::variant(call_limit)}).wait();
            return result.as<hsrcore::wallet::WalletTransactionEntry>();
        }
        hsrcore::wallet::WalletTransactionEntry CommonApiRpcClient::call_contract_build(const std::string& contract, const std::string& caller_public_key, const std::string& function_name, const std::string& params, const std::string& asset_symbol, const fc::optional<double>& call_limit)
        {
            fc::variant result = get_json_connection()->async_call("call_contract_build", std::vector<fc::variant>{fc::variant(contract), fc::variant(caller_public_key), fc::variant(function_name), fc::variant(params), fc::variant(asset_symbol), fc::variant(call_limit)}).wait();
            return result.as<hsrcore::wallet::WalletTransactionEntry>();
        }
        hsrcore::blockchain::ContractEntryPrintable CommonApiRpcClient::get_contract_info(const std::string& contract)
        {
            fc::variant result = get_json_connection()->async_call("get_contract_info", std::vector<fc::variant>{fc::variant(contract)}).wait();
            return result.as<hsrcore::blockchain::ContractEntryPrintable>();
        }
        std::vector<hsrcore::blockchain::BalanceEntry> CommonApiRpcClient::get_contract_balance(const std::string& contract)
        {
            fc::variant result = get_json_connection()->async_call("get_contract_balance", std::vector<fc::variant>{fc::variant(contract)}).wait();
            return result.as<std::vector<hsrcore::blockchain::BalanceEntry>>();
        }
        std::vector<hsrcore::blockchain::Asset> CommonApiRpcClient::call_contract_testing(const std::string& contract, const std::string& caller_name, const std::string& function_name, const std::string& params)
        {
            fc::variant result = get_json_connection()->async_call("call_contract_testing", std::vector<fc::variant>{fc::variant(contract), fc::variant(caller_name), fc::variant(function_name), fc::variant(params)}).wait();
            return result.as<std::vector<hsrcore::blockchain::Asset>>();
        }
        std::string CommonApiRpcClient::call_contract_offline(const std::string& contract, const std::string& caller_name, const std::string& function_name, const std::string& params)
        {
            fc::variant result = get_json_connection()->async_call("call_contract_offline", std::vector<fc::variant>{fc::variant(contract), fc::variant(caller_name), fc::variant(function_name), fc::variant(params)}).wait();
            return result.as<std::string>();
        }
        hsrcore::blockchain::ContractEntryPrintable CommonApiRpcClient::load_contract_to_file(const std::string& contract, const fc::path& file)
        {
            fc::variant result = get_json_connection()->async_call("load_contract_to_file", std::vector<fc::variant>{fc::variant(contract), fc::variant(file)}).wait();
            return result.as<hsrcore::blockchain::ContractEntryPrintable>();
        }
        hsrcore::blockchain::TransactionIdType CommonApiRpcClient::get_result_trx_id(const hsrcore::blockchain::TransactionIdType& request_id)
        {
            fc::variant result = get_json_connection()->async_call("get_result_trx_id", std::vector<fc::variant>{fc::variant(request_id)}).wait();
            return result.as<hsrcore::blockchain::TransactionIdType>();
        }
        hsrcore::blockchain::TransactionIdType CommonApiRpcClient::get_request_trx_id(const hsrcore::blockchain::TransactionIdType& request_id)
        {
            fc::variant result = get_json_connection()->async_call("get_request_trx_id", std::vector<fc::variant>{fc::variant(request_id)}).wait();
            return result.as<hsrcore::blockchain::TransactionIdType>();
        }
        void CommonApiRpcClient::sandbox_open() const
        {
            fc::variant result = get_json_connection()->async_call("sandbox_open", std::vector<fc::variant>{}).wait();
        }
        void CommonApiRpcClient::sandbox_close() const
        {
            fc::variant result = get_json_connection()->async_call("sandbox_close", std::vector<fc::variant>{}).wait();
        }
        std::string CommonApiRpcClient::sandbox_register_contract(const std::string& owner, const fc::path& codefile, const std::string& asset_symbol, const fc::optional<double>& initLimit)
        {
            fc::variant result = get_json_connection()->async_call("sandbox_register_contract", std::vector<fc::variant>{fc::variant(owner), fc::variant(codefile), fc::variant(asset_symbol), fc::variant(initLimit)}).wait();
            return result.as<std::string>();
        }
        hsrcore::wallet::WalletTransactionEntry CommonApiRpcClient::sandbox_call_contract(const std::string& contract, const std::string& caller_name, const std::string& function_name, const std::string& params, const std::string& cost_asset, const fc::optional<double>& callLimit)
        {
            fc::variant result = get_json_connection()->async_call("sandbox_call_contract", std::vector<fc::variant>{fc::variant(contract), fc::variant(caller_name), fc::variant(function_name), fc::variant(params), fc::variant(cost_asset), fc::variant(callLimit)}).wait();
            return result.as<hsrcore::wallet::WalletTransactionEntry>();
        }
        hsrcore::wallet::WalletTransactionEntry CommonApiRpcClient::sandbox_upgrade_contract(const std::string& contract_address, const std::string& upgrader_name, const std::string& new_contract_name, const hsrcore::blockchain::Imessage& new_contract_desc, const std::string& asset_symbol, const fc::optional<double>& exec_limit)
        {
            fc::variant result = get_json_connection()->async_call("sandbox_upgrade_contract", std::vector<fc::variant>{fc::variant(contract_address), fc::variant(upgrader_name), fc::variant(new_contract_name), fc::variant(new_contract_desc), fc::variant(asset_symbol), fc::variant(exec_limit)}).wait();
            return result.as<hsrcore::wallet::WalletTransactionEntry>();
        }
        std::vector<hsrcore::blockchain::Asset> CommonApiRpcClient::sandbox_upgrade_contract_testing(const std::string& contract_address, const std::string& upgrader_name, const std::string& new_contract_name, const hsrcore::blockchain::Imessage& new_contract_desc)
        {
            fc::variant result = get_json_connection()->async_call("sandbox_upgrade_contract_testing", std::vector<fc::variant>{fc::variant(contract_address), fc::variant(upgrader_name), fc::variant(new_contract_name), fc::variant(new_contract_desc)}).wait();
            return result.as<std::vector<hsrcore::blockchain::Asset>>();
        }
        hsrcore::wallet::WalletTransactionEntry CommonApiRpcClient::sandbox_destroy_contract(const std::string& contract_address, const std::string& destroyer_name, const std::string& asset_symbol, const fc::optional<double>& exec_limit)
        {
            fc::variant result = get_json_connection()->async_call("sandbox_destroy_contract", std::vector<fc::variant>{fc::variant(contract_address), fc::variant(destroyer_name), fc::variant(asset_symbol), fc::variant(exec_limit)}).wait();
            return result.as<hsrcore::wallet::WalletTransactionEntry>();
        }
        std::vector<hsrcore::blockchain::Asset> CommonApiRpcClient::sandbox_destroy_contract_testing(const std::string& contract_address, const std::string& destroyer_name)
        {
            fc::variant result = get_json_connection()->async_call("sandbox_destroy_contract_testing", std::vector<fc::variant>{fc::variant(contract_address), fc::variant(destroyer_name)}).wait();
            return result.as<std::vector<hsrcore::blockchain::Asset>>();
        }
        hsrcore::blockchain::ContractEntryPrintable CommonApiRpcClient::sandbox_get_contract_info(const std::string& contract)
        {
            fc::variant result = get_json_connection()->async_call("sandbox_get_contract_info", std::vector<fc::variant>{fc::variant(contract)}).wait();
            return result.as<hsrcore::blockchain::ContractEntryPrintable>();
        }
        std::vector<hsrcore::blockchain::BalanceEntry> CommonApiRpcClient::sandbox_get_contract_balance(const std::string& contract)
        {
            fc::variant result = get_json_connection()->async_call("sandbox_get_contract_balance", std::vector<fc::variant>{fc::variant(contract)}).wait();
            return result.as<std::vector<hsrcore::blockchain::BalanceEntry>>();
        }
        hsrcore::wallet::WalletTransactionEntry CommonApiRpcClient::sandbox_transfer_to_contract(double amount_to_transfer, const std::string& asset_symbol, const std::string& from_account_name, const std::string& to_contract, double amount_for_exec)
        {
            fc::variant result = get_json_connection()->async_call("sandbox_transfer_to_contract", std::vector<fc::variant>{fc::variant(amount_to_transfer), fc::variant(asset_symbol), fc::variant(from_account_name), fc::variant(to_contract), fc::variant(amount_for_exec)}).wait();
            return result.as<hsrcore::wallet::WalletTransactionEntry>();
        }
        hsrcore::wallet::AccountBalanceSummaryType CommonApiRpcClient::sandbox_account_balance(const std::string& account_name /* = fc::json::from_string("\"\"").as<std::string>() */)
        {
            fc::variant result = get_json_connection()->async_call("sandbox_account_balance", std::vector<fc::variant>{fc::variant(account_name)}).wait();
            return result.as<hsrcore::wallet::AccountBalanceSummaryType>();
        }
        fc::path CommonApiRpcClient::sandbox_compile_contract(const fc::path& filename) const
        {
            fc::variant result = get_json_connection()->async_call("sandbox_compile_contract", std::vector<fc::variant>{fc::variant(filename)}).wait();
            return result.as<fc::path>();
        }
        hsrcore::blockchain::ContractEntryPrintable CommonApiRpcClient::sandbox_load_contract_to_file(const std::string& contract, const fc::path& file)
        {
            fc::variant result = get_json_connection()->async_call("sandbox_load_contract_to_file", std::vector<fc::variant>{fc::variant(contract), fc::variant(file)}).wait();
            return result.as<hsrcore::blockchain::ContractEntryPrintable>();
        }
        std::vector<hsrcore::blockchain::Asset> CommonApiRpcClient::sandbox_register_contract_testing(const std::string& owner, const fc::path& codefile)
        {
            fc::variant result = get_json_connection()->async_call("sandbox_register_contract_testing", std::vector<fc::variant>{fc::variant(owner), fc::variant(codefile)}).wait();
            return result.as<std::vector<hsrcore::blockchain::Asset>>();
        }
        std::vector<hsrcore::blockchain::Asset> CommonApiRpcClient::sandbox_call_contract_testing(const std::string& contract, const std::string& caller_name, const std::string& function_name, const std::string& params)
        {
            fc::variant result = get_json_connection()->async_call("sandbox_call_contract_testing", std::vector<fc::variant>{fc::variant(contract), fc::variant(caller_name), fc::variant(function_name), fc::variant(params)}).wait();
            return result.as<std::vector<hsrcore::blockchain::Asset>>();
        }
        std::vector<hsrcore::blockchain::Asset> CommonApiRpcClient::sandbox_transfer_to_contract_testing(double amount_to_transfer, const std::string& asset_symbol, const std::string& from_account_name, const std::string& to_contract)
        {
            fc::variant result = get_json_connection()->async_call("sandbox_transfer_to_contract_testing", std::vector<fc::variant>{fc::variant(amount_to_transfer), fc::variant(asset_symbol), fc::variant(from_account_name), fc::variant(to_contract)}).wait();
            return result.as<std::vector<hsrcore::blockchain::Asset>>();
        }
        vector<hsrcore::blockchain::SandboxAccountInfo> CommonApiRpcClient::sandbox_list_my_addresses(const std::string& account_name /* = fc::json::from_string("\"\"").as<std::string>() */)
        {
            fc::variant result = get_json_connection()->async_call("sandbox_list_my_addresses", std::vector<fc::variant>{fc::variant(account_name)}).wait();
            return result.as<vector<hsrcore::blockchain::SandboxAccountInfo>>();
        }
        std::string CommonApiRpcClient::get_contract_registered_in_transaction(const hsrcore::blockchain::TransactionIdType& trx_id)
        {
            fc::variant result = get_json_connection()->async_call("get_contract_registered_in_transaction", std::vector<fc::variant>{fc::variant(trx_id)}).wait();
            return result.as<std::string>();
        }
        hsrcore::blockchain::TransactionIdType CommonApiRpcClient::get_transaction_id_contract_registered(const std::string& contract_id)
        {
            fc::variant result = get_json_connection()->async_call("get_transaction_id_contract_registered", std::vector<fc::variant>{fc::variant(contract_id)}).wait();
            return result.as<hsrcore::blockchain::TransactionIdType>();
        }
        hsrcore::blockchain::CodePrintAble CommonApiRpcClient::get_contract_info_from_gpc_file(const fc::path& file)
        {
            fc::variant result = get_json_connection()->async_call("get_contract_info_from_gpc_file", std::vector<fc::variant>{fc::variant(file)}).wait();
            return result.as<hsrcore::blockchain::CodePrintAble>();
        }
        MiningInfo CommonApiRpcClient::get_mining_info()
        {
            fc::variant result = get_json_connection()->async_call("get_mining_info", std::vector<fc::variant>{}).wait();
            return result.as<MiningInfo>();
        }
        MiningDifficulty CommonApiRpcClient::get_difficulty()
        {
            fc::variant result = get_json_connection()->async_call("get_difficulty", std::vector<fc::variant>{}).wait();
            return result.as<MiningDifficulty>();
        }
        bool CommonApiRpcClient::set_generate(bool fGenerate, uint32_t nThreads /* = fc::json::from_string("-1").as<uint32_t>() */)
        {
            fc::variant result = get_json_connection()->async_call("set_generate", std::vector<fc::variant>{fc::variant(fGenerate), fc::variant(nThreads)}).wait();
            return result.as<bool>();
        }
        MiningWorkPackage CommonApiRpcClient::get_work()
        {
            fc::variant result = get_json_connection()->async_call("get_work", std::vector<fc::variant>{}).wait();
            return result.as<MiningWorkPackage>();
        }
        bool CommonApiRpcClient::submit_block(const std::string& HashNoNonce, uint64_t Nonce, uint64_t Extra_Nonce)
        {
            fc::variant result = get_json_connection()->async_call("submit_block", std::vector<fc::variant>{fc::variant(HashNoNonce), fc::variant(Nonce), fc::variant(Extra_Nonce)}).wait();
            return result.as<bool>();
        }
        bool CommonApiRpcClient::submit_blockex(const std::string& data)
        {
            fc::variant result = get_json_connection()->async_call("submit_blockex", std::vector<fc::variant>{fc::variant(data)}).wait();
            return result.as<bool>();
        }
        bool CommonApiRpcClient::set_coinbase(const std::string& account_name)
        {
            fc::variant result = get_json_connection()->async_call("set_coinbase", std::vector<fc::variant>{fc::variant(account_name)}).wait();
            return result.as<bool>();
        }
        StakingInfo CommonApiRpcClient::get_staking_info()
        {
            fc::variant result = get_json_connection()->async_call("get_staking_info", std::vector<fc::variant>{}).wait();
            return result.as<StakingInfo>();
        }
        fc::path CommonApiRpcClient::compile_script(const fc::path& filename) const
        {
            fc::variant result = get_json_connection()->async_call("compile_script", std::vector<fc::variant>{fc::variant(filename)}).wait();
            return result.as<fc::path>();
        }
        std::string CommonApiRpcClient::add_script(const fc::path& filename, const hsrcore::blockchain::Imessage& description)
        {
            fc::variant result = get_json_connection()->async_call("add_script", std::vector<fc::variant>{fc::variant(filename), fc::variant(description)}).wait();
            return result.as<std::string>();
        }
        void CommonApiRpcClient::remove_script(const std::string& scriptid)
        {
            fc::variant result = get_json_connection()->async_call("remove_script", std::vector<fc::variant>{fc::variant(scriptid)}).wait();
        }
        hsrcore::wallet::ScriptEntryPrintable CommonApiRpcClient::get_script_info(const std::string& scriptid)
        {
            fc::variant result = get_json_connection()->async_call("get_script_info", std::vector<fc::variant>{fc::variant(scriptid)}).wait();
            return result.as<hsrcore::wallet::ScriptEntryPrintable>();
        }
        std::vector<hsrcore::wallet::ScriptEntryPrintable> CommonApiRpcClient::list_scripts()
        {
            fc::variant result = get_json_connection()->async_call("list_scripts", std::vector<fc::variant>{}).wait();
            return result.as<std::vector<hsrcore::wallet::ScriptEntryPrintable>>();
        }
        void CommonApiRpcClient::disable_script(const std::string& scriptid)
        {
            fc::variant result = get_json_connection()->async_call("disable_script", std::vector<fc::variant>{fc::variant(scriptid)}).wait();
        }
        void CommonApiRpcClient::enable_script(const std::string& scriptid)
        {
            fc::variant result = get_json_connection()->async_call("enable_script", std::vector<fc::variant>{fc::variant(scriptid)}).wait();
        }
        void CommonApiRpcClient::import_script_db(const fc::path& dbfile)
        {
            fc::variant result = get_json_connection()->async_call("import_script_db", std::vector<fc::variant>{fc::variant(dbfile)}).wait();
        }
        void CommonApiRpcClient::export_script_db(const fc::path& dbfile)
        {
            fc::variant result = get_json_connection()->async_call("export_script_db", std::vector<fc::variant>{fc::variant(dbfile)}).wait();
        }
        std::vector<std::string> CommonApiRpcClient::get_events_bound(const std::string& script_id)
        {
            fc::variant result = get_json_connection()->async_call("get_events_bound", std::vector<fc::variant>{fc::variant(script_id)}).wait();
            return result.as<std::vector<std::string>>();
        }
        std::vector<std::string> CommonApiRpcClient::list_event_handler(const std::string& contract_id_str, const std::string& event_type)
        {
            fc::variant result = get_json_connection()->async_call("list_event_handler", std::vector<fc::variant>{fc::variant(contract_id_str), fc::variant(event_type)}).wait();
            return result.as<std::vector<std::string>>();
        }
        void CommonApiRpcClient::add_event_handler(const std::string& contract_id_str, const std::string& event_type, const std::string& script_id, uint32_t index)
        {
            fc::variant result = get_json_connection()->async_call("add_event_handler", std::vector<fc::variant>{fc::variant(contract_id_str), fc::variant(event_type), fc::variant(script_id), fc::variant(index)}).wait();
        }
        void CommonApiRpcClient::delete_event_handler(const std::string& contract_id_str, const std::string& event_type, const std::string& script_id)
        {
            fc::variant result = get_json_connection()->async_call("delete_event_handler", std::vector<fc::variant>{fc::variant(contract_id_str), fc::variant(event_type), fc::variant(script_id)}).wait();
        }

    }
} // end namespace hsrcore::rpc_stubs
