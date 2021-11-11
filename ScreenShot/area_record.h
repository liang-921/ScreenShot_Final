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
#ifndef GITWIDGET_H
#define GITWIDGET_H

#include <QDialog>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QSpacerItem>
#include <QLineEdit>
#include <QTimer>
#include <QPainter>
#include <QPaintEvent>
#include <QEvent>
#include <QFileDialog>
#include <QApplication>
#include <QDesktopServices>
#include <QScreen>
#include "gif.h"

class Area_Record : public QDialog
{
    Q_OBJECT
public:
    explicit Area_Record(QWidget *parent = 0);

    QWidget *widgetTop;
    QWidget *widgetMain;
    QWidget *widgetBottom;

    QLineEdit *txtFps;
    QLineEdit *txtWidth;
    QLineEdit *txtHeight;

    QLabel *labStatus;

    QPushButton *btnStart;

    int borderWidth;
    int fps;
    int count;
    QColor bgColor;
    QRect rectGif;
    QString fileName;

    QTimer *timer;

    Gif gif;
    Gif::GifWriter *gifWriter;
signals:
    void finish();
public slots:
    void closeAll();
    void record();
    void resizeForm();
    void saveImage();

protected:
    virtual bool eventFilter(QObject *, QEvent *);
    virtual void resizeEvent(QResizeEvent *);
    virtual void paintEvent(QPaintEvent *);
};

#endif // GITWIDGET_H
