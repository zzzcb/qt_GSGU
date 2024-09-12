#######################################################################
# Find all necessary and optional qt_GSGU dependencies
#######################################################################

# qt,安装Qt6,并将bin路径添加到环境变量中。cmake查找过程是会到bin的上级中的lib中查找的，所以可以找到Qt6Config.cmake
find_package(Qt6 REQUIRED COMPONENTS Core Widgets Concurrent Network)
qt_standard_project_setup()                 # Qt6标准工程配置（会开启自动MOC和UIC）
set(CMAKE_AUTORCC ON)                       # 开启自动RCC

# OpenCV,Windows平台固定目录配置OpenCV依赖,后序就可以使用头文件和Lib了
if(MSVC)
	set(OpenCV_INC_DIR "D:/dependency/OPENCV346/include")
	set(OpenCV_LIBS "D:/dependency/OPENCV346/x64/vc15/lib/opencv_world346.lib")
endif()







