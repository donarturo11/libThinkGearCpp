#ifndef TG_UDPSOCKET
#define TG_UDPSOCKET
#include "boost/asio.hpp"
#include <memory>
#include <stdexcept>
namespace TG {
using namespace boost::asio;
using namespace boost::asio::ip;
class UdpSocket
{
public:
    UdpSocket(std::string ip_addr, int port) {
        udp::endpoint remote(address::from_string(ip_addr), port);
        _remote = remote;
        _socket = std::make_unique<udp::socket>(_service);
        _socket->open(ip::udp::v4());
    }
    void sendData(const char* data, size_t size) {
        _socket->send_to(buffer(data, size), _remote);
    }
protected:
    io_service _service;
    io_context _context;
    udp::endpoint _remote;
    std::unique_ptr<udp::socket> _socket;
};    
}
#endif // TG_UDPSOCKET
