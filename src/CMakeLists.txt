set(R_CHESS_SOURCES
    main.cpp
    rchess.cpp
    pieces/pieces.cpp
    pieces/rook.cpp
    pieces/knight.cpp
    pieces/bishop.cpp
    pieces/queen.cpp
    pieces/king.cpp
    pieces/pawn.cpp
    config/config.cpp
    case/case.cpp
    board/board.cpp
    ui/rect.cpp
    events/events.cpp)

add_executable(${R_CHESS_BIN_NAME} ${R_CHESS_SOURCES})

# target_link
target_link_libraries(
  ${R_CHESS_BIN_NAME}
  PUBLIC sdlk
  PRIVATE SDL2
  PRIVATE SDL2_image
  PRIVATE SDL2_ttf)

# set properties
set_target_properties(
  ${R_CHESS_BIN_NAME}
  PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
             SOVERSION ${R_CHESS_BIN_VERSION_MAJOR}
             VERSION ${R_CHESS_BIN_VERSION})

if(R_CHESS_BIN_INSTALL)
  include(CMakePackageConfigHelpers)
  write_basic_package_version_file(
    ${CMAKE_BINARY_DIR}/cmake/${R_CHESS_BIN_NAME}Version.cmake
    VERSION ${R_CHESS_VERSION}
    COMPATIBILITY SameMajorVersion)

  include(GNUInstallDirs)

  install(
    TARGETS ${R_CHESS_BIN_NAME}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
            COMPONENT Runtime
            BINRARY
            DESTINATION ${CMAKE_INSTALL_BINDIR}
            COMPONENT Development
    ARCHIVE DESTINATION ${CMAKE_INSTALL_BINDIR} COMPONENT Development)
endif()
