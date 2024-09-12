set(TARGET_NAME 5_OrangeSplash)

set(SOURCES 
    main.cpp
    demo.cpp
    splashscreen.cpp
)

add_executable(${TARGET_NAME} ${SOURCES} demo.qrc)
target_link_libraries(${TARGET_NAME} PUBLIC 
    Qt6::Core Qt6::Widgets
)


