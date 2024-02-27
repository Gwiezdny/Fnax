#include "Office.h"

Office::Office(sf::RenderWindow& Window, sf::Mouse& Mouse) {
    tmpWindow = &Window;
    tmpMouse = &Mouse;
    preWindow.create(1280, 720);
    if (!backgroundTexture.loadFromFile("assets/office.png")) { std::cerr << "Failed to load office_background texture" << std::endl; }
    backgroundSprite.setTexture(backgroundTexture);
    if (!shader.loadFromFile("src/shader/PanoramaShaderVert.vert", "src/shader/PanoramaShaderFrag.frag")) { std::cerr << "Failed to load shader" << std::endl; }
}

sf::Vector2f Office::mouseTracking(sf::Window& tmpWindow, sf::Mouse& tmpMouse) {
    sf::Vector2f direction;
    sf::Vector2i position = tmpMouse.getPosition(tmpWindow);

    int size = tmpWindow.getSize().x;
    double relativePosition = position.x - (size / 2);

    if (relativePosition > tmpWindow.getSize().x / 2 * 0.2 || relativePosition < tmpWindow.getSize().x / 2 * -0.2) { direction.x = relativePosition / (size / 32); }

    return direction;
}

void Office::checkViewMove(sf::View& tmpView, sf::Vector2f tmpVector, int tmpTextureSizeX) {
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

void Office::renderer() {

    shader.setUniform("texture", sf::Shader::CurrentTexture);
    //shader.setUniform("resolution", sf::Vector2f(texture.getSize()));
    shader.setUniform("resolution", view.getSize());
    //shader.setUniform("curvature", 5.5f); // Dostosuj wartoœæ zakrzywienia wed³ug potrzeb

    checkViewMove(view, mouseTracking(*tmpWindow, *tmpMouse), backgroundTexture.getSize().x);

    preWindow.clear();
    preWindow.draw(backgroundSprite);
    preWindow.setView(view);
    preWindow.display();

    preWindowTexture = preWindow.getTexture();
    preWindowSprite.setTexture(preWindowTexture);

    tmpWindow->clear();
    tmpWindow->draw(preWindowSprite, &shader);
    tmpWindow->display();
}