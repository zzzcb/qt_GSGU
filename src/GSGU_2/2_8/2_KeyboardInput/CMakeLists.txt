set(TARGET_NAME 2_KeyboardInput)

set(SOURCES 
    main.cpp
)

add_executable(${TARGET_NAME} ${SOURCES})
target_link_libraries(${TARGET_NAME} PUBLIC 
    Qt6::Core Qt6::Widgets
)

add_executable(2_ShortCut_Mainwindow 
    mainwindow.cpp
    keyboarddialog.cpp
    main_shortcut.cpp
)
target_link_libraries(2_ShortCut_Mainwindow PUBLIC 
    Qt6::Core Qt6::Widgets
)


