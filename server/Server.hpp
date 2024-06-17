#ifndef SERVER_HPP
#define SERVER_HPP
#include <iomanip>
#include <mutex>
#include <fstream>
#include "../common/SocketUser.hpp"

class Server : public SocketUser
{
public:
    Server(int portNumber)
        : SocketUser{portNumber}
    {
    }

    int connectSocket();
    int acceptConnection();
    void writeToFile(std::mutex &file_mutex, std::string_view str);
private:
    
};

#endif