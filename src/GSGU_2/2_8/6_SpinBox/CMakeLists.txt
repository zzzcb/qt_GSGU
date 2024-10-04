set(TARGET_NAME 6_SpinBox)

set(SOURCES 
    main.cpp
)

add_executable(${TARGET_NAME} ${SOURCES})
target_link_libraries(${TARGET_NAME} PUBLIC 
    Qt6::Core Qt6::Widgets
)

add_executable(6_SpinBox_Pdf
    main_pdf.cpp
    mainwindow.h
    mainwindow.cpp
    pdf.qrc
)
target_link_libraries(6_SpinBox_Pdf PUBLIC 
    Qt6::Core Qt6::Widgets Qt6::PdfWidgets
)


