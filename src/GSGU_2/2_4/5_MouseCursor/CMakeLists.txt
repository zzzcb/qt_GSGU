set(TARGET_NAME 5_MouseCursor)

set(SOURCES 
    main.cpp
)

add_executable(${TARGET_NAME} ${SOURCES} cursor.qrc)
target_link_libraries(${TARGET_NAME} PUBLIC 
    Qt6::Core Qt6::Widgets
)
