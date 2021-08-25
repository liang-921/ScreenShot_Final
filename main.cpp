#include <QApplication>
#include <QQmlContext>
#include <QQmlApplicationEngine>
#include <QQuickView>
#include <QQuickItem>

#include "fullcapture.h"
#include "painteditem.h"

int main(int argc, char *argv[]){

#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QApplication app(argc, argv);
    QQmlApplicationEngine engine;


    FullCapture *fullCut=new FullCapture();
    engine.rootContext()->setContextProperty("fullCut",fullCut);
    engine.addImageProvider(QLatin1String("screen"),fullCut->imgProvider);

    //将涂鸦这个类注册到qml中
    qmlRegisterType<PaintedItem>("qml.Controls", 1, 0, "APaintedItem");

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
