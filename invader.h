#ifndef WORD_SPRITE_H
#define WORD_SPRITE_H

#include <SFML/Graphics.hpp>
#include <string>

class Invader {
private:
    sf::RectangleShape shape;   
    sf::Text text;             
    sf::Font font;             

public:
    // Constructor
    Invader(const sf::Vector2f& position, const sf::Vector2f& size, const std::string& word, const std::string& fontFile);

    // Draw the sprite and text
    void draw(sf::RenderWindow& window) const;

    // Set the word
    void setWord(const std::string& word);

    // Move the sprite and text
    void move(const sf::Vector2f& offset);

    // Set the position of the sprite and text
    void setPosition(const sf::Vector2f& position);
};

#endif // WORD_SPRITE_H
