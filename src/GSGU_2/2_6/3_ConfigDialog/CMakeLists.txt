set(TARGET_NAME 3_ConfigDialog)

set(SOURCES 
    main.cpp
    configdialog.cpp
    pages.cpp
)

add_executable(${TARGET_NAME} ${SOURCES} configdialog.qrc)
target_link_libraries(${TARGET_NAME} PUBLIC 
    Qt6::Core Qt6::Widgets
)


