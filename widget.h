#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>


//写一个窗口类，继承自QWidget,使这个窗口变为透明的窗口，
//当画完矩形之后，这个窗口就失去了焦点，不再是顶层窗口
class Widget:public QWidget
{
public:
    Widget();
    //这个函数继承自QWidget
    void resizeEvent(QResizeEvent *);
};

#endif // WIDGET_H
