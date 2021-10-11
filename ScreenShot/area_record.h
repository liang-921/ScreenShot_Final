#ifndef GITWIDGET_H
#define GITWIDGET_H

#include <QDialog>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QSpacerItem>
#include <QLineEdit>
#include <QTimer>
#include <QPainter>
#include <QPaintEvent>
#include <QEvent>
#include <QFileDialog>
#include <QApplication>
#include <QDesktopServices>
#include <QScreen>
#include "gif.h"

class Area_Record : public QDialog
{
    Q_OBJECT
public:
    explicit Area_Record(QWidget *parent = 0);

    QWidget *widgetTop;
    QWidget *widgetMain;
    QWidget *widgetBottom;

    QLineEdit *txtFps;
    QLineEdit *txtWidth;
    QLineEdit *txtHeight;

    QLabel *labStatus;

    QPushButton *btnStart;

    int borderWidth;
    int fps;
    int count;
    QColor bgColor;
    QRect rectGif;
    QString fileName;

    QTimer *timer;

    Gif gif;
    Gif::GifWriter *gifWriter;
signals:
    void finish();
public slots:
    void closeAll();
    void record();
    void resizeForm();
    void saveImage();

protected:
    virtual bool eventFilter(QObject *, QEvent *);
    virtual void resizeEvent(QResizeEvent *);
    virtual void paintEvent(QPaintEvent *);
};

#endif // GITWIDGET_H
