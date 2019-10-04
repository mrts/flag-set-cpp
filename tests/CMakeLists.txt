cmake_minimum_required(VERSION 3.8.0)

project(flag-set)

# Common compile options.

set(CMAKE_CXX_STANDARD 14)

if(MSVC)
  add_compile_options(/W4 /WX)
else(MSVC)
  add_compile_options(-Wall -Wextra -pedantic -Werror)
endif(MSVC)

# Tests with Google Test.

enable_testing()

find_package(GTest REQUIRED)

set(TEST_EXE ${PROJECT_NAME}-test)

include_directories(../include)

add_executable(${TEST_EXE}
  src/${PROJECT_NAME}-tests.cpp
)

target_link_libraries(${TEST_EXE}
  GTest::GTest GTest::Main
)

add_test(${TEST_EXE} ${TEST_EXE})
