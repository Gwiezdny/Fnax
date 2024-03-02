#include "Door.h"

Door::Door(std::string path) {
	std::string tmp;
	for (int i = 0; i < 15; i++) {
		tmp = "/" + std::to_string(i) + ".png";
		if (!animation[i].loadFromFile(path + tmp)) { std::cerr << "Failed to load door texture" << std::endl; }
	}
	if (!buttonOff.loadFromFile(path + "/b0.png")) { std::cerr << "Failed to load button_off texture" << std::endl; }
	if (!buttonDoor.loadFromFile(path + "/b1.png")) { std::cerr << "Failed to load button_door texture" << std::endl; }
	if (!buttonLight.loadFromFile(path + "/b2.png")) { std::cerr << "Failed to load button_light texture" << std::endl; }
	if (!buttonBoth.loadFromFile(path + "/b3.png")) { std::cerr << "Failed to load button_both texture" << std::endl; }
}