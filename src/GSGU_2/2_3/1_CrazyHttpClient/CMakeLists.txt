set(TARGET_NAME 1_CrazyHttpClient)

set(SOURCES 
    main.cpp
)

add_executable(${TARGET_NAME} ${SOURCES})
target_link_libraries(${TARGET_NAME} PUBLIC 
    Qt6::Core Qt6::Widgets Qt6::Network
)


