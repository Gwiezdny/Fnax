//#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Animatronic.h"

class CameraSystem
{
	#define STAGE 1
	#define BACKSTAGE 2
	#define DININGAREA 3
	#define RESTROOMS 4
	#define PIRATECOVE 5
	#define SUPPLYCLOSET 6
	#define KITCHEN 7 
	#define WESTHALLA 8
	#define WESTHALLB 9
	#define EASTHALLA 10
	#define EASTHALLB 11

	sf::View view{ sf::FloatRect(0.f, 0.f, 1280.f, 720.f) };
	sf::RenderTexture preWindow;
	sf::RenderTexture selectCameraButtonRenderTexture[11];
	sf::Shader shader;
	sf::Vector2f mousePosition;
	sf::Vector2f relativeMousePosition;
	bool doAction{ true };
	bool canCloseCameraSystem{ false };
	int selectedCamera = STAGE;
	sf::Clock clock;

	sf::Texture preWindowTexture;
	sf::Texture cameraButtonTexture;
	sf::Texture	locationMapTexture;
	sf::Texture selectedCameraButtonsTexture;
	sf::Texture nonSelectedCameraButtonsTexture;
	std::vector<std::vector<sf::Texture>> Rooms;
	sf::Texture selectCameraButtonsTxtTextures[11];
	sf::Texture backgroundTexture;
	sf::Texture noiseTextures[8];

	sf::Sprite preWindowSprite;
	sf::Sprite cameraButtonSprite;
	sf::Sprite LocationMapSprite;
	sf::Sprite backgroundSprite;
	sf::Sprite selectCameraButtonsSprite[11];
	sf::Sprite noiseSprite;

	int closeCameraSystem();
	void addRoomTexture(short roomID, std::string path);
	void loadRoomsTextures();
	void loadSelectedCameraButtonsTextures();
	bool ifAnimatronicisInTheRoomSetTexture(Animatronic& Animatronic);
	void selectedCameraButtonInit();
	void updateSelectCameraButtonStatus(sf::Sprite targetCameraButton, int cameraID);
	void updateSelectCameraButtonsTextures();
	void generateAndSetSelectCamearButtonTexture(int cameraID);
	void generateAndSetNonSelectCamearButtonTexture(int cameraID);
	void moveView();
	void noiseAnimation();
	void animationModule();
	void loadNoiseTextures();
public:
	CameraSystem();
	int interactCheck(sf::Mouse& tmpMouse, sf::RenderWindow& tmpWindow);
	void renderer(sf::RenderWindow& tmpWindow, sf::Mouse& Mouse);
	void updateRoomTextureBasedOnAnimatronicsPosition(Animatronic& Bonnie, Animatronic& Freddy, Animatronic& Chica, Animatronic& Foxy);
};


