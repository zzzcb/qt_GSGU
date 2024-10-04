set(TARGET_NAME 4_Dialog)

set(SOURCES 
    main.cpp
)

add_executable(${TARGET_NAME} ${SOURCES})
target_link_libraries(${TARGET_NAME} PUBLIC 
    Qt6::Core Qt6::Widgets
)

add_executable(4_Dialog_Palette main_palette.cpp palettedialog.cpp)
target_link_libraries(4_Dialog_Palette PUBLIC 
    Qt6::Core Qt6::Widgets
)

add_executable(4_Dialog_Calib
    main_wizard.cpp 
    calibwizard.cpp
    calibwizard.qrc
)
target_link_libraries(4_Dialog_Calib PUBLIC 
    Qt6::Core Qt6::Widgets
)

