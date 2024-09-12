set(TARGET_NAME 2_SimpleHttpServer)

set(SOURCES 
    main.cpp
    webserver.cpp
)

add_executable(${TARGET_NAME} ${SOURCES})
target_link_libraries(${TARGET_NAME} PUBLIC 
    Qt6::Core Qt6::Widgets Qt6::Network
)


