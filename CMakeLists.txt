cmake_minimum_required(VERSION 3.18)

project(rchess VERSION 0.0.1)

find_package(sdlk REQUIRED VERSION 0.0.3)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

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

add_subdirectory(src)

file(GLOB IMAGES "${CMAKE_CURRENT_SOURCE_DIR}/assets/*")
file(COPY ${IMAGES} DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/assets/")

# clang-format configuration
find_program(CLANG_FORMAT_EXECUTABLE NAMES clang-format)
if(CLANG_FORMAT_EXECUTABLE)
  file(
    GLOB_RECURSE
    ALL_SOURCE_FILES
    "${R_CHESS_SOURCE_DIR}/src/*.cpp"
    "${R_CHESS_SOURCE_DIR}/src/*.hpp"
    "${R_CHESS_SOURCE_DIR}/src/case/*.cpp"
    "${R_CHESS_SOURCE_DIR}/src/case/*.hpp"
    "${R_CHESS_SOURCE_DIR}/src/board/*.cpp"
    "${R_CHESS_SOURCE_DIR}/src/board/*.hpp"
    "${R_CHESS_SOURCE_DIR}/src/pieces/*.cpp"
    "${R_CHESS_SOURCE_DIR}/src/components/*.cpp"
    "${R_CHESS_SOURCE_DIR}/src/components/*.hpp"
    "${R_CHESS_SOURCE_DIR}/src/pieces/*.hpp"
    "${R_CHESS_SOURCE_DIR}/src/moves/*.hpp"
    "${R_CHESS_SOURCE_DIR}/src/moves/*.cpp"
    "${R_CHESS_SOURCE_DIR}/src/ui/*.cpp"
    "${R_CHESS_SOURCE_DIR}/src/fonts/*.cpp"
    "${R_CHESS_SOURCE_DIR}/src/fonts/*.hpp"
    "${R_CHESS_SOURCE_DIR}/src/ui/*.hpp")
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
