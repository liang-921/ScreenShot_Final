#ifndef MOSAIC_H
#define MOSAIC_H

#include <QDialog>

namespace Ui {
class Mosaic;
}

class Mosaic : public QDialog
{
    Q_OBJECT

public:
    explicit Mosaic(QWidget *parent = nullptr);
    ~Mosaic();

    void paintEvent(QMouseEvent *e);
    void mousePressEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::Mosaic *ui;

    QImage m_Image;
    QPixmap m_pixmap;
    QPoint m_point;
    QPoint m_oldPoint;
};

#endif // MOSAIC_H
