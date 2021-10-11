#include "painteditem.h"
#include <QPainter>
#include <QPen>
#include <QBrush>
#include <QColor>
#include <QDebug>
#include <elementgroup.h>
#include <QQuickWindow>
#include "copypaintitem.h"

PaintedItem::PaintedItem(QQuickItem *parent)
    : QQuickPaintedItem(parent)
    , m_pen(Qt::black)
    , m_textPen(Qt::black)
    , m_isFill(false)
    , m_textWidth(0)
    , m_flag(1)
    , m_bEnabled(true)
    , m_bPressed(false)
    , m_bMoved(false)
{
    m_textPen.setWidth(1);

    setAcceptedMouseButtons(Qt::LeftButton);
    connect(this,&PaintedItem::textEditChanged,this,&PaintedItem::on_textEdit_changed);
    connect(this,&PaintedItem::textFontChanged,this,&PaintedItem::on_textFont_changed);
}

PaintedItem::~PaintedItem()
{
}

void PaintedItem::clear()
{
    m_textElements.clear();
    m_circleElements.clear();
    m_rectElements.clear();
    m_lineElements.clear();
    m_doodleElements.clear();
    emit clearSignal();
    update();
}
void PaintedItem::undo()
{
    if(m_sequence.size()!=0){
        int i=m_sequence[m_sequence.size()-1];
        if(i==1){
            if(m_textElements.size()>0){
                m_textElements.takeLast();
                //                delete m_textElements.takeLast();
            }
        }else if(i==2){
            if(m_circleElements.size()>0){
                delete m_circleElements.takeLast();
            }
        }else if(i==3){
            if(m_rectElements.size()>0){
                delete m_rectElements.takeLast();
            }
        }else if(i==4){
            if(m_lineElements.size()>0){
                delete m_lineElements.takeLast();
            }
        }else if(i==5){
            if(m_doodleElements.size()>0){
                delete m_doodleElements.takeLast();
            }
        }
        m_sequence.removeLast();
    }
    emit undoSignal();
    update();
}

void PaintedItem::save(QString filePath)
{
    //    copyPainter=new CopyPaintItem();
    //    copyPainter->CopyPaint(m_elements,m_myImage,m_textElements);
    CopyPaintItem* copyPainter=new CopyPaintItem();
    m_mysource="file:///tmp/1.jpg";
    m_myImage.load("/tmp/1.jpg");
    copyPainter->m_image=m_myImage;
    //文字
    copyPainter->m_textElements=m_textElements;
    //椭圆
    copyPainter->m_circleElements=m_circleElements;
    //矩形
    copyPainter->m_rectElements=m_rectElements;
    //直线
    copyPainter->m_lineElements=m_lineElements;
    //涂鸦
    copyPainter->m_doodleElements=m_doodleElements;
    //剪切
    copyPainter->m_rects=m_rects;
    copyPainter->save(filePath);
}

void PaintedItem::paint(QPainter *painter)
{
    painter->setRenderHint(QPainter::Antialiasing,true);

    textPaintEvent(painter);
    circlePaintEvent(painter);
    rectPaintEvent(painter);
    linePaintEvent(painter);
    doodlePaintEvent(painter);
}

void PaintedItem::mousePressEvent(QMouseEvent *event)
{
    m_bMoved = false;
    //如果m_bEnabled为false或者所用键盘与设置的键盘不一样，就不会触发鼠标按压事件
    if(!m_bEnabled || !(event->button() & acceptedMouseButtons())){
        QQuickPaintedItem::mousePressEvent(event);
    }else{
        qDebug() << "mouse pressed";
        m_bPressed = true;
        event->setAccepted(true);
        if(m_flag==1){        //如果是编辑文字
            textPressEvent();
            m_sequence.push_back(1);
        }else if(m_flag==2){
            qDebug()<<"画椭圆";
            circlePressEvent();   //如果是画椭圆
            m_sequence.push_back(2);
        }else if(m_flag==3){
            rectPressEvent();//画矩形
            m_sequence.push_back(3);
        }else if(m_flag==4){
            linePressEvent();
            m_sequence.push_back(4);
        }else if(m_flag==5){
            doodlePressEvent();//涂鸦
            m_sequence.push_back(5);
        }else if(m_flag==6){   //剪切
            m_sequence.push_back(6);
        }
        //设置起始点
        qDebug()<<"event->pos"<<event->pos().x()<<"+"<<event->pos().y();
        setStartPoint(event->pos());
        update();
    }
}

void PaintedItem::mouseMoveEvent(QMouseEvent *event)
{
    //如果m_bEnabled为false或者鼠标没有被按压或者没有m_textElement为空，则不会触发鼠标移动事件
    if(!m_bEnabled || !m_bPressed/*||!m_textElement*/){
        qDebug()<<"不是鼠标移动事件";
        QQuickPaintedItem::mousePressEvent(event);
    }    else    {
        qDebug() << "mouse move";
        event->setAccepted(true);
        m_bMoved=true;
        setLastPoint(event->pos());
        if(m_flag==1){//如果是编辑文字
            textMoveEvent();
            qDebug()<<"鼠标移动时文字为"<<m_textElement->m_text;
        }else if(m_flag==2){
            circleMoveEvent();  //如果是画椭圆
        }else if(m_flag==3){
            rectMoveEvent();//画矩形
        }else if(m_flag==4){
            lineMoveEvent();
        }else if(m_flag==5){
            doodleMoveEvent();
            //为了连起来
            setStartPoint(m_lastPoint);
        }

        update();
    }
}
void PaintedItem::mouseReleaseEvent(QMouseEvent *event)
{
    if(!m_bEnabled || !(event->button() & acceptedMouseButtons())||!m_bPressed||!m_bMoved){
        qDebug()<<"不是鼠标释放事件";
        QQuickPaintedItem::mousePressEvent(event);
    }else{
        qDebug() << "mouse released";
        event->setAccepted(true);
        setLastPoint(event->pos());

        if(m_flag==1){//如果是编辑文字事件
            textMoveEvent();
        }else if(m_flag==2){
            circleMoveEvent();//如果是画椭圆
        }else if(m_flag==3){
            rectMoveEvent();//画矩形
        }else if(m_flag==4){
            lineMoveEvent();
        }else if(m_flag==5){
            doodleMoveEvent();
        }

        update();

        //将鼠标按压事件和鼠标移动事件设为false,将m_textElement置为空！！
        m_bPressed=false;
        m_bMoved=false;
        settextEdit("");
    }
}

void PaintedItem::textPressEvent()
{
    //关键点，新建一个文字编辑的类
    m_textElement=new TextElement(m_pen,m_textPen,m_textFont,"");
    qDebug()<<"新建了一个文字编辑的类";
    qDebug()<<"文字编辑类的text为："<<m_textElement->m_text;
    m_textElements.push_back(m_textElement);

    //将PaintedItem类中的textEdit的值变为空
    //目的是更新qml中textedit中text的值
    settextEdit("");
}

void PaintedItem::circlePressEvent()
{
    //新建一个画椭圆的类
    m_circleElement=new CircleElement(m_pen,m_isFill);
    m_circleElements.push_back(m_circleElement);
}

void PaintedItem::rectPressEvent()
{
    //新建一个画矩形的类
    m_rectElement=new RectElement(m_pen,m_isFill);
    m_rectElements.push_back(m_rectElement);
}

void PaintedItem::linePressEvent()
{
    //新建一个画直线的类
    m_lineElement=new LineElement(m_pen);
    m_lineElements.push_back(m_lineElement);
}

void PaintedItem::doodlePressEvent()
{
    //新建一个涂鸦的类
    m_doodleElement=new Doodle(m_pen);
    m_doodleElements.push_back(m_doodleElement);
}

void PaintedItem::textPaintEvent(QPainter *painter)
{
    int size = m_textElements.size();
    for(int i = 0; i < size; ++i){
        TextElement* textElement = m_textElements.at(i);

        int endSize=textElement->m_endPoints.size();
        if(endSize>0&&(textElement!=nullptr)){
            QPoint lastPoint=textElement->m_endPoints[endSize-1];
            QPoint startPoint=textElement->m_startPoint;
            QRect rect;
            QPoint p,p1;
            // 确定起始点和终止点的位置
            if(startPoint.x()>lastPoint.x()&&startPoint.y()<lastPoint.y()){
                qDebug()<<"第二种情况";
                p.setX(lastPoint.x());
                p.setY(startPoint.y());
                p1.setX(startPoint.x());
                p1.setY(lastPoint.y());
            }else if(startPoint.x()<lastPoint.x()&&startPoint.y()>lastPoint.y()){
                qDebug()<<"第一种情况";
                p.setX(startPoint.x());
                p.setY(lastPoint.y());
                p1.setX(lastPoint.x());
                p1.setY(startPoint.y());
            }else if(startPoint.x()>lastPoint.x()&&startPoint.y()>lastPoint.y()){
                qDebug()<<"第三种情况";
                p.setX(lastPoint.x());
                p.setY(lastPoint.y());
                p1.setX(startPoint.x());
                p1.setY(startPoint.y());
            }else{
                p=startPoint;
                p1=lastPoint;
            }

            //将起始点和终止点的坐标改变
            //            m_startPoint=p;
            //            m_lastPoint=p1;
            QRect rec(p,p1);
            rect=rec;

            //设置画笔
            painter->setPen(textElement->m_recPen);
            //画一个矩形
            painter->drawRect(rect);
            //设置文字的画笔
            painter->setPen(textElement->m_textPen);
            QFont font;
            font.setPixelSize(textElement->m_font);
            painter->setFont(font);
            painter->drawText(rect,textElement->m_text);
        }
    }
}

void PaintedItem::circlePaintEvent(QPainter *painter)
{
    int size=m_circleElements.size();
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

void PaintedItem::rectPaintEvent(QPainter *painter)
{
    int size=m_rectElements.size();
    //画每一个矩形
    for(int i=0;i<size;i++){
        RectElement *rectElement=m_rectElements[i];
        painter->setPen(rectElement->m_pen);
        int maxSize=rectElement->m_endPoints.size();
        if(maxSize>0&&(rectElement!=nullptr)){
            //椭圆要求在一个矩形区域内
            QRect rect(rectElement->m_startPoint,rectElement->m_endPoints[maxSize-1]);
            painter->drawRect(rect);
            if(rectElement->m_isFill){
                painter->fillRect(rect,rectElement->m_pen.color());
            }
        }
    }
}

void PaintedItem::linePaintEvent(QPainter *painter)
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

void PaintedItem::doodlePaintEvent(QPainter *painter)
{
    int size=m_doodleElements.size();
    for(int i=0;i<size;i++){
        Doodle* doodleElement=m_doodleElements[i];
        painter->setPen(doodleElement->m_pen);
        painter->drawLines(doodleElement->m_lines);
    }
}

void PaintedItem::textMoveEvent()
{
    if(m_startPoint.x()>m_lastPoint.x()&&m_startPoint.y()<m_lastPoint.y()){
        //            qDebug()<<"第二种情况";
        QPoint p(m_lastPoint.x(),m_startPoint.y());
        setprintPoint(p);
    }else if(m_startPoint.x()<m_lastPoint.x()&&m_startPoint.y()>m_lastPoint.y()){
        //            qDebug()<<"第一种情况";
        QPoint p(m_startPoint.x(),m_lastPoint.y());
        setprintPoint(p);
    }else if(m_startPoint.x()>m_lastPoint.x()&&m_startPoint.y()>m_lastPoint.y()){
        //            qDebug()<<"第三种情况";
        QPoint p(m_lastPoint.x(),m_lastPoint.y());
        setprintPoint(p);
    }else{
        setprintPoint(m_startPoint);
    }
    //文字区域的宽度
    int width=m_startPoint.x()-m_lastPoint.y();
    if(width<0){
        width=-width;
    }
    setTextWidth(width);
    qDebug()<<"文字区域的宽度限制为："<<width;

    //在这边不直接将起始点终止点确定下来
    //为了实现随着鼠标的移动，图形也在不断移动
    m_textElement->m_startPoint=m_startPoint;
    m_textElement->m_endPoints.push_back(m_lastPoint);

}

void PaintedItem::circleMoveEvent()
{
    m_circleElement->m_startPoint=m_startPoint;
    m_circleElement->m_endPoints.push_back(m_lastPoint);
}

void PaintedItem::rectMoveEvent()
{
    m_rectElement->m_startPoint=m_startPoint;
    m_rectElement->m_endPoints.push_back(m_lastPoint);
}

void PaintedItem::lineMoveEvent()
{
    m_lineElement->m_startPoint=m_startPoint;
    m_lineElement->m_endPoints.push_back(m_lastPoint);
}

void PaintedItem::doodleMoveEvent()
{
    m_doodleElement->m_lines.push_back(QLineF(m_startPoint,m_lastPoint));
}

void PaintedItem::sendRectNumber(int x,int y,int width,int height)
{
    m_rects.push_back(new CutRectElement(QRectF(x,y,width,height)));
}

QRectF PaintedItem::undo_backRect(QString flag)
{
    QRectF rect;
    if(m_rects.size()!=0){
        if(flag=="clear"){
            rect=m_rects[0]->m_cutRect;
            m_rects.remove(1,m_rects.size()-1);
            return rect;
        }else if(flag=="undo"){
            if(m_rects.size()>1){
                delete m_rects.takeLast();
            }
            rect=m_rects[m_rects.size()-1]->m_cutRect;
            return rect;
        }
        return rect;
    }
    return rect;
}

void PaintedItem::pressCutSequence()
{
    m_sequence.push_back(6);
}

bool PaintedItem::isdoCut(QString flag)
{
    if(m_sequence.size()!=0){
        if(flag=="undo"){
            if(m_sequence[m_sequence.size()-1]==6){
                qDebug()<<"m_sequence";
                return true;
            }
        }
        if(flag=="clear"){
            for (int i=0;i<m_sequence.size() ; i++) {
                if(m_sequence[i]==6){
                    return true;
                }
            }
        }
    }
    return false;
}

void PaintedItem::destroyRect()
{
    m_rects.clear();
}

void PaintedItem::setTextWidth(int newTextWidth)
{
    if (m_textWidth == newTextWidth)
        return;
    m_textWidth = newTextWidth;
    emit textWidthChanged();
}
