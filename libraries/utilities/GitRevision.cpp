#include <stdint.h>
#include <utilities/GitRevision.hpp>

#define HSRCORE_GIT_REVISION_SHA "7e7f255f185ffaf53397084f6ca747674088f176"
#define HSRCORE_GIT_REVISION_UNIX_TIMESTAMP 1512529968
#define HSRCORE_GIT_REVISION_DESCRIPTION "2.0.0"

namespace hsrcore {
    namespace utilities {

        const char* const git_revision_sha = HSRCORE_GIT_REVISION_SHA;
        const uint32_t git_revision_unix_timestamp = HSRCORE_GIT_REVISION_UNIX_TIMESTAMP;
        const char* const git_revision_description = HSRCORE_GIT_REVISION_DESCRIPTION;

    }
} // end namespace hsrcore::utilities
