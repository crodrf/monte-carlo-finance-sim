cmake_minimum_required(VERSION 3.10)
project(QuantSim)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include directories for headers
include_directories(include)

# Main source files
set(SOURCES
        src/main.cpp
        src/monte_carlo_simulation.cpp
        src/payoff.cpp
        src/payoff_factory.cpp
        src/statistical_strategy.cpp
)

# Add headers (optional, helps IDEs recognize header files in the project)
set(HEADERS
        include/monte_carlo_simulation.h
        include/payoff.h
        include/payoff_decorator.h
        include/payoff_factory.h
        include/statistical_strategy.h
        include/thread_pool.h
)

# Create main application executable
add_executable(QuantSim ${SOURCES} ${HEADERS})

# Google Test setup with conditional download
find_package(GTest)

if(NOT GTest_FOUND)
    include(FetchContent)
    FetchContent_Declare(
            googletest
            URL https://github.com/google/googletest/archive/refs/tags/release-1.11.0.zip
    )
    FetchContent_MakeAvailable(googletest)
    set(GTEST_LIBRARIES GTest::gtest GTest::gtest_main)
    set(GTEST_INCLUDE_DIRS ${gtest_SOURCE_DIR}/include)
else()
    set(GTEST_LIBRARIES GTest::GTest GTest::Main)
endif()

# Include directories for GTest
include_directories(${GTEST_INCLUDE_DIRS})

# Test source files
set(TEST_SOURCES
        tests/test_payoff.cpp
        tests/test_payoff_factory.cpp
        tests/test_thread_pool.cpp
        tests/test_monte_carlo_simulation.cpp
        src/monte_carlo_simulation.cpp
        src/payoff.cpp
        src/payoff_factory.cpp
        src/statistical_strategy.cpp
)

# Create test executable
add_executable(QuantSim_tests ${TEST_SOURCES} ${HEADERS})
target_link_libraries(QuantSim_tests ${GTEST_LIBRARIES})

# Enable testing and register tests
enable_testing()
add_test(NAME QuantSim_tests COMMAND QuantSim_tests)