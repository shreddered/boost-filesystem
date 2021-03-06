cmake_minimum_required(VERSION 3.4)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(BUILD_COVERAGE "Build coverage" OFF)

set(
  HUNTER_CACHE_SERVERS
  "https://github.com/bmstu-iu8-cpp-sem-3/hunter-cache"
  CACHE STRING "Default cache server"
)

include("tools/gate/cmake/HunterGate.cmake")

HunterGate(
  URL "https://github.com/cpp-pm/hunter/archive/v0.23.278.tar.gz"
  SHA1 "35fa55bc1dfcf9f4d7264f8bb26cd1759ce1ae07"
)

project(lab-04)
string(APPEND CMAKE_CXX_FLAGS " -pedantic -Werror -Wall -Wextra")
string(APPEND CMAKE_CXX_FLAGS " -Wno-unused-command-line-argument")
string(APPEND CMAKE_CXX_FLAGS " -Wshadow -Wnon-virtual-dtor")

# GTest
hunter_add_package(GTest)
find_package(GTest CONFIG REQUIRED)

# Boost libraries
hunter_add_package(Boost COMPONENTS system filesystem program_options)
find_package(Boost CONFIG REQUIRED system filesystem program_options)

# libftp_analyzer
add_library(libftp_analyzer
  ${CMAKE_CURRENT_SOURCE_DIR}/sources/ftp_analyzer.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/sources/broker_stats.cpp
)

target_include_directories(libftp_analyzer
  PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(libftp_analyzer
  PUBLIC Boost::system
  Boost::filesystem
)

# Optional
if (UNIX)
  # no liblib prefix on unix systems
  set_target_properties(libftp_analyzer PROPERTIES
    PREFIX ""
    OUTPUT_NAME "libftp_analyzer"
  )
elseif(WIN32)
  # no prefix at all at windows systems
  set_target_properties(libftp_analyzer PROPERTIES
    PREFIX ""
    OUTPUT_NAME "ftp_analyzer"
  )
endif()

# ftp_analyzer executable
add_executable(ftp_analyzer
  ${CMAKE_CURRENT_SOURCE_DIR}/sources/main.cpp
)

target_link_libraries(ftp_analyzer
  PRIVATE libftp_analyzer
  Boost::program_options
)

# unit tests
add_executable(tests
  ${CMAKE_CURRENT_SOURCE_DIR}/tests/test.cpp
)

target_include_directories(tests 
  PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_definitions(tests
  PRIVATE "TEST_FTP_PATH=\"${CMAKE_CURRENT_SOURCE_DIR}/misc\""
)

target_link_libraries(tests GTest::gtest_main libftp_analyzer)

# file(RENAME misc/ ${CMAKE_CURRENT_BINARY_DIR}/misc)
enable_testing()
add_test(NAME unit_tests COMMAND tests) 

if(BUILD_COVERAGE)
  set(ENABLE_COVERAGE ON CACHE BOOL "Enable coverage build." FORCE)
  list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
  find_package(codecov)
  add_coverage(libftp_analyzer)
  add_coverage(ftp_analyzer)
  add_coverage(tests)
  list(APPEND LCOV_REMOVE_PATTERNS "'${PROJECT_SOURCE_DIR}/tests/*'")
  coverage_evaluate()
endif()
