cmake_minimum_required(VERSION 3.18)

project(rchess VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Download git submodule
message(STATUS "Updating all submodules recursively...")
execute_process(
  COMMAND git submodule update --init --recursive
  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
  RESULT_VARIABLE res
  OUTPUT_VARIABLE out
  ERROR_VARIABLE err
  OUTPUT_STRIP_TRAILING_WHITESPACE
  ERROR_STRIP_TRAILING_WHITESPACE
)
if(NOT res EQUAL 0)
  message(WARNING "Recursive submodule update failed: ${err}")
else()
  message(STATUS "All submodules updated recursively.")
endif()

set(R_CHESS_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(R_CHESS_IS_MAIN_PROJECT OFF)
if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
  set(R_CHESS_IS_MAIN_PROJECT ON)
endif()

# target names
set(R_CHESS_BIN_NAME rchess)
set(R_CHESS_BIN_VERSION 0.0.1)
set(R_CHESS_BIN_VERSION_MAJOR 0)
set(R_CHESS_VERSION ${PROJECT_VERSION})
set(R_CHESS_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})

# configure build type
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Debug")
endif()

if(WIN32)
  add_compile_options(WIN32)
endif()

add_subdirectory(sources)
add_subdirectory(external/sdlk)

file(GLOB IMAGES "${CMAKE_CURRENT_SOURCE_DIR}/assets/*")
file(COPY ${IMAGES} DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/assets/")

# clang-format configuration
find_program(CLANG_FORMAT_EXECUTABLE NAMES clang-format)
if(CLANG_FORMAT_EXECUTABLE)
  file(
    GLOB_RECURSE
    ALL_SOURCE_FILES
    "${R_CHESS_SOURCE_DIR}/sources/*.cpp"
    "${R_CHESS_SOURCE_DIR}/sources/*.hpp"
    "${R_CHESS_SOURCE_DIR}/sources/case/*.cpp"
    "${R_CHESS_SOURCE_DIR}/sources/case/*.hpp"
    "${R_CHESS_SOURCE_DIR}/sources/board/*.cpp"
    "${R_CHESS_SOURCE_DIR}/sources/board/*.hpp"
    "${R_CHESS_SOURCE_DIR}/sources/pieces/*.cpp"
    "${R_CHESS_SOURCE_DIR}/sources/components/*.cpp"
    "${R_CHESS_SOURCE_DIR}/sources/components/*.hpp"
    "${R_CHESS_SOURCE_DIR}/sources/pieces/*.hpp"
    "${R_CHESS_SOURCE_DIR}/sources/moves/*.hpp"
    "${R_CHESS_SOURCE_DIR}/sources/moves/*.cpp"
    "${R_CHESS_SOURCE_DIR}/sources/ui/*.cpp"
    "${R_CHESS_SOURCE_DIR}/sources/fonts/*.cpp"
    "${R_CHESS_SOURCE_DIR}/sources/fonts/*.hpp"
    "${R_CHESS_SOURCE_DIR}/sources/ui/*.hpp")
  add_custom_target(
    clang-format
    COMMAND ${CLANG_FORMAT_EXECUTABLE} -i -style=file ${ALL_SOURCE_FILES}
    COMMENT "Running clang-format")
else()
  message(
    WARNING "clang-format not found. Clang-format target will not be available."
  )
endif()

# CPack configuration
set(CPACK_PACKAGE_VENDOR "RickaPrincy <rckprincy@gmail.com>")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY R_Chess is a simple chessboard)
include(CPack)
