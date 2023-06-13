include_directories (../include)

set(SRC_LIST TCP.cpp RpcMes.cpp ServiceInfo.cpp RpcService.cpp ThreadPool.cpp Rpc.cpp)
set(CLI_SRC_LIST Client.cpp ${SRC_LIST})
set(REG_SRC_LIST Registry.cpp ${SRC_LIST})
set(SER_SRC_LIST Server.cpp ${SRC_LIST})

add_executable (client ${CLI_SRC_LIST})
add_executable (registry ${REG_SRC_LIST})
add_executable (server ${SER_SRC_LIST})
add_executable (test test.cpp TCP.cpp RpcMes.cpp ServiceInfo.cpp RpcService.cpp)

set (EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)