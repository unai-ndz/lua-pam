variable_watch(LUA51_FOUND)
cmake_minimum_required(VERSION 3.15)
project(lua_pam)

find_package(Lua51 REQUIRED)

include_directories(${LUA_INCLUDE_DIR})

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_DIR src)

add_library(lua_pam SHARED ${SOURCE_DIR}/main.cpp)

target_link_libraries(lua_pam ${LUA_LIBRARIES} pam)

install(TARGETS lua_pam DESTINATION ${CMAKE_INSTALL_LIBDIR}/lua/${LUA_VERSION_MAJOR}.${LUA_VERSION_MINOR})
