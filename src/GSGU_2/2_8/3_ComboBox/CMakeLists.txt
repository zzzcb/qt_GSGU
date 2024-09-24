set(TARGET_NAME 3_ComboBox)

set(SOURCES 
    main.cpp
)

add_executable(${TARGET_NAME} ${SOURCES})
target_link_libraries(${TARGET_NAME} PUBLIC 
    Qt6::Core Qt6::Widgets
)

add_executable(3_ComboBox_Theme
    main_switch_theme.cpp
    theme.qrc
    config.cpp
    icon.cpp
    mainwindow.cpp
)
target_link_libraries(3_ComboBox_Theme PUBLIC 
    Qt6::Core Qt6::Widgets
)

