#include "Root.h"

Root::Root() {
    Window.setFramerateLimit(60);
    loadBonnieTextures();
    loadChicaTextures();
    loadFreddyTextures();
    loadFoxyTextures();
}

void Root::loadBonnieTextures() {
    //Bonnie.addTexture("assets/Animatronics/Bonnie/0101.png", 101);
    Bonnie.addTexture("assets/Animatronics/Bonnie/0302.png", 302);
    Bonnie.addTexture("assets/Animatronics/Bonnie/0201.png", 201);
    Bonnie.addTexture("assets/Animatronics/Bonnie/0202.png", 202);
    Bonnie.addTexture("assets/Animatronics/Bonnie/0301.png", 301);
    Bonnie.addTexture("assets/Animatronics/Bonnie/0601.png", 601);
    Bonnie.addTexture("assets/Animatronics/Bonnie/0801.png", 801);
    Bonnie.addTexture("assets/Animatronics/Bonnie/0901.png", 901);
    Bonnie.addTexture("assets/Animatronics/Bonnie/0902.png", 902);
    Bonnie.addTexture("assets/Animatronics/Bonnie/0903.png", 903);
}

void Root::loadFreddyTextures() {
    //Freedy.addTexture("assets/Animatronics/Freddy/0101.png", 101);
    //Freedy.addTexture("assets/Animatronics/Freddy/0102.png", 102);
    Freedy.addTexture("assets/Animatronics/Freddy/0301.png", 301);
    Freedy.addTexture("assets/Animatronics/Freddy/0401.png", 401);
    Freedy.addTexture("assets/Animatronics/Freddy/1001.png", 1001);
    Freedy.addTexture("assets/Animatronics/Freddy/1101.png", 1101);
}

void Root::loadChicaTextures() {
    //Chica.addTexture("assets/Animatronics/Chica/0101.png", 101);
    Chica.addTexture("assets/Animatronics/Chica/0302.png", 302);
    Chica.addTexture("assets/Animatronics/Chica/0301.png", 301);
    Chica.addTexture("assets/Animatronics/Chica/0401.png", 401);
    Chica.addTexture("assets/Animatronics/Chica/0402.png", 402);
    Chica.addTexture("assets/Animatronics/Chica/1001.png", 1001);
    Chica.addTexture("assets/Animatronics/Chica/1002.png", 1002);
    Chica.addTexture("assets/Animatronics/Chica/1101.png", 1101);
    Chica.addTexture("assets/Animatronics/Chica/1102.png", 1102);
    Chica.addTexture("assets/Animatronics/Chica/1103.png", 1103);
}

void Root::loadFoxyTextures() {
    Foxy.addTexture("assets/Animatronics/Foxy/0501.png", 501);
    Foxy.addTexture("assets/Animatronics/Foxy/0502.png", 502);
    Foxy.addTexture("assets/Animatronics/Foxy/0503.png", 503);
}

int Root::gameLoop() {

    while (Window.isOpen())
    {
        sf::Event event;

        switch (location) {
        case 1: { //main menu

        }
        case 2: { //custom night
           
        }
        case 3: { //office
            if (Office.interactCheck(Mouse, Window) == 1) { location = 4; break; }
            Office.renderer(Window, Mouse);
            break;
        }
        case 4: { //cameras 
            if (CameraSystem.interactCheck(Mouse, Window) == 1) { location = 3; break; }
            CameraSystem.updateRoomTextureBasedOnAnimatronicsPosition(Bonnie, Freedy, Chica, Foxy);
            CameraSystem.renderer(Window, Mouse);
            break;
        }

        default:
            break;
            return 0;
        }

        while (Window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                Window.close();
        }
    }
    return 0;
}