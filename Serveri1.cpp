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

     // main loop
    while (true) {
        memset(buffer, 0, sizeof(buffer));

        int bytesRecv = recv(clientSocket, buffer, sizeof(buffer) - 1, 0);
        if (bytesRecv <= 0) break;

        buffer[bytesRecv] = '\0';

        std::string request(buffer);
        std::string response = "[Server echo]: " + request;

        send(clientSocket, response.c_str(), response.size(), 0);
    }

    std::cout << "[-] Client disconnected\n";
    closesocket(clientSocket);
    return 0;
}

int main()
{
    WSADATA wsa;
    WSAStartup(MAKEWORD(2, 2), &wsa);

    SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in serverAddr{};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    bind(serverSocket, (sockaddr*)&serverAddr, sizeof(serverAddr));
    listen(serverSocket, 5);

    std::cout << "Server running on port " << PORT << "...\n";

    while (true)
    {
        SOCKET clientSocket = accept(serverSocket, NULL, NULL);

     

    closesocket(serverSocket);
    WSACleanup();
}


