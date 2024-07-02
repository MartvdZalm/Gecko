cmake_minimum_required(VERSION 3.10)
project(Gecko)

set(CMAKE_CXX_STANDARD 14)

find_package(Protobuf REQUIRED)
find_package(OpenSSL REQUIRED)
find_package(Boost REQUIRED COMPONENTS system)

include_directories(${Protobuf_INCLUDE_DIRS} ${OpenSSL_INCLUDE_DIR} ${Boost_INCLUDE_DIRS} include)

add_executable(Gecko src/main.cpp)

target_link_libraries(Gecko ${Protobuf_LIBRARIES} ${OPENSSL_LIBRARIES} ${Boost_LIBRARIES})
