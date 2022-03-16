#pragma once

#include <iostream>
#include <memory>
#include <boost/asio.hpp>

#include "types.h"

namespace dao {

using boost::asio::ip::tcp;

class Session : public std::enable_shared_from_this<Session>
{
public:
    Session(tcp::socket socket, data_t &data, bool &readyRead);
    void start();

private:
    void doRead();

    tcp::socket m_socket;
    static const int max_length = sizeof(data_t);
    char m_buffer[max_length];
    data_t &m_data;
    bool &m_readyRead;
};

}
