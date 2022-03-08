#pragma once

#include <QObject>
#include "types.h"
#include <iostream>

namespace dao {

class Detector : public QObject
{
    Q_OBJECT
public:
    explicit Detector(QObject *parent = nullptr) : QObject(parent) {}
    virtual data_t read() = 0;

signals:
    void readyRead();
};

//using DetectorPtr = std::unique_ptr<Detector>;
using DetectorPtr = Detector*;

}

