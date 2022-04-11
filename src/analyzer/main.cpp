#include <iostream>
#include <QApplication>

#include <view/mainwidget.h>
#include <model/analyzer.h>
#include <model/idf/convneuralnet.h>
#include <ctrl/controller.h>
#include <utils/recv/simulatorreceiver.h>
#include <utils/recv/udpreceiver.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    analyzer::view::MainWidget gui;
    analyzer::model::Analyzer analyzer;
    analyzer.addObserver(&gui);
    analyzer.setIdentifyMethod(
                analyzer::model::idf::MethodPtr{
                    new analyzer::model::idf::ConvNeuralNet{"./data/saved_model", utils::SpectrumSize}
                }
                );

    analyzer::ctrl::Controller controller(&analyzer, &gui);

    // Simulator
//    controller.setReceiver(
//                new utils::recv::SimulatorReceiver(&controller)
//                );

    // Udp Receiver
    controller.setReceiver(new utils::recv::UdpReceiver(9999, &controller));

    return a.exec();
}
