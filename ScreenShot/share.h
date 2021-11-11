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
#ifndef SHARE_H
#define SHARE_H

#include <QWidget>
#include <QPrinter>
#include <QProcess>

class Share : public QWidget
{
    Q_OBJECT
public:
    explicit Share(QWidget *parent = nullptr);

    Q_INVOKABLE void sendMail();
    Q_INVOKABLE void shareToQQ();
    Q_INVOKABLE void shareToWeChat();
    Q_INVOKABLE void startPrinter();
signals:
private:
};

#endif // SHARE_H
