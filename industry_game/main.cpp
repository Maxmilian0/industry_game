#include <iostream>
#include <string>
#include <array>
#include <sstream>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>

#include "main_menu.h"
#include "media_loader.h"

int main() {
	// Settuping window, images, cursor, fonts
	sf::RenderWindow gameWindow(sf::VideoMode::getDesktopMode(), "The Game Of Industry", sf::Style::Fullscreen);
	sf::Image cursorImage;
	sf::Cursor gunCursor;
	sf::Font geistMonoExtraBold;
	sf::Font geistMonoMedium;
	std::vector<std::string> menuItems = { "Play", "Settings", "Exit" };
	sf::Text fpsText;
	

	fpsText.setFont(geistMonoMedium);
	fpsText.setFillColor(sf::Color::Black);
	fpsText.setPosition(gameWindow.getSize().x - 200.f, gameWindow.getSize().y - (gameWindow.getSize().y - 50));
	
	sf::Clock clock;
	float fps = 0.f;

	Menu menu(geistMonoMedium, menuItems, "The Game Of Industry", gameWindow);

	// Loading media
	MediaLoader::loadMedia(geistMonoExtraBold, "fonts/GeistMono-ExtraBold.ttf");
	MediaLoader::loadMedia(geistMonoMedium, "fonts/GeistMono-Medium.ttf");
	MediaLoader::loadMedia(cursorImage, "cursor.png");

	gunCursor.loadFromPixels(cursorImage.getPixelsPtr(), cursorImage.getSize(), sf::Vector2u(0, 0));
	gameWindow.setMouseCursor(gunCursor);
	
	// FPS things
	int fpsSlower = 110; // For better debugging output
	gameWindow.setFramerateLimit(60);

	// State switching mechanism (when i play game, i don't see menu)
	enum GameState {MENU, GAME};
	GameState currentState = MENU;

	// Game loop
	while (gameWindow.isOpen()) {
		sf::Event event;
		while (gameWindow.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) {
				gameWindow.close();
			}

			if (currentState == MENU) {
				switch (menu.handleEvent(event, gameWindow)) {
				case 1:
					std::cout << "Start game!" << std::endl;
					currentState = GAME;
					break;
				case 2:
					std::cout << "Open settings" << std::endl;
					break;
				case -1:
					std::cout << "Error_01a4(menu selector)" << std::endl;
					return -1;
				}
			}
			else if (currentState == GAME) {
				std::cout << "Playing game!" << std::endl;
			}
		}

		float deltaTime = clock.restart().asSeconds();
		fps = 1.f / deltaTime;

		fpsSlower++;
		if (fpsSlower > 10) {
			std::ostringstream oss;
			oss << "FPS: " << static_cast<int>(fps);
			fpsText.setString(oss.str());
			fpsSlower = 0;
		}
		gameWindow.clear(sf::Color(246, 246, 246));

		if (currentState == MENU) {
			menu.draw(gameWindow);
		}
		else if (currentState == GAME) {

		}

		gameWindow.draw(fpsText); // FPS count for debug
		

		gameWindow.display();
	}


	return 0;
}