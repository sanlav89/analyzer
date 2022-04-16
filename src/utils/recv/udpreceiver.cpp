#include "udpreceiver.h"

namespace utils {
namespace recv {

UdpReceiver::UdpReceiver(short port, QObject *parent)
    : DataReceiver{parent}
{
    udp::ServerThread *tcpServerThread = new udp::ServerThread(port);
    connect(tcpServerThread, &udp::ServerThread::readyRead, this, &UdpReceiver::onReadyRead);
    connect(tcpServerThread, &udp::ServerThread::finished, tcpServerThread, &QObject::deleteLater);
    tcpServerThread->start();
}

data_t UdpReceiver::recvData() const
{
    return m_data;
}

void UdpReceiver::onReadyRead(data_t data)
{
    m_data = data;
    emit readyRead();
}

}
}
