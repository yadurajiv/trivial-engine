include_directories(${TRIVIAL_INCLUDE_DIR} ${SFML_INCLUDE_PATH})
link_directories(${SFML_INCLUDE_PATH})




#set(TINYXML_LIB ${TINYXML_INCLUDE_PATH}/libtinyxml2.a)

include_directories(${TINYXML_INCLUDE_PATH})

FIND_LIBRARY(TINYXML_LIB
    NAMES libtinyxml2.a libtinyxml2.dylib
    PATHS
    ${PROJECT_SOURCE_DIR}/extlibs/tinyxml2
    DOC "TinyXML Library"
)


#include_directories(${TINYXML_INCLUDE_PATH})

add_executable(TrivialTest main.cpp)

target_link_libraries(TrivialTest TrivialEngine ${TINYXML_LIB})

