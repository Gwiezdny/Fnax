#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

class Animatronic {
	int position;
	int index{ 1 };
	short int iq;
	std::vector<sf::Texture> Textures;
	std::vector<short> PositionIndex; // using to transfortm position to index and like a patern move animatronic

	short transformPosiionToIndex();

public:
	Animatronic(const std::string path, const short tmpIq, const short tmpPos);
	short int getPosition();
	void setPosition(int pos);
	void addTexture(const std::string path, const short index);
	//void addPositionIndex(const short index);
	sf::Texture getTexture();
};