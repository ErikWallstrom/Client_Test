#include "Connection.h"
#include <iostream>

Connection::Connection(const char* ip, Uint16 port)
{
    if(SDLNet_ResolveHost(&server_ip, ip, port))
    {
        throw "Invalid IP or/and port";
    }

    if(!(socket_set = SDLNet_AllocSocketSet(1)))
    {
        throw SDLNet_GetError();
    }

    std::cout << "\nTrying to connect..." << std::endl;
    if(!(socket = SDLNet_TCP_Open(&server_ip)))
    {
        throw "Unable to connect";
    }
    else
    {
        if(SDLNet_TCP_AddSocket(socket_set, socket) == -1)
        {
            throw SDLNet_GetError();
        }

        if(SDLNet_CheckSockets(socket_set, 5000) == 1)
        {
            Uint8 message;
            if(SDLNet_TCP_Recv(socket, &message, 1) < 1)
            {
                throw "Server is down";
            }

            if(message == CONNECTED)
            {
                std::cout << "Successfully connected to server\n" << std::endl;
            }
            else if(message == FULL)
            {
                SDLNet_TCP_DelSocket(socket_set, socket);
                SDLNet_TCP_Close(socket);
                throw "Server is full";
            }
        }
        else
        {
            SDLNet_TCP_DelSocket(socket_set, socket);
            SDLNet_TCP_Close(socket);
            throw "Server not responding";
        }
    }
}

Connection::~Connection()
{
    SDLNet_FreeSocketSet(socket_set);
    SDLNet_TCP_Close(socket);
}

void Connection::flag(Uint8 type)
{
    if(SDLNet_TCP_Send(socket, &type, 1) < 1)
    {
        throw "Lost connection to server";
    }
}

void Connection::send(void* data, int size)
{
    if(SDLNet_TCP_Send(socket, data, size) < size)
    {
        throw "Lost connection to server";
    }
}

bool Connection::data_recieved()
{
    SDLNet_CheckSockets(socket_set, 0);
    return SDLNet_SocketReady(socket);
}

Uint8 Connection::data_type()
{
    Uint8 type;
    if(SDLNet_TCP_Recv(socket, &type, 1) < 1)
    {
        throw "Lost connection to server";
    }

    return type;
}

void Connection::data_recieve(Uint8* buffer, int size)
{
    if(SDLNet_TCP_Recv(socket, buffer, size) < size)
    {
        throw "Lost connection to server";
    }
}
