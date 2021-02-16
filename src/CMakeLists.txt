add_executable(cyber-recorder
    main.cpp
    audiorecorder.cpp
    audioplayer.cpp
    recordingmodel.cpp
    audioprober.cpp
    utils.cpp
    settingsmodel.cpp
    qml.qrc
)

target_link_libraries(cyber-recorder
    PRIVATE
    Qt5::Core
    Qt5::Quick
    Qt5::Multimedia
    MeuiKit
)

file(GLOB TS_FILES translations/*.ts)
qt5_create_translation(QM_FILES ${TS_FILES})
add_custom_target(translations DEPENDS ${QM_FILES} SOURCES ${TS_FILES})
add_dependencies(${PROJECT_NAME} translations)

install(TARGETS cyber-recorder RUNTIME DESTINATION /usr/bin)
install(FILES ${QM_FILES} DESTINATION /usr/share/${PROJECT_NAME}/translations)
