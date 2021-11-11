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
#include <QApplication>
#include <QQmlContext>
#include <QQmlApplicationEngine>
#include <QQuickView>
#include <QQuickItem>

#include "capture.h"
#include "painteditem.h"
#include "share.h"
#include "recorddialog.h"
#include "filter.h"
//#include "mosaic.h"

int main(int argc, char *argv[]){

#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QApplication app(argc, argv);
    QQmlApplicationEngine engine;

    //屏幕截图
    Capture *capture=new Capture();
    engine.rootContext()->setContextProperty("capture",capture);
    engine.addImageProvider(QLatin1String("screen"),capture->imgProvider);
    //分享
    Share *share = new Share();
    engine.rootContext()->setContextProperty("share",share);
    //录制屏幕
    RecordDialog *record = new RecordDialog();
    engine.rootContext()->setContextProperty("record",record);

    //滤镜/*
    Filter *filter = new Filter();
    engine.rootContext()->setContextProperty("filter",filter);

//    Mosaic *mosaic = new Mosaic();
//    engine.rootContext()->setContextProperty("mosaic",mosaic);

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
