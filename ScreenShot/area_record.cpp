#include "area_record.h"

Area_Record::Area_Record(QWidget *parent) : QDialog(parent)
{
    setObjectName("AreaArea_Record");
    resize(800, 600);
    setSizeGripEnabled(true);

    QVBoxLayout *verticalLayout = new QVBoxLayout(this);
    verticalLayout->setSpacing(0);
    verticalLayout->setContentsMargins(0,0,0,0);

    widgetMain = new QWidget(this);
    QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Expanding);
    sizePolicy1.setHorizontalStretch(0);
    sizePolicy1.setVerticalStretch(0);
    sizePolicy1.setHeightForWidth(widgetMain->sizePolicy().hasHeightForWidth());
    widgetMain->setSizePolicy(sizePolicy1);
    verticalLayout->addWidget(widgetMain);

    widgetBottom = new QWidget(this);
    widgetBottom->setMinimumSize(0, 45);
    widgetBottom->setMaximumSize(8000, 45);

    QHBoxLayout *layoutBottom = new QHBoxLayout(widgetBottom);
    layoutBottom->setSpacing(6);
    layoutBottom->setContentsMargins(9,9,-1,-1);

    QLabel *labFps = new QLabel(widgetBottom);
    layoutBottom->addWidget(labFps);

    txtFps = new QLineEdit(widgetBottom);
    txtFps->setMaximumSize(50, 12580);
    txtFps->setAlignment(Qt::AlignCenter);
    layoutBottom->addWidget(txtFps);

    QLabel *labWidth = new QLabel(widgetBottom);
    layoutBottom->addWidget(labWidth);

    txtWidth = new QLineEdit(widgetBottom);
    txtWidth->setEnabled(true);
    txtWidth->setMaximumSize(50, 12580);
    txtWidth->setAlignment(Qt::AlignCenter);
    layoutBottom->addWidget(txtWidth);

    QLabel *labHeight = new QLabel(widgetBottom);
    layoutBottom->addWidget(labHeight);

    txtHeight = new QLineEdit(widgetBottom);
    txtHeight->setMaximumSize(50, 12580);
    txtHeight->setAlignment(Qt::AlignCenter);
    layoutBottom->addWidget(txtHeight);

    labStatus = new QLabel(widgetBottom);
    QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Preferred);
    sizePolicy2.setHorizontalStretch(0);
    sizePolicy2.setHeightForWidth(labStatus->sizePolicy().hasHeightForWidth());
    sizePolicy2.setVerticalStretch(0);
    labStatus->setSizePolicy(sizePolicy2);
    layoutBottom->addWidget(labStatus);

    btnStart = new QPushButton(widgetBottom);
    QSizePolicy sizePolicy;
    sizePolicy.setHeightForWidth(btnStart->sizePolicy().hasHeightForWidth());
    btnStart->setSizePolicy(sizePolicy);
    layoutBottom->addWidget(btnStart);
    verticalLayout->addWidget(widgetBottom);

    QPushButton *btnClose = new QPushButton(widgetBottom);
    sizePolicy.setHeightForWidth(btnStart->sizePolicy().hasHeightForWidth());
    btnStart->setSizePolicy(sizePolicy);
    layoutBottom->addWidget(btnClose);
    verticalLayout->addWidget(widgetBottom);

    labFps->setText("帧率");
    labWidth->setText("宽度");
    labHeight->setText("高度");
    btnStart->setText("开始");
    btnClose->setText("关闭");

    connect(btnStart, SIGNAL(clicked()), this, SLOT(record()));
    connect(txtWidth, SIGNAL(editingFinished()), this, SLOT(resizeForm()));
    connect(txtHeight, SIGNAL(editingFinished()), this, SLOT(resizeForm()));
    connect(btnClose, SIGNAL(clicked()), this, SLOT(closeAll()));

    borderWidth = 1;
    bgColor = QColor("grey");

    fps = 10;
    txtFps->setText(QString::number(fps));
    gifWriter = 0;

    timer = new QTimer(this);
    timer->setInterval(100);
    connect(timer, &QTimer::timeout, this, &Area_Record::saveImage);

    setAttribute(Qt::WA_TranslucentBackground);
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    installEventFilter(this);


    txtWidth->setEnabled(true);
    txtHeight->setEnabled(true);

    labStatus->setObjectName("labStatus");

//    QStringList qss;
//    qss.append("QLabel{color:#ffffff;}");
//    qss.append("#btnClose,#btnIcon{border:none;border-radius:0px;}");
//    qss.append("#btnClose:hover{background-color:#ff0000;}");
//    qss.append("#btnClose{border-top-right-radius:5px;}");
//    qss.append("#labTitle{font:bold 16px;}");
//    qss.append("#labStatus{font:15px;}");
//    setStyleSheet(qss.join(""));
}

void Area_Record::closeAll()
{
    close();
    emit finish();
}

void Area_Record::record()
{
    if(btnStart->text() == "开始")
    {
        setFixedSize(this->width(),this->height());

        if(gifWriter != 0)
        {
            delete gifWriter;
            gifWriter = 0;
        }

        fileName = QFileDialog::getSaveFileName(this, "保存", qApp->applicationDirPath() + "/", "视频(*.mkv)");
        if(fileName.isEmpty())
            return ;

        int width = txtWidth->text().toInt();
        int height = txtHeight->text().toInt();
        fps = txtFps->text().toInt();

        gifWriter = new Gif::GifWriter;
        bool ok = gif.GifBegin(gifWriter, fileName.toLocal8Bit().data(), width, height, fps);
        if(!ok)
        {
            delete gifWriter;
            gifWriter = 0;
            return ;
        }

        count = 0;
        labStatus->setText("开始录制...");
        btnStart->setText("停止");

        timer->setInterval(1000/fps);
        QTimer::singleShot(1000, timer, SLOT(start()));
    }
    else
    {
        timer->stop();
        gif.GifEnd(gifWriter);

        delete gifWriter;
        gifWriter = 0;

        labStatus->setText(QString("录制完成 共 %1 帧").arg(count));
        btnStart->setText("开始");

        QDesktopServices::openUrl(QUrl(fileName));
    }
}

void Area_Record::resizeForm()
{
    int width = txtWidth->text().toInt();
    int height = txtHeight->text().toInt();
    resize(width, height+widgetBottom->height());
}

bool Area_Record::eventFilter(QObject *watched, QEvent *e)
{
    static QPoint mousePoint;
    static bool mousePressed = false;

    QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(e);
    if(mouseEvent->type() == QEvent::MouseButtonPress)
    {
        if(mouseEvent->button() == Qt::LeftButton)
        {
            mousePressed = true;
            mousePoint = mouseEvent->globalPos()-this->pos();
            return true;
        }
    }
    else if(mouseEvent->type() == QEvent::MouseButtonRelease)
    {
        mousePressed = false;
        return true;
    }
    else if(mouseEvent->type() == QEvent::MouseMove)
    {
        if(mousePressed)
        {
            this->move(mouseEvent->globalPos() - mousePoint);
            return true;
        }
    }

    return QWidget::eventFilter(watched, e);
}

void Area_Record::resizeEvent(QResizeEvent *e)
{
    txtWidth->setText(QString::number(widgetMain->width()));
    txtHeight->setText(QString::number(widgetMain->height()));
    QDialog::resizeEvent(e);
}

void Area_Record::paintEvent(QPaintEvent *)
{
    int width = txtWidth->text().toInt();
    int height = txtHeight->text().toInt();

    rectGif = QRect(borderWidth,1, width-(borderWidth*2), height);

    QPainter painter(this);
    painter.setPen(Qt::NoPen);
    painter.setBrush(bgColor);
    painter.drawRoundedRect(this->rect(), 5, 5);
    //定义数字图像合成支持的模式。组合模式用于指定如何将源图像中的像素与目标图像中的像素合并。
    painter.setCompositionMode(QPainter::CompositionMode_Clear);//目标中的像素被清除(设置为完全透明)，独立于源。
    painter.fillRect(rectGif, Qt::SolidPattern);
}

void Area_Record::saveImage()
{
    if(gifWriter == 0)
    {
        return ;
    }

    QScreen *screen = QApplication::primaryScreen();
    QPixmap pixmap = screen->grabWindow(0, x()+rectGif.x(), y()+rectGif.y(), rectGif.width(), rectGif.height());
    QImage image = pixmap.toImage().convertToFormat(QImage::Format_RGBA8888);

    gif.GifWriteFrame(gifWriter, image.bits(), rectGif.width(), rectGif.height(), fps);
    count++;
    labStatus->setText(QString("正在录制 第 %1 帧").arg(count));
}
