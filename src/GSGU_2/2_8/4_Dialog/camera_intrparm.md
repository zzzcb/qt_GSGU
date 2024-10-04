**相机内参**（Camera Intrinsics）是描述相机成像特性的重要参数，主要用于计算三维世界坐标与图像平面坐标之间的关系。相机内参的理解对于相机标定、计算机视觉和图像处理等领域至关重要。
相机内参矩阵一般表示如下:
> 
<div style="text-align: center;">
<img src="qrc:/images/matrix.png" width="114" height="56" />
</div>

其中<span style="font-style: italic;">f<sub>x</sub></span>和<span style="font-style: italic;">f<sub>y</sub></span>
分别对应于水平方向和垂直方向的焦距。焦距影响图像的放大程度。

其中<span style="font-style: italic;">c<sub>x</sub></span>和<span style="font-style: italic;">c<sub>y</sub></span>
代表图像传感器上光轴与图像平面的交点。理想情况下，主点应位于图像中心。

通常描述内参还应包含畸变系数，主要分为径向畸变和切向畸变。常见的畸变模型包括：径向畸变（k1, k2, k3）和切向畸变（p1, p2）

**综上,一般内参标定结果将包含上述的内参矩阵和畸变系数**