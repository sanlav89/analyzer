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
    ../utils/recv/simulatorreceiver.cpp \
    ../utils/recv/udpreceiver.cpp \
    ../utils/udp/serverthread.cpp \
    ../utils/utils.cpp \
    view/mainwidget.cpp \
    view/spectrumnuclides.cpp \
    ctrl/controller.cpp \
    model/analyzer.cpp \
    model/idf/convneuralnet.cpp \
    main.cpp

HEADERS += \
    ../simulator/generator.h \
    ../simulator/measured.h \
    ../simulator/modeling.h \
    ../simulator/simulator.h \
    ../utils/graph/canvas.h \
    ../utils/graph/spectrumonly.h \
    ../utils/matlab/matlab.h \
    ../utils/nuclidelibrary/nuclidelibrary.h \
    ../utils/recv/simulatorreceiver.h \
    ../utils/recv/udpreceiver.h \
    ../utils/udp/serverthread.h \
    ../utils/types.h \
    ../utils/utils.h \
    ../utils/recv/datareceiver.h \
    view/mainwidget.h \
    view/spectrumnuclides.h \
    view/viewinfoupdater.h \
    ctrl/controller.h \
    model/idf/method.h \
    model/idf/convneuralnet.h \
    model/idf/maxpolling.h \
    model/idf/deconvolution.h \
    model/analyzer.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

INCLUDEPATH += $${PWD}/../

INCLUDEPATH += C:/qwt-6.1.5_64/src
LIBS += -LC:/qwt-6.1.5_64/lib -lqwt

INCLUDEPATH += $${PWD}/../../tensorflow/include/
LIBS += -L$${PWD}/../../tensorflow/lib -ltensorflow

INCLUDEPATH += C:/boost/include/boost-1_78/
LIBS += "-LC:/boost/boost-1_78/stage/lib/"
LIBS += -lws2_32 -lwsock32
