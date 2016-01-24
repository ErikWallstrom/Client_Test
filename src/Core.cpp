#include "Core.h"
#include <iostream>
#include <cmath>

Core::Core(const char* title, int width, int height,
           const char* ip, Uint16 port)
{
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO))
    {
        throw SDL_GetError();
    }

    if(SDLNet_Init())
    {
        throw SDLNet_GetError();
    }

    if(!IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG))
    {
        throw IMG_GetError();
    }

    bool connected = false;
    while(!connected)
    {
        try
        {
            connection = new Connection(ip, port);
            connected = true;
        }
        catch(const char* msg)
        {
            std::cout << msg << ", want to retry? (y/n): ";
            std::cout.flush();

            char input;
            std::cin >> input;
            if(input == 'n')
            {
                throw msg;
            }
        }
    }

    window = new Window(title, width, height);
    event_handler = new Event_Handler;
    scene = new Scene(
        window->get_renderer(),
        window->get_width() / 2.0,
        window->get_height() / 2.0,
        window->get_width(),
        window->get_height()
    );
    texture_handler = new Texture_Handler(
        window->get_renderer()
    );

    this->objects = scene->get_objects();
}

Core::~Core()
{
    delete texture_handler;
    delete scene;
    delete event_handler;
    delete window;
    delete connection;

    IMG_Quit();
    SDLNet_Quit();
    SDL_Quit();
}

void Core::handle_events()
{
    while (event_handler->update())
    {
        if(event_handler->triggered(SDL_QUIT))
        {
            running = false;
            break;
        }
    }

    Game_Object* player = (*objects)["localhost"];
    if(event_handler->key_down(SDL_SCANCODE_W))
    {
        player->position.set_y(player->position.get_y() - 5);
    }
    if(event_handler->key_down(SDL_SCANCODE_S))
    {
        player->position.set_y(player->position.get_y() + 5);
    }
    if(event_handler->key_down(SDL_SCANCODE_A))
    {
        player->position.set_x(player->position.get_x() - 5);
    }
    if(event_handler->key_down(SDL_SCANCODE_D))
    {
        player->position.set_x(player->position.get_x() + 5);
    }
}

void Core::update(int delta)
{
    for(auto pair : *objects)
    {
        pair.second->update(delta);
    }

    while(connection->data_recieved())
    {
        if(connection->data_type() == DISCONNECTED)
        {
            Uint8 buffer[6] = {0};
            connection->data_recieve(buffer, 6);

            Uint32 ip = SDLNet_Read32(buffer);
            Uint16 port = SDLNet_Read16(buffer + 4);

            std::printf("%d.%d.%d.%d:%u left the server\n",
                (ip & 0xFF000000) >> 24,
                (ip & 0x00FF0000) >> 16,
                (ip & 0x0000FF00) >> 8,
                (ip & 0x000000FF),
                port
            );
        }
        else if(connection->data_type() == POSITION)
        {
            Uint8 buffer[10] = {0};
            connection->data_recieve(buffer, 10);

            Uint16 x = SDLNet_Read16(buffer);
            Uint16 y = SDLNet_Read16(buffer + 2);

            Uint32 ip = SDLNet_Read32(buffer + 4);
            Uint16 port = SDLNet_Read16(buffer + 8);

            std::string address =
                std::to_string((ip & 0xFF000000) >> 24) + "." +
		        std::to_string((ip & 0x00FF0000) >> 16) + "." +
		        std::to_string((ip & 0x0000FF00) >> 8)  + "." +
		        std::to_string((ip & 0x000000FF)) + ":" + std::to_string(port);

            if(objects->find(address) == objects->end())
            {
                Game_Object* object = new Game_Object(x, y, 120, 80);
                object->set_texture(texture_handler->get(1));
                (*objects)[address] = object;
            }
            else
            {
                (*objects)[address]->position.set_x(x);
                (*objects)[address]->position.set_y(y);
            }
        }
    }

    Uint8 buffer[4] = {0};
    Uint16 x = std::round(((*objects)["localhost"])->position.get_x());
    Uint16 y = std::round(((*objects)["localhost"])->position.get_y());

    SDLNet_Write16(x, buffer);
    SDLNet_Write16(y, buffer + 2);

    connection->flag(POSITION);
    connection->send(buffer, 4);
}

void Core::loop()
{
    int last_time = SDL_GetTicks();
    running = true;
    while(running)
    {
        int delta_time = SDL_GetTicks() - last_time;
        last_time = SDL_GetTicks();

        handle_events();
        update(delta_time);
        scene->draw();
    }
}
