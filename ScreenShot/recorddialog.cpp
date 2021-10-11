#include <QApplication>
#include <QProcess>
#include <QTimer>
#include <QDebug>
#include <QDateTime>
#include <QDesktopWidget>
#include "recorddialog.h"
#include "ui_recorddialog.h"

RecordDialog::RecordDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RecordDialog)
{
    ui->setupUi(this);
    setWindowFlags(windowFlags()&~Qt::WindowMinMaxButtonsHint);
    setWindowFlags(Qt::WindowStaysOnTopHint);
    setWindowOpacity(0.6);

    QDesktopWidget *widget= QApplication::desktop();
    move(widget->width()-this->width(),widget->height()-this->height());

    ui->startBt->setStyleSheet("QPushButton{"
                               "border:2px groove gray;border-radius:10px;"
                               "padding:2px 4px;border-style: outset;}"
                               "QPushButton:hover{background-color:rgb(229, 241, 251); color: red;}"
                               "QPushButton:pressed{background-color:rgb(204, 228, 247);"
                               "border-style: inset;}");
    ui->stopBt->setStyleSheet("QPushButton{"
                              "border:2px groove gray;border-radius:10px;"
                              "padding:2px 4px;border-style: outset;}"
                              "QPushButton:hover{background-color:rgb(229, 241, 251); color: black;}"
                              "QPushButton:pressed{background-color:rgb(204, 228, 247);"
                              "border-style: inset;}");
    connect(ui->startBt,SIGNAL(clicked()),this,SLOT(start()));
    connect(ui->stopBt,SIGNAL(clicked()),this,SLOT(stop()));
    //    connect(this,SIGNAL(close()),this,SLOT(closeAll()));
}

RecordDialog::~RecordDialog()
{
    delete ui;
}

void RecordDialog::start()
{
    QString program = "ffmpeg";
    QString filename= "/tmp/"+QDateTime::currentDateTime().toString("yyyy-MM-dd-hh:mm:ss") + ".mkv";

    QStringList arguments;
    arguments<<"-video_size"<<"1920x1080"<<"-framerate"<<"25"<<"-f"<<"x11grab"
            <<"-i"<<":0.0"<<"-f"<<"pulse"<<"-ac"<<"2"<<"-i"<<"default"<<filename;

    p->startDetached(program,arguments);

}

void RecordDialog::exec(const char *cmd)
{
    FILE* pipe = popen(cmd, "r");
    //if (!pipe) return "ERROR";
    char buffer[128];
    std::string result = "";
    while(!feof(pipe)) {
        if(fgets(buffer, 128, pipe) != NULL)
            result += buffer;
    }
    pclose(pipe);
    //    return result;
}

void RecordDialog::sleep(unsigned int msec)
{
    QTime dieTime = QTime::currentTime().addMSecs(msec);
    while( QTime::currentTime() < dieTime )
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

void RecordDialog::closeEvent(QCloseEvent *e)
{
     Q_UNUSED(e);
    emit finishRecord();
}

void RecordDialog::startRecord()
{
    Area_Record *area_record = new Area_Record();
    area_record->show();
    connect(area_record,SIGNAL(finish()),this,SLOT(closeAll()));
}

void RecordDialog::stop()
{

    this->close();
    emit finishRecord();
    sleep(4000);
    //关闭录制
    qDebug()<<"关闭录制";
    exec("kill -9 $(ps -ef|grep ffmpeg|grep -v grep|awk '{print $2}')");
    //    exec("ps aux | grep ffmpeg | grep -v grep | awk '{print $2}' | sudo xargs kill -9");
}

void RecordDialog::closeAll()
{
    close();
    emit finishRecord();
}
