#include "main_menu.h"

Menu::Menu(const sf::Font& font, const std::vector<std::string>& items, unsigned int characterSize) {
	for (size_t i = 0; i < items.size(); i++) {
		sf::Text text;
		text.setFont(font);
		text.setString(items[i]);
		text.setCharacterSize(characterSize);
		text.setFillColor(sf::Color(100, 100, 100));
		text.setPosition(100, 200 + i * 80);
		menuItems.push_back(text);

	}
}

void Menu::setPosition(float x, float y) {
	for (size_t i = 0; i < menuItems.size(); i++) {
		menuItems[i].setPosition(x, y + i * 80);
	}
}

void Menu::draw(sf::RenderWindow& gameWindow) {
	for (const auto& item : menuItems) {
		gameWindow.draw(item);
	}
}