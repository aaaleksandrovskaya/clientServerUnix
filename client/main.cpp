#include "Client.hpp"
#include <iostream>
#include <thread>
#include <algorithm>
#include <cctype>

bool isValidNumber(std::string_view name)
{
    return std::all_of(name.begin(), name.end(), [](char ch)
                       { return std::isdigit(ch); });
}

int main(int argc, char *argv[])
{
    // Обработка входных аргументов
    if (argc <= 3)
    {
        std::cout << "Usage: client <name> <port_number> <time>" << '\n';
        return 1;
    }

    std::stringstream convertPort{argv[2]};
    int portNumber{};
    if(!(isValidNumber(argv[2])) || !(convertPort >> portNumber))
    {
        std::cout << "Could not convert <port_number> to integer.\n";
        return 1;
    }

    std::stringstream convertTime{argv[3]};
    int time{};
    if(!(isValidNumber(argv[3])) || !(convertTime >> time))
    {
        std::cout << "Could not convert <time> to integer.\n";
        return 1;
    }

    // Создание объекта класса клиент
    Client client{argv[1], portNumber};

    auto errCode{client.connectSocket()};
    if (errCode != 0)
    {
        std::cout << "Could not connect to socket.\n";
        return 1;
    }

    // Цикл работы клиента
    while (true)
    {
        // Отправка строки серверу
        std::string strRecord{client.createRecordString()};
        client.sendData(strRecord, client.sock);

        // Получение подтверждения приема
        std::string message{};
        client.rcvData(message, client.sock);

        // Ожидание в течение time секунд
        std::this_thread::sleep_for(std::chrono::seconds(time));
    }

    return 0;
}
