
add_executable(7_Frame_2_HSplitter
    mainwindow.cpp
    main_hsplitter.cpp
)
target_link_libraries(7_Frame_2_HSplitter PUBLIC 
    Qt6::Core Qt6::Widgets
)

add_executable(7_Frame_2_Splitter
    mainwindow2.cpp
    main_splitter.cpp
)
target_link_libraries(7_Frame_2_Splitter PUBLIC 
    Qt6::Core Qt6::Widgets
)