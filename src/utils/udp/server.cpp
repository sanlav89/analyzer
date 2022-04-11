#include "server.h"

#include <boost/bind.hpp>
#include <QDebug>

namespace utils {
namespace udp {

using boost::asio::ip::udp;

Server::Server(short port, QObject *parent)
    : QThread{parent}
    , m_port{port}
{
    startReceive();
}

void Server::startReceive()
{
    m_udpSocket.async_receive_from(
                boost::asio::buffer(recv_buffer_),
                m_remoteEndpoint,
                boost::bind(
                    &Server::handleReceive,
                    this,
                    boost::asio::placeholders::error,
                    boost::asio::placeholders::bytes_transferred
                    )
                );
}

void Server::handleReceive(const boost::system::error_code &error, std::size_t size)
{
    if (!error) {
        qDebug() << "received" << size;
        startReceive();
    }
}

void Server::handleSend(boost::shared_ptr<std::string>, const boost::system::error_code &, std::size_t)
{
}

}
}
