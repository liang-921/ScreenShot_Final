#include "mousethread.h"

MouseThread::MouseThread(QObject *obj):
    m_obj(obj)
{
}

void MouseThread::callback(XPointer ptr, XRecordInterceptData *data)
{
    ((MouseThread*) ptr)->handleRecordEvent(data);
}

void MouseThread::handleRecordEvent(XRecordInterceptData * data)
{
    if (data->category == XRecordFromServer) {
        data->client_swapped = false;
        xEvent * event = (xEvent *)data->data;
        switch (event->u.u.type) {
        case ButtonPress:
            if(event->u.u.detail == WheelUp){
                emit mouseWhileUp(2,0);
            } else if(event->u.u.detail == WheelDown){
                emit mouseWhileDown(2,1);
            }
        default:
            break;
        }
    }

    //资源释放
    fflush(stdout);
    XRecordFreeData(data);
}


//该函数应该随时用来监听鼠标滚轮的状态
void MouseThread::run()
{
    //创建、记录 XRecord 协议的X专属连接
    Display* display = XOpenDisplay(0);
    // 连接打开检查
    if (display == 0) {
        fprintf(stderr, "unable to open display\n");
        return;
    }

    //初始化 XRecorfCreateContext 所需的 XRecordClientSpec参数
    //XRecordAllClients的意思是“记录所有 X Client ”的事件
    XRecordClientSpec clients = XRecordAllClients;
    //XRecordRange 用于控制记录事件的范围
    XRecordRange* range = XRecordAllocRange();
    if (range == 0) {
        fprintf(stderr, "unable to allocate XRecordRange\n");
        return;
    }

    //初始化记录事件范围，范围开头设置成KeyPress,范围结尾设置成 MotionNotify后，事件类型就包括 KeyPress\KeyRlease\ButtonPress\ButtonRlease\MotionNotify
    memset(range, 0, sizeof(XRecordRange));
    range->device_events.first = KeyPress;
    range->device_events.last  = MotionNotify;

    //根据上面的记录客户端类型和记录事件范围来创建“记录上下文”
    //然后把 XRecordContext 传递给 XRecordCreateCOntext 函数开始事件循环
    XRecordContext context = XRecordCreateContext(display, 0, &clients, 1, &range, 1);
    if (context == 0) {
        fprintf(stderr, "XRecordCreateContext failed\n");
        return;
    }
    //释放range 指针
    XFree(range);

    // XSync 的作用就是把上面的 X 代码立即发给 X Server
    // 这样 X Server 接受到事件以后会立即发送给 XRecord 的 Client 连接
    XSync(display, False);

    // 建立一个专门读取 XRecord 协议数据的 X 链接
    Display* display_datalink = XOpenDisplay(0);
    // 连接打开检查
    if (display_datalink == 0) {
        fprintf(stderr, "unable to open second display\n");
        return;
    }

    // 调用 XRecordEnableContext 函数建立 XRecord 上下文
   // XRecordEnableContext 函数一旦调用就开始进入堵塞时的事件循环，直到线程或所属进程结束
   // X Server 事件一旦发生就传递给事件处理回调函数
    if (!XRecordEnableContext(display_datalink, context,  callback, (XPointer) this)) {
        fprintf(stderr, "XRecordEnableContext() failed\n");
        return;
    }
}
