#include <QDebug>
#include <QImage>
#include <QSharedPointer>
#include <QQuickItem>
#include <QQuickItemGrabResult>
#include <QQuickWindow>

class ScreenShot : public QObject
{
    Q_OBJECT
public:
    explicit ScreenShot(QObject *parent = nullptr);

    Q_INVOKABLE void shootScreen(QObject *itemObj);	//截图控件

    Q_INVOKABLE void shootScreenWindow(QQuickWindow *rootWindow);	//截图窗口

private slots:
    void saveimage();

private:
    QQuickItem      *grabItem;
    QSharedPointer<QQuickItemGrabResult> grabResult;
};
