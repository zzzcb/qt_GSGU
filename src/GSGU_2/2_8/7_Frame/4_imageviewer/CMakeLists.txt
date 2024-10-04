
add_executable(7_Frame_4_ImageViewer
    main_imageviewer.cpp 
    mainwindow.cpp
    imageviewer.cpp
    imageviewer.qrc
)
target_link_libraries(7_Frame_4_ImageViewer PUBLIC 
    Qt6::Core Qt6::Widgets
)