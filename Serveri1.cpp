#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <string>
#include <thread>

#pragma comment(lib, "ws2_32.lib")

// IP dhe Port i fiksuar (Pika 4 e kërkesës së klientit)
const char* SERVER_IP = "127.0.0.1";
const int PORT = 5050;

// Funksioni për të marrë mesazhe nga serveri në sfond (Pika 6)
DWORD WINAPI receiveMessages(LPVOID param)
{
    SOCKET sock = (SOCKET)param;
    char buffer[4096];

    while (true)
    {
        int bytes = recv(sock, buffer, sizeof(buffer) - 1, 0);
        if (bytes <= 0)
        {
            std::cout << "\n[!] Serveri u shkëput ose lidhja dështoi.\n";
            exit(0);
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
        std::cerr << "WSAStartup failed\n";
        return 1;
    }

    // Pika 1 & 5: Krijimi i socket-it (Pika 5 kërkon që lidhja të mos dështojë)
    SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sock == INVALID_SOCKET)
    {
        std::cerr << "Socket creation failed\n";
        WSACleanup();
        return 1;
    }

    sockaddr_in serv_addr{};
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    inet_pton(AF_INET, SERVER_IP, &serv_addr.sin_addr);

    // Pika 4: Lidhja me serverin duke përcaktuar IP dhe Port
    if (connect(sock, (sockaddr*)&serv_addr, sizeof(serv_addr)) == SOCKET_ERROR)
    {
        std::cerr << "Lidhja dështoi! Sigurohu që serveri është aktiv.\n";
        closesocket(sock);
        WSACleanup();
        return 1;
    }

    std::cout << "Connected successfully to " << SERVER_IP << ":" << PORT << "!\n";

    // Pika 2 & 3: Zgjedhja e privilegjeve (Dërgimi i rolit për serverin)
    std::string role;
    std::cout << "Zgjidh rolin (admin/user): ";
    std::getline(std::cin, role);
    std::string roleMsg = "ROLE " + role + "\n";
    send(sock, roleMsg.c_str(), (int)roleMsg.size(), 0);

    // Nisja e thread-it për të dëgjuar mesazhet e serverit (Pika 6)
    CreateThread(NULL, 0, receiveMessages, (LPVOID)sock, 0, NULL);

    // Pika 7: Loop për të dërguar mesazhe tekstuale (komanda)
    std::string msg;
    std::cout << "Klienti gati. Shkruaj komandat (LIST, /read <file>, etj.):\n";
    while (true)
    {
        std::cout << "> ";
        std::getline(std::cin, msg);

        if (msg == "exit") break;

        msg += "\n"; // Serveri yt pret \n
        send(sock, msg.c_str(), (int)msg.size(), 0);
    }

    closesocket(sock);
    WSACleanup();
    return 0;
}