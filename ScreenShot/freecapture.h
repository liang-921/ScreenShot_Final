/*
 * author: 李梦雪 梁淑贞 张宝丹
 * email：2304768518@qq.com 2239602082@qq.com 1395089569@qq.com
 * time:2021.10

 * Copyright (C) <2021>  <Mengxue Li,Shuzhen Liang,Baodan zhang>

 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */
#ifndef FREECAPTURE_H
#define FREECAPTURE_H

#include <QWidget>
#include <QPainter>
#include "imageprovider.h"

class FreeCapture : public QWidget
{
    Q_OBJECT
public:
    explicit FreeCapture(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);

private:
    void initWindow();
    void loadBackgroundPixmap();

private:
    QPixmap m_loadPixmap;//加载背景图片
    int m_screenwidth;
    int m_screenheight;
    bool m_isMousePress;  //是否鼠标左击
    QPolygon  m_pPoints;   //点集合
    QPainter  m_painter;
    QPainter  m_imagePaint;


signals:
    // 通知截图完毕，并将截取图片传递给调用类;
    void signalCompleteCapture(QPixmap captureImage);

};

#endif // FREECAPTURE_H
