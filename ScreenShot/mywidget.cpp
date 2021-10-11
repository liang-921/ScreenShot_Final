#include "mywidget.h"
#include "ui_mywidget.h"
#include "compute.h"
#include <QWindow>
#include <QLabel>
#include <capture.h>
#include <QScreen>
//#include <Python.h>
#include <unistd.h>
#include <fcntl.h>
#include <mousethread.h>
#include <QPainter>
#include <QPen>
#include <QPushButton>

MyWidget::MyWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MyWidget)
{
    ui->setupUi(this);
    m_startButton=new QPushButton(this);
    m_startButton->setText("开始");
    m_endButton=new QPushButton(this);
    m_endButton->setText("结束");
    m_startButton->setVisible(false);
    m_endButton->setVisible(false);

    m_previewMode=new QLabel(this);
    m_previewMode->setVisible(false);


    //先让窗口变透明
    this->setWindowOpacity(0);
    //先截一张初始图片
    qDebug()<<"初始图片";
    on_wheelMove(1,3);
    //让窗口恢复不透明
    this->setWindowOpacity(0.8);
    setWindowFlags(Qt::WindowStaysOnTopHint|Qt::Tool|Qt::FramelessWindowHint);

    picDiff=new QRect(-1,-1,-1,-1);

    //利用线程一直检测有无需要的鼠标事件发生
    m_thread=new MouseThread(this);
    connect(m_thread,&MouseThread::mouseWhileDown,this, &MyWidget::on_wheelMove);
    connect(m_thread,&MouseThread::mouseWhileUp,this, &MyWidget::on_wheelMove);
    //防止内存泄漏
    connect(m_thread, &QThread::finished, this, &QObject::deleteLater);

    connect(this,&MyWidget::releaseEvent,this, &MyWidget::on_releaseEvent);
    connect(m_startButton,&QPushButton::clicked,this, &MyWidget::on_startButtonPressed);
    connect(m_endButton,&QPushButton::clicked,this, &MyWidget::on_endButtonPressed);
}

MyWidget::~MyWidget()
{
    delete ui;
    m_thread->quit();
    m_thread->wait();
}

void MyWidget::on_wheelMove(int flags,int dir)
{
    //全屏截图
    QPixmap pixmap;
    QScreen *screen=QApplication::primaryScreen();
    pixmap=screen->grabWindow(0);

    QImage img=pixmap.toImage();

    if(flags==1){
        m_imgOrigin=img;
        m_hecheng=img;
    }else{
        //将矩形区域扣出来
        //m_isSecond为flase,将m_imgOrigin,m_hecheng进行扣图
        if(!m_isSecond){
            m_imgOrigin=cutRectImage(m_imgOrigin);
            m_hecheng=cutRectImage(m_hecheng);
            m_start=m_imgOrigin;
            m_hecheng.save("/tmp/1.jpg");
            m_imgOrigin.save("/tmp/1.png");
        }
        m_isSecond=true;
        //将img进行扣图
        img=cutRectImage(img);
        m_imgNew=img;
        m_imgNew.save("/tmp/2.png");
        //滚轮滚动
        if(!m_imgNew.isNull()){
            computeMoveH(dir);
            cutImage(dir);
        }else{
            qDebug()<<"图片是空的";
        }
    }
}

void MyWidget::on_releaseEvent()
{
    m_startButton->setVisible(true);
    m_endButton->setVisible(true);
    if(m_startPoint.x()>m_endPoint.x()&&m_startPoint.y()>m_endPoint.y()){
        m_startButton->setGeometry(m_endPoint.x(),m_endPoint.y()-30,50,30);
        m_endButton->setGeometry(m_endPoint.x()+50,m_endPoint.y()-30,50,30);
    }else{
        m_startButton->setGeometry(m_endPoint.x(),m_endPoint.y(),50,30);
        m_endButton->setGeometry(m_endPoint.x()+50,m_endPoint.y(),50,30);
    }
}

void MyWidget::on_startButtonPressed()
{
    m_isStart=true;

    //区域进行鼠标穿透
    //找到矩形
    QRect rect=findRect();
    QRegion r1(0,0,this->width(),this->height(),QRegion::Rectangle);
    QRegion r2(rect);
    QRegion r3=r1.xored(r2);
    setMask(r3);
    m_thread->start();
}

void MyWidget::on_endButtonPressed()
{
    m_isStart=false;
    m_isSecond=false;
    m_isStartup=false;
    m_isStartdown=false;
    //用这种方式结束线程不太安全，最好的办法使用m_isstoped和stop()的方法
    //但是由于x11不太了解，所以只能用这种不太安全的方法来结束线程
    m_thread->terminate();
    close();
    emit closewidget(m_hecheng);
}

void MyWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (m_isPress&&!m_isStart){
        m_endPoint=event->pos();
//        qDebug()<<"鼠标移动事件";
        update();
    }
    qDebug()<<"鼠标移动事件";
}

void MyWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if (m_isPress&&!m_isStart){
        m_endPoint=event->pos();
        qDebug()<<"鼠标释放事件\n";
        update();
        m_isPress=false;
        emit releaseEvent();
    }
}

void MyWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton&&!m_isStart){
        m_startPoint=event->pos();
        qDebug()<<"鼠标按压事件\n";
        m_isPress=true;
    }
}

void MyWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    QPainter painter(this);
    QColor shadowColor = QColor(0, 0, 0, 50);
    painter.fillRect(this->rect(), shadowColor);
    painter.setPen(QPen(Qt::blue, 1, Qt::SolidLine, Qt::FlatCap));
    QRect rect(m_startPoint,m_endPoint);
    painter.drawRect(rect);
      QColor backColor = QColor(0, 0, 0, 0);
    painter.fillRect(rect,backColor);

    painter.end();
}

void MyWidget::keyPressEvent(QKeyEvent *event)
{
    // Esc 键退出截图;
    if (event->key() == Qt::Key_Escape){
        on_endButtonPressed();
    }else if (event->key() == Qt::Key_Space){
        on_startButtonPressed();
    }
}

QImage MyWidget::cutRectImage(QImage img)
{
    //把那块矩形给扣下来
    if(m_endPoint.x()>m_startPoint.x()&&m_endPoint.y()>m_startPoint.y()){
        img=img.copy(m_startPoint.x(),m_startPoint.y(),m_endPoint.x()-m_startPoint.x(),m_endPoint.y()-m_startPoint.y());
    }else if(m_startPoint.x()>m_endPoint.x()&&m_startPoint.y()<m_endPoint.y()){
        img=img.copy(m_endPoint.x(),m_startPoint.y(),m_startPoint.x()-m_endPoint.x(),m_endPoint.y()-m_startPoint.y());
    }else if(m_startPoint.x()<m_endPoint.x()&&m_startPoint.y()>m_endPoint.y()){
        img=img.copy(m_startPoint.x(),m_endPoint.y(),m_endPoint.x()-m_startPoint.x(),m_startPoint.y()-m_endPoint.y());
    }else if(m_startPoint.x()>m_endPoint.x()&&m_startPoint.y()>m_endPoint.y()){
        img=img.copy(m_endPoint.x(),m_endPoint.y(),m_startPoint.x()-m_endPoint.x(),m_startPoint.y()-m_endPoint.y());
    }
    return img;
}

QRect MyWidget::findRect()
{
    QRect rect;
    //把那块矩形给扣下来
    if(m_endPoint.x()>m_startPoint.x()&&m_endPoint.y()>m_startPoint.y()){
        QRect rect1(m_startPoint.x(),m_startPoint.y(),m_endPoint.x()-m_startPoint.x(),m_endPoint.y()-m_startPoint.y());
        rect=rect1;
    }else if(m_startPoint.x()>m_endPoint.x()&&m_startPoint.y()<m_endPoint.y()){
        QRect rect1(m_endPoint.x(),m_startPoint.y(),m_startPoint.x()-m_endPoint.x(),m_endPoint.y()-m_startPoint.y());
        rect=rect1;
    }else if(m_startPoint.x()<m_endPoint.x()&&m_startPoint.y()>m_endPoint.y()){
        QRect rect1(m_startPoint.x(),m_endPoint.y(),m_endPoint.x()-m_startPoint.x(),m_startPoint.y()-m_endPoint.y());
        rect=rect1;
    }else if(m_startPoint.x()>m_endPoint.x()&&m_startPoint.y()>m_endPoint.y()){
        QRect rect1(m_endPoint.x(),m_endPoint.y(),m_startPoint.x()-m_endPoint.x(),m_startPoint.y()-m_endPoint.y());
        rect=rect1;
    }
    return rect;
}

void MyWidget::compareImage()
{
    cv::Mat img1=cv::imread("/tmp/1.png");
    cv::Mat img2=cv::imread("/tmp/2.png");
    //计算重合区域
    cv::Mat diff;
    absdiff(img1,img2,diff);

    double r=0.0,g=0.0,b=0.0;
    int x=0,y=0,w=0,h=0,y2=0,x1=0,x2=0;
    bool isBreak=false;

     //cols代表图片宽度，rows代表图片的高度
    for (int i = 0; i < diff.rows; i++)
    {
        for (int j = 0; j < diff.cols; j++)
        {
            // 读取每一点HSV值，存在H,S,V变量中。
            r = diff.at<cv::Vec3b>(i, j)[0];
            g = diff.at<cv::Vec3b>(i, j)[1];
            b = diff.at<cv::Vec3b>(i, j)[2];

            if(r==0&&g==0&&b==0){
                x+=1;
            }else{
                isBreak=true;
                break;
            }
        }
        if(x==diff.cols){
            y+=1;
            x=0;
        }
        if(isBreak){
//            x1=x;
            isBreak=false;
            break;
        }
    }

    x=0;
    for (int i = diff.rows-1; i >=0 ; i--)
    {
        for (int j = 0; j < diff.cols; j++)
        {
            // 读取每一点HSV值，存在H,S,V变量中。
            r = diff.at<cv::Vec3b>(i, j)[0];
            g = diff.at<cv::Vec3b>(i, j)[1];
            b = diff.at<cv::Vec3b>(i, j)[2];

            if(r==0&&g==0&&b==0){
                x+=1;
            }else{
                isBreak=true;
                break;
            }
        }
        if(x==diff.cols){
            y2+=1;
            x=0;
        }
        if(isBreak){
            isBreak=false;
            break;
        }
    }

    x=0;
    //cols代表图片宽度，rows代表图片的高度
    for (int i = 0; i < diff.cols; i++)
    {
        for (int j = 0; j < diff.rows; j++)
        {
            // 读取每一点HSV值，存在H,S,V变量中。
            r = diff.at<cv::Vec3b>(j, i)[0];
            g = diff.at<cv::Vec3b>(j, i)[1];
            b = diff.at<cv::Vec3b>(j, i)[2];

            if(r==0&&g==0&&b==0){
                x+=1;
            }else{
                isBreak=true;
                break;
            }
        }
        if(x==diff.rows){
            x1+=1;
            x=0;
        }
        if(isBreak){
            isBreak=false;
            break;
        }
    }

    x=0;
    for (int i = diff.cols-1; i >=0; i--)
    {
        for (int j = diff.rows-1; j>=0; j--)
        {
            // 读取每一点HSV值，存在H,S,V变量中。
            r = diff.at<cv::Vec3b>(j, i)[0];
            g = diff.at<cv::Vec3b>(j, i)[1];
            b = diff.at<cv::Vec3b>(j, i)[2];

            if(r==0&&g==0&&b==0){
                x+=1;
            }else{
                isBreak=true;
                break;
            }
        }
        if(x==diff.rows){
            x2+=1;
            x=0;
        }
        if(isBreak){
            isBreak=false;
            break;
        }
    }

    w=diff.cols-x1-x2;
    h=diff.rows-y-y2;
    if(x1==0&&y==0&&y2==0){   //完全不同
        w=diff.cols;
        h=diff.rows;
        x1=0;
        y=0;
    }else if(x1==diff.cols&&y==diff.rows){//完全相同
        x1=0;
        y=0;
        w=0;
        h=0;
    }

    QRect rect(x1,y,w,h);
    *picDiff=rect;

    qDebug()<<"rect"<<rect;
}

void MyWidget::cutImage(int dir)
{
    if(!picDiff->isEmpty() && moveH!=0){
        //m_flag>=0代表用户一直向下走，或者向下走的区域是大于向上走的区域的
        //此时如果用户向下走是正常操作，向上走不会做任何操作，也就是此时moveH为0
        if(m_flag>=0){
            if(!m_isStartdown){
                m_imgOrigin=m_start;
                cutTopandBotton(m_imgOrigin,m_imgNew);
                qDebug()<<"ok";
                m_isStartdown=true;
            }
            //down向下
            if(dir==1){
                int bottomH=m_imgOrigin.height()-picDiff->y()-picDiff->height();

                m_hecheng=m_hecheng.copy(0,0,m_imgOrigin.width(),m_hecheng.height()-bottomH);
                m_imgOrigin=m_imgNew;
                m_imgNew.save("/tmp/1.png");
                m_imgNew=m_imgNew.copy(0,picDiff->y()+picDiff->height()-moveH,m_imgNew.width(),m_imgNew.height()-picDiff->y()-picDiff->height()+moveH);
                stickImage(m_hecheng,m_imgNew);

            }else if(dir==0){
                m_imgOrigin=m_imgNew;
                moveH=0;
                m_imgNew.save("/tmp/1.png");
            }
        }else{
            //m_flag<0代表用户一直向上走或者用户向上走的距离大于向下走的距离
            //此时如果用户向上走是正常操作，向下走此时不做任何操作,moveH=0
            //检测用户此时是不是第一次向上走的距离超过向下走的距离
            if(!m_isStartup){
                m_imgOrigin=m_start;
                cutTopandBotton(m_imgNew,m_imgOrigin);
                qDebug()<<"ok";
                m_isStartup=true;
            }
            if(dir==0){//向上
                qDebug()<<"向上";
                m_hecheng=m_hecheng.copy(0,picDiff->y(),m_imgOrigin.width(),m_hecheng.height()-picDiff->y());
                m_imgOrigin=m_imgNew;
                m_imgNew.save("/tmp/1.png");
                m_imgNew=m_imgNew.copy(0,0,m_imgNew.width(),picDiff->y()+moveH);
                stickImage(m_imgNew,m_hecheng);
                qDebug()<<"down";
            }else if(dir==1){//向下
                m_imgOrigin=m_imgNew;
                moveH=0;
                m_imgNew.save("/tmp/1.png");
            }
        }
    }
}

void MyWidget::stickImage(QImage hecheng,QImage imgNew)
{
    int m_imgOriginwidth = hecheng.width();
    int m_imgOriginheight = hecheng.height();
    int m_imgNewwidth = imgNew.width();
    int m_imgNewheight = imgNew.height();

    int newImageWidth = m_imgOriginwidth >= m_imgNewwidth ? m_imgOriginwidth : m_imgNewwidth;
    int newImageHeight = m_imgOriginheight + m_imgNewheight;

    QPixmap newImage(newImageWidth, newImageHeight);   //1.创建大图（使用QImage类也可以）
    QPainter p(&newImage);

    //2.绘制两幅小图到QPixmap上
    QRect imgRect2(0,hecheng.height(), imgNew.width(), imgNew.height());
   p.drawImage(imgRect2, imgNew);
    QRect imgRect1(0, 0, hecheng.width(), hecheng.height());
    p.drawImage(imgRect1, hecheng);

    QPixmap image = newImage;   //控制缩放比例，因为label显示有大小限制
    qDebug()<<"合成图片进行保存";
    m_hecheng=image.toImage();
}

//这个函数的作用是将两张图片相同的部分去掉，只留下中间不同的部分，然后计算moveH
void MyWidget::cutTopandBotton(QImage one, QImage two)
{
    m_imgone=one;
    m_imgtwo=two;
    if((picDiff->x()>=0)||(picDiff->width()<m_imgOrigin.width())){
        //代表两张图片左边相同的距离
        int left=m_imgOrigin.width()-picDiff->width();
        //裁剪图片
        m_imgone=m_imgone.copy(picDiff->x(),picDiff->y(),m_imgOrigin.width()-left,picDiff->height());
        m_imgtwo=m_imgtwo.copy(picDiff->x(),picDiff->y(),m_imgOrigin.width()-left,picDiff->height());
    }
    m_imgone=m_imgone.convertToFormat(QImage::Format_RGB888);
    m_imgtwo=m_imgtwo.convertToFormat(QImage::Format_RGB888);
    moveH=compute_moveh(qim2mat(m_imgone),qim2mat(m_imgtwo));
}

cv::Mat MyWidget::qim2mat(QImage qim)
{
    cv::Mat mat;
    switch(qim.format()){
        case QImage::Format_RGB888:
            mat = cv::Mat(qim.height(), qim.width(),
                CV_8UC3,(void*)qim.bits(),qim.bytesPerLine());
            break;
        case QImage::Format_ARGB32_Premultiplied:
            mat = cv::Mat(qim.height(), qim.width(),
                CV_8UC4,(void*)qim.bits(),qim.bytesPerLine());
            break;
        default:
            break;
    }
    return mat;
}

//这个是一个计算moveH的函数
//也是计算m_flag的函数，就是检测是上移距离大于下移的距离，还是下移的距离大于上移的距离
void MyWidget::computeMoveH(int dir)
{
    //这个函数是比较两张图片，返回中间不同的区域范围给picDiff这个私有属性，这个函数要写在cutTopandBotton这个函数上面
    QRect* rect1=new QRect(-1,-1,-1,-1);
    QRect* rect2=new QRect(0,0,0,0);
    if(*picDiff==*rect1||*picDiff==*rect2){
        compareImage();
        qDebug()<<picDiff->x()<<picDiff->y()<<picDiff->width()<<picDiff->height();
    }
    //这个if语句是检测两张图片是否有不同的部分，也就是看两张图片是否完全相同
    //如果两张图片完全相同，moveH应该为0
    //如果两张图片不是完全相同，要计算moveH m_flag,也就是其移动的距离 相对距离
    QRect *rect=new QRect{0,0,0,0};
    if(*picDiff!=*rect){
        //0向上，1向下
        if(dir==1){
            //如果是向下走，m_flag要加上moveH
            cutTopandBotton(m_imgOrigin,m_imgNew);
            m_flag+=moveH;
        }else if(dir==0) {
            //如果是向上走,m_flag要减去moveH
            cutTopandBotton(m_imgNew,m_imgOrigin);
            m_flag-=moveH;
        }else{
            qDebug()<<"error";
        }
        qDebug()<<"flag="<<m_flag;
    }else{
        moveH=0;
    }
    delete rect;
}

