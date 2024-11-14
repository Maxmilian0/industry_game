// #################
// ### INCLUDING ###
// #################
#include <iostream>
#include <string>
#include <array>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>

#include "main_menu.h"

// ##############################
// ### FUNCTIONS DECLARATIONS ###
// ##############################

template <typename T>
bool loadResource(T& resource, const std::string& filename);

int main() {
	// #############################################
	// ### SETUPING WINDOW, CURSOR, IMAGES, MENU ###
	// #############################################
	sf::RenderWindow gameWindow(sf::VideoMode::getDesktopMode(), "The Game Of Industry", sf::Style::Fullscreen);
	sf::Image cursorImage;
	sf::Cursor gunCursor;
	sf::Font geistMonoExtraBold;
	sf::Font geistMonoMedium;
	std::vector<std::string> menuItems = {"Play", "Settings", "Exit"};
	Menu menu(geistMonoMedium, menuItems, "The Game Of Industry", gameWindow);

	// #########################
	// ### LOADING RESOURCES ###
	// #########################
	loadResource(geistMonoExtraBold,"fonts/GeistMono-ExtraBold.ttf");
	loadResource(geistMonoMedium, "fonts/GeistMono-Medium.ttf");
	loadResource(cursorImage, "cursor.png");

	// #################
	// ### GAME LOOP ###
	// #################

	gunCursor.loadFromPixels(cursorImage.getPixelsPtr(), cursorImage.getSize(), sf::Vector2u(0, 0));
	gameWindow.setMouseCursor(gunCursor);

	while (gameWindow.isOpen()) {
		sf::Event event;
		while (gameWindow.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) {
				gameWindow.close();
			}
			menu.handleEvent(event, gameWindow);
		}

		gameWindow.clear(sf::Color(246, 246, 246));

		menu.draw(gameWindow);

		gameWindow.display();
	}


	return 0;
}

// Loader of media (need file path)
template <typename T>
bool loadResource(T& resource, const std::string& filename) {
	if (!resource.loadFromFile(filename)) {
		std::cerr << "Error loadning " << filename << "!" << std::endl;
		return false;
	}
	return true;
}