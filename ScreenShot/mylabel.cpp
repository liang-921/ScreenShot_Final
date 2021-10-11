#include "mylabel.h"

MyLabel::MyLabel()
{
    Qt::WindowFlags nType = Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint;
    setWindowFlags(nType);
}

void MyLabel::setimagetolabel(QPixmap pixmap)
{
    setPixmap(pixmap);
    setScaledContents(true);
}

//当鼠标拖动时 调用move函数，来实现窗口的移动
void MyLabel::mouseMoveEvent(QMouseEvent *event)
{
    QPoint y = event->globalPos();
    QPoint x= y - m_zPos;
    this->move(x);
}

//通过鼠标按下,获取到当前相对窗口的坐标，
void MyLabel::mousePressEvent(QMouseEvent *event)
{

    //获取的鼠标位置是鼠标偏离电脑屏幕左上角（x=0,y=0）的位置；
    //返回鼠标的世界坐标.
    QPoint y = event->globalPos();
    //geometry 此属性保存小部件相对于其父部件的几何形状，并排除窗口框架
    QPoint x = this->geometry().topLeft();
    // 求差值 左键按下的点 - 窗口左上角的点坐标
    m_zPos = y-x;
}

//当拖动结束后，鼠标释放，不再按下，这时候将上次鼠标按下的坐标赋值置空。
void MyLabel::mouseReleaseEvent(QMouseEvent *)
{
    m_zPos = QPoint();
}
