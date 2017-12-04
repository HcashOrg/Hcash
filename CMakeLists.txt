AUX_SOURCE_DIRECTORY(libraries/api API_SRC)
AUX_SOURCE_DIRECTORY(libraries/cli CLI_SRC)
AUX_SOURCE_DIRECTORY(libraries/client CLIENT_SRC)
AUX_SOURCE_DIRECTORY(libraries/db DB_SRC)
AUX_SOURCE_DIRECTORY(libraries/net NET_SRC)
AUX_SOURCE_DIRECTORY(libraries/rpc RPC_SRC)
AUX_SOURCE_DIRECTORY(libraries/rpc_stubs RPC_STUBS_SRC)
AUX_SOURCE_DIRECTORY(libraries/utilities UTILITIES_SRC)
AUX_SOURCE_DIRECTORY(libraries/wallet WALLET_SRC)
AUX_SOURCE_DIRECTORY(libraries/blockchain BLOCKCHAIN_SRC)
AUX_SOURCE_DIRECTORY(libraries/glua GLUA_SRC)
AUX_SOURCE_DIRECTORY(libraries/contract_engine CONTRACT_SRC)
AUX_SOURCE_DIRECTORY(libraries/hshare HSHARE_SRC)
AUX_SOURCE_DIRECTORY(libraries/include/hshare_wallet HSHARE_WALLET_SRC)

LIST(REMOVE_ITEM BLOCKCHAIN_SRC "libraries/blockchain/applink.c")
LIST(REMOVE_ITEM GLUA_SRC "libraries/glua/main.cpp" "libraries/glua/cdemo1.cpp" "libraries/glua/hsrcore_lua_api.demo.cpp")
ADD_DEFINITIONS("-DHAVE_CXX_STDHEADERS")
cmake_minimum_required(VERSION 2.8)
SET (CMAKE_CXX_COMPILER     "/usr/bin/g++")

# Boost settings
set(Boost_USE_STATIC_LIBS     ON)
set(Boost_USE_MULTITHREADED   ON)
set(Boost_USE_STATIC_RUNTIME  ON)

# Specify Boost libraries that will use.
FIND_PACKAGE( Boost 1.54.0 REQUIRED COMPONENTS system program_options chrono context coroutine date_time exception filesystem iostreams locale thread )

set(CMAKE_CXX_FLAGS "-std=c++11 -DHSR_GLOBAL_API_LOG=1 -DHSR_TEST_NETWORK -D_DARWIN_C_SOURCE" )
set(Boost_INCLUDE_DIR　"/usr/include/boost")
set(Boost_LIBRARY_DIR  "/usr/lib/x86_64-linux-gnu")

INCLUDE_DIRECTORIES( ${Boost_INCLUDE_DIR} 
        "libraries/include"
        "dependence/fc/include"
        "dependence/leveldb/include"
        "dependence/miniupnp"
        "dependence/openssl1.0.2/include"
	"dependence/db-5.3.28.NC/build_unix"
	"libraries/hshare"
)

LINK_DIRECTORIES( ${Boost_LIBRARY_DIR}
        "dependence/fc"
        "dependence/leveldb"
        "dependence/miniupnp/miniupnpc"
        "dependence/openssl1.0.2"
        "dependence/fc/vendor/secp256k1-zkp/src/project_secp256k1-build/.libs"
        "."
        "libraries/api"
        "libraries/blockchain"
        "libraries/cli"
        "libraries/client"
	"libraries/contract_engine"
        "libraries/db"
        "libraries/glua"
        "libraries/net"
        "libraries/rpc"
        "libraries/rpc_stubs"
        "libraries/utilities"
        "libraries/wallet"
	"libraries/hshare"
	"dependence/db-5.3.28.NC/build_unix"
)

set(SOURCE_FILES
	Main.cpp
)

add_library(glua ${GLUA_SRC})
add_library(all ${API_SRC} ${BLOCKCHAIN_SRC} ${CLI_SRC} ${CLIENT_SRC} ${DB_SRC} ${NET_SRC} ${RPC_SRC} ${RPC_STUBS_SRC} ${UTILITIES_SRC} ${WALLET_SRC} ${CONTRACT_SRC} ${HSHARE_SRC} ${HSHARE_WALLET_SRC})

add_executable(hsrcore ${SOURCE_FILES})

TARGET_LINK_LIBRARIES(hsrcore liball.a libglua.a libfc.a libsecp256k1.a libleveldb.a libdb_cxx.a libminiupnpc.a ${Boost_LIBRARIES} libcrypto.a dl)
