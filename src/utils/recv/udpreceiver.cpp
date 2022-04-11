#include "udpreceiver.h"

namespace utils {
namespace recv {

UdpReceiver::UdpReceiver(short port, QObject *parent)
    : DataReceiver{parent}
{
    tcp::ServerThread *tcpServerThread = new tcp::ServerThread(port);
    connect(tcpServerThread, &tcp::ServerThread::readyRead, this, &UdpReceiver::onReadyRead);
    connect(tcpServerThread, &tcp::ServerThread::finished, tcpServerThread, &QObject::deleteLater);
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
