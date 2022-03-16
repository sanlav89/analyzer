#pragma once

#include "detectoraccess.h"
#include <thread>
#include <boost/asio.hpp>

namespace dao {

using boost::asio::ip::tcp;

class TcpServer : public DetectorAccess
{
    Q_OBJECT
public:
    TcpServer(short port, QObject *parent = nullptr);
    ~TcpServer();
    data_t read() override;

private:
    void doAccept();
    boost::asio::io_context m_ioContext;
    tcp::acceptor m_acceptor;
    data_t m_dataToRead;
    bool m_readyRead;
    std::thread m_thread;
};

}

