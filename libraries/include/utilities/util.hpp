#pragma once



#ifndef WIN32
#include <sys/types.h>
#include <sys/time.h>
#include <sys/resource.h>
#endif


#include <map>
#include <list>
#include <utility>
#include <vector>
#include <string>

#include <boost/thread.hpp>
#include <boost/filesystem.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/date_time/gregorian/gregorian_types.hpp>
#include <boost/date_time/posix_time/posix_time_types.hpp>

#include <stdint.h>





#ifdef WIN32
inline void SetThreadPriority(int nPriority)
{
	SetThreadPriority(GetCurrentThread(), nPriority);
}
#else

#define THREAD_PRIORITY_LOWEST          PRIO_MAX
#define THREAD_PRIORITY_BELOW_NORMAL    2
#define THREAD_PRIORITY_NORMAL          0
#define THREAD_PRIORITY_ABOVE_NORMAL    0

inline void SetThreadPriority(int nPriority)
{
	// It's unclear if it's even possible to change thread priorities on Linux,
	// but we really and truly need it for the generation threads.
#ifdef PRIO_THREAD
	setpriority(PRIO_THREAD, 0, nPriority);
#else
	setpriority(PRIO_PROCESS, 0, nPriority);
#endif
}
#endif







void RenameThread(const char* name)
{
#if defined(PR_SET_NAME)
	// Only the first 15 characters are used (16 - NUL terminator)
	::prctl(PR_SET_NAME, name, 0, 0, 0);
#elif 0 && (defined(__FreeBSD__) || defined(__OpenBSD__))
	// TODO: This is currently disabled because it needs to be verified to work
	//       on FreeBSD or OpenBSD first. When verified the '0 &&' part can be
	//       removed.
	pthread_set_name_np(pthread_self(), name);

#elif defined(MAC_OSX) && defined(__MAC_OS_X_VERSION_MAX_ALLOWED)

	// pthread_setname_np is XCode 10.6-and-later
#if __MAC_OS_X_VERSION_MAX_ALLOWED >= 1060
	pthread_setname_np(name);
#endif

#else
	// Prevent warnings for unused parameters...
	(void)name;
#endif
}
