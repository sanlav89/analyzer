#pragma once

#include <QObject>
#include "types.h"
#include <iostream>

namespace dao {

class DetectorAccess : public QObject
{
    Q_OBJECT
public:
    explicit DetectorAccess(QObject *parent = nullptr) : QObject(parent) {}
    virtual data_t read() = 0;

signals:
    void readyRead();
};

using DetectorAccessPtr = DetectorAccess*;

}

