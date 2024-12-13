#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include "invader.h"
#include "trie.h"

class Game {
private:
    sf::RenderWindow window;             // Main game window
    sf::Texture backgroundTexture;       // Texture for the background
    sf::Sprite backgroundSprite;         // Sprite to render the background
    std::vector<Invader> invaders;       // Vector of invaders
    sf::Font font;                       // Font for rendering text
    sf::Text userInput;                  // User input text
    sf::Clock clock;                     // Clock for delta time calculations
    sf::Clock spawnClock;                // Clock for spawning new invaders
    std::vector<std::string> words;      // Words loaded from the text file "words.txt"
    Trie wordTrie;                       // Trie data structure for checking user input
    int wordIdx;                         // Index to the words vector
    std::string inputString;             // User input string 
    int numHit;                          // Number of correctly entered words 
    bool gameOver;                       // Used as an element to terminate the main loop 
    bool playAgain;                      // Used to signal window closure or game restart. 
    std::string endString;               // Captures message to display in endgame screen (win or loss)
    sf::Clock gameTimer;                 // Used to calculate WPM 
    float finalElapsedTime;              // captures final gameTimer in seconds to calculate WPM
public:
    // Constructor with background file and font file. other relevant members are initialized in the body of the constructor. 
    Game(const std::string& backgroundFile, const std::string& fontFile);
    // Loads resources and instantiates first five invaders. 
    void initialize();
    // Main game loop  
    void run();
    // Spawn a new invader using the spawnClock (every 3 seconds)  
    void spawnInvader(); 

private:
    // Handles user text input and window closure events. 
    void handleEvents();

    // Updates the gamestate to include invader position. Captures any game ending criteria. 
    void update(float deltaTime);

    // Renders all game elements
    void render();
    // Load words from a given text file
    void loadWords(const std::string& filename); 

    // Render and handle play again option. 
    void renderPlayAgainPrompt(); 
    void handlePlayAgainInput(); 
 

    

 



};

#endif // GAME_H
