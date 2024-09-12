set(TARGET_NAME 4_EventHandle)

set(SOURCES 
    main.cpp
)

add_executable(${TARGET_NAME} ${SOURCES} handle.qrc)
target_link_libraries(${TARGET_NAME} PUBLIC 
    Qt6::Core Qt6::Widgets
)


