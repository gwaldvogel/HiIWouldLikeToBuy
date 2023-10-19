cmake_minimum_required(VERSION 3.26)
project(HiIWouldLikeToBuy)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# enable_testing()

# set(VCPKG_TRACE_FIND_PACKAGE ON)

# find_package(Qt6 REQUIRED COMPONENTS Core Qml)
find_package(spdlog CONFIG REQUIRED)
find_package(httplib CONFIG REQUIRED)
find_package(OpenSSL REQUIRED)
find_package(yaml-cpp CONFIG REQUIRED)

add_definitions("-DCPPHTTPLIB_OPENSSL_SUPPORT")

add_subdirectory(src)
