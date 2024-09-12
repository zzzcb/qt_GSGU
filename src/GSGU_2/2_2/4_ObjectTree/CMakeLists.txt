set(TARGET_NAME 4_ObjectTree)

set(SOURCES 
    main.cpp
    mybutton.cpp
)

add_executable(${TARGET_NAME} ${SOURCES})
target_link_libraries(${TARGET_NAME} PUBLIC 
    Qt6::Core Qt6::Widgets
)


