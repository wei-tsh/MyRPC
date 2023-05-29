cmake_minimum_required(VERSION 3.0.0)

project(MyRpc)

set(Cli_SRC_LIST RpcClient.cpp)
set(Ser_SRC_LIST RpcServer.cpp)

add_executable(Client ${Cli_SRC_LIST})
add_executable(Server ${Ser_SRC_LIST})