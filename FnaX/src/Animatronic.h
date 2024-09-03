#include <SFML/Graphics.hpp>
#include <vector>

class Animatronic {
	short int position;
	short int iq;
	std::vector<sf::Texture> Textures;
	std::vector<short> PositionIndex;

	short transformPosiionToIndex();

public:
	Animatronic(const std::string path, const short tmpIq, const short tmpPos);
	short int getPosition();
	void setPosition(short pos);
	void addTexture(const std::string path, const short index);
	//void addPositionIndex(const short index);
	sf::Texture getTexture();
};