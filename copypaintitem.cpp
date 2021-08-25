#include "copypaintitem.h"
#include <QPainter>
#include <QPaintEvent>

#include "elementgroup.h"
#include "painteditem.h"

CopyPaintItem::CopyPaintItem(QQuickItem *parent)
    :QQuickPaintedItem(parent)
{

}

void CopyPaintItem::save(QString filepath)
{
    qDebug()<<"qml中传过来的路径是"<<filepath;
    copyPainter=new QPainter(&m_image);
    copyPainter->setRenderHint(QPainter::Antialiasing,true);
    paintEvent(nullptr);
    QString path;
    for(int i=7;i<filepath.size();i++){
        path.push_back(filepath[i]);
    }
    saveCutImg();
    qDebug()<<"-----------------c++中所要保存的路径是："<<path;
    m_image.save(path,nullptr,-1);
}

void CopyPaintItem::paint(QPainter *painter)
{
    saveTextElement(painter);
    saveCircleElement(painter);
}

void CopyPaintItem::paintEvent(QEvent *event)
{
    saveTextElement(copyPainter);
    saveCircleElement(copyPainter);
    saveRectElement(copyPainter);
    saveLineElement(copyPainter);
    saveDoodleElement(copyPainter);
}

void CopyPaintItem::saveTextElement(QPainter *painter)
{
    int size = m_textElements.size();
//    qDebug()<<"size:"<<size;
    for(int i = 0; i < size; ++i){
        TextElement* m_textElement = m_textElements.at(i);
        int endSize=m_textElement->m_endPoints.size();
        if(endSize>0&&(m_textElement!=nullptr)){
            QPoint lastPoint=m_textElement->m_endPoints[endSize-1];
            QPoint startPoint=m_textElement->m_startPoint;
            QRect rect;
            if(startPoint.x()>lastPoint.x()&&startPoint.y()<lastPoint.y()){
                qDebug()<<"第二种情况";
                QPoint p(lastPoint.x(),startPoint.y());
                QPoint p1(startPoint.x(),lastPoint.y());
                QRect rec(p,p1);
                rect=rec;
            }else if(startPoint.x()<lastPoint.x()&&startPoint.y()>lastPoint.y()){
                qDebug()<<"第一种情况";
                QPoint p(startPoint.x(),lastPoint.y());
                QPoint p1(lastPoint.x(),startPoint.y());
                QRect rec(p,p1);
                rect=rec;
            }else if(startPoint.x()>lastPoint.x()&&startPoint.y()>lastPoint.y()){
                qDebug()<<"第三种情况";
                QPoint p(lastPoint.x(),lastPoint.y());
                QPoint p1(startPoint.x(),startPoint.y());
                QRect rec(p,p1);
                rect=rec;
            }else{
                QRect rec(startPoint,lastPoint);
                rect=rec;
            }

            painter->setPen(m_textElement->m_recPen);
            painter->drawRect(rect);
            painter->setPen(m_textElement->m_textPen);
            QFont font;
            font.setPixelSize(m_textElement->m_font);
            painter->setFont(font);
            painter->drawText(rect,m_textElement->m_text);
        }
    }
}

void CopyPaintItem::saveCircleElement(QPainter *painter)
{
    int size=m_circleElements.size();
    qDebug()<<"m_circleElements"<<size;
    //画每一个椭圆
    for(int i=0;i<size;i++){
        CircleElement *circleElement=m_circleElements[i];
        painter->setPen(circleElement->m_pen);
        int maxSize=circleElement->m_endPoints.size();
        if(maxSize>0&&(circleElement!=nullptr)){
            //椭圆要求在一个矩形区域内
            QRect rect(circleElement->m_startPoint,circleElement->m_endPoints[maxSize-1]);
            painter->drawEllipse(rect);
//            painter->drawRect(rect);
        }
    }
}

void CopyPaintItem::saveRectElement(QPainter *painter)
{
    int size=m_rectElements.size();
    for(int i=0;i<size;i++){
        RectElement *rectElement=m_rectElements[i];
        painter->setPen(rectElement->m_pen);
        int maxSize=rectElement->m_endPoints.size();
        if(maxSize>0&&(rectElement!=nullptr)){
            //椭圆要求在一个矩形区域内
            QRect rect(rectElement->m_startPoint,rectElement->m_endPoints[maxSize-1]);
//            painter->drawEllipse(rect);
            painter->drawRect(rect);
        }
    }
}

void CopyPaintItem::saveLineElement(QPainter *painter)
{
    int size=m_lineElements.size();
    for(int i=0;i<size;i++){
        LineElement *lineElement=m_lineElements[i];
        painter->setPen(lineElement->m_pen);
        int maxSize=lineElement->m_endPoints.size();
        if(maxSize>0&&(lineElement!=nullptr)){
            painter->drawLine(lineElement->m_startPoint,lineElement->m_endPoints[maxSize-1]);
        }
    }
}

void CopyPaintItem::saveDoodleElement(QPainter *painter)
{
    int size=m_doodleElements.size();
    for(int i=0;i<size;i++){
        Doodle* doodleElement=m_doodleElements[i];
        painter->setPen(doodleElement->m_pen);
        painter->drawLines(doodleElement->m_lines);
    }
}

void CopyPaintItem::saveCutImg()
{
    QRectF rect;
    if(m_rects.size()>0){
        rect=m_rects[m_rects.size()-1]->m_cutRect;
        m_image=m_image.copy(-rect.x(),-rect.y(),rect.width(),rect.height());
    }
}
