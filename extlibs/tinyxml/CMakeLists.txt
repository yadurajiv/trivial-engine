set(TINYXMLROOT ${PROJECT_SOURCE_DIR}/extlibs/tinyxml)

set(TINYXMLSRC
    ${TINYXMLROOT}/tinyxml.cpp
    ${TINYXMLROOT}/tinyxml.h
    ${TINYXMLROOT}/tinyxmlerror.cpp
    ${TINYXMLROOT}/tinyxmlparser.cpp
    ${TINYXMLROOT}/tinystr.cpp
    ${TINYXMLROOT}/tinystr.h
)

add_library(TinyXML ${TINYXMLSRC})
