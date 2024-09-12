set(TARGET_NAME 4_PPTStatusBar)

set(SOURCES 
    main.cpp
    mainwindow.cpp
)

add_executable(${TARGET_NAME} ${SOURCES} main.qrc)
target_link_libraries(${TARGET_NAME} PUBLIC 
    Qt6::Core Qt6::Widgets
)


