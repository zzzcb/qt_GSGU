# qt_GSGU
```
    QQQQ     TTTTTTTTTTTTTT     GGGGG         SSSSS       GGGGG      UU      UU
  QQ    QQ         TT         GG            SS          GG           UU      UU
 QQ      QQ        TT        GG            SS          GG            UU      UU
QQ        QQ       TT       GG      GGGGGG   SSSSSS   GG      GGGGGG UU      UU
 QQ   QQ QQ        TT        GG       GG           SS  GG       GG   UU      UU
  QQ    QQ         TT         GG     GGG          SS    GG     GGG   UU      UU
    QQQQ  QQ       TT          GGGGGG  G     SSSSS       GGGGGG  G    UUUUUUUU
```

### 介绍
欢迎来到qt_GSGU,这里是Qt Framework相关教程代码仓库，致力于带你从入门到"放弃"(doge)。 教程按照**模块**、**继承结构**等思路进行构建。
> 关于GSGU,它是Getting Started to Giving Up的缩写,以对应自称“从入门到精通”的书籍、教程、视频。

> 视频链接: https://www.bilibili.com/video/BV1824y1d7kM

> PPT链接: https://pan.baidu.com/s/1aqZLghVKhk0K6h6r2k-KKw?pwd=g8uu

### 工程代码说明
- 构建工具采用CMake(>=3.16)
- Qt版本采用Qt6.7.2
- VS版本采用VS2022(可选,也可以使用vs code)

### 章节目录
```
├─GSGU_1                            //Qt简介、相关工具安装及使用,见视频
│  └─1_1
│      └─1_SimpleShow 
├─GSGU_2
│  ├─2_1                            //2.1 Widgets体系概述、Qt命名空间、编程规范
│  │  └─1_NameSpace
│  ├─2_2                            //2.2 QObject之事件系统、信号和槽、对象树、计时功能
│  │  ├─1_DrawBoard                 
│  │  ├─2_DrawBoard
│  │  ├─3_DrawBoard
│  │  ├─4_ObjectTree
│  │  └─5_Timer
│  ├─2_3                            //2.3 Application相关
│  │  ├─1_CrazyHttpClient
│  │  ├─2_SimpleHttpServer
│  │  ├─3_MagicObject
│  │  │  └─images
│  │  └─4_ArgParser
│  │      └─images
│  ├─2_4                            //2.4 QWidget-所有可视化控件的基石
│  │  ├─1_WidgetPos
│  │  ├─2_ChildWidget
│  │  ├─3_MinMaxSize
│  │  ├─4_EventHandle
│  │  │  └─images
│  │  ├─5_MouseCursor
│  │  │  └─images
│  │  ├─6_ParentChild
│  │  ├─7_ZOrder
│  │  ├─8_TopWindow
│  │  │  └─images
│  │  ├─9_WindowState
│  │  ├─10_InfoShow
│  │  ├─11_FocusControl
│  │  ├─12_SignalSlot
│  │  └─13_CoordConvert
│  ├─2_5                            //2.5 QSS-控件也爱美
│  │  └─1_QssDemo
│  │      └─images
│  ├─2_6                            //2.6 主窗口—QMainWindow相关
│  │  ├─1_Olive
│  │  │  ├─panel
│  │  │  │  ├─audiopanel
│  │  │  │  ├─footagepanel
│  │  │  │  ├─nodepanel
│  │  │  │  ├─parampanel
│  │  │  │  ├─projectpanel
│  │  │  │  ├─sequencepanel
│  │  │  │  ├─timelinepanel
│  │  │  │  └─toolpanel
│  │  │  └─window
│  │  ├─2_TextEditor
│  │  │  └─images
│  │  ├─3_ConfigDialog
│  │  │  └─images
│  │  ├─4_PPTStatusBar
│  │  │  └─images
│  │  ├─5_OrangeSplash
│  │  │  └─images
│  │  └─6_MdiArea
│  ├─2_7                            //2.7 布局系统
│  │  ├─1_BuiltinLayout
│  │  ├─2_LayoutAllocate
│  │  ├─3_LayoutAdjust
│  │  ├─4_LayoutNest
│  │  ├─5_LayoutDynamic
│  │  └─6_CustomLayout
│  └─2_8                            //2.8 Widgets控件体系
│      ├─1_Button
│      │  └─images
│      ├─2_KeyboardInput
│      ├─3_ComboBox
│      │  └─images
│      ├─4_Dialog
│      │  └─images
│      ├─5_Slider
│      │  └─images
│      ├─6_SpinBox
│      │  └─images
│      └─7_Frame
│          ├─2_splitter
│          ├─3_imageviewer
│          │  └─images
│          └─4_pointcloud
└─Qt3D                              //Qt3D基础
    ├─1_SimpleDemo
    ├─2_AxisDemo
    ├─3_PlaneDemo
    ├─4_LineDemo
    ├─5_GridDemo
    └─6_CameraController
```
