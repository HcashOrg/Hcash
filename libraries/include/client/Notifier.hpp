#pragma once
#include <memory>
#include <string>
#include <stdint.h>

#include <fc/time.hpp>

namespace hsrcore {
    namespace client {
        namespace detail {
            class HSRGntpNotifierImpl;
        }

        class HSRGntpNotifier {
        public:
            HSRGntpNotifier(const std::string& host_to_notify = "127.0.0.1", uint16_t port = 23053,
                const std::string& hsr_instance_identifier = "HSR",
                const fc::optional<std::string>& password = fc::optional<std::string>());
            ~HSRGntpNotifier();

            void client_is_shutting_down();
            void notify_connection_count_changed(uint32_t new_connection_count);
            void notify_client_exiting_unexpectedly();
            void notify_head_block_too_old(const fc::time_point_sec head_block_age);
        private:
            std::unique_ptr<detail::HSRGntpNotifierImpl> my;
        };
        typedef std::shared_ptr<HSRGntpNotifier> HSRGntpNotifierPtr;

    }
} // end namespace hsrcore::client
