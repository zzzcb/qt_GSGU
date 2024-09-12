#######################################################################
# Find all necessary and optional qt_GSGU dependencies
#######################################################################

# qt,��װQt6,����bin·����ӵ����������С�cmake���ҹ����ǻᵽbin���ϼ��е�lib�в��ҵģ����Կ����ҵ�Qt6Config.cmake
find_package(Qt6 REQUIRED COMPONENTS Core Widgets Concurrent Network)
qt_standard_project_setup()                 # Qt6��׼�������ã��Ὺ���Զ�MOC��UIC��
set(CMAKE_AUTORCC ON)                       # �����Զ�RCC

# OpenCV,Windowsƽ̨�̶�Ŀ¼����OpenCV����,����Ϳ���ʹ��ͷ�ļ���Lib��
if(MSVC)
	set(OpenCV_INC_DIR "D:/dependency/OPENCV346/include")
	set(OpenCV_LIBS "D:/dependency/OPENCV346/x64/vc15/lib/opencv_world346.lib")
endif()







