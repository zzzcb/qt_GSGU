set(TARGET_NAME 8_TopWindow)

set(SOURCES 
    main.cpp
)

add_executable(${TARGET_NAME} ${SOURCES} window.qrc)
target_link_libraries(${TARGET_NAME} PUBLIC 
    Qt6::Core Qt6::Widgets
)
