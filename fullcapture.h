#ifndef FULLCAPTURE_H
#define FULLCAPTURE_H

#include <QObject>
#include <QQuickWindow>
#include <qqml.h>
#include <QMainWindow>
#include "imageprovider.h"
#include "reccapture.h"


class FullCapture:public QMainWindow
{
    Q_OBJECT
public:
    explicit FullCapture(QMainWindow *parent=0);
    //活动窗口截图
//    void activeCapture();
    ImageProvider *imgProvider;

    //利用命令行参数获取顶层窗口的wid，exec对命令汗参数进行解析
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
    void cutRecScreen(QPixmap pixmap);
    void cutContinueScreen();
    void cutNailScreen();

    void startActiveCapture();
    void startFullScreen();
    void startRecCapture();
    void startContinueCapture();
    void startNailCapture();

private:
    QImage m_img;
    RecCapture *m_recCapture;
};

#endif // FULLCAPTURE_H
