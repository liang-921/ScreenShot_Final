#include "mosaic.h"
#include "ui_mosaic.h"

#include <QPainter>
#include <QMouseEvent>
#include <QFileDialog>
#include <QBrush>
#include <QDebug>

Mosaic::Mosaic(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Mosaic)
{
    ui->setupUi(this);

    setWindowTitle(tr("马赛克"));

    ui->scrollArea->setWidget(ui->label);
    m_Image.load("/tmp/1.jpg");
    m_pixmap = QPixmap::fromImage(m_Image).scaled(size()/*,Qt::KeepAspectRatio,Qt::SmoothTransformation*/);
    ui->label->setPixmap(m_pixmap);
}

Mosaic::~Mosaic()
{
    delete ui;
}

void Mosaic::paintEvent(QMouseEvent *e)
{
    Q_UNUSED(e)
    QPainter p(ui->scrollArea);
    p.drawPixmap(0,0,m_pixmap);
}

void Mosaic::mousePressEvent(QMouseEvent *e)
{
    if(e->button() == Qt::LeftButton)
    {
        qDebug()<<"鼠标按压";
        QPainter p;
        p.begin(&m_pixmap);

        QPoint temp_point;
        if(e->pos().x()%20 > 0){
            temp_point.setX(e->pos().x()/20*20 + 10);
        }
        else{
            temp_point.setX(e->pos().x()/20*20 - 10);
        }

        if(e->pos().y()%20 > 0){
            temp_point.setY(e->pos().y()/20*20 + 10);
        }else{
            temp_point.setY(e->pos().y()/20*20 - 10);
        }

        QRgb rgb = m_Image.pixel(temp_point);
        QColor color;
        color.setRgb(rgb);
        color.setAlpha(180);
        QPen pen;
        pen.setColor(color);
        QRect rect(temp_point.x()-10,temp_point.y()-10,20,20);
        p.fillRect(rect,color);
        p.end();
        update();
    }
}

void Mosaic::mouseMoveEvent(QMouseEvent *e)
{
    {
        QPainter *p = new QPainter;
        p->begin(&m_pixmap);

        QPoint temp_point;
        if(e->pos().x()%20 > 0){
            temp_point.setX(e->pos().x()/20*20 + 10);
        }
        else{
            temp_point.setX(e->pos().x()/20*20 - 10);
        }
        if(e->pos().y()%20 > 0){
            temp_point.setY(e->pos().y()/20*20 + 10);
        }
        else{
            temp_point.setY(e->pos().y()/20*20 - 10);
        }
        QRgb rgb = m_Image.pixel(temp_point);
        QColor color;
        color.setRgb(rgb);
        color.setAlpha(180);
        QPen pen;
        pen.setColor(color);
        QRect rect(temp_point.x()-10,temp_point.y()-10,20,20);
        p->fillRect(rect,color);
        p->end();
        update();
        ui->label->setPixmap(m_pixmap);
    }

//    m_pixmap.save("/root/new.png");
}

//重置
void Mosaic::on_pushButton_clicked()
{
    m_Image.load("/tmp/1.jpg");
    m_pixmap = QPixmap::fromImage(m_Image).scaled(size(),Qt::KeepAspectRatio);
    ui->label->setPixmap(m_pixmap);
}

//另存为
void Mosaic::on_pushButton_2_clicked()
{
    QString path=QFileDialog::getSaveFileName(this,tr("另存为"),tr(""),tr("图片(*.png *.jpeg *.jpg)"));
    m_pixmap.save(path);
}

//打开
void Mosaic::on_pushButton_3_clicked()
{
    QString path=QFileDialog::getOpenFileName();
    m_Image.load(path);
    m_pixmap = QPixmap::fromImage(m_Image).scaled(size()/*,Qt::KeepAspectRatio,Qt::SmoothTransformation*/);
    ui->label->setPixmap(m_pixmap);
    ui->label->setScaledContents(true);
    update();
}

