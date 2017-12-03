#include <stdint.h>
#include <utilities/GitRevision.hpp>

#define HSRCORE_GIT_REVISION_SHA "7e7f255f185ffaf53397084f6ca747674088f176"
#define HSRCORE_GIT_REVISION_UNIX_TIMESTAMP 1488663957
#define HSRCORE_GIT_REVISION_DESCRIPTION "3.1.3"

namespace hsrcore {
    namespace utilities {

        const char* const git_revision_sha = HSRCORE_GIT_REVISION_SHA;
        const uint32_t git_revision_unix_timestamp = HSRCORE_GIT_REVISION_UNIX_TIMESTAMP;
        const char* const git_revision_description = HSRCORE_GIT_REVISION_DESCRIPTION;

    }
} // end namespace hsrcore::utilities
