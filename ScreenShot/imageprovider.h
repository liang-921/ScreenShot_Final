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

#ifndef IMAGEPROVIDER_H
#define IMAGEPROVIDER_H
#include <QQuickImageProvider>
#include<QImage>
#include <QSize>
#include<QTcpSocket>
#include <QTcpServer>
#include<QBuffer>
class ImageProvider : public QQuickImageProvider
{
public:
    ImageProvider(): QQuickImageProvider(QQuickImageProvider::Image){ }
    QImage requestImage(const QString &id, QSize *size, const QSize &requestedSize){
        Q_UNUSED(id);
        Q_UNUSED(size);
        Q_UNUSED(requestedSize);
        return this->img;
    }

    QImage img;
};

#endif // IMAGEPROVIDER_H
