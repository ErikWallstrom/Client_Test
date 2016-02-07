#include "Core.h"
#include <string>
#include <ctime>
#include <iostream>
#include "Font_Handler.h"

#undef main
int main()
{
    Core core(
        "Game Window",
        800, 600
    );

    Event_Handler event_handler;
    Font_Handler font_handler(core.window->get_renderer());
    Font_ID id = font_handler.load(
        "../../res/fonts/OpenSans.ttf", 72
    );

    int frames = 0;
    Uint32 seconds = 0;
    double x = 400.0, y = 300.0;
    int i = 0;
    while(true)
    {
        //SDL_RenderClear(core.window->get_renderer());
        font_handler.render(
            id,
            std::to_string(i).c_str(),
            //std::rand() % 800,
            //std::rand() % 600
            x, y
        );
        font_handler.set_color(
            id,
            std::rand() % 255,
            std::rand() % 255,
            std::rand() % 255
        );
        SDL_RenderPresent(core.window->get_renderer());
        i++;

        event_handler.update();
        if(event_handler.triggered(SDL_QUIT))
        {
            break;
        }

        if(event_handler.key_down(SDL_SCANCODE_W))
        {
            y -= 0.1;
        }
        if(event_handler.key_down(SDL_SCANCODE_S))
        {
            y += 0.1;
        }
        if(event_handler.key_down(SDL_SCANCODE_A))
        {
            x -= 0.1;
        }
        if(event_handler.key_down(SDL_SCANCODE_D))
        {
            x += 0.1;
        }
        if(event_handler.key_down(SDL_SCANCODE_R))
        {
            SDL_RenderClear(core.window->get_renderer());
        }

        if(SDL_GetTicks() / 1000 > seconds)
        {
            seconds++;
            printf("FPS: %i\n", frames);
            frames = 0;

            try
            {
                id = font_handler.load(
                    "../../res/fonts/OpenSans.ttf", seconds * 20
                );
            }
            catch(const char* msg)
            {
                printf("%s\n", msg);
                getchar();
                return EXIT_FAILURE;
            }

        }
        frames++;
    }

    /*
    std::cout << "EW_AH Client V_1.0\n" << std::endl;

    std::string ip;
    std::cout << "IP: ";
    std::cout.flush();
    std::cin >> ip;

    Uint16 port;
    std::cout << "Port: ";
    std::cout.flush();
    std::cin >> port;

    try
    {
        Core core(
            "Game Window", 800, 600,
            ip.c_str(), port
        );

        Font f(core.window->get_renderer(), "test", 16);


        std::srand(std::time(0));

        size_t id = core.texture_handler->load("../../res/images/TB1.0.png");
        IPaddress ip_addr = Connection_get_address(core.connection);
        std::string name =
            std::to_string((ip_addr.host & 0xFF000000) >> 24) +
            std::to_string((ip_addr.host & 0x00FF0000) >> 16) +
            std::to_string((ip_addr.host & 0x0000FF00) >> 8) +
            std::to_string((ip_addr.host & 0x000000FF)) +
            std::to_string(ip_addr.port);

        Player* player = new Player(
            std::rand() % 800, std::rand() % 600, 120, 80
        );
        player->set_texture(core.texture_handler->get(id));

        core.scene->add(player, name);
        core.loop();
    }
    catch(const char* message)
    {
        std::cout << message << std::endl;
        return EXIT_FAILURE;
    }*/

    return EXIT_SUCCESS;
}
