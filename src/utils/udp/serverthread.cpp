#include "serverthread.h"
#include <iostream>
#include <cstring>
#include <QDebug>

namespace utils {
namespace tcp {

namespace ba = boost::asio;

ServerThread::ServerThread(short port, QObject *parent)
    : QThread(parent)
    , m_port(port)
{
}

void ServerThread::run()
{
    try {
        boost::asio::io_context io_context;

        ba::ip::udp::socket socket(io_context, ba::ip::udp::endpoint(ba::ip::udp::v4(), m_port));

        for (;;) {
             ba::ip::udp::endpoint remote_endpoint;
             boost::system::error_code error;
             char *data = reinterpret_cast<char *>(&m_data);
             socket.receive_from(boost::asio::buffer(data, sizeof(data_t)), remote_endpoint);
             emit readyRead(m_data);
        }

    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
}

}
}
