#include "Server.hpp"
#include <iostream>
#include <thread>
#include <algorithm>
#include <cctype>
#include <memory>

std::mutex g_file_mutex;

bool isValidNumber(std::string_view name)
{
    return std::all_of(name.begin(), name.end(), [](char ch)
                       { return std::isdigit(ch); });
}

void threadFunc(Server &server, int clientSocket)
{
    std::string message{};
    // Получение сообщения от клиента
    while (server.rcvData(message, clientSocket) > 0)
    {
        // Запись сообщения в файл
        server.writeToFile(std::ref(g_file_mutex), message);

        // Отправка подтверждения приема
        server.sendData("response", clientSocket);
    }
}

int main(int argc, char *argv[])
{
    // Обработка входных аргументов
    if (argc <= 1)
    {
        std::cout << "Usage: server <port_number>" << '\n';
        return 1;
    }

    std::stringstream convertPort{argv[1]};
    int portNumber{};
    if(!(isValidNumber(argv[1])) || !(convertPort >> portNumber))
    {
        std::cout << "Could not convert <port_number> to integer.\n";
        return 1;
    }

    // Создание объекта класса сервер
    Server server{portNumber};
    if (server.connectSocket() != 0)
    {
        std::cout << "Could not connect to server.\n";
        return 1;
    }

    // Цикл работы сервера
    while (true)
    {
        // Подтверждение соединения с клиентом
        int clientSocket{server.acceptConnection()};

        // Создание нового потока для обмена сообщениями с клиентом clientSocket
        auto thread = std::make_unique<std::thread>(std::bind(&threadFunc, std::ref(server), clientSocket));
        thread->detach();
    }

    return 0;
}