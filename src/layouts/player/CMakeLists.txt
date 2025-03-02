# Generated from player.pro.

cmake_minimum_required(VERSION 3.16)
project(player LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

if(NOT DEFINED INSTALL_EXAMPLESDIR)
  set(INSTALL_EXAMPLESDIR "examples")
endif()

set(INSTALL_EXAMPLEDIR "${INSTALL_EXAMPLESDIR}/multimediawidgets/player")

find_package(Qt6 COMPONENTS Network)
find_package(Qt6 COMPONENTS MultimediaWidgets)

qt_add_executable(player
    histogramwidget.cpp histogramwidget.h
    main.cpp
    player.cpp player.h
    playercontrols.cpp playercontrols.h
    playlistmodel.cpp playlistmodel.h
    videowidget.cpp videowidget.h
    qmediaplaylist.cpp qmediaplaylist.h qmediaplaylist_p.h
    qplaylistfileparser.cpp qplaylistfileparser_p.h
)
set_target_properties(player PROPERTIES
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE TRUE
)
target_link_libraries(player PUBLIC
    Qt::MultimediaWidgets
    Qt::Network
)

install(TARGETS player
    RUNTIME DESTINATION "${INSTALL_EXAMPLEDIR}"
    BUNDLE DESTINATION "${INSTALL_EXAMPLEDIR}"
    LIBRARY DESTINATION "${INSTALL_EXAMPLEDIR}"
)
