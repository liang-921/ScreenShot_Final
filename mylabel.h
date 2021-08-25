#ifndef MYLABEL_H
#define MYLABEL_H

#include <QLabel>
#include <QMouseEvent>

class MyLabel : public QLabel
{
    Q_OBJECT
public:
    MyLabel();

    void setimagetolabel(QPixmap pixmap);
private:
    //鼠标移动事件
    void mouseMoveEvent(QMouseEvent *event);
    //鼠标释放事件
    void mouseReleaseEvent(QMouseEvent *event);
    //鼠标按下事件
    void mousePressEvent(QMouseEvent *);

private:
    QPoint m_zPos;
};

#endif // MYLABEL_H
