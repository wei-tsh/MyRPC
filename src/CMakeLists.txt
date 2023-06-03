include_directories (../include)

set(CLI_SRC_LIST RpcClient.cpp TCP.cpp RpcMes.cpp ServiceInfo.cpp)
set(REG_SRC_LIST Registry.cpp TCP.cpp RpcMes.cpp ServiceInfo.cpp)
set(SER_SRC_LIST RpcServer.cpp TCP.cpp RpcMes.cpp ServiceInfo.cpp)

add_executable (client ${CLI_SRC_LIST})
add_executable (registry ${REG_SRC_LIST})
add_executable (server ${SER_SRC_LIST})
add_executable (test test.cpp ThreadPool.cpp)

set (EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)