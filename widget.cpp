#include "widget.h"
#include <QBitmap>
#include <QPainter>

Widget::Widget()
{

}

void Widget::resizeEvent(QResizeEvent *)
{
    QBitmap bitMap(width(),height()); // A bit map has the same size with current widget
        QPainter painter(&bitMap);
        painter.setPen(QColor(255,255,255)); // Any color that is not QRgb(0,0,0) is right
        painter.drawRect(0,0,width(),height());

        // Now begin to draw the place where we want to show it
        painter.setPen(QColor(0,0,0));
        drawTextOnWin(&painter);
        drawImageOnWin(&painter);

        setMask(bitMap);
}
