#include "Core.h"
#include <string>
#include <ctime>
#include <iostream>
/*
size_t id = texture_handler.load_texture("../../res/images/Logo.png");

Game_Object object(50.0, 50.0, 100, 100);
object.set_texture(texture_handler.get_texture(id));
scene.add(&object);
*/

int main()
{
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

        std::srand(std::time(0));

        size_t id = core.texture_handler->load("../../res/images/Logo.png");
        Game_Object object(
            std::rand() % 800, std::rand() % 600, 120, 80
        );
        object.set_texture(core.texture_handler->get(id));

        core.scene->add(&object, "localhost");
        core.loop();
    }
    catch(const char* message)
    {
        std::cout << message << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
