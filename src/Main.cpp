#include "Connection.h"
#include <iostream>
#include <string>

int main()
{
    if(SDL_Init(0)) throw SDL_GetError();
    if(SDLNet_Init()) throw SDLNet_GetError();

    std::cout << "EW_AH Client V_1.0\n" << std::endl;

    std::string ip;
    std::cout << "IP: ";
    std::cout.flush();
    std::cin >> ip;

    Uint16 port;
    std::cout << "Port: ";
    std::cout.flush();
    std::cin >> port;

    while(true)
    {
        try
        {
            Connection connection(ip, port);
            while(true)
            {
                std::cout << "Send: ";
                std::cout.flush();

                char buffer[1024];
                std::cin.getline(buffer, 1024);
                connection.flag(Connection::DATA);
                connection.send(buffer, 1024);
            }
        }
        catch(const char* msg)
        {
            std::cout << msg << ", want to retry? (y/n): ";
            std::cout.flush();

            char input;
            std::cin >> input;
            if(input == 'y')
            {
                continue;
            }
            else
            {
                return EXIT_FAILURE;
            }
        }
    }
}
