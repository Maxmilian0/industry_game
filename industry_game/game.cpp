#include "game.h"

// Globální inicializace generátoru náhodných čísel
std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<> dis(0, 4);

// Konstruktor třídy Game
Game::Game() : camera(sf::FloatRect(0, 0, 800, 600))
{
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    camera   = sf::View(sf::FloatRect(0, 0, desktop.width, desktop.height));
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

void Game::update() {
    float cameraSpeed = 150.f;  // Rychlost pohybu kamery
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {
        cameraSpeed = 15.f;  // Rychlost při držení shiftu
    }

    // Získání delta time, které udává čas, který uplynul od posledního snímku
    float deltaTime = deltaClock.restart().asSeconds();  // Vrátí čas mezi snímky v sekundách

    // Posun kamery na základě kláves s plynulým pohybem
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        camera.move(0, -cameraSpeed * deltaTime);  // Nahoru
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        camera.move(0, cameraSpeed * deltaTime);  // Dolů
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        camera.move(-cameraSpeed * deltaTime, 0);  // Doleva
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        camera.move(cameraSpeed * deltaTime, 0);  // Doprava
    }
}

// Zpracování událostí
int Game::handleEvent(const sf::Event& _Event, sf::RenderWindow& _GameWindow) {
    // Vrátí 0, pokud hra pokračuje
    // Vrátí 1, pokud se má vrátit do hlavního menu
    sf::Vector2i mousePos = sf::Mouse::getPosition(_GameWindow);

    if (_Event.type == sf::Event::KeyPressed && _Event.key.scancode == sf::Keyboard::Scan::Escape) {
        return 1;
    }

    for (size_t i = 0; i < mapItems.size(); ++i) {
        // Zde můžete implementovat zpracování kliknutí na dlaždice
        // if (/* nějaká podmínka */) {
        //     // Reakce na událost
        // }
    }

    return 0;
}
