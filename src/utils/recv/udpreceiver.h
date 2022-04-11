#pragma once

#include <utils/recv/datareceiver.h>
#include <utils/udp/serverthread.h>


namespace utils {
namespace recv {

class UdpReceiver : public DataReceiver
{
    Q_OBJECT
public:
    explicit UdpReceiver(short port, QObject *parent = nullptr);

    utils::data_t recvData() const override;

private:
    data_t m_data;

private slots:
    void onReadyRead(utils::data_t);

};

}
}

