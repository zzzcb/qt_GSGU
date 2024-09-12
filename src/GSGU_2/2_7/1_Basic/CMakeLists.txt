set(TARGET_NAME 1_Basic)

set(SOURCES 
    main.cpp
    mypushbutton.cpp
    mystyle.cpp
)

add_executable(${TARGET_NAME} ${SOURCES} demo.qrc)
target_link_libraries(${TARGET_NAME} PUBLIC 
    Qt6::Core Qt6::Widgets
)



