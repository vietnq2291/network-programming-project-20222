QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets network

TEMPLATE = app

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Client.cpp \
    Controller.cpp \
    Message.cpp \
    Utils.cpp \
    Views.cpp \
    chatwindow.cpp \
    loginwindow.cpp \
    main.cpp

HEADERS += \
    Client.h \
    Controller.h \
    Message.h \
    Utils.h \
    Views.h \
    chatwindow.h \
    common.h \
    loginwindow.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

FORMS += \
    chatwindow.ui \
    loginwindow.ui

DISTFILES += \
    ../../../OneDrive/Hình ảnh/Ảnh chụp màn hình/2023-01-06.png

RESOURCES += \
    chatIcon.qrc
