#-------------------------------------------------------------------
# This file is part of the CMake build system for qt_GSGU
#-------------------------------------------------------------------

# 1.CMake 版本要求
cmake_minimum_required(VERSION 3.16)

# 2.工程配置
project(qt_GSGU VERSION 2.0)

# 3.全局选项配置
set(CMAKE_CXX_STANDARD 17)  	            # 全局C++版本
# 设置默认构建类型为 Release
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()

set(RESOURCE_DIR "${CMAKE_SOURCE_DIR}/resources")

# 4.包含子模块(.cmake),以便后面include就可以直接引用子模块【include大致相当于c++中的宏替换】
set(CMAKE_MODULE_PATH 
    "${CMAKE_SOURCE_DIR}/cmake"
)

# 5.第三方包配置
include(Dependencies)

# 6.子文件夹配置
add_subdirectory(src)
# add_subdirectory(docs) 					# HTML文档生成
