#include "Server.hpp"

// Функция подключения к сокету со стороны сервера
int Server::connectSocket()
{
    int errorCode{bind(sock, (struct sockaddr *)&sockAddress, sizeof(sockAddress))};
    if (errorCode != 0)
        return errorCode;

    return listen(sock, 5);
}

// Функция подтверждения соединения
int Server::acceptConnection()
{
    return accept(sock, nullptr, nullptr);
}

// Функция записи принятого сообщения в файл
void Server::writeToFile(std::mutex &file_mutex, std::string_view str)
{
    const std::lock_guard<std::mutex> lock(file_mutex);
    std::ofstream outf{"log.txt", std::ios_base::app};
    outf << str << '\n';
}
