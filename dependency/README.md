# vcpkg如何编译依赖


## **安装vcpkg** 
> vcpkg是一个强大的包管理工具。再通俗一点，就是它帮助我们下载源代码，并完成目标平台的编译构建。作为开发者，我们只需要输入vcpkg install xxx，我们就可以得到编译好的基础库（dll,lib,h,xxxConfig.cmake）。在我们的上层工程中，直接使用即可，极大的简化了C++开发的构建流程。

- 从github克隆vcpkg仓库。
之所以通过克隆的方式，是因为默认的vcpkg只安装最新版本的三方库。如果想要安装指定版本的三方库，就需要进行一些变基的操作，这就需要通过克隆的方式把完整的仓库拉到本地。
- 初始化vcpkg，通过仓库中的bootstrap-vcpkg.bat。如下图：
![image](https://img2024.cnblogs.com/blog/1600711/202409/1600711-20240917105721856-607698419.png)
它会下载安装好一个vcpkg.exe到同级目录
- 安装完成


2. **配置vcpkg环境变量**。把vcpkg仓库目录添加到系统环境变量
![image](https://img2024.cnblogs.com/blog/1600711/202409/1600711-20240917110213280-1276079711.png)


## 举个栗子(以PCL为例)
>通过**vcpkg.json**的方式安装依赖，并使用**triplet**来指定编译选项
>- vcpkg.json中可以指定依赖名称，基线版本
>- triplet选项，可以指定编译的选项，例如只安装release版本

1. 新建目录pcl_dep，用于最终存放所有依赖,拷贝本仓库中的vcpkg.json和x64-windows-release.cmake到该目录中
2. cmd进入pcl_dep，执行**vcpkg x-update-baseline**，更新到最新基线。命令执行完成，我们可以看到vcpkg.json中的baseline字段就自动更新到了最新
3. 接下来，就可以安装依赖了，cmd进入pcl_dep,执行**vcpkg install --triplet x64-windows-release**
4. 等待安装完成即可。
5. 拷贝bin include lib share tool等,到pcl_dep中,即形成了最终的依赖包

## 配置依赖
将安装好的依赖配置到环境变量，方便后序编译时CMake的查找,参考下图
![image](https://img2024.cnblogs.com/blog/1600711/202409/1600711-20240917115534860-1231602056.png)
