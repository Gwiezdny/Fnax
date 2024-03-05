#include <SFML/Graphics.hpp>
#include <iostream>
#include "Door.h"
#include <string>


class Office {
	sf::View view{ sf::FloatRect(0.f, 0.f, 1280.f, 720.f) };
	sf::RenderTexture preWindow;
	Door DoorLeft{ "assets/office/DoorLeft" };
	Door DoorRight{ "assets/office/DoorRight" };
	sf::Vector2f relativeMousePosition;
	sf::Vector2f mousePosition;
	bool textureUpdateNeed{ false };
	bool doAction{ true };
	bool canOpenCameraSystem{ true };
	bool isCameraOpening{ false };
	bool isCameraClosing{ false };
	int cameraAnimationFrame{ 0 };
	
	sf::Clock clock;
	int fanAnimationFrame{ 0 };
	bool isBonnie{ false };
	bool isChica{ false };

	sf::Texture backgroundTexture[5];
	sf::Shader shader;
	sf::Texture preWindowTexture;
	sf::Texture fan[3];
	sf::Texture cameraButtonTexture;
	sf::Texture cameraAnimationTexture[11];

	sf::Sprite backgroundSprite;
	sf::Sprite preWindowSprite;
	sf::Sprite DoorLeftSprite;
	sf::Sprite ButtonLeftSprite;
	sf::Sprite DoorRightSprite;
	sf::Sprite ButtonRightSprite;
	sf::Sprite fanSprite;
	sf::Sprite cameraButtonSprite;
	sf::Sprite cameraAnimationSprite;

	void checkViewMove(sf::View& tmpView, sf::Vector2f tmpVector, int tmpTextureSizeX);
	sf::Vector2f mouseMoveTracking(sf::Window& tmpWindow, sf::Mouse& tmpMouse);
	void updateButtonStatus(Door& TargetDoor, sf::Sprite& DoorSprite, Door& SecoundDoor);
	void textureModule();
	void animationModule();
	void buttonTextureUpdate(Door& Door, sf::Sprite& buttonSprite);
	void doorTextureUpdate(Door& Door, sf::Sprite& doorSprite);
	void fanAnimation();
	void lightTextureUpdate();
	int openCameraSystem();
	void cameraSystemAnimation();

public:
	Office();
	int interactCheck(sf::Mouse& tmpMouse, sf::RenderWindow& tmpWindow);
	void renderer(sf::RenderWindow& Window, sf::Mouse& Mouse);
};