#include "share.h"
#include <QDesktopServices>
#include <QUrl>
#include  <QProcess>
#include <QDebug>
#include <QPainter>
#include <QPrinter>
#include <QPrintDialog>

Share::Share(QWidget *parent) : QWidget(parent)
{

}

void Share::sendMail()
{
    QDesktopServices::openUrl(QUrl("https://mail.qq.com"));
}

void Share::shareToQQ()
{
    system("qq");
}

void Share::shareToWeChat()
{
    QDesktopServices::openUrl(QUrl("https://wx.qq.com"));
}

void Share::startPrinter()
{
    QImage img;
    img.load("/tmp/1.jpg");
    //将打印设备的分辨率设置为屏幕分辨率。这有很大的好处，当在打印机上作画时，得到的结果将或多或少与屏幕上可见的输出相匹配。它是最容易使用的，因为屏幕上和打印机上的字体参数是相同的。这是默认值。屏幕分辨率将产生一个较低的质量输出比高分辨率，应该只用于草案。
    QPrinter printer(QPrinter::ScreenResolution);
    QPrintDialog printDialog(&printer);
    //判断打印对话框显示后用户是否单击“打印”按钮
    if (printDialog.exec() == QDialog::Accepted) {
        QPainter painterimg;
        painterimg.begin(&printer);
        QRect rect =painterimg.viewport();  //获得QPainter对象的视图矩形区域
        QSize size = img.size(); //获得图像的大小
        /* 按照图形的比例大小重新设置视图矩形区域 */
        size.scale(rect.size(),Qt::KeepAspectRatio);
        painterimg.setViewport(rect.x(),rect.y(),size.width(),size.height());
        painterimg.setWindow(img.rect());   //设置QPainter窗口大小为图像的大小
        painterimg.drawImage(0,0,img);	//打印图像
        painterimg.end();
    }
}



