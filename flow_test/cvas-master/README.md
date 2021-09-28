# CVAS
![Hardware](https://img.shields.io/badge/Hardware-Nividia%20Jetson%20NX-green)
![os](https://img.shields.io/badge/os-Ubuntu-yellow)
![build](https://img.shields.io/badge/build-fail-red)
![Language](https://img.shields.io/badge/Language-cpp%2017-brightgreen)

Computer Vision Assistant System (CVAS)

请在自己的分支上进行开发，阶段性开发完成后发起mater merge请求。

稍后我会更新你所需要实现的函数的声明，而你需要做的是完成函数的定义。

如果你发现已有的bug，欢迎提出pull request！
## build

```console
mkdir build
cd build
cmake ..
make
```

## 检测模块
- [ ] 使用光流法实现车辆形式视频分析
    - [ ] 在全静止画面的情况下分析
    - [ ] 在车辆行驶的情况下分析
    - [ ] 在车辆静止，其他车辆或路人走动的情况下分析
    - [ ] 返回的结果需使用网络通信模块所提供的数据结构进行封装
## code
你需要完成的函数定义在src/car_status.cpp中，为：
```c++
[[noreturn]] void car_status(int camera_id, std::vector<CarStatusData>& msg_pool, std::mutex& locker);
```
其中camera_id为你所被分配到的摄像头，现在测试可以不使用这个参数，而是使用视频替代摄像头；

msg_pool为与通信模块共享的消息池，CarStatusData定义在include/data.hpp中，你只需要写入car_status数据即可，其中1为行驶中，0为静止；

locker为多线程锁。

## 光流法
光流（optical flow）是空间运动物体在观察成像平面上的像素运动的瞬时速度。

光流法是利用图像序列中像素在时间域上的变化以及相邻帧之间的相关性来找到上一帧跟当前帧之间存在的对应关系，从而计算出相邻帧之间物体的运动信息的一种方法。

简而言之，光流 $F_{t\rightarrow t+1}[x]$ 指明了x位置上的像素在t到t+1时的位移，所以在t+1时刻，原本在x位置上的像素移动到了x + $F_{t\rightarrow t+1}[x]$位置上。

所以我们可以通过光流法来判断画面中物体的运动信息！但是获取了画面中的每个像素运动信息之后，如何确定车辆（摄像头）是否移动，需要额外判断。

### 光流的预估
光流的预估是CV的热门话题之一，现在我们使用opencv中自带的光流预估算法来获取光流，当然你可以选择PWC-Net等性能更加优异的深度学习算法，但是如何在快发板上得到速度与精度的平衡，需要你自己把握。

opencv中光流的获取有以下几种方法：
- calcOpticalFlowPyrLK：通过金字塔Lucas-Kanade 光流方法计算某些点集的光流（稀疏光流）。想要深入理解的话，可以参考这篇论文：”Pyramidal Implementation of the Lucas Kanade Feature TrackerDescription of the algorithm”。
- calcOpticalFlowFarneback：用Gunnar Farneback 的算法计算稠密光流（即图像上所有像素点的光流都计算出来）。它的相关论文是："Two-Frame Motion Estimation Based on PolynomialExpansion"。
- CalcOpticalFlowBM：通过块匹配的方法来计算光流。
- CalcOpticalFlowHS：用Horn-Schunck 的算法计算稠密光流。相关论文是这篇：”Determining Optical Flow”。
- calcOpticalFlowSF：这一个是ECCV2012的一篇文章的实现："SimpleFlow: A Non-iterative, Sublinear Optical FlowAlgorithm"，工程网站是：http://graphics.berkeley.edu/papers/Tao-SAN-2012-05/  在OpenCV新版本中有引入。

光流的获取和可视化可以参考 optical_flow_example.cpp

### 测试数据集
正在收集