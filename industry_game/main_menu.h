#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <string>
#include <iostream>

class Menu {
public:
    Menu(const sf::Font& font, const std::vector<std::string>& items, std::string menuTitle, sf::RenderWindow& gameWindow);

    void setPosition(float x, float y);
    void draw(sf::RenderWindow& gameWindow);
    void handleEvent(const sf::Event& event, sf::RenderWindow& gameWindow);

private:
    std::vector<sf::Text> menuItems;
    std::vector<bool> howers; // Dynamický vektor pro správu hoverů
    sf::Text menuTitleTextGlobal;

    sf::SoundBuffer buffer; // Buffer pro zvuk
    std::vector<sf::Sound> soundPool; // Pole zvuků pro cyklické přehrávání
    size_t currentSoundIndex = 0; // Index aktuálního zvuku v poolu
};

#endif // MAIN_MENU_H
