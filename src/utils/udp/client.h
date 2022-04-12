#pragma once

#include <boost/asio.hpp>
#include <utils/types.h>

namespace utils {
namespace udp {

class Client
{
public:
    Client(const std::string &hostAddr = "127.0.0.1", short port = 9999);
    ~Client();

    void sendData(const data_t &data);

private:

    std::string m_hostAddr;
    boost::asio::io_context m_ioContext;
    boost::asio::ip::udp::endpoint m_endpoint;
    boost::asio::ip::udp::socket m_udpSocket;

};

using ClientPtr = std::unique_ptr<Client>;

}
}
