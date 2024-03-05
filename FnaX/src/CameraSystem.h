#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Room.h"

class CameraSystem
{
	sf::View view{ sf::FloatRect(0.f, 0.f, 1280.f, 720.f) };
	sf::RenderTexture preWindow;
	sf::Shader shader;
	sf::Vector2f mousePosition;
	bool doAction{ true };
	bool canCloseCameraSystem{ false };

	sf::Texture preWindowTexture;
	sf::Texture cameraButtonTexture;

	sf::Sprite preWindowSprite;
	sf::Sprite cameraButtonSprite;


	int closeCameraSystem();
public:
	CameraSystem();
	int interactCheck(sf::Mouse& tmpMouse, sf::RenderWindow& tmpWindow);
	void renderer(sf::RenderWindow& tmpWindow, sf::Mouse& Mouse);
};


