#ifndef lhsrcorelib_h
#define lhsrcorelib_h

#include <glua/lprefix.h>
#include <stdlib.h>
#include <math.h>
#include <string>
#include <list>
#include <set>
#include <unordered_map>
#include <memory>

#include <glua/lua.h>
#include <glua/lauxlib.h>
#include <glua/lualib.h>
#include <glua/lapi.h>

#include <glua/hsrcore_lua_api.h>
#include <glua/hsrcore_lua_lib.h>

namespace glua
{
	namespace lib
	{
		// int HSRCORElib_get_storage(lua_State *L);
		// HSRCORE.get_storage具体的实现
		int hsrcorelib_get_storage_impl(lua_State *L,
			const char *contract_id, const char *name);

		// int HSRCORElib_set_storage(lua_State *L);

        int hsrcorelib_set_storage_impl(lua_State *L,
          const char *contract_id, const char *name, int value_index);
	}
}

#endif
