#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
//#include "Crown.h"
#include "Office.h"
#include "Menu.h"
#include "CustomNight.h"
#include "CameraSystem.h"

class Root
{
	sf::RenderWindow Window{ sf::VideoMode(1280, 720), "SFML Shader Example" };
	int location{ 3 }; 
	CameraSystem CameraSystem;
	Office Office;
	sf::Mouse Mouse;

public:
	Root();
	int gameLoop();
};

