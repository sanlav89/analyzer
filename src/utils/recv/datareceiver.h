#pragma once

#include <QObject>
#include <utils/types.h>
#include <iostream>

namespace utils {
namespace recv {

class DataReceiver : public QObject
{
    Q_OBJECT
public:
    explicit DataReceiver(QObject *parent = nullptr)
        : QObject(parent)
    {
        qRegisterMetaType<utils::data_t>("utils::data_t");
    }

    virtual utils::data_t recvData() const = 0;

signals:
    void readyRead();

};

}
}

