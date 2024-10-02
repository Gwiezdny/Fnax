#include "CameraSystem.h"

CameraSystem::CameraSystem() {
    preWindow.create(1280, 720);
    for(int i = 0; i < 11; i++){ selectCameraButtonRenderTexture[i].create(60, 40); }
    if (!cameraButtonTexture.loadFromFile("assets/office/cameraButton.png")) { std::cerr << "Failed to load camera_button texture" << std::endl; }
    if (!locationMapTexture.loadFromFile("assets/cameraSystem/locationMap.png")) { std::cerr << "Failed to load LocationMap texture" << std::endl; }
    cameraButtonSprite.setTexture(cameraButtonTexture);
    cameraButtonSprite.setPosition(256.0f, 645.0f);
    LocationMapSprite.setTexture(locationMapTexture);
    LocationMapSprite.setPosition(860.0f, 260.0f);

    if (!shader.loadFromFile("src/shader/PanoramaShaderVert.vert", "src/shader/PanoramaShaderFrag.frag")) { std::cerr << "Failed to load shader" << std::endl; }

    std::vector<sf::Texture> Room;
    for (int i = 1; i <= 11; i++) { Rooms.push_back(Room); } 
    for(int i = 0; i <= 8; i++) {  }
    loadRoomsTextures();
    loadSelectedCameraButtonsTextures();
    selectedCameraButtonInit();
    loadNoiseTextures();
}

void CameraSystem::loadNoiseTextures() {
    std::string tmp;
    for (int i = 0; i <= 7; i++) {
        tmp = "/" + std::to_string(i) + ".png";
        if (!noiseTextures[i].loadFromFile("assets/general/noise" + tmp)) { std::cerr << "Failed to load noise texture" << std::endl; }
    }
}

void CameraSystem::addRoomTexture(short roomID, std::string path) {
    sf::Texture tmpTexture;
    tmpTexture.loadFromFile(path);
    Rooms[roomID - 1].push_back(tmpTexture);
}

void CameraSystem::moveView() {
    static sf::Vector2f direction{ 0.5, 0 };
    view.move(direction);

    if (view.getCenter().x > backgroundTexture.getSize().x - view.getSize().x / 2) {
        direction.x = -0.5;
    }
    else if (view.getCenter().x < view.getSize().x / 2) {
        direction.x = 0.5;
    }

}

void CameraSystem::loadSelectedCameraButtonsTextures() {
    if (!selectedCameraButtonsTexture.loadFromFile("assets/cameraSystem/selectedCamera.png")) { std::cerr << "Failed to load selectedCamera.png texture" << std::endl; }
    if (!nonSelectedCameraButtonsTexture.loadFromFile("assets/cameraSystem/nonSelectedCamera.png")) { std::cerr << "Failed to nonSelectedCamera.png texture" << std::endl; }
    sf::Texture tmpTexture;
    std::string tmp;
    for (int i = 0; i < 11; i++) {
        tmp = "/" + std::to_string(i + 1) + ".png";
        if (!selectCameraButtonsTxtTextures[i] .loadFromFile("assets/cameraSystem" + tmp)) { std::cerr << "Failed to load selectedCameraButton texture" << std::endl; }
    }
}

void CameraSystem::loadRoomsTextures() {
    addRoomTexture(1, "assets/Rooms/01/0100.png");
    addRoomTexture(1, "assets/Rooms/01/0101.png");
    addRoomTexture(1, "assets/Rooms/01/0102.png");
    addRoomTexture(1, "assets/Rooms/01/0103.png");
    addRoomTexture(1, "assets/Rooms/01/0104.png");
    addRoomTexture(1, "assets/Rooms/01/0105.png");
    addRoomTexture(1, "assets/Rooms/01/0106.png");
    addRoomTexture(2, "assets/Rooms/02/0200.png");
    addRoomTexture(2, "assets/Rooms/02/0299.png");
    addRoomTexture(3, "assets/Rooms/03/0300.png");
    addRoomTexture(4, "assets/Rooms/04/0400.png");
    addRoomTexture(5, "assets/Rooms/05/0500.png");
    addRoomTexture(5, "assets/Rooms/05/itsme.png");
    addRoomTexture(6, "assets/Rooms/06/0600.png");
    addRoomTexture(7, "assets/Rooms/07/0700.png");
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

void CameraSystem::selectedCameraButtonInit() {

    generateAndSetSelectCamearButtonTexture(STAGE);

    for (int i = 2; i <= 11; i++) {
        generateAndSetNonSelectCamearButtonTexture(i);
    }

    selectCameraButtonsSprite[STAGE - 1].setPosition(960.0f, 280.0f);
    selectCameraButtonsSprite[BACKSTAGE - 1].setPosition(840.0f, 364.0f);
    selectCameraButtonsSprite[DININGAREA - 1].setPosition(940.0f, 336.0f);
    selectCameraButtonsSprite[RESTROOMS - 1].setPosition(1177.0f, 365.0f);
    selectCameraButtonsSprite[PIRATECOVE - 1].setPosition(910.0f, 415.0f);
    selectCameraButtonsSprite[SUPPLYCLOSET - 1].setPosition(880.0f, 515.0f);
    selectCameraButtonsSprite[KITCHEN - 1].setPosition(1170.0f, 497.0f);
    selectCameraButtonsSprite[WESTHALLA - 1].setPosition(964.0f, 530.0f);
    selectCameraButtonsSprite[WESTHALLB - 1].setPosition(964.0f, 570.0f);
    selectCameraButtonsSprite[EASTHALLA - 1].setPosition(1073.0f, 530.0f);
    selectCameraButtonsSprite[EASTHALLB - 1].setPosition(1073.0f, 570.0f);
}

void CameraSystem::generateAndSetSelectCamearButtonTexture(int cameraID) {
    sf::Sprite tmpSprite;
    sf::Sprite tmpSpriteTXT;

    selectCameraButtonRenderTexture[cameraID - 1].clear();
    tmpSprite.setTexture(selectedCameraButtonsTexture);
    selectCameraButtonRenderTexture[cameraID - 1].draw(tmpSprite);
    tmpSpriteTXT.setTexture(selectCameraButtonsTxtTextures[cameraID - 1]);
    tmpSpriteTXT.setPosition(6.0f, 6.0f);
    selectCameraButtonRenderTexture[cameraID - 1].draw(tmpSpriteTXT);
    selectCameraButtonRenderTexture[cameraID - 1].display();
    selectCameraButtonsSprite[cameraID - 1].setTexture(selectCameraButtonRenderTexture[cameraID - 1].getTexture());
}

void CameraSystem::generateAndSetNonSelectCamearButtonTexture(int cameraID) {
    sf::Sprite tmpSprite;
    sf::Sprite tmpSpriteTXT;

    selectCameraButtonRenderTexture[cameraID - 1].clear();
    tmpSprite.setTexture(nonSelectedCameraButtonsTexture);
    selectCameraButtonRenderTexture[cameraID - 1].draw(tmpSprite);
    tmpSpriteTXT.setTexture(selectCameraButtonsTxtTextures[cameraID - 1]);
    tmpSpriteTXT.setPosition(6.0f, 6.0f);
    selectCameraButtonRenderTexture[cameraID - 1].draw(tmpSpriteTXT);
    selectCameraButtonRenderTexture[cameraID - 1].display();
    selectCameraButtonsSprite[cameraID - 1].setTexture(selectCameraButtonRenderTexture[cameraID - 1].getTexture());
}

bool CameraSystem::ifAnimatronicisInTheRoomSetTexture(Animatronic& Animatronic) {
    if (selectedCamera * 100 <= Animatronic.getPosition() && (selectedCamera * 100) + 100 > Animatronic.getPosition()) {
        backgroundTexture = Animatronic.getTexture();
        backgroundSprite.setTexture(backgroundTexture);
        return true;
    }
    return false;
}

void CameraSystem::updateRoomTextureBasedOnAnimatronicsPosition(Animatronic& Bonnie, Animatronic& Freddy, Animatronic& Chica, Animatronic& Foxy) {
    if (selectedCamera == STAGE) {
        if (selectedCamera * 100 <= Freddy.getPosition() && (selectedCamera * 100) + 100 > Freddy.getPosition()) {
            if (selectedCamera * 100 <= Chica.getPosition() && (selectedCamera * 100) + 100 > Chica.getPosition()) {
                if (selectedCamera * 100 <= Bonnie.getPosition() && (selectedCamera * 100) + 100 > Bonnie.getPosition()) {
                    backgroundTexture = Rooms[STAGE - 1][1];
                    backgroundSprite.setTexture(backgroundTexture);
                }
                else {
                    backgroundTexture = Rooms[STAGE - 1][3];
                    backgroundSprite.setTexture(backgroundTexture);
                }
            }
            else {
                if (selectedCamera * 100 <= Bonnie.getPosition() && (selectedCamera * 100) + 100 > Bonnie.getPosition()) {
                    backgroundTexture = Rooms[STAGE - 1][4];
                    backgroundSprite.setTexture(backgroundTexture);
                }
                else {
                    backgroundTexture = Rooms[STAGE - 1][5];
                    backgroundSprite.setTexture(backgroundTexture);
                }
            }
        }
        else {
            backgroundTexture = Rooms[STAGE - 1][0];
            backgroundSprite.setTexture(backgroundTexture);
        }
    }
    else if (ifAnimatronicisInTheRoomSetTexture(Freddy)) { return; }
    else if (ifAnimatronicisInTheRoomSetTexture(Foxy)) { return; }
    else if (ifAnimatronicisInTheRoomSetTexture(Bonnie)) { return; }
    else if (ifAnimatronicisInTheRoomSetTexture(Chica)) { return; }
    else { 
        backgroundTexture = Rooms[selectedCamera - 1][0]; 
        backgroundSprite.setTexture(backgroundTexture); 
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

void CameraSystem::updateSelectCameraButtonsTextures() {
    for (int i = 1; i <= 11; i++) {
        generateAndSetNonSelectCamearButtonTexture(i);
    }
    generateAndSetSelectCamearButtonTexture(selectedCamera);
}

void CameraSystem::updateSelectCameraButtonStatus(sf::Sprite targetCameraButton, int cameraID) {
    if (targetCameraButton.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
        selectedCamera = cameraID;
        updateSelectCameraButtonsTextures();
    }
}

void CameraSystem::noiseAnimation() {
    static int animationFrame{ 0 };
    noiseSprite.setTexture(noiseTextures[animationFrame]);
    animationFrame++;
    if (animationFrame >= 8) { animationFrame = 0; }
}

void CameraSystem::animationModule() {
    if (clock.getElapsedTime().asSeconds() > 0.02) {
        noiseAnimation();
        clock.restart();
    }
}

int CameraSystem::interactCheck(sf::Mouse& tmpMouse, sf::RenderWindow& tmpWindow) {
    relativeMousePosition = tmpWindow.mapPixelToCoords(tmpMouse.getPosition(tmpWindow), view);
    mousePosition = tmpWindow.mapPixelToCoords(tmpMouse.getPosition(tmpWindow));
    if (!tmpMouse.isButtonPressed(tmpMouse.Left)) { doAction = true; }
    if (tmpMouse.isButtonPressed(tmpMouse.Left) && doAction) {
        updateSelectCameraButtonStatus(selectCameraButtonsSprite[STAGE - 1], STAGE);
        updateSelectCameraButtonStatus(selectCameraButtonsSprite[BACKSTAGE - 1], BACKSTAGE);
        updateSelectCameraButtonStatus(selectCameraButtonsSprite[DININGAREA - 1], DININGAREA);
        updateSelectCameraButtonStatus(selectCameraButtonsSprite[RESTROOMS - 1], RESTROOMS);
        updateSelectCameraButtonStatus(selectCameraButtonsSprite[PIRATECOVE - 1], PIRATECOVE);
        updateSelectCameraButtonStatus(selectCameraButtonsSprite[SUPPLYCLOSET - 1], SUPPLYCLOSET);
        updateSelectCameraButtonStatus(selectCameraButtonsSprite[KITCHEN - 1], KITCHEN);
        updateSelectCameraButtonStatus(selectCameraButtonsSprite[WESTHALLA - 1], WESTHALLA);
        updateSelectCameraButtonStatus(selectCameraButtonsSprite[WESTHALLB - 1], WESTHALLB);
        updateSelectCameraButtonStatus(selectCameraButtonsSprite[EASTHALLA - 1], EASTHALLA);
        updateSelectCameraButtonStatus(selectCameraButtonsSprite[EASTHALLB - 1], EASTHALLB);
    }
    return closeCameraSystem();
}

void CameraSystem::renderer(sf::RenderWindow& tmpWindow, sf::Mouse& Mouse) {
    shader.setUniform("texture", sf::Shader::CurrentTexture);
    shader.setUniform("resolution", view.getSize());

    animationModule();

    preWindow.clear();
    preWindow.draw(backgroundSprite);

    moveView();
    preWindow.setView(view);
    preWindow.display();

    preWindowTexture = preWindow.getTexture();
    preWindowSprite.setTexture(preWindowTexture);

    tmpWindow.clear();
    tmpWindow.draw(preWindowSprite, &shader);
    tmpWindow.draw(noiseSprite);
    tmpWindow.draw(LocationMapSprite);
    for (int i = 0; i < 11; i++) { tmpWindow.draw(selectCameraButtonsSprite[i]); }
    if (canCloseCameraSystem) { tmpWindow.draw(cameraButtonSprite); }
    tmpWindow.display();
}