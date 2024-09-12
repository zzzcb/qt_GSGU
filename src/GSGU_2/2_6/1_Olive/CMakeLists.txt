set(TARGET_NAME 1_Olive)

file(GLOB_RECURSE  PANEL_SRC "panel/*.cpp")
file(GLOB_RECURSE  WINDOW_SRC "window/*.cpp")

set(SOURCES 
    main.cpp
    ${PANEL_SRC}
    ${WINDOW_SRC}
)

add_executable(${TARGET_NAME} ${SOURCES})
target_link_libraries(${TARGET_NAME} PUBLIC 
    Qt6::Core Qt6::Widgets
)
target_include_directories(${TARGET_NAME} PUBLIC 
    "panel" 
    "window"
)


