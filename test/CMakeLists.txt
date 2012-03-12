include_directories(${TRIVIAL_INCLUDE_DIR} ${SFML_INCLUDE_PATH})
link_directories(${SFML_INCLUDE_PATH})


include_directories(${TINYXML_INCLUDE_PATH})

#set(TINYXML_INCLUDE_PATH ${PROJECT_SOURCE_DIR}/extlibs/tinyxml)

#include_directories(${TINYXML_INCLUDE_PATH})

add_executable(TrivialTest main.cpp)

target_link_libraries(TrivialTest TrivialEngine)

