#include "client.h"
#include <iostream>

namespace utils {
namespace udp {

namespace ba = boost::asio;

Client::Client(const std::string &hostAddr, short port)
    : m_endpoint{ba::ip::udp::endpoint(ba::ip::address::from_string(hostAddr), port)}
    , m_udpSocket{m_ioContext}
{
    m_udpSocket.open(ba::ip::udp::v4());
}

Client::~Client()
{
    m_udpSocket.close();
}

void Client::sendData(const data_t &data)
{
    boost::system::error_code err;
    m_udpSocket.send_to(boost::asio::buffer(&data, sizeof(data)), m_endpoint, 0, err);
    assert(err.value() == 0);
}

}
}
