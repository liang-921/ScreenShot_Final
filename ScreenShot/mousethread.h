/*
 * 这个库是用来随时检测全局鼠标滚轮事件，当鼠标滚轮上移或者下移时发送信号
 *
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
