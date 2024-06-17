#ifndef SOCKETUSER_HPP
#define SOCKETUSER_HPP
#include <netinet/in.h>
#include <unistd.h>
#include <string>
#include <cstring>
#include <string_view>

// Родительский класс для дочерних классов сервера и клиента
class SocketUser
{
public:
    SocketUser(int portNumber)
        : portNumber{portNumber}
    {
        createSocket();
    }

    ~SocketUser()
    {
        closeSocket();
    }

    int rcvData(std::string &str, int userSock);
    int sendData(std::string_view str, int userSock);
    int sock{};

protected:
    sockaddr_in sockAddress{};
    virtual int connectSocket() = 0;

private:
    constexpr static int bufferSize{1024};
    int portNumber{};
    void createSocket();
    void closeSocket();
};

#endif