#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
//#include "message_box.h"

class Menu {
public:
    Menu(const sf::Font& _Font, const std::vector<std::string>& _Items, std::string _MenuTitle, sf::RenderWindow& _GameWindow);

    void setPosition(float _X, float _Y);
    void draw(sf::RenderWindow& _GameWindow);
    int handleEvent(const sf::Event& _Event, sf::RenderWindow& _GameWindow);

private:
    std::vector<sf::Text> menuItems;
    std::vector<bool> howers;
    sf::Text menuTitleTextGlobal;
    sf::SoundBuffer buffer;
    std::vector<sf::Sound> soundPool;
    size_t currentSoundIndex = 0;
    std::fstream logFile;
    //MessageBox test;
};

#endif // MAIN_MENU_H
