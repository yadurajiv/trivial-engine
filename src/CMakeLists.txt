set(SRCROOT ${PROJECT_SOURCE_DIR}/src)

set(SRC
    ${SRCROOT}/TrivialAnimatedSprite.cpp
    ${SRCROOT}/TrivialAnimatedSprite.h
    ${SRCROOT}/TrivialApp.cpp
    ${SRCROOT}/TrivialApp.h
    ${SRCROOT}/TrivialAudioManager.cpp
    ${SRCROOT}/TrivialAudioManager.h
    ${SRCROOT}/TrivialAudioResource.h
    ${SRCROOT}/TrivialBox2D.cpp
    ${SRCROOT}/TrivialBox2D.h
	${SRCROOT}/TrivialButton.h
    ${SRCROOT}/TrivialCamera.cpp
    ${SRCROOT}/TrivialCamera.h
	${SRCROOT}/TrivialCanvas.cpp
	${SRCROOT}/TrivialCanvas.h
    ${SRCROOT}/TrivialEngine.h
    ${SRCROOT}/TrivialEventManager.cpp
    ${SRCROOT}/TrivialEventManager.h
    ${SRCROOT}/TrivialFontManager.cpp
    ${SRCROOT}/TrivialFontManager.h
    ${SRCROOT}/TrivialGUIObject.cpp
    ${SRCROOT}/TrivialGUIObject.h
    ${SRCROOT}/TrivialGUIText.cpp
    ${SRCROOT}/TrivialGUIText.h
    ${SRCROOT}/TrivialGraphicsObject.cpp
    ${SRCROOT}/TrivialGraphicsObject.h
    ${SRCROOT}/TrivialHelper.h
    ${SRCROOT}/TrivialImageManager.cpp
    ${SRCROOT}/TrivialImageManager.h
    ${SRCROOT}/TrivialObject.cpp
    ${SRCROOT}/TrivialObject.h
    ${SRCROOT}/TrivialScene.cpp
    ${SRCROOT}/TrivialScene.h
    ${SRCROOT}/TrivialSceneManager.cpp
    ${SRCROOT}/TrivialSceneManager.h
    ${SRCROOT}/TrivialSceneObject.cpp
    ${SRCROOT}/TrivialSceneObject.h
    ${SRCROOT}/TrivialSprite.cpp
    ${SRCROOT}/TrivialSprite.h
	${SRCROOT}/TrivialSettings.cpp
	${SRCROOT}/TrivialSettings.h
#    ${SRCROOT}/TrivialShapes.cpp
#    ${SRCROOT}/TrivialShapes.h
#    ${SRCROOT}/TrivialTileMap.cpp
#    ${SRCROOT}/TrivialTileMap.h
)

include_directories(${SFML_INCLUDE_PATH})
# include_directories(${TINYXML_INCLUDE_PATH})


add_library(TrivialEngine ${SRC})


target_link_libraries(TrivialEngine ${SFML_AUDIO_LIB} 
            ${SFML_GRAPHICS_LIB} 
            ${SFML_NETWORK_LIB} 
            ${SFML_SYSTEM_LIB}
            ${SFML_WINDOW_LIB}
#            ${TINYXML_LIB}
)
            