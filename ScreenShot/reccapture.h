#ifndef RECCAPTURE_H
#define RECCAPTURE_H

#include <QWidget>
#include <QPainter>

#include "painteditem.h"
#include "mylabel.h"


extern QImage image;

enum CaptureState{
    InitCapture = 0,
    BeginCaptureImage,
    FinishCaptureImage,
    BeginMoveCaptureArea,
    FinishMoveCaptureArea,
    BeginMoveStretchRect,
    FinishMoveStretchRect,
    FinishCapture
}; //进行截屏的状态;

enum StretchRectState{
    NotSelect = 0,
    TopLeftRect,
    TopRightRect,
    BottomLeftRect,
    BottomRightRect,
    LeftCenterRect,
    TopCenterRect,
    RightCenterRect,
    BottomCenterRect
};// 当前鼠标所在顶点状态;

class RecCapture : public QWidget
{
    Q_OBJECT
public:
    explicit RecCapture(QWidget *parent = nullptr);


    ~RecCapture();
signals:
    // 通知截图完毕，并将截取图片传递给调用类;
    void signalCompleteCapture(QPixmap captureImage);
    //通知连续截图完成
    void signalCompleteContinue();
    //通知钉图完成
    void signalCompleteNail();
    //通知放弃截取图片
    void signalNull();

private:
    void initWindow();
    void loadBackgroundPixmap();
    void initStretchRect();

    QRect getRect(const QPoint &beginPoint, const QPoint &endPoint);
    QRect getMoveRect();
    QRect getSelectRect();
    QRect getStretchRect();
    bool isPressPointInSelectRect(QPoint mousePressPoint);
    QPoint getMovePoint();
    StretchRectState getStrethRectState(QPoint point);
    void setStretchCursorStyle(StretchRectState stretchRectState);

    void drawCaptureImage();
    void drawStretchRect();

    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void paintEvent(QPaintEvent *event);

    void drawSelectRectInfo();
    void drawEndPointImage();

public:
    QPixmap m_capturePixmap;

private:
    bool m_isMousePress;
    QPixmap m_loadPixmap;
    int m_screenwidth;
    int m_screenheight;
    QPainter m_painter;

    // 保存确定选区的坐标点;
    QPoint  m_beginPoint,m_endPoint,m_beginMovePoint, m_endMovePoint;
    // 保存当前截图状态;
    CaptureState m_currentCaptureState;
    // 当前选择区域矩形;
    QRect m_currentSelectRect;
    // 选中矩形8个顶点小矩形;
    QRect m_topLeftRect, m_topRightRect, m_bottomLeftRect, m_bottomRightRect;
    QRect m_leftCenterRect, m_topCenterRect, m_rightCenterRect, m_bottomCenterRect;
    // 当前鼠标所在顶点状态;
    StretchRectState m_stretchRectState;

    //保存要截取的矩形
    QVector<QPixmap> *pixs;
    QVector<QString> *curtimes;
    //截取下来的图片保存的文件名
    QString m_filename;
    //当前时间
    QString strtime;

    MyLabel *labelimage;
};

#endif // RECCAPTURE_H
