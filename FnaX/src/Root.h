#include <SFML/Graphics.hpp>
//#include <iostream>
//#include "Crown.h"
#include "Office.h"
#include "Menu.h"
#include "CustomNight.h"
#include "CameraSystem.h"
//#include "Animatronic.h"

class Root
{
	sf::RenderWindow Window{ sf::VideoMode(1280, 720), "SFML Shader Example" };
	int location{ 3 }; 
	CameraSystem CameraSystem;
	Office Office;
	sf::Mouse Mouse;

	Animatronic Bonnie{ "assets/general/nan.png", 10, 101 };
	Animatronic Freedy{ "assets/general/nan.png", 10, 1101 };
	Animatronic Chica{ "assets/general/nan.png", 10, 101 };
	Animatronic Foxy{ "assets/general/nan.png", 10, 501 };

	void loadBonnieTextures();
	void loadFreddyTextures();
	void loadChicaTextures();
	void loadFoxyTextures();
public:
	Root();
	int gameLoop();
};

