

add_executable(7_Frame_1_qframe main_1_qframe.cpp "3_splitter/main_hsplitter.cpp")
target_link_libraries(7_Frame_1_qframe PUBLIC 
    Qt6::Core Qt6::Widgets
)


add_subdirectory(2_pointcloud)
add_subdirectory(3_splitter)
add_subdirectory(4_imageviewer)
