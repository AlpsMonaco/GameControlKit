QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    aboutwindow.cpp \
    keyboard.cpp \
    keyboardmonitorwidget.cpp \
    main.cpp \
    mainwindow.cpp \
    virtualcontroller.cpp \
    xinputlistener.cpp

HEADERS += \
    keyboard_handler_enum.h \
    widgetkeeper.h \
    aboutwindow.h \
    keyboard.h \
    keyboardmonitorwidget.h \
    logs.h \
    mainwindow.h \
    virtualcontroller.h \
    widgetsingleton.h \
    xinputlistener.h

FORMS += \
    aboutwindow.ui \
    keyboardmonitorwidget.ui \
    mainwindow.ui

CONFIG(release, debug|release):DEFINES += QT_NO_DEBUG_OUTPUT

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../lib/ -lViGEmClient
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../lib/ -lViGEmClientd

INCLUDEPATH += $$PWD/../third_party/ViGEmClient/include
DEPENDPATH += $$PWD/../third_party/ViGEmClient/include

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../lib/libViGEmClient.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../lib/libViGEmClientd.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../lib/ViGEmClient.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../lib/ViGEmClientd.lib
