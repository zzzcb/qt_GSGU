set(TARGET_NAME 1_QssDemo)

set(SOURCES 
    main.cpp
    vs2017_solution.cpp
)

add_executable(${TARGET_NAME} ${SOURCES} vs2017_solution.qrc)
target_link_libraries(${TARGET_NAME} PUBLIC 
    Qt6::Core Qt6::Widgets
)


