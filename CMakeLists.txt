## Copyright (C) 2020 Alexis LE GOADEC.

## This file is part of the Graphthewy project which is licensed under
## the European Union Public License v1.2.

## If a copy of the EUPL v1.2 was not distributed with this software,
## you can obtain one at : https://joinup.ec.europa.eu/collection/eupl/eupl-text-eupl-12


cmake_minimum_required(VERSION 3.0)

project(graphthewy VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_C_FLAGS "-Og")

set(CMAKE_MODULE_PATH ".")
set(CTEST_BINARY_DIRECTORY "./tests")

option(CMAKE_BUILD_TYPE "Debuging configuration for tests" Debug)
option(GRAPHTHEWY_BUILD_TESTS "Whether or not to build the tests" ON)

if (GRAPHTHEWY_BUILD_TESTS)
    find_package(Criterion)
    include(CTest)
    enable_testing()
    if(CRITERION_FOUND)
        include_directories(${CRITERION_INCLUDE_DIRS})
        target_link_libraries(${CRITERION_LIBRARIES})
    endif()
    add_subdirectory(tests)
endif()

install(FILES src/include/UndirectedGraph.hpp src/include/UndirectedGraphCycle.hpp DESTINATION include/graphthewy)
