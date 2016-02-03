#include "Connection.h"
#include <stdlib.h>
#include <stdio.h>

struct Connection
{
    SDLNet_SocketSet socket_set;
    IPaddress address;
    IPaddress local_address;
    TCPsocket socket;
};

Connection* Connection_create(const char* ip, Uint16 port)
{
    Connection* self = (Connection*)calloc(1, sizeof(Connection));
    if(!self)
    {
        return NULL;
    }

    if(SDLNet_ResolveHost(&self->address, ip, port))
    {
        Connection_destroy(&self);
        return NULL;
    }

    if(!(self->socket = SDLNet_TCP_Open(&self->address)))
    {
        Connection_destroy(&self);
        return NULL;
    }

    if(!(self->socket_set = SDLNet_AllocSocketSet(1)))
    {
        Connection_destroy(&self);
        return NULL;
    }

    if(SDLNet_TCP_AddSocket(self->socket_set, self->socket) == -1)
    {
        Connection_destroy(&self);
        return NULL;
    }

    if(SDLNet_CheckSockets(self->socket_set, 5000) == 1)
    {
        Uint8 message = Connection_recv_flag(self);
        if(message == CONNECTED)
        {
            Uint8 buffer[6] = {0};
            Connection_recv_data(self, buffer, 6);

            self->local_address.host = SDLNet_Read32(buffer);
            self->local_address.port = SDLNet_Read16(buffer + 4);
            printf("Successfully connected to server\n");
            return self;
        }
        else if(message == FULL)
        {
            printf("Server is full\n");
        }
    }
    else
    {
        printf("Server is not responding\n");
    }

    Connection_destroy(&self);
    return NULL;
}

void Connection_destroy(Connection** connection)
{
    Connection* self = (*connection);
    if(self)
    {
        if(self->socket_set)
        {
            SDLNet_FreeSocketSet(self->socket_set);
        }
        if(self->socket)
        {
            SDLNet_TCP_Close(self->socket);
        }

        free(self);
    }

    (*connection) = NULL;
}

void Connection_send_flag(Connection* self, Uint8 flag)
{
    if(SDLNet_TCP_Send(self->socket, &flag, 1) < 1)
    {
        printf("Lost connection to server\n");
        Connection_destroy(&self);
    }
}

void Connection_send_data(Connection* self, Uint8* data, int size)
{
    if(SDLNet_TCP_Send(self->socket, data, size) < size)
    {
        printf("Lost connection to server\n");
        Connection_destroy(&self);
    }
}

bool Connection_recieved(Connection* self)
{
    return SDLNet_CheckSockets(self->socket_set, 0);
}

Uint8 Connection_recv_flag(Connection* self)
{
    Uint8 flag;
    if(SDLNet_TCP_Recv(self->socket, &flag, 1) < 1)
    {
        printf("Lost connection to server\n");
        Connection_destroy(&self);
    }
    return flag;
}

void Connection_recv_data(Connection* self, Uint8* buffer, int size)
{
    if(SDLNet_TCP_Recv(self->socket, buffer, size) < size)
    {
        printf("Lost connection to server\n");
        Connection_destroy(&self);
    }
}

IPaddress Connection_get_address(Connection* self)
{
    return self->local_address;
}
