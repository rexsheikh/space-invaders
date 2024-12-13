#ifndef WORD_SPRITE_H
#define WORD_SPRITE_H

#include <SFML/Graphics.hpp>
#include <string>
#include <random>

class Invader {
public:
// Enum for motion behavior (REFERENCE #13)
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
    MotionType motion; // Set using the enum class above in the constructor using a switch statement.
    float init_x; 
    bool hit; 
public:
    // Constructor
    Invader(const sf::Vector2f& position, const sf::Vector2f& size, const std::string& word, const std::string& fontFile);

    // Draw the invader and text
    void draw(sf::RenderWindow& window) const;

    // Set/get the word
    void setWord(const std::string& word);
    std::string getWord() const; 

    // Move the invader and text
    void move(const sf::Vector2f& offset);

    // Set the position of the sprite and text
    void setPosition(const sf::Vector2f& position);

    // Get the position of the invader 
    sf::Vector2f getPosition() const; 
    
    // Randomly select motion type from enum class above 
    static MotionType getRandomMotion(); 

    // Update position based on motion
    void updatePosition(float deltaTime); 
    std::string getMotionTypeAsString() const;
    std::string getInfo() const; 
    bool getHit() const; 
    void setHit(bool hit); 


};

#endif // WORD_SPRITE_H
