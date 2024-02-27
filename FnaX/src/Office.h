#include <SFML/Graphics.hpp>
#include <iostream>


class Office {
	sf::RenderWindow *tmpWindow;
	sf::Mouse *tmpMouse;
	sf::View view{ sf::FloatRect(0.f, 0.f, 1280.f, 720.f) };
	sf::Texture backgroundTexture;
	sf::RenderTexture preWindow;
	sf::Sprite backgroundSprite;
	sf::Sprite preWindowSprite;
	sf::Shader shader;
	sf::Texture preWindowTexture;


	void checkViewMove(sf::View& tmpView, sf::Vector2f tmpVector, int tmpTextureSizeX);
	sf::Vector2f mouseTracking(sf::Window& tmpWindow, sf::Mouse& tmpMouse);
public:
	Office(sf::RenderWindow& Window, sf::Mouse& Mouse);
	void renderer();
};