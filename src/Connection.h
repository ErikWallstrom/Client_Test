#ifndef CONNECTION_H
#define CONNECTION_H

#include <stdbool.h>
#include "../include/SDL2/SDL_net.h"
typedef struct Connection Connection;

#define CONNECTED    1
#define DISCONNECTED 2
#define FULL         3
#define POSITION     4

Connection* Connection_create       (const char* ip, Uint16 port);
void        Connection_destroy      (Connection** connection);
void        Connection_send_flag    (Connection* self, Uint8 flag);
void        Connection_send_data    (Connection* self, Uint8* data, int size);
bool        Connection_recieved     (Connection* self);
Uint8       Connection_recv_flag    (Connection* self);
void        Connection_recv_data    (Connection* self, Uint8* buffer, int size);
IPaddress   Connection_get_address  (Connection* self);

#endif
