#include "SocketUser.hpp"

// Функция инициализации sock и sockAddress
void SocketUser::createSocket()
{
    sock = socket(AF_INET, SOCK_STREAM, 0);
    sockAddress.sin_family = AF_INET;
    sockAddress.sin_port = htons(portNumber);
    sockAddress.sin_addr.s_addr = INADDR_ANY;
}

// Функция приема строки по сокету userSock
// Строка записывается в str по ссылке
int SocketUser::rcvData(std::string &str, int userSock)
{
    char buffer[bufferSize] = {0};
    int num{recv(userSock, buffer, bufferSize, 0)};
    str = std::string(buffer);
    return num;
}

// Функция отправки строки str по сокету userSock
int SocketUser::sendData(std::string_view str, int userSock)
{
    const char *message = str.data();
    return send(userSock, message, strlen(message), 0);
}

// Функция завершения работы с сокетом
void SocketUser::closeSocket()
{
    close(sock);
}