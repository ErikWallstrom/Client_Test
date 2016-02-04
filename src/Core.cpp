#include "Core.h"
#include "../include/SDL2/SDL_net.h"
#include "../include/SDL2/SDL_ttf.h"
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

    if(TTF_Init())
    {
        throw TTF_GetError();
    }
/*
    connection = Connection_create(ip, port);
    if(!connection)
    {
        std::cout << "\nConnection failed, retrying..." << std::endl;
        for(int i = 0; i < 3; i++)
        {
            connection = Connection_create(ip, port);
            if(connection)
            {
                break;
            }
        }

        if(connection == nullptr)
        {
            throw "Connection failed";
        }
    }
*/
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
}

Core::~Core()
{
    delete texture_handler;
    delete scene;
    delete event_handler;
    delete window;
    //Connection_destroy(&connection);

    TTF_Quit();
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
/*
    IPaddress ip_addr = Connection_get_address(connection);
    std::string local =
        std::to_string((ip_addr.host & 0xFF000000) >> 24) +
        std::to_string((ip_addr.host & 0x00FF0000) >> 16) +
        std::to_string((ip_addr.host & 0x0000FF00) >> 8) +
        std::to_string((ip_addr.host & 0x000000FF)) +
        std::to_string(ip_addr.port);

    Player* player = dynamic_cast<Player*>(scene->get(local));
    if(event_handler->mouse_down(Event_Handler::LEFT))
    {
        Uint16 mouse_x = event_handler->mouse_x();
        Uint16 mouse_y = event_handler->mouse_y();

        player->move_to(Vector2d(
            static_cast<double>(mouse_x),
            static_cast<double>(mouse_y)
        ));

        Uint8 buffer[4] = {0};
        SDLNet_Write16(mouse_x, buffer);
        SDLNet_Write16(mouse_y, buffer + 2);

        Connection_send_flag(connection, POSITION);
        Connection_send_data(connection, buffer, 4);
    }*/
}

void Core::update(int delta)
{
    scene->update(delta);
    /*
    while(Connection_recieved(connection))
    {
        Uint8 type = Connection_recv_flag(connection);
        if(type == POSITION)
        {
            Uint8 buffer[10] = {0};
            Connection_recv_data(connection, buffer, 10);

            Uint16 x = SDLNet_Read16(buffer);
            Uint16 y = SDLNet_Read16(buffer + 2);

            Uint32 ip = SDLNet_Read32(buffer + 4);
            Uint16 port = SDLNet_Read16(buffer + 8);

            std::string address =
                std::to_string((ip & 0xFF000000) >> 24) +
                std::to_string((ip & 0x00FF0000) >> 16) +
                std::to_string((ip & 0x0000FF00) >> 8) +
                std::to_string((ip & 0x000000FF)) +
                std::to_string(port);

            IPaddress ip_addr = Connection_get_address(connection);
            std::string local =
                std::to_string((ip_addr.host & 0xFF000000) >> 24) +
                std::to_string((ip_addr.host & 0x00FF0000) >> 16) +
                std::to_string((ip_addr.host & 0x0000FF00) >> 8) +
                std::to_string((ip_addr.host & 0x000000FF)) +
                std::to_string(ip_addr.port);

            Player* p = dynamic_cast<Player*>(scene->get(address));
            if(p == nullptr)
            {
                Player* p = new Player(
                    static_cast<double>(x),
                    static_cast<double>(y),
                    120, 80
                );
                size_t id = texture_handler->load("../../res/images/TB1.0.png");
                SDL_SetTextureColorMod(
                    texture_handler->get(id),
                    std::rand() % 255,
                    std::rand() % 255,
                    std::rand() % 255
                );
                p->set_texture(texture_handler->get(id));
                scene->add(p, address);
            }
            else if(p != scene->get(local))
            {
                p->move_to(Vector2d(
                    static_cast<double>(x),
                    static_cast<double>(y)
                ));
            }
        }
        else if(type == DISCONNECTED)
        {
            Uint8 buffer[6] = {0};
            Connection_recv_data(connection, buffer, 6);

            Uint32 ip = SDLNet_Read32(buffer);
            Uint16 port = SDLNet_Read16(buffer + 4);

            std::string address =
                std::to_string((ip & 0xFF000000) >> 24) +
                std::to_string((ip & 0x00FF0000) >> 16) +
                std::to_string((ip & 0x0000FF00) >> 8) +
                std::to_string((ip & 0x000000FF)) +
                std::to_string(port);

            if(scene->get(address))
            {
                std::cout << address << " disconnected" << std::endl;
                scene->remove(address);
            }
        }
    }*/
}

void Core::loop()
{
    int last_time = SDL_GetTicks();
    running = true;
    while(running)
    {
        int delta_time = SDL_GetTicks() - last_time;
        last_time = SDL_GetTicks();

        scene->draw();
        update(delta_time);
        handle_events();
    }

    //Connection_send_flag(connection, DISCONNECTED);
}
