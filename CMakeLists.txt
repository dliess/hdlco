cmake_minimum_required(VERSION 3.9)

project(hdlc
  VERSION 1.0.2
  LANGUAGES CXX
)

include(cmake/CPM.cmake)

# Enable/disable testing
option(TESTS_ENABLED "Enable automatic tests" OFF)
set(LIBRARY_OUTPUT_PATH "${CMAKE_BINARY_DIR}/lib")
set(EXECUTABLE_OUTPUT_PATH "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_MODULE_PATH ${CMAKE_BINARY_DIR})

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
add_compile_options("-Wall" "-Wextra" "-Werror" "$<$<CONFIG:RELEASE>:-O3>")

if (NOT CMAKE_BUILD_TYPE)
    message(STATUS "No build type selected, defaulting to Debug")
    set(CMAKE_BUILD_TYPE "Debug")
endif()

CPMFindPackage(
  NAME fmt
  GITHUB_REPOSITORY fmtlib/fmt
  GIT_TAG 5.2.1
)
if(fmt_ADDED)
  add_library(fmt::fmt ALIAS fmt)
endif()

CPMFindPackage(
  NAME spdlog
  GITHUB_REPOSITORY gabime/spdlog
  GIT_TAG v1.2.1
)
if(spdlog_ADDED)
  add_library(spdlog::spdlog ALIAS spdlog)
endif()


CPMFindPackage(
  NAME Boost
  GITHUB_REPOSITORY boostorg/boost
  GIT_TAG boost-1.68.0
)
if(Boost_ADDED)
  add_library(boost INTERFACE)
  target_include_directories(boost INTERFACE 
    "${boost_SOURCE_DIR}/libs/circular_buffer/include/"
    "${boost_SOURCE_DIR}/libs/crc/include/"
    "${boost_SOURCE_DIR}/libs/asio/include/"
    "${boost_SOURCE_DIR}/libs/config/include/"
    "${boost_SOURCE_DIR}/libs/integer/include/"
    "${boost_SOURCE_DIR}/libs/static_assert/include/"
    "${boost_SOURCE_DIR}/libs/system/include/"
    "${boost_SOURCE_DIR}/libs/predef/include/"
    "${boost_SOURCE_DIR}/libs/assert/include/"
    "${boost_SOURCE_DIR}/libs/core/include/"
    "${boost_SOURCE_DIR}/libs/throw_exception/include/"
    "${boost_SOURCE_DIR}/libs/date_time/include/"
    "${boost_SOURCE_DIR}/libs/smart_ptr/include/"
    "${boost_SOURCE_DIR}/libs/utility/include/"
    "${boost_SOURCE_DIR}/libs/type_traits/include/"
    "${boost_SOURCE_DIR}/libs/mpl/include/"
    "${boost_SOURCE_DIR}/libs/preprocessor/include/"
    "${boost_SOURCE_DIR}/libs/numeric/conversion/include/"
    "${boost_SOURCE_DIR}/libs/bind/include/"
    "${boost_SOURCE_DIR}/libs/regex/include/"
    "${boost_SOURCE_DIR}/libs/container/include/"
    "${boost_SOURCE_DIR}/libs/move/include/"
    "${boost_SOURCE_DIR}/libs/intrusive/include/"
    "${boost_SOURCE_DIR}/libs/concept_check/include/"
    "${boost_SOURCE_DIR}/libs/iterator/include/"
    "${boost_SOURCE_DIR}/libs/detail/include/"
  )
  add_library(Boost::boost ALIAS boost)
endif()

option(HDLCO_BUILD_TESTS "Build with tests" ON)
option(HDLCO_BUILD_EXAMPLES "Build with examples" OFF)

add_subdirectory(${PROJECT_NAME})

if(HDLCO_BUILD_EXAMPLES)
  add_subdirectory(example)
endif()
if(HDLCO_BUILD_TESTS)
  find_package(Threads REQUIRED)
  
  CPMFindPackage(
    NAME catch2
    GITHUB_REPOSITORY catchorg/Catch2
    GIT_TAG v2.4.1
  )
  if(catch2_ADDED)
    add_library(Catch2::Catch2 ALIAS Catch2)
  endif()

  add_subdirectory(test)
endif()
