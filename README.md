# ScreenShot_Final
  ![](https://img.shields.io/github/issues/liang-921/ScreenShot_Final)
  ![](https://img.shields.io/github/forks/liang-921/ScreenShot_Final)
  ![](https://img.shields.io/github/stars/liang-921/ScreenShot_Final)
<div align=center><img src="https://github.com/liang-921/ScreenShot_Final/blob/main/效果演示/logo.png" width="200" height="200" /></div>
    
    多功能图片编辑器--截屏

这是一个linux环境下的基于QT的截屏及图片编辑项目

## 开发环境

 基于Qt和OpenCv，使用Qml和C++交互 官网地址:https://www.qt.io

    Qt: 5.12.2
 
 Qt 5.12.2下载地址:

 https://download.qt.io/archive/qt/5.12/5.12.2/

请选择正确的操作系统版本

OpenCv 下载地址：

https://github.com/opencv/opencv/releases/tag/4.5.3

下载安装包后，解压缩进入该目录，执行下列命令安装：
  
    mkdir build
    cd bulid
    cmake -D CMAKE_BUILD_TYPE=Release -D CMAKE_INSTALL_PREFIX = /usr/local ..
    sudo make -j 8
    make install

 配置环境：
  
    用 vim 打开 /ect/ld.so.conf , 注意用sudo打开获得权限，不然无法修改。
    在文件中加上一行/usr/local/lib /usr/local 是opencv的安装路径加了之后的 变为
<div align=center><img src="https://github.com/liang-921/ScreenShot_Final/blob/main/效果演示/123.png" /></div>
    

### 上手指南

 将项目源码克隆到本地，使用Qt Creator进行编译运行
 
## 演示预览

<div align=center><img src="https://github.com/liang-921/ScreenShot_Final/blob/main/效果演示/rec.png" /></div>
    
    区域截图

<div align=center><img src="https://github.com/liang-921/ScreenShot_Final/blob/main/效果演示/edit.png" /></div>
    
    编辑界面
    
## 功能说明
    
    1. 屏幕截取方式： 全屏截取，矩形截取，不规则截取，活动窗口截取，连续截取，钉在桌面，长截屏
    2. 选择在屏幕截取时，是否隐藏当前应用窗口
    3. 在1,2的基础上，设置了延时处理
    4. 对截取的图片即时注释编辑，可以自由裁剪，自定义选择画笔的颜色和粗细进行涂鸦，画框，画矩形，椭圆，直线，添加文字等操作
    5. 在图片编辑过程中，可撤销上一步操作及一键清除所有操作
    6. 实时进行图片保存和另存为操作，自定义选择图片保存格式，默认情况下，图片保存到/root/tmp/目录下，以当时系统时间命名
    7. 除从屏幕截取获得图片外，可导入本地图片进行编辑操作
    8. 连接系统打印机，可对图片进行打印操作
    9. 在系统已安装相应第三方应用程序的情况下，可将图片进行复制到粘贴板，一键分享至QQ,微信(网页版)，邮箱等，也可直接在Ctrl+V将图片粘贴
    10.屏幕录制：全屏录制，区域录屏
，
## 目前已知问题

    1.由于linux系统性能不同，在进行屏幕录制时，部分系统会出现黑屏现象。
    2.opencv库链接问题，后续将继续改进。

## 后续要加的功能

    1.实现多屏幕截图
    2.对屏幕所截取的图片进行文字提取，并将文字保存在剪贴板中
    3.自定义对图片进行多张编辑合成
    4.将图片钉在桌面上后，可对图片进行二次编辑

## 如何参与开源项目

 贡献使开源社区成为一个学习、激励和创造的绝佳场所。您所作的任何贡献都是非常感谢的。

    1.Fork the Project
    2.Create your Feature Branch (git checkout -b main)
    3.Commit your Changes (git commit -m 'Add some commit')
    4.Push to the Branch (git push origin main)
    5.Open a Pull Request

## 版本控制
 
 本项目使用Git进行版本管理。您可以在仓库中查看当前可用版本。
 
## 作者
    email:2304768518@qq.com   qq:2304768518
