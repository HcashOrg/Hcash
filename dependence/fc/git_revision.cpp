#include <fc/git_revision.hpp>

#define FC_GIT_REVISION_SHA "GITDIR-NOTFOUND"
#define FC_GIT_REVISION_UNIX_TIMESTAMP HEAD-HASH-NOTFOUND

namespace fc { 

const char* const git_revision_sha = FC_GIT_REVISION_SHA;
const uint32_t git_revision_unix_timestamp = FC_GIT_REVISION_UNIX_TIMESTAMP;

} // end namespace fc
