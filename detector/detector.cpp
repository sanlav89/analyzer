#include <iostream>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    std::cout << "Hello form Detector" << std::endl;

    return a.exec();
}
