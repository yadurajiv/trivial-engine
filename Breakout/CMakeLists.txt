include_directories(${TRIVIAL_INCLUDE_DIR} ${SFML_INCLUDE_PATH})
link_directories(${SFML_INCLUDE_PATH})


include_directories(${TINYXML_INCLUDE_PATH})

#set(TINYXML_INCLUDE_PATH ${PROJECT_SOURCE_DIR}/extlibs/tinyxml)

#include_directories(${TINYXML_INCLUDE_PATH})

add_executable(BreakOut main.cpp)

target_link_libraries(BreakOut TrivialEngine
	${OpenGL_LIBRARY}
	
)