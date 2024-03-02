#include <SFML/Graphics.hpp>
#include <iostream>
#include "Door.h"
#include <string>


class Office {
	sf::View view{ sf::FloatRect(0.f, 0.f, 1280.f, 720.f) };
	Door DoorLeft{ "assets/office/DoorLeft" };
	Door DoorRight{ "assets/office/DoorRight" };
	sf::Vector2f mousePosition;
	bool textureUpdateNeed{ false };
	bool doAction{ true };
	sf::Clock clock;
	int fanAnimationFrame{ 0 };

	sf::Texture backgroundTexture;
	sf::RenderTexture preWindow;
	sf::Shader shader;
	sf::Texture preWindowTexture;
	sf::Texture fan[3];

	sf::Sprite backgroundSprite;
	sf::Sprite preWindowSprite;
	sf::Sprite DoorLeftSprite;
	sf::Sprite ButtonLeftSprite;
	sf::Sprite DoorRightSprite;
	sf::Sprite ButtonRightSprite;
	sf::Sprite fanSprite;

	void checkViewMove(sf::View& tmpView, sf::Vector2f tmpVector, int tmpTextureSizeX);
	sf::Vector2f mouseMoveTracking(sf::Window& tmpWindow, sf::Mouse& tmpMouse);
	void updateButtonStatus(Door& Door, sf::Sprite& DoorSprite);
	void textureModule();
	void animationModule();
	void buttonTextureUpdate(Door& Door, sf::Sprite& buttonSprite);
	void doorTextureUpdate(Door& Door, sf::Sprite& doorSprite);
	void fanAnimation();
public:
	Office();
	void interactCheck(sf::Mouse& tmpMouse, sf::RenderWindow& tmpWindow);
	void renderer(sf::RenderWindow& Window, sf::Mouse& Mouse);
};