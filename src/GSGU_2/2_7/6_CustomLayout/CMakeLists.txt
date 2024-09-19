set(TARGET_NAME 6_CustomLayout)

set(SOURCES 
    main.cpp
    "myhlayout.cpp"
)

add_executable(${TARGET_NAME} ${SOURCES})
target_link_libraries(${TARGET_NAME} PUBLIC 
    Qt6::Core Qt6::Widgets
)

add_executable(6_FlowLayout main_test_flow.cpp flowlayout.cpp)
target_link_libraries(6_FlowLayout PUBLIC 
    Qt6::Core Qt6::Widgets
)
