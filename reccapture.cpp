#include "reccapture.h"
#include <QApplication>
#include <QMouseEvent>
#include <QScreen>
#include <QClipboard>
#include <QDir>
#include <QDateTime>
#include <QTimer>

// 选中矩形8个拖拽点小矩形的宽高;
#define STRETCH_RECT_WIDTH 6
#define STRETCH_RECT_HEIGHT 6

// 矩形选中区边框宽度;
#define SELECT_RECT_BORDER_WIDTH                1

// 选中矩形8个拖拽点小矩形的宽高;
#define STRETCH_RECT_WIDTH                      6
#define STRETCH_RECT_HEIGHT                     6

// 选中矩形信息矩形的宽高;
#define SELECT_RECT_INFO_WIDTH                  75
#define SELECT_RECT_INFO_HEIGHT                 20

// 选区矩形的右下顶点放大图的宽高;
#define END_POINT_RECT_WIDTH                    122
#define END_POINT_RECT_HEIGHT                   122
#define END_POINT_IMAGE_HEIGHT                  90

RecCapture::RecCapture(QWidget *parent)
    : QWidget(parent)
    , m_isMousePress(false)
    , m_currentCaptureState(InitCapture)
{


    pixs=new QVector<QPixmap>;
    curtimes = new QVector<QString>;
    m_filename = "/tmp/Cut/";

    initWindow();
    initStretchRect();
    loadBackgroundPixmap();
}

RecCapture::~RecCapture()
{
    if(!pixs->empty()){
        delete pixs;
    }
}

void RecCapture::initWindow()
{
    this->setMouseTracking(true);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    setWindowState(Qt::WindowActive | Qt::WindowFullScreen);
}

void RecCapture::initStretchRect()
{
    m_stretchRectState = NotSelect;
    m_topLeftRect = QRect(0 , 0 , 0 , 0);
    m_topRightRect = QRect(0, 0, 0, 0);
    m_bottomLeftRect = QRect(0, 0, 0, 0);
    m_bottomRightRect = QRect(0, 0, 0, 0);

    m_leftCenterRect = QRect(0, 0, 0, 0);
    m_topCenterRect = QRect(0, 0, 0, 0);
    m_rightCenterRect = QRect(0, 0, 0, 0);
    m_bottomCenterRect = QRect(0, 0, 0, 0);
}

//获取当前屏幕图片
void RecCapture::loadBackgroundPixmap()
{
    m_loadPixmap = QApplication::primaryScreen()->grabWindow(0); //抓取当前屏幕的图片;
    m_screenwidth = m_loadPixmap.width();
    m_screenheight = m_loadPixmap.height();
}

void RecCapture::mousePressEvent(QMouseEvent *event)
{
    m_stretchRectState = getStrethRectState(event->pos());
    if (event->button() == Qt::LeftButton){
        if (m_currentCaptureState == InitCapture)
        {
            m_currentCaptureState = BeginCaptureImage;
            m_beginPoint = event->pos();
        }
        // 是否在拉伸的小矩形中;
        else if (m_stretchRectState != NotSelect)
        {
            m_currentCaptureState = BeginMoveStretchRect;
            // 当前鼠标在拖动选中区顶点时,设置鼠标当前状态;
            setStretchCursorStyle(m_stretchRectState);
            m_beginMovePoint = event->pos();
        }
        // 是否在选中的矩形中;
        else if (isPressPointInSelectRect(event->pos()))
        {
            m_currentCaptureState = BeginMoveCaptureArea;
            m_beginMovePoint = event->pos();
        }
    }

    return QWidget::mousePressEvent(event);
}

void RecCapture::mouseMoveEvent(QMouseEvent* event)
{
    if (m_currentCaptureState == BeginCaptureImage)
    {
        m_endPoint = event->pos();
        update();
    }
    else if (m_currentCaptureState == BeginMoveCaptureArea)
    {
        m_endMovePoint = event->pos();
        update();
    }
    else if (m_currentCaptureState == BeginMoveStretchRect)
    {
        m_endMovePoint = event->pos();
        update();
        // 当前鼠标在拖动选中区顶点时,在鼠标未停止移动前，一直保持鼠标当前状态;
        return QWidget::mouseMoveEvent(event);
    }


    // 根据鼠标是否在选中区域内设置鼠标样式;
    StretchRectState stretchRectState = getStrethRectState(event->pos());
    if (stretchRectState != NotSelect)
    {
        setStretchCursorStyle(stretchRectState);
    }
    else if (isPressPointInSelectRect(event->pos()))
    {
        setCursor(Qt::SizeAllCursor);
    }
    else if (!isPressPointInSelectRect(event->pos()) && m_currentCaptureState != BeginMoveCaptureArea)
    {
        setCursor(Qt::ArrowCursor);
    }

    return QWidget::mouseMoveEvent(event);
}

void RecCapture::mouseReleaseEvent(QMouseEvent *event)
{
    if (m_currentCaptureState == BeginCaptureImage)
    {
        m_currentCaptureState = FinishCaptureImage;
        m_endPoint = event->pos();
        update();
    }
    else if (m_currentCaptureState == BeginMoveCaptureArea)
    {
        m_currentCaptureState = FinishMoveCaptureArea;
        m_endMovePoint = event->pos();
        update();
    } else if (m_currentCaptureState == BeginMoveStretchRect)
    {
        m_currentCaptureState = FinishMoveStretchRect;
        m_endMovePoint = event->pos();
        update();
    }

    return QWidget::mouseReleaseEvent(event);
}

// 当前鼠标坐标是否在选取的矩形区域内;
bool RecCapture::isPressPointInSelectRect(QPoint mousePressPoint)
{
    QRect selectRect = getRect(m_beginPoint, m_endPoint);
    if (selectRect.contains(mousePressPoint))
    {
        return true;
    }

    return false;
}

void RecCapture::paintEvent(QPaintEvent *)
{
    m_painter.begin(this);          //进行重绘;

    QColor shadowColor = QColor(0, 0, 0, 100);                      //阴影颜色设置;
    m_painter.setPen(QPen(Qt::blue, 1, Qt::SolidLine, Qt::FlatCap));    //设置画笔;
    m_painter.drawPixmap(0, 0, m_loadPixmap);                       //将背景图片画到窗体上;
    m_painter.fillRect(m_loadPixmap.rect(), shadowColor);           //画影罩效果;

    switch (m_currentCaptureState)
    {
    case InitCapture:
        break;
    case BeginCaptureImage:
    case FinishCaptureImage:
    case BeginMoveCaptureArea:
    case FinishMoveCaptureArea:
    case BeginMoveStretchRect:
    case FinishMoveStretchRect:
        m_currentSelectRect = getSelectRect();
        drawCaptureImage();
    case FinishCapture:
        break;
    default:
        break;
    }

    drawSelectRectInfo();
    drawEndPointImage();

    m_painter.end();  //重绘结束;
}

// 根据当前截取状态获取当前选中的截图区域;
QRect RecCapture::getSelectRect()
{
    QRect selectRect(0, 0, 0, 0);
    if (m_currentCaptureState == BeginCaptureImage || m_currentCaptureState == FinishCaptureImage)
    {
        selectRect = getRect(m_beginPoint, m_endPoint);
    }
    else if (m_currentCaptureState == BeginMoveCaptureArea || m_currentCaptureState == FinishMoveCaptureArea)
    {
        selectRect = getMoveRect();
    }
    else if (m_currentCaptureState == BeginMoveStretchRect || m_currentCaptureState == FinishMoveStretchRect)
    {
        selectRect = getStretchRect();
    }

    if (m_currentCaptureState == FinishCaptureImage || m_currentCaptureState == FinishMoveCaptureArea || m_currentCaptureState == FinishMoveStretchRect)
    {
        m_currentCaptureState = FinishCapture;
    }

    return selectRect;
}

// 绘制当前选中的截图区域;
void RecCapture::drawCaptureImage()
{
    m_capturePixmap = m_loadPixmap.copy(m_currentSelectRect);
    m_painter.drawPixmap(m_currentSelectRect.topLeft(), m_capturePixmap);
    m_painter.setPen(QPen(QColor(0, 180, 255), SELECT_RECT_BORDER_WIDTH));    //设置画笔;
    m_painter.drawRect(m_currentSelectRect);
    drawStretchRect();
}

// 绘制选中矩形各拖拽点小矩形;
void RecCapture::drawStretchRect()
{
    QColor color = QColor(0, 174, 255);
    // 四个角坐标;
    QPoint topLeft = m_currentSelectRect.topLeft();
    QPoint topRight = m_currentSelectRect.topRight();
    QPoint bottomLeft = m_currentSelectRect.bottomLeft();
    QPoint bottomRight = m_currentSelectRect.bottomRight();
    // 四条边中间点坐标;
    QPoint leftCenter = QPoint(topLeft.x(), (topLeft.y() + bottomLeft.y()) / 2);
    QPoint topCenter = QPoint((topLeft.x() + topRight.x()) / 2, topLeft.y());
    QPoint rightCenter = QPoint(topRight.x(), leftCenter.y());
    QPoint bottomCenter = QPoint(topCenter.x(), bottomLeft.y());

    m_topLeftRect = QRect(topLeft.x() - STRETCH_RECT_WIDTH / 2, topLeft.y() - STRETCH_RECT_HEIGHT / 2, STRETCH_RECT_WIDTH, STRETCH_RECT_HEIGHT);
    m_topRightRect = QRect(topRight.x() - STRETCH_RECT_WIDTH / 2, topRight.y() - STRETCH_RECT_HEIGHT / 2, STRETCH_RECT_WIDTH, STRETCH_RECT_HEIGHT);
    m_bottomLeftRect = QRect(bottomLeft.x() - STRETCH_RECT_WIDTH / 2, bottomLeft.y() - STRETCH_RECT_HEIGHT / 2, STRETCH_RECT_WIDTH, STRETCH_RECT_HEIGHT);
    m_bottomRightRect = QRect(bottomRight.x() - STRETCH_RECT_WIDTH / 2, bottomRight.y() - STRETCH_RECT_HEIGHT / 2, STRETCH_RECT_WIDTH, STRETCH_RECT_HEIGHT);

    m_leftCenterRect = QRect(leftCenter.x() - STRETCH_RECT_WIDTH / 2, leftCenter.y() - STRETCH_RECT_HEIGHT / 2, STRETCH_RECT_WIDTH, STRETCH_RECT_HEIGHT);
    m_topCenterRect = QRect(topCenter.x() - STRETCH_RECT_WIDTH / 2, topCenter.y() - STRETCH_RECT_HEIGHT / 2, STRETCH_RECT_WIDTH, STRETCH_RECT_HEIGHT);
    m_rightCenterRect = QRect(rightCenter.x() - STRETCH_RECT_WIDTH / 2, rightCenter.y() - STRETCH_RECT_HEIGHT / 2, STRETCH_RECT_WIDTH, STRETCH_RECT_HEIGHT);
    m_bottomCenterRect = QRect(bottomCenter.x() - STRETCH_RECT_WIDTH / 2, bottomCenter.y() - STRETCH_RECT_HEIGHT / 2, STRETCH_RECT_WIDTH, STRETCH_RECT_HEIGHT);

    m_painter.fillRect(m_topLeftRect, color);
    m_painter.fillRect(m_topRightRect, color);
    m_painter.fillRect(m_bottomLeftRect, color);
    m_painter.fillRect(m_bottomRightRect, color);
    m_painter.fillRect(m_leftCenterRect, color);
    m_painter.fillRect(m_topCenterRect, color);
    m_painter.fillRect(m_rightCenterRect, color);
    m_painter.fillRect(m_bottomCenterRect, color);
}

void RecCapture::keyPressEvent(QKeyEvent *event)
{
    // Esc 键退出截图;
    if (event->key() == Qt::Key_Escape){
        //退出截图
        close();
    }

    // Eeter键完成矩形区域截图;
    if (event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return)
    {
        QApplication::clipboard()->setImage(m_capturePixmap.toImage());
        QImage img=m_capturePixmap.toImage();
        img.save("/tmp/1.jpg",nullptr,100);

        emit signalCompleteCapture(m_capturePixmap);

        close();
    }

    // 空格键进行连续截图;
    if (event->key() == Qt::Key_Space)
    {
        //将矩形截图压入QVector里面
        pixs->append(m_capturePixmap);
        QString curtime = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss zzz");
        curtimes->append(curtime);
        //清空画布
        update();
        //重新定义当前截取图片的状态
        m_currentCaptureState = InitCapture;
    }

    //backspace完成连续截图
    if(event->key() == Qt::Key_Backspace){
        //判断是否有截图 若有，则保存
        if(!pixs->isEmpty()){
            //建立一个文件夹
            QDir *filedir=new QDir;
            if(!filedir->exists(m_filename)){
                //判断文件夹是否存在，若不存在则将自己创建
                filedir->mkdir(m_filename);
            }
            for(int i=0;i<pixs->length();i++){
                //将保存的矩形截图依次保存在指定文件夹
                QImage img=pixs->at(i).toImage();
                qDebug()<<curtimes->at(i);
                QString filename=m_filename + curtimes->at(i) + ".png";
                img.save(filename,nullptr,100);
            }

            emit signalCompleteContinue();
        }

        close();
    }

    //Tab进行钉图操作
    if(event->key() == Qt::Key_Tab){

        labelimage=new MyLabel();

        if(!m_capturePixmap.toImage().isNull()){
            qDebug()<<"所截的图不是空的!!";
            qDebug()<<"宽："<<m_capturePixmap.width()<<"高："<<m_capturePixmap.height();
        }
        labelimage->setimagetolabel(m_capturePixmap);
        labelimage->setFixedSize(m_capturePixmap.width(),m_capturePixmap.height());

        //钉在桌面
        labelimage->show();

        //清空画布
        update();
        //重新定义当前截取图片的状态
        m_currentCaptureState = InitCapture;

        emit signalCompleteNail();
    }
}

QRect RecCapture::getRect(const QPoint &beginPoint, const QPoint &endPoint)
{
    int x, y, width, height;
    width = qAbs(beginPoint.x() - endPoint.x());
    height = qAbs(beginPoint.y() - endPoint.y());
    x = beginPoint.x() < endPoint.x() ? beginPoint.x() : endPoint.x();
    y = beginPoint.y() < endPoint.y() ? beginPoint.y() : endPoint.y();

    QRect selectedRect = QRect(x, y, width, height);
    // 避免宽或高为零时拷贝截图有误;
    // 可以看QQ截图，当选取截图宽或高为零时默认为2;
    if (selectedRect.width() == 0)
    {
        selectedRect.setWidth(1);
    }
    if (selectedRect.height() == 0)
    {
        selectedRect.setHeight(1);
    }

    return selectedRect;
}

// 获取移动后,当前选中的矩形;
QRect RecCapture::getMoveRect()
{
    // 通过getMovePoint方法先检查当前是否移动超出屏幕;
    QPoint movePoint = getMovePoint();
    QPoint beginPoint = m_beginPoint + movePoint;
    QPoint endPoint = m_endPoint + movePoint;
    // 结束移动选区时更新当前m_beginPoint , m_endPoint,防止下一次操作时截取的图片有问题;
    if (m_currentCaptureState == FinishMoveCaptureArea)
    {
        m_beginPoint = beginPoint;
        m_endPoint = endPoint;
        m_beginMovePoint = QPoint(0, 0);
        m_endMovePoint = QPoint(0, 0);
    }
    return getRect(beginPoint, endPoint);
}

QPoint RecCapture::getMovePoint()
{
    QPoint movePoint = m_endMovePoint - m_beginMovePoint;
    QRect currentRect = getRect(m_beginPoint, m_endPoint);
    // 检查当前是否移动超出屏幕;

    //移动选区是否超出屏幕左边界;
    if (currentRect.topLeft().x() + movePoint.x() < 0)
    {
        movePoint.setX(0 - currentRect.topLeft().x());
    }
    //移动选区是否超出屏幕上边界;
    if (currentRect.topLeft().y() + movePoint.y() < 0)
    {
        movePoint.setY(0 - currentRect.topLeft().y());
    }
    //移动选区是否超出屏幕右边界;
    if (currentRect.bottomRight().x() + movePoint.x() > m_screenwidth)
    {
        movePoint.setX(m_screenwidth - currentRect.bottomRight().x());
    }
    //移动选区是否超出屏幕下边界;
    if (currentRect.bottomRight().y() + movePoint.y() > m_screenheight)
    {
        movePoint.setY(m_screenheight - currentRect.bottomRight().y());
    }

    return movePoint;
}
// 获取当前鼠标位于哪一个拖拽顶点;
StretchRectState RecCapture::getStrethRectState(QPoint point)
{
    StretchRectState stretchRectState = NotSelect;
    if (m_topLeftRect.contains(point))
    {
        stretchRectState = TopLeftRect;
    }
    else if (m_topCenterRect.contains(point))
    {
        stretchRectState = TopCenterRect;
    }
    else if (m_topRightRect.contains(point))
    {
        stretchRectState = TopRightRect;
    }
    else if (m_rightCenterRect.contains(point))
    {
        stretchRectState = RightCenterRect;
    }
    else if (m_bottomRightRect.contains(point))
    {
        stretchRectState = BottomRightRect;
    }
    else if (m_bottomCenterRect.contains(point))
    {
        stretchRectState = BottomCenterRect;
    }
    else if (m_bottomLeftRect.contains(point))
    {
        stretchRectState = BottomLeftRect;
    }
    else if (m_leftCenterRect.contains(point))
    {
        stretchRectState = LeftCenterRect;
    }

    return stretchRectState;
}

// 设置鼠标停在拖拽定点处的样式;
void RecCapture::setStretchCursorStyle(StretchRectState stretchRectState)
{
    switch (stretchRectState)
    {
    case NotSelect:
        setCursor(Qt::ArrowCursor);
        break;
    case TopLeftRect:
    case BottomRightRect:
        setCursor(Qt::SizeFDiagCursor);
        break;
    case TopRightRect:
    case BottomLeftRect:
        setCursor(Qt::SizeBDiagCursor);
        break;
    case LeftCenterRect:
    case RightCenterRect:
        setCursor(Qt::SizeHorCursor);
        break;
    case TopCenterRect:
    case BottomCenterRect:
        setCursor(Qt::SizeVerCursor);
        break;
    default:
        break;
    }
}

// 获取拖拽后的矩形选中区域;
QRect RecCapture::getStretchRect()
{
    QRect stretchRect;
    QRect currentRect = getRect(m_beginPoint, m_endPoint);
    switch (m_stretchRectState)
    {
    case NotSelect:
        stretchRect = getRect(m_beginPoint, m_endPoint);
        break;
    case TopLeftRect:
    {
        stretchRect = getRect(currentRect.bottomRight(), m_endMovePoint);
    }
        break;
    case TopRightRect:
    {
        QPoint beginPoint = QPoint(currentRect.topLeft().x(), m_endMovePoint.y());
        QPoint endPoint = QPoint(m_endMovePoint.x(), currentRect.bottomRight().y());
        stretchRect = getRect(beginPoint, endPoint);
    }
        break;
    case BottomLeftRect:
    {
        QPoint beginPoint = QPoint(m_endMovePoint.x() , currentRect.topLeft().y());
        QPoint endPoint = QPoint(currentRect.bottomRight().x(), m_endMovePoint.y());
        stretchRect = getRect(beginPoint, endPoint);
    }
        break;
    case BottomRightRect:
    {
        stretchRect = getRect(currentRect.topLeft(), m_endMovePoint);
    }
        break;
    case LeftCenterRect:
    {
        QPoint beginPoint = QPoint(m_endMovePoint.x(), currentRect.topLeft().y());
        stretchRect = getRect(beginPoint, currentRect.bottomRight());
    }
        break;
    case TopCenterRect:
    {
        QPoint beginPoint = QPoint(currentRect.topLeft().x(), m_endMovePoint.y());
        stretchRect = getRect(beginPoint, currentRect.bottomRight());
    }
        break;
    case RightCenterRect:
    {
        QPoint endPoint = QPoint(m_endMovePoint.x(), currentRect.bottomRight().y());
        stretchRect = getRect(currentRect.topLeft(), endPoint);
    }
        break;
    case BottomCenterRect:
    {
        QPoint endPoint = QPoint(currentRect.bottomRight().x(), m_endMovePoint.y());
        stretchRect = getRect(currentRect.topLeft(), endPoint);
    }
        break;
    default:
    {
        stretchRect = getRect(m_beginPoint , m_endPoint );
    }
        break;
    }

    // 拖动结束更新 m_beginPoint , m_endPoint;
    if (m_currentCaptureState == FinishMoveStretchRect)
    {
        m_beginPoint = stretchRect.topLeft();
        m_endPoint = stretchRect.bottomRight();
    }

    return stretchRect;
}

void RecCapture::drawSelectRectInfo()
{
    int posX, posY;
    QPoint topLeftPoint = m_currentSelectRect.topLeft();

    posX = topLeftPoint.x() + SELECT_RECT_BORDER_WIDTH;
    if (topLeftPoint.y() > SELECT_RECT_INFO_HEIGHT)
    {
        posY = topLeftPoint.y() - SELECT_RECT_INFO_HEIGHT - SELECT_RECT_BORDER_WIDTH;
    }
    else
    {
        posY = topLeftPoint.y() + SELECT_RECT_BORDER_WIDTH;
    }
    topLeftPoint = QPoint(posX, posY);

    QColor backColor = QColor(0, 0, 0, 160);
    m_painter.fillRect(QRect(topLeftPoint, QSize(SELECT_RECT_INFO_WIDTH, SELECT_RECT_INFO_HEIGHT)), backColor);

    // 当前选中矩形的宽高信息;
    QString selectRectSizeInfo = QString("%1 * %2").arg(m_currentSelectRect.width()).arg(m_currentSelectRect.height());
    int fontWidth = this->fontMetrics().averageCharWidth();
    m_painter.setPen(QPen(Qt::white));
    m_painter.drawText(QPoint(topLeftPoint.x() + (SELECT_RECT_INFO_WIDTH - fontWidth) / 2, topLeftPoint.y() + 14), selectRectSizeInfo);
}

// 绘制鼠标拖拽时选区矩形的右下顶点的放大图;
void RecCapture::drawEndPointImage()
{
    int posX, posY;
    QPoint topLeftPoint = QCursor::pos();

    // 5、25 分别为鼠标所在点距离放大图的X轴、Y轴距离;
    //当放大图片区域超出右边屏幕时;
    if (topLeftPoint.x() + END_POINT_RECT_WIDTH + 5 > m_screenwidth)
    {
        // 这里暂时未考虑到双屏幕（多屏幕）;
        if (topLeftPoint.x() > m_screenwidth)
        {
            posX = m_screenwidth - END_POINT_RECT_WIDTH - 5;
        }
        else
        {
            posX = topLeftPoint.x() - END_POINT_RECT_WIDTH - 5;
        }
    }
    else
    {
        posX = topLeftPoint.x() + 5;
    }

    // 当放大图片区域超出屏幕下方时;
    if (topLeftPoint.y() + END_POINT_RECT_HEIGHT + 25 > m_screenheight)
    {
        posY = topLeftPoint.y() - END_POINT_RECT_HEIGHT - 25;
    }
    // 当鼠标未屏幕下方，正常显示时;
    else
    {
        posY = topLeftPoint.y() + 25;
    }

    topLeftPoint = QPoint(posX, posY);

    // 绘制放大图;
    QPixmap endPointImage = m_loadPixmap.copy(QRect(QCursor::pos().x() - 15, QCursor::pos().y() - 11, 30, 22)).scaled(END_POINT_RECT_WIDTH, END_POINT_IMAGE_HEIGHT);
    m_painter.drawPixmap(topLeftPoint, endPointImage);

    // 绘制十字坐标;
    m_painter.setPen(QPen(QColor(0, 180, 255 , 180), 4));
    // 竖线;
    m_painter.drawLine(QPoint(topLeftPoint.x() + END_POINT_RECT_WIDTH / 2, topLeftPoint.y() + 2), QPoint(topLeftPoint.x() + END_POINT_RECT_WIDTH / 2, topLeftPoint.y() + END_POINT_IMAGE_HEIGHT - 2));
    // 横线;
    m_painter.drawLine(QPoint(topLeftPoint.x() + 2 , topLeftPoint.y() + END_POINT_IMAGE_HEIGHT / 2), QPoint(topLeftPoint.x() + END_POINT_RECT_WIDTH - 2 , topLeftPoint.y() + END_POINT_IMAGE_HEIGHT / 2));

    m_painter.setPen(QPen(Qt::white, 3));
    m_painter.drawRect(QRect(QPoint(topLeftPoint.x() + 1 , topLeftPoint.y() + 1), QSize(END_POINT_RECT_WIDTH - 2, END_POINT_IMAGE_HEIGHT - 2)));
    m_painter.setPen(QPen(Qt::black, 1));
    m_painter.drawRect(QRect(topLeftPoint, QSize(END_POINT_RECT_WIDTH, END_POINT_IMAGE_HEIGHT)));

    // 绘制放大图信息;
    topLeftPoint = QPoint(topLeftPoint.x(), topLeftPoint.y() + END_POINT_IMAGE_HEIGHT);
    QColor backColor = QColor(0, 0, 0, 160);
    m_painter.fillRect(QRect(topLeftPoint, QSize(END_POINT_RECT_WIDTH, END_POINT_RECT_HEIGHT - END_POINT_IMAGE_HEIGHT)), backColor);
    // 当前选中矩形的宽高信息;
    QString selectRectSizeInfo = QString("%1 * %2").arg(m_currentSelectRect.width()).arg(m_currentSelectRect.height());
    QImage image = m_loadPixmap.toImage();
    QColor endPointColor = image.pixel(QCursor::pos());
    QString selectPointRGBInfo = QString("RGB:(%1,%2,%3)").arg(endPointColor.red()).arg(endPointColor.green()).arg(endPointColor.blue());
    m_painter.setPen(Qt::white);
    m_painter.drawText(QPoint(topLeftPoint.x() + 6, topLeftPoint.y() + 14), selectRectSizeInfo);
    m_painter.drawText(QPoint(topLeftPoint.x() + 6, topLeftPoint.y() + 27), selectPointRGBInfo);
}
