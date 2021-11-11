/*
 * author: 李梦雪 梁淑贞 张宝丹
 * email：2304768518@qq.com 2239602082@qq.com 1395089569@qq.com
 * time:2021.10

 * Copyright (C) <2021>  <Mengxue Li,Shuzhen Liang,Baodan zhang>

 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */
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
