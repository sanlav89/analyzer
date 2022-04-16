QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../simulator/measured.cpp \
    ../simulator/modeling.cpp \
    ../simulator/simulator.cpp \
    ../utils/graph/canvas.cpp \
    ../utils/graph/spectrumonly.cpp \
    ../utils/matlab/matlab.cpp \
    ../utils/nuclidelibrary/nuclidelibrary.cpp \
    ../utils/udp/client.cpp \
    ../utils/utils.cpp \
    ctrl/controller.cpp \
    main.cpp \
    model/engine.cpp \
    view/mainwidget.cpp \
    view/measuredwidget.cpp \
    view/modelingwidget.cpp \
    view/sliderwithlabel.cpp

HEADERS += \
    ../simulator/generator.h \
    ../simulator/measured.h \
    ../simulator/modeling.h \
    ../simulator/simulator.h \
    ../utils/graph/canvas.h \
    ../utils/graph/spectrumonly.h \
    ../utils/matlab/matlab.h \
    ../utils/nuclidelibrary/nuclidelibrary.h \
    ../utils/types.h \
    ../utils/udp/client.h \
    ../utils/utils.h \
    ctrl/controller.h \
    model/engine.h \
    model/modes.h \
    view/mainwidget.h \
    view/measuredwidget.h \
    view/modelingwidget.h \
    view/sliderwithlabel.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

INCLUDEPATH += $${PWD}/../

INCLUDEPATH += C:/qwt-6.1.5_64/src
LIBS += -LC:/qwt-6.1.5_64/lib -lqwt

INCLUDEPATH += C:/boost/include/boost-1_78/
LIBS += "-LC:/boost/boost-1_78/stage/lib/"
LIBS += -lws2_32 -lwsock32
