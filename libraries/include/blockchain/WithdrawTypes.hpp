#pragma once

#include <blockchain/Asset.hpp>
#include <blockchain/Config.hpp>
#include <blockchain/Types.hpp>

#include <fc/io/enum_type.hpp>
#include <fc/io/raw.hpp>

namespace hsrcore {
    namespace blockchain {

        enum WithdrawConditionTypes
        {
            withdraw_null_type = 0,
            withdraw_signature_type = 1,
            withdraw_multisig_type = 3,
            withdraw_escrow_type = 6,
			withdraw_p2sh_multisig_type = 7
        };

        enum WithdrawBalanceTypes
        {
            withdraw_common_type = 0,
            withdraw_contract_type = 1,
            withdraw_margin_type = 2
        };

        /**
         * The withdraw condition defines which delegate this address
         * is voting for, assuming asset_type == 0
         */
        struct WithdrawCondition
        {
            WithdrawCondition() :asset_id(0), slate_id(0), type(withdraw_null_type), balance_type(withdraw_common_type){}

            template<typename WithdrawType>
            WithdrawCondition(const WithdrawType& t, AssetIdType asset_id_arg = 0, SlateIdType delegate_id_arg = 0, fc::enum_type<uint8_t, WithdrawBalanceTypes> balance_type_arg = withdraw_common_type)
            {
                type = WithdrawType::type;
                asset_id = asset_id_arg;
                slate_id = delegate_id_arg;
                balance_type = balance_type_arg;
                data = fc::raw::pack(t);
            }

            template<typename WithdrawType>
            WithdrawType as()const
            {
                FC_ASSERT(type == WithdrawType::type, "", ("type", type)("WithdrawType", WithdrawType::type));
                return fc::raw::unpack<WithdrawType>(data);
            }

            BalanceIdType get_address()const;

            set<Address>      owners()const;
            optional<Address> owner()const;
            string            type_label()const;

            AssetIdType                                     asset_id;
            SlateIdType                                     slate_id = 0;
            fc::enum_type<uint8_t, WithdrawConditionTypes>  type = withdraw_null_type;
            fc::enum_type<uint8_t, WithdrawBalanceTypes>  balance_type = withdraw_common_type;
            std::vector<char>                                 data;
        };

        struct TransferMemo
        {
            PublicKeyType   one_time_key;
            vector<char>      encrypted_memo_data;
        };

        enum MemoFlagsEnum
        {
            from_memo = 0, ///< default memo type, the public key is who the deposit is from
            /**
             *  Alternative memo type, the public key is who the deposit is to.  This
             *  can be used for 'change' memos and help the sender reconstruct information
             *  in the event they lose their wallet.
             */
             to_memo = 1,
        };

        struct MemoData
        {
            PublicKeyType                      from;
            uint64_t                             from_signature = 0;

            void        set_message(const std::string& message);
            std::string get_message()const;

            /** messages are a constant length to preven analysis of
             * transactions with the same length memo_data
             */
            fc::array<char, HSR_BLOCKCHAIN_MAX_MEMO_SIZE>     message;
            fc::enum_type<uint8_t, MemoFlagsEnum>           memo_flags;
        };
        typedef fc::optional<MemoData>         oMemoData;

        /** The purpose of the extended memo data is to support extra
         * message data beyond the 19 bytes afforded by the default
         * message.
         */
        struct ExtendedMemoData
        {
            PublicKeyType                      from;
            uint64_t                             from_signature = 0;

            void        set_message(const std::string& message);
            std::string get_message()const;

            /** messages are a constant length to preven analysis of
             * transactions with the same length memo_data
             */
            fc::array<char, HSR_BLOCKCHAIN_MAX_MEMO_SIZE>      message;
            fc::enum_type<uint8_t, MemoFlagsEnum>            memo_flags;
            fc::array<char, HSR_BLOCKCHAIN_EXTENDED_MEMO_SIZE> extra_memo;
        };
        typedef fc::optional<ExtendedMemoData> oExtendedMemoData;

        struct MemoStatus : public ExtendedMemoData
        {
            MemoStatus(){}
            MemoStatus(const ExtendedMemoData& memo,
                bool valid_signature,
                const fc::ecc::private_key& opk);

            bool                 has_valid_signature = false;
            fc::ecc::private_key owner_private_key;
        };
        typedef fc::optional<MemoStatus> oMessageStatus;

        struct WithdrawWithSignature
        {
            static const uint8_t    type;

            WithdrawWithSignature(const Address owner_arg = Address())
                :owner(owner_arg){}

            oMessageStatus     decrypt_memo_data(const fc::ecc::private_key& receiver_key, bool ignore_owner = false)const;
            PublicKeyType  encrypt_memo_data(const fc::ecc::private_key& one_time_private_key,
                const fc::ecc::public_key&  to_public_key,
                const fc::ecc::private_key& from_private_key,
                const std::string& memo_message,
                const fc::ecc::public_key&  memo_pub_key,
                MemoFlagsEnum memo_type = from_memo,
                bool use_stealth_address = true);

            ExtendedMemoData decrypt_memo_data(const fc::sha512& secret)const;
            void         encrypt_memo_data(const fc::sha512& secret, const MemoData&);
            void         encrypt_memo_data(const fc::sha512& secret, const ExtendedMemoData&);

            Address                 owner;
            optional<TransferMemo>    memo;
        };


        struct WithdrawWithMultisig
        {
            static const uint8_t    type;

            uint32_t                required;
            std::set<Address>       owners;
            optional<TransferMemo>    memo;
        };

		struct WithdrawP2shMultisig
		{
			WithdrawP2shMultisig(const Address owner_arg = Address())
				:owner(owner_arg) {}
			static const uint8_t    type;

			Address                 owner;
		};

        struct withdraw_with_escrow
        {
            static const uint8_t    type;

            Address                 sender;
            Address                 receiver;
            Address                 escrow;
            DigestType             agreement_digest;

            oMessageStatus decrypt_memo_data(const fc::ecc::private_key& receiver_key, bool ignore_owner = false)const;
            PublicKeyType encrypt_memo_data(const fc::ecc::private_key& one_time_private_key,
                const fc::ecc::public_key&  to_public_key,
                const fc::ecc::private_key& from_private_key,
                const std::string& memo_message,
                const fc::ecc::public_key&  memo_pub_key,
                MemoFlagsEnum memo_type = from_memo);

            ExtendedMemoData    decrypt_memo_data(const fc::sha512& secret)const;
            void                  encrypt_memo_data(const fc::sha512& secret, const ExtendedMemoData&);
            void                  encrypt_memo_data(const fc::sha512& secret, const MemoData&);

            optional<TransferMemo>    memo;
        };

    }
} // hsrcore::blockchain

namespace fc {
    void to_variant(const hsrcore::blockchain::WithdrawCondition& var, variant& vo);
    void from_variant(const variant& var, hsrcore::blockchain::WithdrawCondition& vo);
    void to_variant(const hsrcore::blockchain::MemoData& var, variant& vo);
    void from_variant(const variant& var, hsrcore::blockchain::MemoData& vo);
}

FC_REFLECT_ENUM(hsrcore::blockchain::WithdrawConditionTypes,
    (withdraw_null_type)
    (withdraw_signature_type)
    (withdraw_multisig_type)
    (withdraw_escrow_type)
	(withdraw_p2sh_multisig_type)
    )
    FC_REFLECT_ENUM(hsrcore::blockchain::WithdrawBalanceTypes,
    (withdraw_common_type)
    (withdraw_contract_type)
    (withdraw_margin_type)
    )
    FC_REFLECT(hsrcore::blockchain::WithdrawCondition,
    (asset_id)
    (slate_id)
    (type)
    (balance_type)
    (data)
    )
    FC_REFLECT(hsrcore::blockchain::TransferMemo,
    (one_time_key)
    (encrypted_memo_data)
    )
    FC_REFLECT_ENUM(hsrcore::blockchain::MemoFlagsEnum,
    (from_memo)
    (to_memo)
    )
    FC_REFLECT(hsrcore::blockchain::MemoData,
    (from)
    (from_signature)
    (message)
    (memo_flags)
    )

    FC_REFLECT(hsrcore::blockchain::ExtendedMemoData,
    (from)
    (from_signature)
    (message)
    (memo_flags)
    (extra_memo)
    )
    FC_REFLECT_DERIVED(hsrcore::blockchain::MemoStatus,
    (hsrcore::blockchain::MemoData),
    (has_valid_signature)
    (owner_private_key)
    )
    FC_REFLECT(hsrcore::blockchain::WithdrawWithSignature,
    (owner)
    (memo)
    )

    FC_REFLECT(hsrcore::blockchain::WithdrawWithMultisig,
    (required)
    (owners)
    (memo)
    )
	FC_REFLECT(hsrcore::blockchain::WithdrawP2shMultisig,
	(owner)
	)

    FC_REFLECT(hsrcore::blockchain::withdraw_with_escrow,
    (sender)
    (receiver)
    (escrow)
    (agreement_digest)
    (memo)
    )
