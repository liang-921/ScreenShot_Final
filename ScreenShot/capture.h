#ifndef CAPTURE_H
#define CAPTURE_H

#include <QObject>
#include <QQuickWindow>
#include <qqml.h>
#include <QMainWindow>
#include "imageprovider.h"
#include "reccapture.h"
#include "freecapture.h"
#include "mywidget.h"


class Capture:public QMainWindow
{
    Q_OBJECT
public:
    explicit Capture(QMainWindow *parent=0);
    //活动窗口截图
//    void activeCapture();
    ImageProvider *imgProvider;

    //利用命令行参数获取顶层窗口的wid，exec对命令行参数进行解析
    std::string exec(const char* cmd);


    Q_INVOKABLE void delay(int time){
        clock_t now=clock();
        while(clock()-now<time){
        }
    }

signals:
    void callImgChanged();
    void finishCapture();

public slots:
    void cutScreen(QPixmap pixmap);
    void cutNull();
    void cutNailScreen(QPixmap pixmap);

    void startActiveCapture();
    void startFullScreen();
    void startRecCapture();
    void startContinueCapture();
    void startNailCapture();
    void startFreeCapture();
    void copytoClip();

    void captureLongPicture();

    void stopLongcapture(QImage img);


private:
    QImage m_img;
    RecCapture *m_recCapture;
    FreeCapture *m_freeCapture;
    MyLabel *m_nailImage;
    MyWidget *m_myWidget;
};


#endif // CAPTURE_H
