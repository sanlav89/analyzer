#pragma once

#include <QObject>
#include "types.h"
#include <iostream>

namespace dao {

class DetectorAccess : public QObject
{
    Q_OBJECT
public:
    explicit DetectorAccess(QObject *parent = nullptr)
        : QObject(parent)
    {
        qRegisterMetaType<data_t>("data_t");
    }

signals:
    void readyRead(data_t);
};

using DetectorAccessPtr = DetectorAccess*;

}

