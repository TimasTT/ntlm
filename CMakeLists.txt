cmake_minimum_required(VERSION 3.20)
project(ntlm_auth)
set(NAME ntlm_)

set(CMAKE_CXX_STANDARD 14)

add_executable(${NAME} main.cpp ntlm.cpp)

target_link_libraries(${NAME} ntlm)