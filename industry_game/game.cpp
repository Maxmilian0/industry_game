#include "game.h"

std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<> dis(0, 255);


Game::Game()
{
	// define the position of the triangle's points
	float height = 100.f;
	float width = height * 2;

	int line = 0;
	float halfer = width / 2;
	int lineCutter = 11;

	for (size_t i = 0; i < 252; i++) {
		float x = width * line - halfer;
		float y = (i / lineCutter) * height - height;
		line++;
		if (line >= lineCutter) {
			line = 0;
			if (halfer == 0) {
				halfer = width / 2;
			}
			else {
				halfer = 0;
			}
		}
		y /= 2;
		sf::VertexArray rhombus(sf::Quads, 4);
		rhombus[0].position = sf::Vector2f(x, height / 2 + y);
		rhombus[1].position = sf::Vector2f(width / 2 + x, y);
		rhombus[2].position = sf::Vector2f(width + x, height / 2 + y);
		rhombus[3].position = sf::Vector2f(width / 2 + x, height + y);

		// define the color of the triangle's points
		rhombus[0].color = sf::Color(dis(gen), dis(gen), dis(gen));
		rhombus[1].color = sf::Color(dis(gen), dis(gen), dis(gen));
		rhombus[2].color = sf::Color(dis(gen), dis(gen), dis(gen));
		rhombus[3].color = sf::Color(dis(gen), dis(gen), dis(gen));

		mapItems.push_back(rhombus);
	}
}

void Game::draw(sf::RenderWindow& _GameWindow) {
	for (const auto& mapItem : mapItems) {
		_GameWindow.draw(mapItem);
	}
}

void Game::update() {
}

void Game::handleEvent(const sf::Event& _Event, sf::RenderWindow& _GameWindow) {
	sf::Vector2i mousePos = sf::Mouse::getPosition(_GameWindow);

	if (_Event.type == sf::Event::KeyPressed && _Event.key.scancode == sf::Keyboard::Scan::Escape) {
		logFile.open("REPORT.txt", std::ios::app);
		logFile << "[!] Closing program (Esc key in game)" << std::endl;
		logFile.close();
		_GameWindow.close();
	}
	for (size_t i = 0; i < mapItems.size(); ++i) {
		//if ())) {

		//}
	}
}