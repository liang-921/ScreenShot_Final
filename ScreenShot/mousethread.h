/*
 * This library is used to detect global mouse wheel events at any time and send signals when the mouse wheel moves up or down
 *
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

#ifndef MOUSETHREAD_H
#define MOUSETHREAD_H

#include <QThread>
#include <QFile>
#include <X11/Xlib.h>
#include <X11/extensions/record.h>
#include <X11/Xlibint.h>

// Virtual button codes that are not defined by X11.
#define WheelUp			4
#define WheelDown		5

class MouseThread : public QThread
{
    Q_OBJECT

public:
    MouseThread(QObject* obj);
signals:
    void mouseWhileUp(int i,int dir);
    void mouseWhileDown(int i,int dir);
protected:
    static void callback(XPointer ptr, XRecordInterceptData* data);
    void handleRecordEvent(XRecordInterceptData *);
    void run() Q_DECL_OVERRIDE;

private:
    QObject * m_obj;
};

#endif // MOUSETHREAD_H
