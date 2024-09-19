set(TARGET_NAME 1_BuiltinLayout)

set(SOURCES 
    main.cpp 
    hwidget.cpp
    vwidget.cpp
    gridwidget.cpp
    formwidget.cpp
    stackwidget.cpp
)

add_executable(${TARGET_NAME} ${SOURCES})
target_link_libraries(${TARGET_NAME} PUBLIC 
    Qt6::Core Qt6::Widgets
)
