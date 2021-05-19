cmake_minimum_required(VERSION 3.5)

project(dixon LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
find_package(Threads REQUIRED)
find_package(NTL REQUIRED)
find_package(benchmark REQUIRED)


add_executable(dixon dixon.cpp dixon.hpp gauss.hpp slaves.hpp gauss_testing.hpp main.cpp)
target_link_libraries(dixon ${NTL_LIBRARY} Threads::Threads benchmark::benchmark)
