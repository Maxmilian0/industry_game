#include "game.hpp"

// Globální inicializace generátoru náhodných čísel
std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<> dis(0, 4);

// Konstruktor třídy Game
Game::Game()
{
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    camera = sf::View(sf::FloatRect(0, 0, desktop.width, desktop.height));
    // Pokus o načtení textury
    if (!tileSet.loadFromFile("img/texture4.png")) {
        logFile.open("REPORT.txt", std::ios::app);
        if (logFile.is_open()) {
            logFile << "\t[X] Error while loading img/texture.png" << std::endl;
            logFile.close();
        }
        else {
            std::cerr << "Failed to open log file." << std::endl;
        }
        return;  // Ukončí konstruktor, pokud se textura nepodaří načíst
    }

    // Vytvoření a inicializace dlaždic
    int halfer = 0;
    int y = 0;
    int iHelper = 0;
    unsigned int worldSize = 50;
    for (size_t i = 0; i < worldSize * worldSize * 2; i++) {
        sf::ConvexShape mapTile;
        mapTile.setPointCount(6); // Hexagonální tvar
        if (i % worldSize == 0 && i != 0) {
            y += 50;
            iHelper = 0;
            if (halfer == 100) {
                halfer = 0;
            }
            else {
                halfer = 100;
            }
        }
        mapTile.setPosition(sf::Vector2f(iHelper * 200 - halfer, y - 200));

        // Nastavení bodů hexagonu
        mapTile.setPoint(0, sf::Vector2f(0, 50));
        mapTile.setPoint(1, sf::Vector2f(100, 0));
        mapTile.setPoint(2, sf::Vector2f(200, 50));
        mapTile.setPoint(3, sf::Vector2f(200, 150));
        mapTile.setPoint(4, sf::Vector2f(100, 200));
        mapTile.setPoint(5, sf::Vector2f(0, 150));

        // Připojení textury k dlaždici
        mapTile.setTexture(&tileSet);
        mapTile.setTextureRect(sf::IntRect(dis(gen) * 200, 0, 200, 200));

        // Přidání dlaždice do seznamu
        mapItems.push_back(mapTile);
        iHelper++;
    }
}

void Game::draw(sf::RenderWindow& _GameWindow) {
    _GameWindow.setView(camera);  // Nastavení pohledu podle kamera

    // Získání oblasti zorného pole kamery
    sf::FloatRect viewBounds(camera.getCenter() - camera.getSize() / 2.f, camera.getSize());

    // Pro každý objekt v mapItems zkontrolujeme, jestli je uvnitř zorného pole
    for (const auto& mapItem : mapItems) {
        // Získáme pozici dlaždice (bounding box)
        sf::FloatRect itemBounds = mapItem.getGlobalBounds();

        // Pokud se dlaždice nachází uvnitř kamery, vykreslíme ji
        if (viewBounds.intersects(itemBounds)) {
            _GameWindow.draw(mapItem);
        }
    }
}

void Game::update(sf::RenderWindow& _GameWindow) {
    float cameraSpeed = 5.f + cameraMoreSpeed * cameraMoreSpeed / 3;  // Rychlost pohybu kamery
    sf::Vector2i mousePos = sf::Mouse::getPosition(_GameWindow);
    movedCameraQuestion = sf::Vector2f(camera.getCenter().x, camera.getCenter().y);

    float deltaTime = deltaClock.restart().asSeconds();
    // Posun kamery na základě kláves s plynulým pohybem
    if (mousePos.y == 0 && camera.getCenter().y) {
        camera.move(0, -cameraSpeed * deltaTime);  // Nahoru
    }
    if (mousePos.y >= _GameWindow.getSize().y - 11) {
        camera.move(0, cameraSpeed * deltaTime);  // Dolů
    }
    if (mousePos.x == 0) {
        camera.move(-cameraSpeed * deltaTime, 0);  // Doleva
    }
    if (mousePos.x >= _GameWindow.getSize().x - 1) {
        camera.move(cameraSpeed * deltaTime, 0);  // Doprava
    }
    if (movedCameraQuestion == sf::Vector2f(camera.getCenter().x, camera.getCenter().y)) {
        cameraMoreSpeed = 0;
    }else {
        if (cameraMoreSpeed >= 100) {
            cameraMoreSpeed = 100;
        }
        else {
            cameraMoreSpeed++;
        }
    }
}   

// Zpracování událostí
int Game::handleEvent(const sf::Event& _Event, sf::RenderWindow& _GameWindow) {
    // Vrátí 0, pokud hra pokračuje
    // Vrátí 1, pokud se má vrátit do hlavního menu
    sf::Vector2i mousePos = sf::Mouse::getPosition(_GameWindow);

    if (_Event.type == sf::Event::KeyPressed && _Event.key.scancode == sf::Keyboard::Scan::Escape) {
        camera.setCenter(_GameWindow.getSize().x / 2, _GameWindow.getSize().y / 2);
        _GameWindow.setView(camera);
        return 1;
    }
        

    // ## clicking on tiles ##
    sf::FloatRect viewBounds(camera.getCenter() - camera.getSize() / 2.f, camera.getSize());

    for (const auto& mapItem : mapItems) {
        sf::FloatRect itemBounds = mapItem.getGlobalBounds();

        if (viewBounds.intersects(itemBounds)) { // Tiles in camera
        }
    }

    return 0;
}
