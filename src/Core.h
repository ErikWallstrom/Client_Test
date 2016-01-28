#ifndef CORE_H
#define CORE_H

#include "Texture_Handler.h"
#include "Event_Handler.h"
#include "Connection.h"
#include "Window.h"
#include "Scene.h"

class Core
{
private:
    Event_Handler* event_handler;

    bool running;

    void handle_events();
    void update(int delta);

public:
    Connection* connection;
    Window* window;
    Scene* scene;
    Texture_Handler* texture_handler;

    Core(const char* title, int width, int height,
         const char* ip, Uint16 port);
    ~Core();
    void loop();
};

#endif
