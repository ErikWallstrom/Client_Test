#ifndef CONNECTION_H
#define CONNECTION_H

#include "../include/SDL2/SDL_net.h"
#include <string>
class Connection
{
private:
    TCPsocket socket;
    IPaddress server_ip;
    SDLNet_SocketSet socket_set;

public:
    enum Message : char
    {
        CONNECTED = 0,
        FULL,
        DATA
    };

    Connection(std::string ip, Uint16 port);
    ~Connection();

    void flag(Message type);
    void send(void* data, int size);
};

#endif
