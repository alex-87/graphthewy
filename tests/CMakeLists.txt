## Copyright (C) 2020, 2021 Alexis LE GOADEC.

## This file is part of the Graphthewy project which is licensed under
## the European Union Public License v1.2.

## If a copy of the EUPL v1.2 was not distributed with this software,
## you can obtain one at : https://joinup.ec.europa.eu/collection/eupl/eupl-text-eupl-12


add_executable(test_int test_int.cpp)
add_executable(test_char test_char.cpp)
add_executable(test_string test_string.cpp)
add_executable(test_ullint test_ullint.cpp)

add_executable(test_d_int test_d_int.cpp)
add_executable(test_d_char test_d_char.cpp)
add_executable(test_d_string test_d_string.cpp)
add_executable(test_d_ullint test_d_ullint.cpp)

target_link_libraries(test_int CppUTest CppUTestExt)
target_link_libraries(test_char CppUTest CppUTestExt)
target_link_libraries(test_string CppUTest CppUTestExt)
target_link_libraries(test_ullint CppUTest CppUTestExt)
target_link_libraries(test_d_int CppUTest CppUTestExt)
target_link_libraries(test_d_char CppUTest CppUTestExt)
target_link_libraries(test_d_string CppUTest CppUTestExt)
target_link_libraries(test_d_ullint CppUTest CppUTestExt)

add_test(NAME "test_int" COMMAND test_int)
add_test(NAME "test_char" COMMAND test_char)
add_test(NAME "test_string" COMMAND test_string)
add_test(NAME "test_ullint" COMMAND test_ullint)
add_test(NAME "test_d_int" COMMAND test_d_int)
add_test(NAME "test_d_char" COMMAND test_d_char)
add_test(NAME "test_d_string" COMMAND test_d_string)
add_test(NAME "test_d_ullint" COMMAND test_d_ullint)
