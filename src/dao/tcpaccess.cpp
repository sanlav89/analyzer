#include "tcpaccess.h"

#include "tcpserverthread.h"

namespace dao {

TcpAccess::TcpAccess(short port, QObject *parent)
    : DetectorAccess(parent)
{
    TcpServerThread *tcpServerThread = new TcpServerThread(port);
    connect(tcpServerThread, &TcpServerThread::readyRead, this, &TcpAccess::readyRead);
    connect(tcpServerThread, &TcpServerThread::finished, tcpServerThread, &QObject::deleteLater);
    tcpServerThread->start();
}

}
