#ifndef CLIENT_HPP
#define CLIENT_HPP
#include <iomanip>
#include <chrono>
#include "../common/SocketUser.hpp"

class Client : public SocketUser
{
public:
    Client(std::string_view name, int portNumber)
        : SocketUser{portNumber}, name{name}
    {
    }

    int connectSocket();
    std::string createRecordString();

private:
    std::string_view name{};
};

#endif