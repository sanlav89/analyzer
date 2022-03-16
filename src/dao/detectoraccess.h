#pragma once

#include <QObject>
#include "utils/types.h"
#include <iostream>

namespace dao {

using namespace utils;

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

}

