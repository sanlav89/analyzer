#include "tcpserverthread.h"
#include <iostream>
#include <cstring>

namespace dao {

TcpServerThread::TcpServerThread(short port, QObject *parent)
    : QThread(parent)
    , m_port(port)
{
}

void TcpServerThread::run()
{
    ba::io_context io_context;
    ba::ip::tcp::endpoint ep(ba::ip::tcp::v4(), m_port);
    ba::ip::tcp::acceptor acc(io_context, ep);
    while (true) {
        auto sock = ba::ip::tcp::socket(io_context);
        acc.accept(sock);
        clientSession(std::move(sock));
    }
}

void TcpServerThread::clientSession(boost::asio::ip::tcp::socket sock)
{
    char buffer[sizeof(data_t)];
    while (true) {
        try {
            size_t len = sock.read_some(ba::buffer(buffer));
            if (len == sizeof(data_t)) {
                char *data = reinterpret_cast<char *>(&m_data);
                std::memcpy(data, buffer, sizeof(data_t));
                emit readyRead(m_data);
            }
        } catch (const std::exception &e) {
            std::cerr << "client_session exception! " << e.what() << std::endl;
            break;
        }
    }
}

}
