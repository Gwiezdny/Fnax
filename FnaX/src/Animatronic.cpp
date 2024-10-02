#include "Animatronic.h"

Animatronic::Animatronic(const std::string path,const short tmpIq,const short tmpPos) {
	iq = tmpIq;
	position = tmpPos;
	sf::Texture nanTexture;
	nanTexture.loadFromFile(path);
	Textures.push_back(nanTexture);
	PositionIndex.push_back(0);
}

short Animatronic::transformPosiionToIndex() { //return index of texture in Textures vector
	for (short i = 1; i < PositionIndex.size(); i++) {
		if (PositionIndex[i] == position) { return i; }
	}
	return 0; // nanTexture
}

void Animatronic::setPosition(int pos) { position = pos; }

void Animatronic::addTexture(const std::string path, const short index) {
	sf::Texture tmpTexture;
	if (!tmpTexture.loadFromFile(path)) { std::cout << "error" << std::endl; }
	Textures.push_back(tmpTexture);
	PositionIndex.push_back(index);
}

//void Animatronic::addPositionIndex(const short index) { PositionIndex.push_back(index); }

short int Animatronic::getPosition() { return position; }

sf::Texture Animatronic::getTexture() {
	//std::cout << "zwraca " << transformPosiionToIndex() << std::endl;
	return Textures[transformPosiionToIndex()];
}