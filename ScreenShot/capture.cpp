#include "capture.h"
#include <QImage>
#include <QWindow>
#include <QApplication>
#include <QScreen>
#include <QDebug>
#include <QClipboard>
#include <string>
#include <iostream>
#include <stdio.h>

Capture::Capture(QMainWindow *parent)
    :QMainWindow(parent)
{
    imgProvider=new ImageProvider();
    startFullScreen();
}

//开始活动窗口截图
void Capture::startActiveCapture()
{

    //得到窗口的wid,string类型的16进制
    std::string  string=exec(" xprop -root | awk '/_NET_ACTIVE_WINDOW\\(WINDOW\\)/{print $NF}'").c_str();
 const char *c=string.data();
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

std::string Capture::exec(const char *cmd)
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
void Capture::startFullScreen()
{
    QPixmap pixmap;
    QScreen *screen=QApplication::primaryScreen();
    pixmap=screen->grabWindow(0);

    QImage img=pixmap.toImage();
    imgProvider->img=img.copy(img.rect());

    img.save("/tmp/1.jpg");

    emit callImgChanged();
}

void Capture::cutScreen(QPixmap pixmap)
{
    QImage img=pixmap.toImage();
    imgProvider->img=img.copy(img.rect());

    img.save("/tmp/1.jpg");

    //发送信号 将截取的图片在界面显示
    emit callImgChanged();
    //发送信号 告知qml矩形截屏结束
    emit finishCapture();
}

void Capture::cutNull()
{
    //发送信号 告知qml截屏结束
    //或 不返回图片给界面
    emit finishCapture();
}

void Capture::cutNailScreen(QPixmap pixmap)
{
    m_nailImage=new MyLabel();

    if(!pixmap.toImage().isNull()){
        qDebug()<<"所截的图不是空的!!";
        qDebug()<<"宽："<<pixmap.width()<<"高："<<pixmap.height();
    }

    m_nailImage->setimagetolabel(pixmap);
    m_nailImage->setFixedSize(pixmap.width(),pixmap.height());

    //钉在桌面
    m_nailImage->show();

    //发送信号 告知qml钉图结束
    emit finishCapture();
}

//开始矩形截图
void Capture::startRecCapture()
{
    qDebug()<<"开始矩形截图";
    m_recCapture = new RecCapture();
    connect(m_recCapture,SIGNAL(signalCompleteCapture(QPixmap)),
            this,SLOT(cutScreen(QPixmap)));
    connect(m_recCapture,SIGNAL(signalNull()),
            this,SLOT(cutNull()));
    m_recCapture->show();
}

//开始连续截图
void Capture::startContinueCapture()
{
    m_recCapture=new RecCapture;
    connect(m_recCapture,SIGNAL(signalCompleteContinue()),
            this,SLOT(cutNull()));
    connect(m_recCapture,SIGNAL(signalNull()),
            this,SLOT(cutNull()));
    m_recCapture->show();

}

//开始钉图
void Capture::startNailCapture()
{
    m_recCapture=new RecCapture;
    connect(m_recCapture,SIGNAL(signalCompleteCapture(QPixmap)),
            this,SLOT(cutNailScreen(QPixmap)));
    connect(m_recCapture,SIGNAL(signalNull()),
            this,SLOT(cutNull()));
    m_recCapture->show();
}

void Capture::startFreeCapture()
{
    m_freeCapture=new FreeCapture;
    connect(m_freeCapture,SIGNAL(signalCompleteCapture(QPixmap)),
            this,SLOT(cutScreen(QPixmap)));
    m_freeCapture->show();
}

void Capture::copytoClip()
{
    QImage img;
    img.load("/tmp/1.jpg");
    QApplication::clipboard()->setImage(img);
}

void Capture::captureLongPicture()
{
    m_myWidget=new MyWidget();
    connect(m_myWidget,&MyWidget::closewidget,
            this,&Capture::stopLongcapture);
    m_myWidget->showFullScreen();
}

void Capture::stopLongcapture(QImage img)
{
    imgProvider->img=img;
    img.save("/tmp/1.jpg");

    //发送信号 将矩形截取的图片在界面显示
    emit callImgChanged();
    emit finishCapture();
}

