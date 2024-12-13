#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include "invader.h"
#include "trie.h"

class Game {
private:
    sf::RenderWindow window;       // Main game window
    sf::Texture backgroundTexture; // Texture for the background
    sf::Sprite backgroundSprite;   // Sprite to render the background
    std::vector<Invader> invaders; // Vector of invaders
    sf::Font font;                 // Font for rendering text
    sf::Text userInput;            // User input text
    sf::Clock clock;               // Clock for delta time calculations
    sf::Clock spawnClock;                // Clock for spawning new invaders
    std::vector<std::string> words; 
    Trie wordTrie; 
    int wordIdx; 
    std::string inputString;  
    int numHit;     // Current user input
    bool gameOver; 
    bool playAgain;
    std::string endString; 
    sf::Clock gameTimer; 
    float finalElapsedTime; 
public:
    // Constructor
    Game(const std::string& backgroundFile, const std::string& fontFile);

    // Initializes the game (e.g., load resources, setup initial state)
    void initialize();

    // Runs the main game loop
    void run();

    // Spawn a new invader 
    void spawnInvader(); 
    
    // Check end game conditions (cleared all words or invader reached bottom)


private:
    // Handles all game events (e.g., user input)
    void handleEvents();

    // Updates the game state (e.g., invaders, animations)
    void update(float deltaTime);

    // Renders all game elements
    void render();
    
    // Load words from a given text file
    void loadWords(const std::string& filename); 

    void renderPlayAgainPrompt(); 
    void handlePlayAgainInput(); 
 

    

 



};

#endif // GAME_H
