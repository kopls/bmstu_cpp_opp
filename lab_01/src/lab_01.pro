Q+= core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    request.cpp \
    errors.cpp \
    link.cpp \
    vertex.cpp \
    draw.cpp \
    figure.cpp \

HEADERS += \
    mainwindow.h \
    request.h \
    errors.h \
    link.h \
    vertex.h \
    draw.h \
    figure.h \


FORMS += \
    mainwindow.ui

qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
