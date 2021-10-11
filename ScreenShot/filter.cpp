#include "filter.h"
#include "ui_filter.h"

#include <math.h>
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <QFileDialog>
#include "mosaic.h"

Filter::Filter(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Filter)
{
    ui->setupUi(this);
    update();

    setWindowTitle("滤镜");

    m_Image.load("/tmp/1.jpg");
    m_pixmap = QPixmap::fromImage(m_Image).scaled(size(),Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ui->label->setPixmap(m_pixmap);
    ui->label->setScaledContents(true);

    connect(ui->btn_grey,SIGNAL(clicked()),this,SLOT(grey()));
    connect(ui->btn_cool,SIGNAL(clicked()),this,SLOT(cool()));
    connect(ui->btn_warm,SIGNAL(clicked()),this,SLOT(warm()));
    connect(ui->btn_old,SIGNAL(clicked()),this,SLOT(old()));
    connect(ui->btn_vague,SIGNAL(clicked()),this,SLOT(vague()));
    connect(ui->btn_reverse,SIGNAL(clicked()),this,SLOT(reverse()));
    connect(ui->btn_sharpen,SIGNAL(clicked()),this,SLOT(sharpen()));
    connect(ui->btn_soften,SIGNAL(clicked()),this,SLOT(soften()));
}

Filter::~Filter()
{
    delete ui;
}

void Filter::coolImage(int delta)
{
    QImage tmp = m_Image.copy();

    int r,g,b;
    QColor frontColor;
    for(int x=0; x<tmp.width(); x++){
        for(int y=0; y<tmp.height(); y++){
            frontColor = QColor(m_Image.pixel(x,y));

            r = frontColor.red();
            g = frontColor.green();
            b = frontColor.blue()+delta;

            //we check if the new value is between 0 and 255
            b = qBound(0, b, 255);

            tmp.setPixel(x,y, qRgb(r,g,b));
        }
    }

    m_pixmap = QPixmap::fromImage(tmp).scaled(size(),Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ui->label_2->setPixmap(m_pixmap);
    ui->label_2->setScaledContents(true);
    update();
}

void Filter::warmImage(int delta)
{
    QImage tmp = m_Image.copy();

    int r,g,b;
    QColor frontColor;
    for(int x=0; x<tmp.width(); x++){
        for(int y=0; y<tmp.height(); y++){
            frontColor = QColor(m_Image.pixel(x,y));

            r = frontColor.red()+delta;
            g = frontColor.green()+delta;
            b = frontColor.blue();

            //we check if the new value is between 0 and 255
            r = qBound(0, r, 255);
            g = qBound(0,g,255);

            tmp.setPixel(x,y, qRgb(r,g,b));
        }
    }
    m_pixmap = QPixmap::fromImage(tmp).scaled(size(),Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ui->label_2->setPixmap(m_pixmap);
    ui->label_2->setScaledContents(true);
    update();
}

void Filter::mosaic()
{
    Mosaic *mosaic = new Mosaic();
    mosaic->show();
}

//灰度
void Filter::grey()
{
    //    m_Image.load("/root/images/04.jpg");
    QImage tmp = m_Image.copy();
    for (int i = 0; i < m_Image.width(); i++)
    {
        for (int j = 0; j < m_Image.height(); j++)
        {
            QColor oriColor = m_Image.pixel(i, j);
            int average = (oriColor.red() + oriColor.green() + oriColor.blue()) / 3;
            oriColor = QColor(average, average, average);
            tmp.setPixelColor(i, j, oriColor);
        }
    }
    m_pixmap = QPixmap::fromImage(tmp).scaled(size(),Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ui->label_2->setPixmap(m_pixmap);
    ui->label_2->setScaledContents(true);
    update();
}

//老照片
void Filter::old()
{
    QImage tmp = m_Image.copy();

    QColor frontColor;
    for(int x=0; x<tmp.width(); x++){
        for(int y=0; y<tmp.height(); y++){
            frontColor = QColor(m_Image.pixel(x,y));

            int r = 0.393 * frontColor.red() + 0.769 * frontColor.green() + 0.189 * frontColor.blue();
            int g = 0.349 * frontColor.red() + 0.686 * frontColor.green() + 0.168 * frontColor.blue();
            int b = 0.272 * frontColor.red() + 0.534 * frontColor.green() + 0.131 * frontColor.blue();
            r = qBound(0, r, 255);
            g = qBound(0, g, 255);
            b = qBound(0, b, 255);

            tmp.setPixel(x,y, qRgb(r,g,b));
        }
    }

    m_pixmap = QPixmap::fromImage(tmp).scaled(size(),Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ui->label_2->setPixmap(m_pixmap);
    ui->label_2->setScaledContents(true);
    update();
}

//打开
void Filter::on_open_clicked()
{
    QString path=QFileDialog::getOpenFileName();
    m_Image.load(path);
    m_pixmap = QPixmap::fromImage(m_Image).scaled(size(),Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ui->label->setPixmap(m_pixmap);
    ui->label->setScaledContents(true);
    update();
}

//暖调
void Filter::warm()
{
    warmImage(30);
}

//冷调
void Filter::cool()
{
    coolImage(50);
}

//模糊
void Filter::vague()
{

    int kernel [5][5]= {{0,0,1,0,0},
                        {0,1,3,1,0},
                        {1,3,7,3,1},
                        {0,1,3,1,0},
                        {0,0,1,0,0}};
    int kernelSize = 5;
    int sumKernel = 27;
    int r,g,b;
    QColor color;

    QImage tmp = m_Image.copy();
    for(int x=kernelSize/2; x<tmp.width()-(kernelSize/2); x++){
        for(int y=kernelSize/2; y<tmp.height()-(kernelSize/2); y++){

            r = 0;
            g = 0;
            b = 0;

            for(int i = -kernelSize/2; i<= kernelSize/2; i++){
                for(int j = -kernelSize/2; j<= kernelSize/2; j++){
                    color = QColor(m_Image.pixel(x+i, y+j));
                    r += color.red()*kernel[kernelSize/2+i][kernelSize/2+j];
                    g += color.green()*kernel[kernelSize/2+i][kernelSize/2+j];
                    b += color.blue()*kernel[kernelSize/2+i][kernelSize/2+j];
                }
            }

            r = qBound(0, r/sumKernel, 255);
            g = qBound(0, g/sumKernel, 255);
            b = qBound(0, b/sumKernel, 255);

            tmp.setPixel(x,y, qRgb(r,g,b));
        }
    }

    m_pixmap = QPixmap::fromImage(tmp).scaled(size(),Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ui->label_2->setPixmap(m_pixmap);
    ui->label_2->setScaledContents(true);
    update();
}

//反色
void Filter::reverse()
{
    QImage tmp = m_Image.copy();

    int r,g,b;
    QColor frontColor;
    for(int x=0; x<tmp.width(); x++){
        for(int y=0; y<tmp.height(); y++){
            frontColor = QColor(m_Image.pixel(x,y));

            r = frontColor.red();
            g = frontColor.green();
            b = frontColor.blue();

            tmp.setPixel(x,y, qRgb(255-r,255-g,255-b));
        }
    }

    m_pixmap = QPixmap::fromImage(tmp).scaled(size(),Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ui->label_2->setPixmap(m_pixmap);
    ui->label_2->setScaledContents(true);
    update();
}

//锐化
void Filter::sharpen()
{
    int kernel [3][3]= {{0,-1,0},
                        {-1,5,-1},
                        {0,-1,0}};
    int kernelSize = 3;
    int sumKernel = 1;
    int r,g,b;
    QColor color;

    QImage tmp = m_Image.copy();
    for(int x=kernelSize/2; x<tmp.width()-(kernelSize/2); x++){
        for(int y=kernelSize/2; y<tmp.height()-(kernelSize/2); y++){

            r = 0;
            g = 0;
            b = 0;

            for(int i = -kernelSize/2; i<= kernelSize/2; i++){
                for(int j = -kernelSize/2; j<= kernelSize/2; j++){
                    color = QColor(tmp.pixel(x+i, y+j));
                    r += color.red()*kernel[kernelSize/2+i][kernelSize/2+j];
                    g += color.green()*kernel[kernelSize/2+i][kernelSize/2+j];
                    b += color.blue()*kernel[kernelSize/2+i][kernelSize/2+j];
                }
            }

            r = qBound(0, r/sumKernel, 255);
            g = qBound(0, g/sumKernel, 255);
            b = qBound(0, b/sumKernel, 255);

            tmp.setPixel(x,y, qRgb(r,g,b));

        }
    }
    m_pixmap = QPixmap::fromImage(tmp).scaled(size(),Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ui->label_2->setPixmap(m_pixmap);
    ui->label_2->setScaledContents(true);
    update();
}

//柔化
void Filter::soften()
{

    QImage tmp = m_Image.copy();
    int r,g,b;
    QRgb color;
    for(int x=1; x<tmp.width()-1; x++){
        for(int y=1; y<tmp.height()-1; y++){
            r = 0; g = 0; b = 0;
            for(int m = 0; m < 9; m++)
            {
                int s = 0;
                int p = 0;
                switch(m){
                    case 0: s = x - 1;  p = y - 1;  break;
                    case 1: s = x;  p = y - 1;  break;
                    case 2: s = x + 1 ;  p = y -1;  break;
                    case 3: s = x + 1;  p = y ;  break;
                    case 4: s = x + 1;  p = y + 1;  break;
                    case 5: s = x;  p = y + 1;  break;
                    case 6: s = x - 1;  p = y + 1;  break;
                    case 7: s = x - 1;  p = y ;  break;
                    case 8: s = x;  p = y;  break;
                }
                color = tmp.pixel(s, p);
                r += qRed(color);
                g += qGreen(color);
                b += qBlue(color);
            }

            r = (int) (r / 9.0);
            g = (int) (g / 9.0);
            b = (int) (b / 9.0);

            r = qMin(255, qMax(0, r));
            g = qMin(255, qMax(0, g));
            b = qMin(255, qMax(0, b));

            tmp.setPixel(x, y, qRgb(r, g, b));
        }
    }

    m_pixmap = QPixmap::fromImage(tmp).scaled(size(),Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ui->label_2->setPixmap(m_pixmap);
    ui->label_2->setScaledContents(true);
    update();
}

void Filter::on_btn_saveas_clicked()
{
    QString path=QFileDialog::getSaveFileName(this,tr("另存为"),tr(""),tr("图片(*.png *.jpeg *.jpg)"));
    m_pixmap.save(path);
}

