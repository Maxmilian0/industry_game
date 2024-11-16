#ifndef MESSAGE_BOX_H
#define MESSAGE_BOX_H

#include <SFML/Graphics.hpp>
#include <string>

class MessageBox {
public:
    MessageBox(const sf::Font& font, const std::string& message, const std::string& title = "Message");
    bool show(sf::RenderWindow& window) const; // Display the message box and return user choice

private:
    sf::RectangleShape background;
    sf::Text titleText;
    sf::Text messageText;
    sf::RectangleShape yesButton;
    sf::RectangleShape noButton;
    sf::Text yesButtonText;
    sf::Text noButtonText;
};

#endif // MESSAGE_BOX_H
