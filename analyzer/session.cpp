#include "session.h"
#include <cstring>

namespace dao {

Session::Session(tcp::socket socket, data_t &data, bool &readyRead)
    : m_socket(std::move(socket))
    , m_data(data)
    , m_readyRead(readyRead)

{
}

void Session::start()
{
    doRead();
}

void Session::doRead()
{
    auto self(shared_from_this());
    m_socket.async_read_some(boost::asio::buffer(m_buffer, max_length),
        [this, self](boost::system::error_code ec, std::size_t length)
        {
            if (!ec) {
                std::cout << "receive " << length << std::endl;
                if (length == max_length) {
                    char *data = reinterpret_cast<char *>(&m_data);
                    std::memcpy(data, m_buffer, length);
                    m_readyRead = true;
                }

            }
        });
}

}
