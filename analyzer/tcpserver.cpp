#include "tcpserver.h"

#include "session.h"

namespace dao {

TcpServer::TcpServer(short port, QObject *parent)
    : DetectorAccess(parent)
    , m_acceptor(m_ioContext, tcp::endpoint(tcp::v4(), port))
    , m_readyRead(false)
{
//    m_thread = std::thread(&TcpServer::doAccept, this);
    doAccept();
    m_ioContext.run();
}

TcpServer::~TcpServer()
{
//    m_thread.join();
}

data_t TcpServer::read()
{
    return m_dataToRead;
}

void TcpServer::doAccept()
{
    m_acceptor.async_accept(
        [this](boost::system::error_code ec, tcp::socket socket)
        {
          if (!ec) {
              std::make_shared<Session>(std::move(socket), m_dataToRead, m_readyRead)->start();
          }
          if (m_readyRead) {
              emit readyRead();
              m_readyRead = false;
              std::cout << "readyRead() " << m_dataToRead.first.count() << std::endl;
          }
          doAccept();
        }
    );
}

}
