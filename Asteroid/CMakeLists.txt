include_directories(${TRIVIAL_INCLUDE_DIR} ${SFML_INCLUDE_PATH})
link_directories(${SFML_INCLUDE_PATH})


include_directories(${TINYXML_INCLUDE_PATH})

FIND_LIBRARY(TINYXML_LIB
    NAMES libtinyxml2.a libtinyxml2.dylib
    PATHS
    ${PROJECT_SOURCE_DIR}/extlibs/tinyxml2
    DOC "TinyXML Library"
)

#set(TINYXML_INCLUDE_PATH ${PROJECT_SOURCE_DIR}/extlibs/tinyxml)

#include_directories(${TINYXML_INCLUDE_PATH})

add_executable(Asteroid main.cpp)

target_link_libraries(Asteroid TrivialEngine
	${OpenGL_LIBRARY} ${TINYXML_LIB}
	
)
