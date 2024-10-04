set(TARGET_NAME 5_Slider)

set(SOURCES 
    main.cpp
)

add_executable(${TARGET_NAME} ${SOURCES})
target_link_libraries(${TARGET_NAME} PUBLIC 
    Qt6::Core Qt6::Widgets
)

find_package(FFMPEG REQUIRED
  COMPONENTS
  avutil
  avcodec
  avformat
  avfilter
  swscale
  swresample
)

add_executable(5_Slider_Audio 
    main_audio.cpp
    mainwindow.cpp
    audiodecoder.cpp
    waveformwidget.cpp
    audioplayer.cpp
    "global.cpp"
    audiosplit.qrc
)
target_link_libraries(5_Slider_Audio PUBLIC 
    Qt6::Core 
    Qt6::Widgets
    Qt6::Multimedia
    FFMPEG::avutil
    FFMPEG::avcodec
    FFMPEG::avformat
    FFMPEG::avfilter
    FFMPEG::swscale
    FFMPEG::swresample
)

