#include "Root.h"

Root::Root() {
    Window.setFramerateLimit(60);
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
            Office.renderer();
        }
        case 4: { //cameras 

        }

        default:
            break;
            return 0;
        }
    }
}