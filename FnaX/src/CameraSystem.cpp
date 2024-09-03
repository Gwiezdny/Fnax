#include "CameraSystem.h"

CameraSystem::CameraSystem() {
    if (!cameraButtonTexture.loadFromFile("assets/office/cameraButton.png")) { std::cerr << "Failed to load camera_button texture" << std::endl; }
    if (!locationMapTexture.loadFromFile("assets/cameraSystem/locationMap.png")) { std::cerr << "Failed to load LocationMap texture" << std::endl; }
    cameraButtonSprite.setTexture(cameraButtonTexture);
    cameraButtonSprite.setPosition(256.0f, 645.0f);
    LocationMapSprite.setTexture(locationMapTexture);
    LocationMapSprite.setPosition(860.0f, 260.0f);

    if (!shader.loadFromFile("src/shader/PanoramaShaderVert.vert", "src/shader/PanoramaShaderFrag.frag")) { std::cerr << "Failed to load shader" << std::endl; }

    std::vector<sf::Texture> Room;
    for (int i = 1; i <= 11; i++) { Rooms.push_back(Room); } 
    loadTextures();
    
}

void CameraSystem::addRoomTexture(short roomID, std::string path) {
    sf::Texture tmpTexture;
    tmpTexture.loadFromFile(path);
    Rooms[roomID - 1].push_back(tmpTexture);
}

void CameraSystem::loadTextures() {
    addRoomTexture(1, "assets/Rooms/01/0100.png");
    addRoomTexture(1, "assets/Rooms/01/0199.png");
    addRoomTexture(1, "assets/Rooms/01/0198.png");
    addRoomTexture(2, "assets/Rooms/02/0200.png");
    addRoomTexture(2, "assets/Rooms/02/0299.png");
    addRoomTexture(3, "assets/Rooms/03/0300.png");
    addRoomTexture(4, "assets/Rooms/04/0400.png");

    addRoomTexture(6, "assets/Rooms/06/0600.png");
    addRoomTexture(8, "assets/Rooms/08/0800.png");
    addRoomTexture(8, "assets/Rooms/08/0899.png");
    addRoomTexture(9, "assets/Rooms/09/0900.png");
    addRoomTexture(9, "assets/Rooms/09/0999.png");
    addRoomTexture(9, "assets/Rooms/09/0998.png");
    addRoomTexture(10, "assets/Rooms/10/1000.png");
    addRoomTexture(10, "assets/Rooms/10/1099.png");
    addRoomTexture(10, "assets/Rooms/10/1098.png");
    addRoomTexture(11, "assets/Rooms/11/1100.png");
    addRoomTexture(11, "assets/Rooms/11/1199.png");
    addRoomTexture(11, "assets/Rooms/11/1198.png");
    addRoomTexture(11, "assets/Rooms/11/1197.png");
    addRoomTexture(11, "assets/Rooms/11/1196.png");
}

void CameraSystem::updateRoomTextureBasedOnAnimatronicsPosition(Animatronic& Bonnie, Animatronic& Freddy, Animatronic& Chica, Animatronic& Foxy) {
    if ( true ) {

    }
    else {

    }
}

int CameraSystem::closeCameraSystem() {
    if (cameraButtonSprite.getGlobalBounds().contains(mousePosition.x, mousePosition.y) && canCloseCameraSystem) {
        canCloseCameraSystem = false;
        return 1;
    }
    else if (mousePosition.y < 640 && !canCloseCameraSystem) {
        canCloseCameraSystem = true;
        return 0; 
    }
    else {
        return 0;
    }
}

int CameraSystem::interactCheck(sf::Mouse& tmpMouse, sf::RenderWindow& tmpWindow) {
    mousePosition = tmpWindow.mapPixelToCoords(tmpMouse.getPosition(tmpWindow));
    return closeCameraSystem();
}

void CameraSystem::renderer(sf::RenderWindow& tmpWindow, sf::Mouse& Mouse) {

    preWindow.clear();
    preWindow.setView(view);
    preWindow.display();

    preWindowTexture = preWindow.getTexture();
    preWindowSprite.setTexture(preWindowTexture);

    tmpWindow.clear();
    tmpWindow.draw(preWindowSprite, &shader);
    tmpWindow.draw(LocationMapSprite);
    if (canCloseCameraSystem) { tmpWindow.draw(cameraButtonSprite); }
    tmpWindow.display();
}