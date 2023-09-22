cmake_minimum_required(VERSION 3.19)

project(hello_fuzz)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)

FetchContent_Declare(
    fuzztest
    GIT_REPOSITORY https://github.com/google/fuzztest.git
    GIT_TAG main 
)
FetchContent_MakeAvailable(fuzztest)

enable_testing()

include(GoogleTest)

fuzztest_setup_fuzzing_flags()

add_executable(
    run_tests
    hello_fuzz.cpp
)

link_fuzztest(run_tests)
gtest_discover_tests(run_tests)