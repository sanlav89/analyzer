#pragma once

#include <QThread>
#include <boost/asio.hpp>
#include "utils/types.h"

namespace dao {

namespace ba = boost::asio;
using namespace utils;

class TcpServerThread : public QThread
{
    Q_OBJECT
public:
    explicit TcpServerThread(short port, QObject *parent = nullptr);

private:
    void run() override;

    void clientSession(ba::ip::tcp::socket sock);

    short m_port;
    data_t m_data;

signals:
    void readyRead(data_t);

};

}

