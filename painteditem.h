/*
 * 这个类负责c++与qml的各种交互
 */

#ifndef PAINTEDITEM_H
#define PAINTEDITEM_H

#include <QQuickPaintedItem>
#include <QVector>
#include <QPointF>
#include <QLineF>
#include <QPen>
#include <QImage>
#include "elementgroup.h"

class PaintedItem : public QQuickPaintedItem
{
    Q_OBJECT

    //涂鸦的目标图片
    Q_PROPERTY(QImage myImage READ myImage WRITE setMyImage)
    Q_PROPERTY(QUrl mysource READ mysource WRITE setMysource)

    //是否触发相应的涂鸦事件
    Q_PROPERTY(bool enabled READ isEnabled WRITE setEnabled)

    //画笔的宽度、画笔的颜色
    Q_PROPERTY(int penWidth READ penWidth WRITE setPenWidth NOTIFY penWidthChanged)
    Q_PROPERTY(QColor penColor READ penColor WRITE setPenColor)
    //文字的宽度、文字的颜色
    Q_PROPERTY(int textFont READ textFont WRITE setTextFont NOTIFY textFontChanged)
    Q_PROPERTY(QColor textColor READ textColor WRITE setTextColor NOTIFY textColorChanged)

    //矩形|椭圆形|直线的起始点与终止点
    Q_PROPERTY(QPoint startPoint READ startPoint WRITE setStartPoint NOTIFY startPointChanged)
    Q_PROPERTY(QPoint lastPoint READ lastPoint WRITE setLastPoint NOTIFY lastPointChanged)
    //文字以及键盘输入文字的起始点
    Q_PROPERTY(QString textEdit READ textEdit WRITE settextEdit NOTIFY textEditChanged)
    Q_PROPERTY(QPoint printPoint READ printPoint WRITE setprintPoint NOTIFY printPointChanged)

    //是否要对图形进行颜色填充
    Q_PROPERTY(bool isFill READ isFill WRITE setIsFill NOTIFY isFillChanged);

    //当前进行的编辑操作是什么
    Q_PROPERTY(int  flag READ flag WRITE setFlag NOTIFY flagChanged);

    QImage m_myImage;
    QUrl m_mysource;

    //画各种涂鸦形状的笔
    QPen m_pen;
    //写文字的笔
    QPen m_textPen;
    //文字的大小
    int m_textFont;
    //矩形区域的起始点与终止点
    QPoint m_startPoint;
    QPoint m_lastPoint;
    //输入的文字
    QString m_textEdit;
    //键盘事件的起始点
    QPoint m_printPoint;

    //文字
    TextElement* m_textElement;
    QVector<TextElement*> m_textElements;

    //是否要对图形进行颜色填充
    bool m_isFill;

    //椭圆
    CircleElement* m_circleElement;
    QVector<CircleElement*> m_circleElements;

    //矩形
    RectElement* m_rectElement;
    QVector<RectElement*> m_rectElements;

    //直线
    LineElement* m_lineElement;
    QVector<LineElement*> m_lineElements;

    //涂鸦
    Doodle *m_doodleElement;
    QVector<Doodle*> m_doodleElements;

//    //剪切矩形
//    CutRectElement* m_rectCut;
    QVector<CutRectElement*> m_rects;
//    QRectF *m_rect;
//    QVector<QRectF*> m_rects;

    //当前所进行的编辑操作，1是文字，2是椭圆,3是矩形，4是直线,5是涂鸦
    int m_flag;

public:
    PaintedItem(QQuickItem *parent = 0);
    ~PaintedItem();

    //清除、撤销、保存
    Q_INVOKABLE void clear();
    Q_INVOKABLE void undo();
    Q_INVOKABLE void save(QString filePath);

    //设置剪切矩形
    Q_INVOKABLE void sendRectNumber(int x,int y,int width,int height);
    //undo或clear后，将图片恢复特定样子，flag为标志，"clear"为恢复为最开始大小和位置，“undo”恢复为最近一次大小和位置
    Q_INVOKABLE QRectF undo_backRect(QString flag);
    //如果是剪切操作向m_sequence里push_back(6),6表示剪切
    Q_INVOKABLE void pressCutSequence();
    //查看m_sequence里的最后一个值，如果是6,返回bool值true,否则返回false
    Q_INVOKABLE bool isdoCut();

    //每次调用update()函数时就会调用paint函数进行画布的更新
    void paint(QPainter *painter);

    bool isEnabled() const{ return m_bEnabled; }
    int penWidth() const { return m_pen.width(); }
    QColor penColor() const { return m_pen.color(); }
    QImage myImage() const{return m_myImage;}
    QUrl mysource() const{return m_mysource;}
    QPoint startPoint() const
    {
        return m_startPoint;
    }
    QPoint lastPoint() const
    {
        return m_lastPoint;
    }

    QString textEdit() const
    {
        return m_textEdit;
    }

    QPoint printPoint() const
    {
        return m_printPoint;
    }

    int textWidth() const
    {
        return m_textPen.width();
    }

    QColor textColor() const
    {
        return m_textPen.color();
    }

    bool isFill() const
    {
        return m_isFill;
    }

    int flag() const
    {
        return m_flag;
    }

    int textFont() const
    {
        return m_textFont;
    }

signals:
    void clearSignal();

    void undoSignal();

    void PaintChangeSignal();

    void startPointChanged(QPoint startPoint);

    void lastPointChanged(QPoint lastPoint);

    void textEditChanged();

    void penWidthChanged();

    void printPointChanged(QPoint printPoint);

    void textWidthChanged(int textWidth);

    void textColorChanged(QColor textColor);

    void isFillChanged(bool isFill);

    void flagChanged(int flag);

    void textFontChanged(int textFont);

public slots:
    void setEnabled(bool enabled){ m_bEnabled = enabled; }

    void setPenWidth(int width) {
        m_pen.setWidth(width);
    }

    void setPenColor(QColor color) {
        m_pen.setColor(color);
    }
    void setMyImage(QImage myImage){m_myImage = myImage;}
    void setMysource(QUrl mysource){m_mysource = mysource;}

    void setStartPoint(QPoint startPoint)
    {
        if (m_startPoint == startPoint)
            return;

        m_startPoint = startPoint;
        emit startPointChanged(m_startPoint);
    }

    void setLastPoint(QPoint lastPoint)
    {
        if (m_lastPoint == lastPoint)
            return;

        m_lastPoint = lastPoint;
        emit lastPointChanged(m_lastPoint);
    }

    void settextEdit(QString textEdit)
    {
        if (m_textEdit == textEdit)
            return;

        if(m_flag==1){
            m_textEdit = textEdit;
            qDebug()<<"settextEdit";
            emit textEditChanged();
        }
    }

    void on_textEdit_changed(){
        qDebug()<<"on_textEdit_changed:"<<&m_textElement;
        if(m_flag==1&&m_textElement!=nullptr){
            m_textElement->m_text=m_textEdit;
            qDebug()<<m_textElement->m_text;
//            update();
        }
    }

    void setprintPoint(QPoint printPoint)
    {
        if (m_printPoint == printPoint)
            return;

        m_printPoint = printPoint;
        emit printPointChanged(m_printPoint);
    }

    void setTextColor(QColor textColor)
    {
        if (m_textPen.color() == textColor)
            return;

        m_textPen.setColor(textColor);
        emit textColorChanged(m_textPen.color());
    }

    void setIsFill(bool isFill)
    {
        if (m_isFill == isFill)
            return;

        m_isFill = isFill;
        emit isFillChanged(m_isFill);
    }

    void setFlag(int flag)
    {
        if (m_flag == flag)
            return;

        m_flag = flag;
        emit flagChanged(m_flag);
    }

    void setTextFont(int textFont)
    {
        if (m_textFont == textFont)
            return;

        m_textFont = textFont;
        emit textFontChanged(m_textFont);
    }

    //当文字的粗细中途发生改变时
    void on_textFont_changed(int textFont)
    {
        if(m_flag==1&&m_textElement!=nullptr){
            m_textElement->m_font=m_textFont;
        }
    }

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    //记录每一步操作都是什么，确保可以撤销
    QVector<int> m_sequence;
    //撤销操作
    void purgePaintElements();

    //添加文字，鼠标按压时应进行的操作
    void textPressEvent();
    void circlePressEvent();
    void rectPressEvent();
    void linePressEvent();
    void doodlePressEvent();
    //添加文字，鼠标移动时应进行的操作
    void textMoveEvent();
    void circleMoveEvent();
    void rectMoveEvent();
    void lineMoveEvent();
    void doodleMoveEvent();
    //添加文字，重绘时应进行的操作
    void textPaintEvent(QPainter *painter);
    void circlePaintEvent(QPainter *painter);
    void rectPaintEvent(QPainter *painter);
    void linePaintEvent(QPainter *painter);
    void doodlePaintEvent(QPainter *painter);
    // the Current ElementGroup
    bool m_bEnabled;
    bool m_bPressed;
    bool m_bMoved;
    //进行保存操作的指针
};

#endif // PAINTEDITEM_H
