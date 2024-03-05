#include "Office.h"

Office::Office() {
    preWindow.create(1280, 720);
    if (!backgroundTexture[0].loadFromFile("assets/office/OfficeBackground/default.png")) { std::cerr << "Failed to load office_background texture" << std::endl; }
    if (!backgroundTexture[1].loadFromFile("assets/office/OfficeBackground/leftLight.png")) { std::cerr << "Failed to load office_background texture" << std::endl; }
    if (!backgroundTexture[2].loadFromFile("assets/office/OfficeBackground/rightLight.png")) { std::cerr << "Failed to load office_background texture" << std::endl; }
    if (!backgroundTexture[3].loadFromFile("assets/office/OfficeBackground/bonnie.png")) { std::cerr << "Failed to load office_background texture" << std::endl; }
    if (!backgroundTexture[4].loadFromFile("assets/office/OfficeBackground/chica.png")) { std::cerr << "Failed to load office_background texture" << std::endl; }
    backgroundSprite.setTexture(backgroundTexture[0]);
    if (!cameraButtonTexture.loadFromFile("assets/office/cameraButton.png")) { std::cerr << "Failed to load camera_button texture" << std::endl; }
    cameraButtonSprite.setTexture(cameraButtonTexture);
    cameraButtonSprite.setPosition(256.0f, 645.0f);

    if (!shader.loadFromFile("src/shader/PanoramaShaderVert.vert", "src/shader/PanoramaShaderFrag.frag")) { std::cerr << "Failed to load shader" << std::endl; }
    std::string tmp;
    for (int i = 0; i < 3; i++) {
        tmp = "/" + std::to_string(i) + ".png";
        if (!fan[i].loadFromFile("assets/office/fan" + tmp)) { std::cerr << "Failed to load door texture" << std::endl; }
    }

    ButtonLeftSprite.setTexture(DoorLeft.buttonOff);
    ButtonLeftSprite.setPosition(5.0f, 310.0f);
    ButtonRightSprite.setTexture(DoorRight.buttonOff);
    ButtonRightSprite.setPosition(1517.0f, 305.0f);
    DoorLeftSprite.setTexture(DoorLeft.animation[0]);
    DoorLeftSprite.setPosition(70.0f, 5.0f);
    DoorRightSprite.setTexture(DoorRight.animation[0]);
    DoorRightSprite.setPosition(1272.0f, 5.0f);
    fanSprite.setPosition(780.0f, 303.0f);
}

sf::Vector2f Office::mouseMoveTracking(sf::Window& tmpWindow, sf::Mouse& tmpMouse) {
    sf::Vector2f direction;
    sf::Vector2i position = tmpMouse.getPosition(tmpWindow);

    int size = tmpWindow.getSize().x;
    double relativePosition = position.x - (size / 2);

    if (relativePosition > tmpWindow.getSize().x / 2 * 0.2 || relativePosition < tmpWindow.getSize().x / 2 * -0.2) { direction.x = relativePosition / (size / 48); }

    return direction;
}

void Office::checkViewMove(sf::View& tmpView, sf::Vector2f tmpVector, int tmpTextureSizeX) { //Check office border
    if (tmpView.getCenter().x < tmpTextureSizeX - tmpView.getSize().x / 2 && tmpVector.x > 0) {
        tmpView.move(tmpVector);
        if (tmpView.getCenter().x > tmpTextureSizeX - tmpView.getSize().x / 2) {
            tmpView.setCenter(tmpTextureSizeX - tmpView.getSize().x / 2, tmpView.getCenter().y);
        }
    }
    if (tmpView.getCenter().x > tmpView.getSize().x / 2 && tmpVector.x < 0) {
        tmpView.move(tmpVector);
        if (tmpView.getCenter().x < tmpView.getSize().x / 2) {
            tmpView.setCenter(tmpView.getSize().x / 2, tmpView.getCenter().y);
        }
    }
}

void Office::updateButtonStatus(Door& TargetDoor, sf::Sprite& ButtonSprite, Door& SecoundDoor) {
    if (ButtonSprite.getGlobalBounds().contains(relativeMousePosition.x, relativeMousePosition.y)) {
        if (relativeMousePosition.y < ButtonSprite.getPosition().y + (ButtonSprite.getTexture()->getSize().y / 2)) {
            TargetDoor.isClose = !TargetDoor.isClose;
            textureUpdateNeed = true;
            doAction = false;
        }
        else {
            TargetDoor.isLightOn = !TargetDoor.isLightOn;
            SecoundDoor.isLightOn = false;
            textureUpdateNeed = true;
            doAction = false;
        }
    }
}

int Office::openCameraSystem() {
    if (cameraButtonSprite.getGlobalBounds().contains(mousePosition.x, mousePosition.y) && canOpenCameraSystem) {
        canOpenCameraSystem = false;
        return 1;
    }
    else if (!cameraButtonSprite.getGlobalBounds().contains(mousePosition.x, mousePosition.y) && !canOpenCameraSystem) {
        canOpenCameraSystem = true;
        return 0;
    }
    else { 
        return 0; 
    }
}

int Office::interactCheck(sf::Mouse& tmpMouse, sf::RenderWindow& tmpWindow) {
    relativeMousePosition = tmpWindow.mapPixelToCoords(tmpMouse.getPosition(tmpWindow), view);
    mousePosition = tmpWindow.mapPixelToCoords(tmpMouse.getPosition(tmpWindow));
    if (!tmpMouse.isButtonPressed(tmpMouse.Left)) { doAction = true; }
    if (tmpMouse.isButtonPressed(tmpMouse.Left) && doAction) {
        updateButtonStatus(DoorLeft, ButtonLeftSprite, DoorRight);
        updateButtonStatus(DoorRight, ButtonRightSprite, DoorLeft);
    }
    return openCameraSystem();
}
void Office::buttonTextureUpdate(Door& Door, sf::Sprite& buttonSprite) {
    if (!Door.isClose && !Door.isLightOn) { //both off
        buttonSprite.setTexture(Door.buttonOff);
    }
    else if (Door.isClose && !Door.isLightOn) {//door close
        buttonSprite.setTexture(Door.buttonDoor);
    }
    else if (!Door.isClose && Door.isLightOn) {//light on
        buttonSprite.setTexture(Door.buttonLight);
    }
    else {//both on
        buttonSprite.setTexture(Door.buttonBoth);
    }
}

void Office::doorTextureUpdate(Door& Door, sf::Sprite& doorSprite) {
    if (Door.isClose && Door.animationFrame < 15) {
        doorSprite.setTexture(Door.animation[Door.animationFrame]);
        Door.animationFrame++;
    }
    else if(!Door.isClose && Door.animationFrame > 0) {
        Door.animationFrame--;
        doorSprite.setTexture(Door.animation[Door.animationFrame]);
    }
}

void Office::fanAnimation() {
    fanSprite.setTexture(fan[fanAnimationFrame]);
    fanAnimationFrame++;
    if (fanAnimationFrame > 2) { fanAnimationFrame = 0; }
}

void Office::lightTextureUpdate() {
    if (DoorLeft.isLightOn && !isBonnie) {
        backgroundSprite.setTexture(backgroundTexture[1]);
    }
    else if(DoorRight.isLightOn && !isChica){
        backgroundSprite.setTexture(backgroundTexture[2]);
    }
    else if(DoorLeft.isLightOn && isBonnie){
        backgroundSprite.setTexture(backgroundTexture[3]);
    }
    else if (DoorRight.isLightOn && isChica) {
        backgroundSprite.setTexture(backgroundTexture[4]);
    }
    else {
        backgroundSprite.setTexture(backgroundTexture[0]);
    }
}

void Office::textureModule() {
    if (textureUpdateNeed == true) {
        buttonTextureUpdate(DoorLeft, ButtonLeftSprite);
        buttonTextureUpdate(DoorRight, ButtonRightSprite);
        lightTextureUpdate();
    }
}

void Office::animationModule() {
    doorTextureUpdate(DoorLeft, DoorLeftSprite);
    doorTextureUpdate(DoorRight, DoorRightSprite);
    if (clock.getElapsedTime().asSeconds() > 0.02) {
        fanAnimation();
        clock.restart();
    }
}

void Office::renderer(sf::RenderWindow& tmpWindow, sf::Mouse& tmpMouse) {

    shader.setUniform("texture", sf::Shader::CurrentTexture);
    //shader.setUniform("resolution", sf::Vector2f(texture.getSize()));
    shader.setUniform("resolution", view.getSize());
    //shader.setUniform("curvature", 5.5f); // Dostosuj wartoœæ zakrzywienia wed³ug potrzeb

    checkViewMove(view, mouseMoveTracking(tmpWindow, tmpMouse), backgroundTexture[0].getSize().x);

    textureModule();
    animationModule();

    preWindow.clear();
    preWindow.draw(backgroundSprite);
    preWindow.draw(ButtonLeftSprite);
    preWindow.draw(ButtonRightSprite);
    preWindow.draw(DoorLeftSprite);
    preWindow.draw(DoorRightSprite);
    preWindow.draw(fanSprite);

    preWindow.setView(view);
    preWindow.display();

    preWindowTexture = preWindow.getTexture();
    preWindowSprite.setTexture(preWindowTexture);

    tmpWindow.clear();
    tmpWindow.draw(preWindowSprite, &shader);
    tmpWindow.draw(cameraButtonSprite);
    tmpWindow.display();
}