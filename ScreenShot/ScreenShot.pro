QT += quick
QT += gui
QT += widgets printsupport
QT += network
QT += x11extras
#QT += dbus

LIBS+= -ldl
LIBS+= -lutil

LIBS += -L /usr/lib -lX11 -lXext -lXtst
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

#TARGET = X11-Mouse-Keyboard-Hook
TEMPLATE = app

#CONFIG += link_pkgconfig

CONFIG += c++17
PKGCONFIG += xcb xcb-util

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

DEFINES += QT_DEPRECATED_WARNINGS
#DEFINES += GSL.DLL

HEADERS += \
    area_record.h \
    capture.h \
    compute.h \
    copypaintitem.h \
    elementgroup.h \
    filter.h \
    freecapture.h \
    gif.h \
    imageprovider.h \
    mosaic.h \
    mousethread.h \
    mylabel.h \
    mywidget.h \
    painteditem.h \
    reccapture.h \
    recorddialog.h \
    share.h

SOURCES += \
    area_record.cpp \
    capture.cpp \
    copypaintitem.cpp \
    filter.cpp \
    freecapture.cpp \
    main.cpp \
    mosaic.cpp \
    mousethread.cpp \
    mylabel.cpp \
    mywidget.cpp \
    painteditem.cpp \
    reccapture.cpp \
    recorddialog.cpp \
    share.cpp

RESOURCES += qml.qrc

#INCLUDEPATH += ../../ffmpeg/include/
INCLUDEPATH += $$PWD/src/

#LIBS += -L/usr/lib -lavcodec \
#        -lavdevice \
#        -lavfilter \
#        -lavformat \
#        -lavutil \
#        -lpostproc \

#LIBS += /usr/local/lib/lib*

INCLUDEPATH += /usr/local/include\
               /usr/local/include/opencv4\
               /usr/local/include/opencv4/opencv2

LIBS += -L/usr/lib/

#LIBS += -L/opt/dm/lib/ -ldl -lwebp -lavcodec -lopenjp2 -lpng16 -ljpeg -ltiff -lopencv_core -ltbb -lopencv_calib3d \
LIBS += -ldl -lopencv_core \
 -lopencv_dnn\
 -lopencv_features2d\
 -lopencv_flann\
 -lopencv_highgui\
 -lopencv_imgcodecs\
 -lopencv_imgproc\
 -lopencv_ml\
 -lopencv_objdetect\
 -lopencv_photo\
 -lopencv_stitching\
 -lopencv_video

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/binLIBS += -L /opt/dm/lib/lib/lib*
!isEmpty(target.path): INSTALLS += target

FORMS += \
    filter.ui \
    mosaic.ui \
    mywidget.ui \
    recorddialog.ui

