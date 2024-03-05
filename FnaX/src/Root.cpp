#include "Root.h"

Root::Root() {
    Window.setFramerateLimit(60);

    std::string tmp;
    for (int i = 0; i < 11; i++) {
        tmp = "/" + std::to_string(i) + ".png";
        if (!CameraAnimation[i].loadFromFile("assets/general/CameraAnimation" + tmp)) { std::cerr << "Failed to load door texture" << std::endl; }
    }
}

int Root::gameLoop() {

    while (Window.isOpen())
    {
        sf::Event event;
        while (Window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                Window.close();
        }

        switch (location) {
        case 1: { //main menu

        }
        case 2: { //custom night
           
        }
        case 3: { //office
            if (Office.interactCheck(Mouse, Window) == 1) { location = 4; }
            Office.renderer(Window, Mouse);
            break;
        }
        case 4: { //cameras 
            if (CameraSystem.interactCheck(Mouse, Window) == 1) { location = 3; }
            CameraSystem.renderer(Window, Mouse);
            break;
        }

        default:
            break;
            return 0;
        }
    }
}