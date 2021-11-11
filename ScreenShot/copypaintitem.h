/*
 * This class is responsible for saving operations and drawing the edited things into the picture
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
#ifndef COPYPAINTITEM_H
#define COPYPAINTITEM_H

#include <QQuickPaintedItem>
#include <QImage>
#include <QPaintEvent>
#include "elementgroup.h"

class CopyPaintItem:public QQuickPaintedItem
{
public:
    CopyPaintItem(QQuickItem *parent=0);
    void save(QString filePath);
    void paint(QPainter *painter);
    void paintEvent(QEvent *event);

    void saveTextElement(QPainter *painter);
    void saveCircleElement(QPainter *painter);
    void saveRectElement(QPainter *painter);
    void saveLineElement(QPainter* painter);
    void saveDoodleElement(QPainter *painter);
    void saveCutImg();
    QPainter *copyPainter;
    QVector<TextElement*> m_textElements;
    QVector<CircleElement*> m_circleElements;
    QVector<RectElement*> m_rectElements;
    QVector<LineElement*> m_lineElements;
    QVector<Doodle*> m_doodleElements;
    QVector<CutRectElement*> m_rects;
    QImage m_image;
};

#endif // COPYPAINTITEM_H
