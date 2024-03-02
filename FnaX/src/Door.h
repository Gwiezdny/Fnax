#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
struct Door
{
	bool isClose{ false };
	bool isLightOn{ false };
	sf::Texture animation[15];
	sf::Texture buttonOff;
	sf::Texture buttonDoor;
	sf::Texture buttonLight;
	sf::Texture buttonBoth;
	int animationFrame{ 0 };

	Door(std::string path);
};

