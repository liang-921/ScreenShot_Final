#ifndef SHARE_H
#define SHARE_H

#include <QWidget>
#include <QPrinter>
#include <QProcess>

class Share : public QWidget
{
    Q_OBJECT
public:
    explicit Share(QWidget *parent = nullptr);

    Q_INVOKABLE void sendMail();
    Q_INVOKABLE void shareToQQ();
    Q_INVOKABLE void shareToWeChat();
    Q_INVOKABLE void startPrinter();
signals:
private:
};

#endif // SHARE_H
