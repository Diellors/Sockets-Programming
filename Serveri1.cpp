#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <string>
#include <cstring>

<<<<<<< HEAD
#pragma comment(lib, "ws2_32.lib")

#define PORT 8080

DWORD WINAPI handleClient(LPVOID param)
{
    SOCKET clientSocket = (SOCKET)param;
    char buffer[1024];

    // read role
    int bytes = recv(clientSocket, buffer, sizeof(buffer) - 1, 0);
    if (bytes <= 0) {
        closesocket(clientSocket);
        return 0;
    }
}
=======


>>>>>>> 3812282621f13159befec6357226e57cd2c0cbfa
