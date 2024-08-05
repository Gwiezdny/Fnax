#include "CameraSystem.h"

CameraSystem::CameraSystem() {
    if (!cameraButtonTexture.loadFromFile("assets/office/cameraButton.png")) { std::cerr << "Failed to load camera_button texture" << std::endl; }
    if (!locationMapTexture.loadFromFile("assets/cameraSystem/locationMap.png")) { std::cerr << "Failed to load LocationMap texture" << std::endl; }
    cameraButtonSprite.setTexture(cameraButtonTexture);
    cameraButtonSprite.setPosition(256.0f, 645.0f);
    LocationMapSprite.setTexture(locationMapTexture);
    LocationMapSprite.setPosition(860.0f, 260.0f);

    if (!shader.loadFromFile("src/shader/PanoramaShaderVert.vert", "src/shader/PanoramaShaderFrag.frag")) { std::cerr << "Failed to load shader" << std::endl; }
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