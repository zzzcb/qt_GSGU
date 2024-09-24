set(TARGET_NAME 1_Button)

set(SOURCES 
    main.cpp
)

add_executable(${TARGET_NAME} ${SOURCES} demo.qrc)
target_link_libraries(${TARGET_NAME} PUBLIC 
    Qt6::Core Qt6::Widgets
)

add_executable(1_Button_custombutton main2.cpp custombutton.cpp)
target_link_libraries(1_Button_custombutton PUBLIC 
    Qt6::Core Qt6::Widgets
)
