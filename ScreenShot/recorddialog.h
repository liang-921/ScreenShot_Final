#ifndef RECORDDIALOG_H
#define RECORDDIALOG_H

#include <QDialog>
#include <QProcess>
#include "area_record.h"

namespace Ui {
class RecordDialog;
}

class RecordDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RecordDialog(QWidget *parent = nullptr);
    ~RecordDialog();

private:
    //exec对命令行参数进行解析
    void exec(const char* cmd);
    void sleep(unsigned int msec);
    void closeEvent(QCloseEvent *e);
signals:
    void finishRecord();
public slots:
    void startRecord();
    void closeAll();
    void start();
    void stop();

private:
    QProcess *p;
    Ui::RecordDialog *ui;
};

#endif // RECORDDIALOG_H
