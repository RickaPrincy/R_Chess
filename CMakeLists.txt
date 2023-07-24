cmake_minimum_required(VERSION 3.10)

project(R_Chess)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
set(SOURCES_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(INCLUDES_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})
include_directories(${SDL2_IMAGE_INCLUDE_DIRS})

file(GLOB SOURCES "${SOURCES_DIR}/*.cpp" "${SOURCES_DIR}/*.c")
file(GLOB HEADERS "${INCLUDES_DIR}/*.h" "${INCLUDES_DIR}/*.hh" "${INCLUDES_DIR}/*.hpp")
 
add_executable(R_Chess WIN32 ${SOURCES} ${HEADERS})
target_link_libraries(R_Chess ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES})

file(GLOB IMAGES "${CMAKE_CURRENT_SOURCE_DIR}/graphics/*")
file(COPY ${IMAGES} DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/graphics/")