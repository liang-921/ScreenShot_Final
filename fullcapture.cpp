#include "fullcapture.h"
#include <QGuiApplication>
#include <QImage>
#include <QWindow>
#include <QApplication>
#include <QScreen>
#include <QDebug>
#include <string>
#include <iostream>
#include <stdio.h>

FullCapture::FullCapture(QMainWindow *parent)
    :QMainWindow(parent)
{
    imgProvider=new ImageProvider();
    startFullScreen();
}

//开始活动窗口截图
void FullCapture::startActiveCapture()
{

    //得到窗口的wid,string类型的16进制
    std::string  string=exec(" xprop -root | awk '/_NET_ACTIVE_WINDOW\\(WINDOW\\)/{print $NF}'").c_str();
    char *c=string.data();
    char *stop;
    WId id=std::strtol(c,&stop,16);

    qDebug()<<"窗口ID："<<id;

    QPixmap pixmap;
    QScreen *screen=QApplication::primaryScreen();

    this->setCursor(Qt::ArrowCursor);  //显示正常鼠标
    pixmap=screen->grabWindow(id);
    imgProvider->img=pixmap.toImage();

    QImage img=pixmap.toImage();

    img.save("/tmp/1.jpg");

    //发送信号 将矩形截取的图片在姐妹显示
    emit callImgChanged();
    //发送信号 告知qml矩形截屏结束
    emit finishCapture();
}

std::string FullCapture::exec(const char *cmd)
{
    FILE* pipe = popen(cmd, "r");
    if (!pipe) return "ERROR";
    char buffer[128];
    std::string result = "";
    while(!feof(pipe)) {
        if(fgets(buffer, 128, pipe) != NULL)
                result += buffer;
    }
    pclose(pipe);
    return result;
}

//开始全屏截图
void FullCapture::startFullScreen()
{
    QPixmap pixmap;
    QScreen *screen=QApplication::primaryScreen();

    this->setCursor(Qt::ArrowCursor);  //显示正常鼠标

    pixmap=screen->grabWindow(0);

//    pixmap=screen->grabWindow(71303186);
    imgProvider->img=pixmap.toImage();

    QImage img=pixmap.toImage();
    img.save("/tmp/1.jpg");

    emit callImgChanged();
}

void FullCapture::cutRecScreen(QPixmap pixmap)
{

    imgProvider->img=pixmap.toImage();

    QImage img=pixmap.toImage();
    img.save("/tmp/1.jpg");

    //发送信号 将矩形截取的图片在姐妹显示
    emit callImgChanged();
    //发送信号 告知qml矩形截屏结束
    emit finishCapture();
}

void FullCapture::cutContinueScreen()
{
    //发送信号 告知qml连续截屏结束
    emit finishCapture();
}

void FullCapture::cutNailScreen()
{
    //发送信号 告知qml钉图结束
    emit finishCapture();
}

//开始矩形截图
void FullCapture::startRecCapture()
{
    qDebug()<<"开始矩形截图";
    m_recCapture = new RecCapture();
    connect(m_recCapture,SIGNAL(signalCompleteCapture(QPixmap)),
            this,SLOT(cutRecScreen(QPixmap)));
    m_recCapture->show();
}

//开始连续截图
void FullCapture::startContinueCapture()
{
    m_recCapture=new RecCapture;
    connect(m_recCapture,SIGNAL(signalCompleteContinue()),
            this,SLOT(cutContinueScreen()));
    m_recCapture->show();

}

//开始钉图
void FullCapture::startNailCapture()
{
    m_recCapture=new RecCapture;
    connect(m_recCapture,SIGNAL(signalCompleteNail()),
            this,SLOT(cutNailScreen()));
    m_recCapture->show();
}

