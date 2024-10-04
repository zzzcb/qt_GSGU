
find_package(PCL REQUIRED)
find_package(VTK REQUIRED)

add_executable(7_Frame_2_PointCloud 
    main_pointcloud.cpp 
    mainwindow.cpp
)
target_link_libraries(7_Frame_2_PointCloud PUBLIC 
    Qt6::Core Qt6::Widgets Qt6::OpenGLWidgets Qt6::Concurrent
    ${PCL_LIBRARIES}
    ${VTK_LIBRARIES}
)