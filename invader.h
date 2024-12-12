#ifndef WORD_SPRITE_H
#define WORD_SPRITE_H

#include <SFML/Graphics.hpp>
#include <string>
#include <random>

class Invader {
public:
// Enum for motion behavior
enum class MotionType {
    Downward,
    DownwardSine,
    Diagonal
};
private:
    sf::ConvexShape triangle;   
    sf::Text text;             
    sf::Font font;      
    std::string word;
    MotionType motion; 
    float init_x; 
public:
    // Constructor
    Invader(const sf::Vector2f& position, const sf::Vector2f& size, const std::string& word, const std::string& fontFile);

    // Draw the sprite and text
    void draw(sf::RenderWindow& window) const;

    // Set the word
    void setWord(const std::string& word);

    std::string getWord() const; 

    // Move the sprite and text
    void move(const sf::Vector2f& offset);

    // Set the position of the sprite and text
    void setPosition(const sf::Vector2f& position);
    
    // Randomly select motion type from enum class above 
    static MotionType getRandomMotion(); 

    // Update position based on motion
    void updatePosition(float deltaTime); 
    std::string getMotionTypeAsString() const;
    std::string getInfo() const; 


};

#endif // WORD_SPRITE_H
