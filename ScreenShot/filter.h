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
#ifndef FILTER_H
#define FILTER_H

#include <QDialog>

namespace Ui {
class Filter;
}

class Filter : public QDialog
{
    Q_OBJECT

public:
    explicit Filter(QWidget *parent = nullptr);
    ~Filter();

    void coolImage(int delta);
    void warmImage(int delta);

    Q_INVOKABLE void mosaic();

private slots:
    void on_open_clicked();

    void grey();
    void old();
    void warm();
    void cool();
    void vague();
    void reverse();
    void sharpen();
    void soften();

    void on_btn_saveas_clicked();

private:
    Ui::Filter *ui;
    QImage m_Image;
    QPixmap m_pixmap;
};

#endif // FILTER_H
