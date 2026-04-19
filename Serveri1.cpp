#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <string>
#include <cstring>


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

     buffer[bytes] = '\0';
    std::string role(buffer);

    std::cout << "[+] Client role: " << role << std::endl;

    const char* msg = "Connected successfully\n";
    send(clientSocket, msg, strlen(msg), 0);
}




