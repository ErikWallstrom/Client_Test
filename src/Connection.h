#ifndef CONNECTION_H
#define CONNECTION_H

#include "../include/SDL2/SDL_net.h"
#include <string>

#define CONNECTED    1
#define DISCONNECTED 2
#define FULL         3
#define POSITION     4

class Connection
{
private:
    TCPsocket socket;
    IPaddress server_ip;
    SDLNet_SocketSet socket_set;

public:
    Connection(const char* ip, Uint16 port);
    ~Connection();

    void flag(Uint8 type);
    void send(void* data, int size);
    bool data_recieved();
    Uint8 data_type();
    void data_recieve(Uint8* buffer, int size);
};

#endif
