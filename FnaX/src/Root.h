#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
//#include "Crown.h"
#include "Room.h"
#include "Office.h"
#include "Menu.h"
#include "CustomNight.h"

class Root
{
	sf::RenderWindow Window{ sf::VideoMode(1280, 720), "SFML Shader Example" };
	int location{ 2 };
	Room Map[11]; 
	Office Office{ Window, Mouse };
	sf::Mouse Mouse;

public:
	Root();
	int gameLoop();
};

