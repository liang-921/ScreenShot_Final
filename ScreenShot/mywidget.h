#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/imgproc/types_c.h>
#include <opencv2/imgcodecs/legacy/constants_c.h>
#include <QWidget>
class MouseThread;
class QPushButton;
class QLabel;

namespace Ui {
class MyWidget;
}
class MyWidget : public QWidget
{
    Q_OBJECT

public:
    MyWidget(QWidget *parent = nullptr);
    ~MyWidget();
private slots:
    void on_wheelMove(int flags,int dir);
    void on_releaseEvent();
    void on_startButtonPressed();
    void on_endButtonPressed();
signals:
    void releaseEvent();
    void closewidget(QImage img);
private:
    //鼠标移动事件
    void mouseMoveEvent(QMouseEvent *event);
    //鼠标释放事件
    void mouseReleaseEvent(QMouseEvent *event);
    //鼠标按下事件
    void mousePressEvent(QMouseEvent *);
    //绘画事件
    void paintEvent(QPaintEvent * event);

    void keyPressEvent(QKeyEvent *event);
private:
    //将所画的矩形区域给扣出来
    QImage cutRectImage(QImage img);
    //找到所画矩形的起始点和终止点
    QRect findRect();
    //比较两张图片
    void compareImage();
    //裁剪图片
    void cutImage(int dir);
    void stickImage(QImage hecheng,QImage imgNew);
    void cutTopandBotton(QImage one,QImage two);
    //将QImage类型转换为cv::Mat类型
    cv::Mat qim2mat(QImage qim);
    void computeMoveH(int dir);

    //鼠标的起始点和终止点
    QPoint m_startPoint={0,0};
    QPoint m_endPoint={0,0};

    //检测是否被按下
    bool m_isPress=false;
    //检测开始按钮是否被点击
    bool m_isStart=false;
    //检测是不是第二次进行截图
    bool m_isSecond=false;

    const char *  dev="/dev/input/mice";
    QImage m_imgOrigin;
    QImage m_imgNew;
    QImage m_hecheng;
    QObject* m_obj;

    //裁剪头部后的两张图片
    QImage m_imgone;
    QImage m_imgtwo;
    //两张图片从头开始相同的长度,也就是寻找有没有相同的头
    QRect *picDiff;
    int moveH=0;

    //检测向上的距离是否超过向下的距离
    int m_flag=0;

    bool m_isStartup=false;
    bool m_isStartdown=false;

    //保存第一张图片
    QImage m_start;

    //利用线程检测鼠标滚轮事件
    MouseThread *m_thread;

    //开始按钮和结束按钮
    QPushButton *m_startButton;
    QPushButton *m_endButton;

    //合成的图片预览模式
    QLabel *m_previewMode;

    Ui::MyWidget *ui;
};

#endif // MYWIDGET_H
