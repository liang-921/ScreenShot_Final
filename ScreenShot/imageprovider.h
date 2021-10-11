#ifndef IMAGEPROVIDER_H
#define IMAGEPROVIDER_H
#include <QQuickImageProvider>
#include<QImage>
#include <QSize>
#include<QTcpSocket>
#include <QTcpServer>
#include<QBuffer>
class ImageProvider : public QQuickImageProvider
{
public:
    ImageProvider(): QQuickImageProvider(QQuickImageProvider::Image){ }
    QImage requestImage(const QString &id, QSize *size, const QSize &requestedSize){
        Q_UNUSED(id);
        Q_UNUSED(size);
        Q_UNUSED(requestedSize);
        return this->img;
    }

    QImage img;
};

#endif // IMAGEPROVIDER_H
