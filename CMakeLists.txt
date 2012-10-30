cmake_minimum_required(VERSION 2.6)

project(Trivial)

set(TRIVIAL_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/src)
set(TRIVIAL_LIB_DIR ${PROJECT_SOURCE_DIR}/src)

FIND_PATH(SFML_INCLUDE_PATH SFML
	DOC "The directory where SFML include files reside"
)

FIND_LIBRARY(SFML_AUDIO_LIB
    NAMES sfml-audio.2.0
    DOC "SFML Audio Library"
)
    
FIND_LIBRARY(SFML_GRAPHICS_LIB
    NAMES sfml-graphics.2.0
    DOC "SFML Graphics Library"
)

FIND_LIBRARY(SFML_NETWORK_LIB
    NAMES sfml-network.2.0
    DOC "SFML Network Library"
)

FIND_LIBRARY(SFML_SYSTEM_LIB
    NAMES sfml-system.2.0
    DOC "SFML System Library"
)

FIND_LIBRARY(SFML_WINDOW_LIB
    NAMES sfml-window.2.0
    DOC "SFML Window Library"
)

   FIND_LIBRARY(OpenGL_LIBRARY OpenGL )

set(TINYXML_INCLUDE_PATH ${PROJECT_SOURCE_DIR}/extlibs/tinyxml)

FIND_LIBRARY(TINYXML_LIB
    NAMES tinyxml
    PATHS
    ${PROJECT_SOURCE_DIR}/extlibs/tinyxml
    DOC "TinyXML Library"
)

add_subdirectory(extlibs/tinyxml)

add_subdirectory(src)

add_subdirectory(test)

add_subdirectory(Breakout)

add_subdirectory(Asteroid)

add_subdirectory(byog12)
