#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <string>

#pragma comment(lib, "ws2_32.lib")

const char* SERVER_IP = "127.0.0.1";
const int PORT = 8080;

DWORD WINAPI receiveMessages(LPVOID param)
{
    SOCKET sock = (SOCKET)param;
    char buffer[4096];

    while (true)
    {
        int bytes = recv(sock, buffer, sizeof(buffer) - 1, 0);

        if (bytes <= 0)
        {
            std::cout << "\n[!] Server disconnected.\n";
            break;
        }

        buffer[bytes] = '\0';
        std::cout << "\n[Server]: " << buffer << "\n> ";
        std::cout.flush();
    }

    return 0;
}

int main()
{
    WSADATA wsa;

    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
    {
        std::cout << "WSAStartup failed\n";
        return 1;
    }

    SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);

    if (sock == INVALID_SOCKET)
    {
        std::cout << "Socket error\n";
        WSACleanup();
        return 1;
    }

    sockaddr_in serv_addr{};
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    serv_addr.sin_addr.s_addr = inet_addr(SERVER_IP);


    // provoj me u lidh me server dhe nese deshton del error
    if (connect(sock, (sockaddr*)&serv_addr, sizeof(serv_addr)) == SOCKET_ERROR)
    {
        int err = WSAGetLastError();
        std::cout << "CONNECT FAILED!" << std::endl;
        std::cout << "Error code: " << err << std::endl;

        closesocket(sock);
        WSACleanup();
        return 1;
    }

    std::cout << "Connected successfully!\n";

    std::string role;
    std::cout << "Zgjidh rolin (admin/user): ";
    std::getline(std::cin, role);

    send(sock, role.c_str(), role.size(), 0);

    CreateThread(
        NULL,
        0,
        receiveMessages,
        (LPVOID)sock,
        0,
        NULL
    );

    std::string msg;

    while (true)
    {
        std::cout << "> ";
        std::getline(std::cin, msg);

        if (msg == "exit")
            break;

        msg += "\n";
        send(sock, msg.c_str(), msg.size(), 0);
    }

    closesocket(sock);
    WSACleanup();

    return 0;
}