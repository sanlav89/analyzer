#pragma once

#include <QThread>
#include <boost/asio.hpp>
#include <utils/types.h>

namespace utils {
namespace tcp {

class ServerThread : public QThread
{
    Q_OBJECT
public:
    explicit ServerThread(short port, QObject *parent = nullptr);

private:
    void run() override;

    short m_port;
    utils::data_t m_data;

signals:
    void readyRead(utils::data_t);

};

}
}

