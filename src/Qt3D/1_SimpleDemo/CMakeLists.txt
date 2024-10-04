set(TARGET_NAME 3D_1_SimpleDemo)

set(SOURCES 
    main.cpp
    
)

find_package(Qt6 REQUIRED COMPONENTS 3DCore 3DRender 3DInput 3DExtras  Core Widgets Gui)
add_executable(${TARGET_NAME} ${SOURCES})
target_link_libraries(${TARGET_NAME} PUBLIC 
    Qt::3DCore
    Qt::3DRender
    Qt::3DInput
    Qt::3DExtras
    Qt::Core
    Qt::Widgets
    Qt::Gui
)