#pragma once

#include "detectoraccess.h"

namespace dao {

class TcpAccess : public DetectorAccess
{
    Q_OBJECT
public:
    explicit TcpAccess(short port, QObject *parent = nullptr);
};

}

