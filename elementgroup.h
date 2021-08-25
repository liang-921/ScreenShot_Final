/*
 * 日期：2021-8-20、
 * 作者：2304768518@qq.com
 * 这个函数中定义了编辑所需要的所有的类
 *
 */

#ifndef ELEMENTGROUP_H
#define ELEMENTGROUP_H

#include <QQuickPaintedItem>
#include <QVector>
#include <QPointF>
#include <QLineF>
#include <QPen>
#include <QRectF>

//文字编辑
class TextElement
{
public:
    //构造函数
    TextElement(){}
    TextElement(const QPen &recPen,const QPen &textPen,const int &textFont)
        :m_recPen(recPen),m_textPen(textPen),m_font(textFont)
    {}

    //矩形区域的起始点
    QPoint m_startPoint;
    //矩形区域的终止点，用vector容器装可以确保当鼠标移动时，矩形区域也随之移动
    std::vector<QPoint> m_endPoints;
    //矩形区域的文本
    QString m_text;
    //矩形边框的画笔
    QPen m_recPen;
    //文字的画笔
    QPen  m_textPen;
    //文字的宽度
    int m_font;
};

//椭圆形
class CircleElement{
public:
    CircleElement(){}
    CircleElement(const QPen& pen,const bool isFill):
        m_pen(pen),
        m_isFill(isFill)
    {}
    //椭圆型区域的起始点
    QPoint m_startPoint;
    //椭圆型区域的终止点，用vector容器装可以确保当鼠标移动时，椭圆型区域也随之移动
    std::vector<QPoint> m_endPoints;
    //椭圆边框的画笔
    QPen m_pen;
    //是否要填充颜色
    bool m_isFill;
};

//矩形
class RectElement{
public:
    RectElement(){}
    RectElement(const QPen &pen,const bool isFill):
        m_pen(pen),
        m_isFill(isFill)
    {}

    //矩形区域的起始点
    QPoint m_startPoint;
    //矩形区域的终止点，用vector容器装可以确保当鼠标移动时，矩形区域也随之移动
    std::vector<QPoint> m_endPoints;
    //矩形边框的画笔
    QPen m_pen;
    //是否要填充颜色
    bool m_isFill;
};

//直线
class LineElement{
public:
    LineElement(){}
    LineElement(const QPen &pen):
        m_pen(pen)
    {}
    //直线的起始点
    QPoint m_startPoint;
    //直线的终止点，用vector容器装可以确保当鼠标移动时，直线也随之移动
    std::vector<QPoint> m_endPoints;
    //直线的画笔
    QPen m_pen;
};

//涂鸦
class Doodle
{
public:
    Doodle()    {    }
    Doodle(const QPen &pen)
        : m_pen(pen)    {    }
    Doodle(const Doodle &e)
    {        m_lines = e.m_lines;
             m_pen = e.m_pen;
    }
    Doodle & operator=(const Doodle &e)
    {
        if(this != &e)
        {
            m_lines = e.m_lines;
            m_pen = e.m_pen;
        }
        return *this;
    }
    ~Doodle()    {}
    QVector<QLineF> m_lines;
    QPen m_pen;
};

//裁剪
class CutRectElement
{
public:
    CutRectElement()   {    }
    CutRectElement(const QRectF &rect)
        :m_cutRect(rect)    {    }

    ~CutRectElement() {   }

    QRectF m_cutRect;
};

#endif // ELEMENTGROUP_H
