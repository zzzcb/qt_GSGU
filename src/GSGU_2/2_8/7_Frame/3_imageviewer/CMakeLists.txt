
add_executable(7_Frame_3_ImageViewer
    main_imageviewer.cpp 
    mainwindow.cpp
    imageresource.cpp
    imageviewer.cpp
    imageviewer.qrc
)
target_link_libraries(7_Frame_3_ImageViewer PUBLIC 
    Qt6::Core Qt6::Widgets
)