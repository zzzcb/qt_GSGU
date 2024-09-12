set(TARGET_NAME 4_ArgParser)

set(SOURCES 
    main.cpp
    demo.cpp
)

add_executable(${TARGET_NAME} ${SOURCES} demo.qrc)
target_link_libraries(${TARGET_NAME} PUBLIC 
    Qt6::Core Qt6::Widgets
)


