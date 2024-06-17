#include "Client.hpp"

// Функция подключения к сокету со стороны клиента
int Client::connectSocket()
{
    return connect(sock, (struct sockaddr *)&sockAddress, sizeof(sockAddress));
}

// Функция создания строки для отправки на сервер
std::string Client::createRecordString()
{
    auto now{std::chrono::system_clock::now()};
    auto seconds{std::chrono::time_point_cast<std::chrono::seconds>(now)};
    auto milliseconds{std::chrono::duration_cast<std::chrono::milliseconds>(now - seconds)};
    std::time_t tt = std::chrono::system_clock::to_time_t(now);
    std::tm tm = *std::localtime(&tt);

    std::stringstream ss;
    ss << '[' << (tm.tm_year + 1900) << '-' << std::setw(2) << std::setfill('0') << (tm.tm_mon + 1) << '-' << std::setw(2) << tm.tm_mday << ' ';
    ss << std::setw(2) << tm.tm_hour << ':' << std::setw(2) << tm.tm_min << ':' << std::setw(2) << tm.tm_sec;
    ss << '.' << std::setw(3) << milliseconds.count();
    ss << "] " << name << '\0';
    return ss.str();
}
