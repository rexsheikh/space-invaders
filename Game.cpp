#include "Game.h"
#include <iostream>
#include <stdexcept>
#include <fstream>

// Constructor
Game::Game(const std::string& backgroundFile, const std::string& fontFile)
    : window(sf::VideoMode(800, 800), "Space Invaders") {
    // Load background texture (REFERENCE #6) 
    if (!backgroundTexture.loadFromFile("assets/background.png")) {
        throw std::runtime_error("Failed to load background image: " + backgroundFile);
    }
   backgroundSprite.setTexture(backgroundTexture);

    // Get the size of the texture and the window
    sf::Vector2u textureSize = backgroundTexture.getSize(); // Size of the image
    sf::Vector2u windowSize = window.getSize();             // Size of the window

    // Calculate scale factors
    // Note: Casting to float then dividing cleared a warning of implicit casting. 
    float scaleX = static_cast<float>(windowSize.x) / textureSize.x;
    float scaleY = static_cast<float>(windowSize.y) / textureSize.y;
    backgroundSprite.setScale(scaleX, scaleY);

    // Load font - Using Roboto Regular from google fonts (REFERENCE #5) 
    if (!font.loadFromFile(fontFile)) {
        throw std::runtime_error("Failed to load font file: " + fontFile);
    }

    // Place the user input toward the botton of the screen with white font. 
    //initialize key globals (see Game.h for explanation of each)

    userInput.setFont(font);
    userInput.setCharacterSize(24);
    userInput.setFillColor(sf::Color::White);
    userInput.setPosition(400.f, 750.f);
    wordIdx = 0;
    numHit = 0; 
    gameOver = false; 
    playAgain = false; 
    finalElapsedTime = 0; 
}

// Spawns a new invader. First checks if all of the words have been used already. If not, a random x coordinate is chosen, a word is assigned to an invader 
// and the wordIdx is incremented. 
void Game::spawnInvader(){
    if (wordIdx >= static_cast<int>(words.size())) {
        std::cout << "All words have been used. No more invaders to spawn." << std::endl;
        return;
    }

    const std::string& word = words[wordIdx]; 
    // The width of the invade is subtracted to ensure it appears on screen. 
    float randomX = static_cast<float>(std::rand() % (window.getSize().x - 80)); 
    invaders.emplace_back(
        sf::Vector2f(randomX, 0.f),      
        sf::Vector2f(80.f, 50.f),       
        word,                           
        "Roboto-Regular.ttf"            
    );
    wordIdx++; 
}
// Reads words from the text file to populate the words vector. Words are separated by new lines 
// (REFERENCE #9)
void Game::loadWords(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Error: Could not open file " + filename);
    }

    std::string word;
    while (file >> word) { 
        words.push_back(word);
    }

    file.close();

    if (words.empty()) {
        std::cerr << "Warning: No words found in file " << filename << std::endl;
    } else {
        std::cout << "Loaded " << words.size() << " words from file." << std::endl;
    }
}

// Load words from the text file and initialize game with 5 invaders. 
// use the insert method to populate the Trie. 
void Game::initialize() {

    // Reset key globals if the user has played and they are now playing again. 
    wordIdx = 0; 
    numHit = 0; 
    gameOver = false; 
    invaders.clear();
    userInput.setString(""); 
    gameTimer.restart(); 
    spawnClock.restart(); 
 

    // Load words from the text file.
    loadWords("words.txt");
    for(const auto& word:words){
        wordTrie.insert(word); 
    } 
    // The combination of reserve and emplace back prevented segmentation faults by protecting memory space
    // for the invader instances. (REFERENCE #4). 
    invaders.reserve(words.size()); 
    wordIdx = 0; 
    for (; wordIdx < 5; ++wordIdx) {
        invaders.emplace_back(
            sf::Vector2f(100.f + (wordIdx * 100.f), 50.f), // Position
            sf::Vector2f(80.f, 50.f),                      // Size
            words[wordIdx],                                // Word
            "Roboto-Regular.ttf"                           // Font file
        );
    }
}

// Main game loop. Do/while is used so the user plays at least once and is then 
// given the opportunity to play again when the game is over.  
void Game::run() {
    do {
        initialize();
        while (window.isOpen() && !gameOver) {
            float deltaTime = clock.restart().asSeconds();
            handleEvents();
            update(deltaTime);
            render();
        }

        if (gameOver) {
            renderPlayAgainPrompt();
            handlePlayAgainInput();
        }
    } while (playAgain && window.isOpen());
 
}

// Handle user text input and window closures (REFERENCE #2/#10)
void Game::handleEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
        
        // Build the input string with letters (no numbers) and handle backspace
        if (event.type == sf::Event::TextEntered) {
            char typed = static_cast<char>(event.text.unicode);

            // Backspace
            if (typed == '\b' && !inputString.empty()) {
                inputString.pop_back();
            }
            // Append characters
            else if (std::isalpha(typed)) {
                inputString += typed;
            }
        }
        // Handle enter, user has completed a word and it now must be checked in the Trie
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
            // Check if the input matches any word in the Trie with the search method. 
            // Clear the  user input no matter the outcome (must restart on bad input)
            if (wordTrie.search(inputString)) {
                std::cout << "Correct word: " << inputString << std::endl;
                // Mark corresponding invader as hit
                for (auto& invader : invaders) {
                    if (invader.getWord() == inputString) {
                        invader.setHit(true);
                        numHit++; 
                        break;
                    }
                }
            } else {
                std::cout << "Incorrect word: " << inputString << std::endl;
            }
            inputString.clear();
        }
    }
}


// Update game elements position, hits, and spawn on a timer. 
// Capture game ending events (A) Clearing all words - win (B) Invader reaches planet - loss 
// Update the user input string. 
void Game::update(float deltaTime) {
    for (auto& invader : invaders) {
        if(!invader.getHit()){
            invader.updatePosition(deltaTime); 
        }
        if(invader.getPosition().y >= window.getSize().y){
            endString = "Game Over! An invader reached your planet!";
            gameOver = true; 
            finalElapsedTime = gameTimer.getElapsedTime().asSeconds(); 
            return; 
        }
    }

    if(spawnClock.getElapsedTime().asSeconds() >= 3.0f){
        spawnInvader(); 
        spawnClock.restart(); 
    }

    if(numHit == static_cast<int>(words.size())){
        endString = "Congratulations! You cleared all words!"; 
        finalElapsedTime = gameTimer.getElapsedTime().asSeconds(); 
        gameOver = true; 
    }

    // Update user input display
    userInput.setString("Input: " + inputString);
}


// Render all elements to the screen
void Game::render() {
    window.clear();
    window.draw(backgroundSprite);

    for (size_t i = 0; i < invaders.size(); ++i) {
        invaders[i].draw(window);
    }
    window.draw(userInput);
    window.display();
}

// Render a simple prompt with the endText generated from win or loss. 
// Calculates and displays words per minute 
void Game::renderPlayAgainPrompt() {
    sf::RectangleShape overlay(sf::Vector2f(window.getSize().x, window.getSize().y));
    overlay.setFillColor(sf::Color(0, 0, 0, 100)); // Black with transparency

    // End string
    sf::Text endText(endString, font, 36);
    endText.setFillColor(sf::Color::White);
    sf::FloatRect endTextBounds = endText.getLocalBounds();
    endText.setPosition(
        window.getSize().x / 2.f - endTextBounds.width / 2.f,
        window.getSize().y / 3.f
    );

    // Calculate WPM and display. 
    int wpm = static_cast<int>((numHit * 60) /finalElapsedTime);
    sf::Text wpmText("WPM: " + std::to_string(wpm), font, 28);
    wpmText.setFillColor(sf::Color::Yellow);
    sf::FloatRect wpmTextBounds = wpmText.getLocalBounds();
    wpmText.setPosition(
        window.getSize().x / 2.f - wpmTextBounds.width / 2.f,
        window.getSize().y / 2.f - 50.f
    );

    // Play again prompt with Y/N
    sf::Text promptText("Play Again?", font, 28);
    promptText.setFillColor(sf::Color::White);
    sf::FloatRect promptTextBounds = promptText.getLocalBounds();
    promptText.setPosition(
        window.getSize().x / 2.f - promptTextBounds.width / 2.f,
        window.getSize().y / 2.f + 20.f
    );

    sf::Text yesText("Yes (Y)", font, 24);
    yesText.setFillColor(sf::Color::Green);
    sf::FloatRect yesTextBounds = yesText.getLocalBounds();
    yesText.setPosition(
        window.getSize().x / 2.f - yesTextBounds.width / 2.f - 50.f,
        window.getSize().y / 2.f + 70.f
    );

    sf::Text noText("No (N)", font, 24);
    noText.setFillColor(sf::Color::Red);
    sf::FloatRect noTextBounds = noText.getLocalBounds();
    noText.setPosition(
        window.getSize().x / 2.f - noTextBounds.width / 2.f + 50.f,
        window.getSize().y / 2.f + 70.f
    );

    // Render overlays, endText, and prompt. 
    window.clear();
    window.draw(overlay);
    window.draw(endText);
    window.draw(wpmText);
    window.draw(promptText);
    window.draw(yesText);
    window.draw(noText);
    window.display();
}

// Loop that checks for user input (Y or N) to restart the game or close the window. 
void Game::handlePlayAgainInput() {
    sf::Event event;
    while (true) {
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                playAgain = false; 
                window.close();
                return;
            }

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Y) {
                    playAgain = true;  
                    return;
                }
                if (event.key.code == sf::Keyboard::N) {
                    playAgain = false; 
                    return;
                }
            }
        }

        // Render the prompt while waiting for user input
        renderPlayAgainPrompt();
    }
}
