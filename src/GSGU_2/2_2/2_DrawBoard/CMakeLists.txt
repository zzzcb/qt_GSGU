set(TARGET_NAME 2_DrawBoard)

set(SOURCES 
    main.cpp
    mydrawboard2.cpp
)

add_executable(${TARGET_NAME} ${SOURCES})
target_link_libraries(${TARGET_NAME} PUBLIC 
    Qt6::Core Qt6::Widgets
)


