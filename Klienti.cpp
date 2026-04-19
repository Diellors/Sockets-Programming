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

