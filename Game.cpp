#include "Game.h"
#include <iostream>
#include <stdexcept>
#include <fstream>

// Constructor
Game::Game(const std::string& backgroundFile, const std::string& fontFile)
    : window(sf::VideoMode(800, 800), "Typing Game") {
    // Load background texture
    if (!backgroundTexture.loadFromFile("assets/background.png")) {
        throw std::runtime_error("Failed to load background image: " + backgroundFile);
    }
   backgroundSprite.setTexture(backgroundTexture);

// Get the size of the texture and the window
    sf::Vector2u textureSize = backgroundTexture.getSize(); // Size of the image
    sf::Vector2u windowSize = window.getSize();             // Size of the window

    // Calculate scale factors
    float scaleX = static_cast<float>(windowSize.x) / textureSize.x;
    float scaleY = static_cast<float>(windowSize.y) / textureSize.y;

    // Apply the scale to the sprite
    backgroundSprite.setScale(scaleX, scaleY);

    // Load font
    if (!font.loadFromFile(fontFile)) {
        throw std::runtime_error("Failed to load font file: " + fontFile);
    }

    // Setup user input text
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

void Game::spawnInvader(){
    if (wordIdx >= static_cast<int>(words.size())) {
        std::cout << "All words have been used. No more invaders to spawn." << std::endl;
        return;
    }

    const std::string& word = words[wordIdx]; 
    float randomX = static_cast<float>(std::rand() % (window.getSize().x - 80)); // Subtract invader width
    invaders.emplace_back(
        sf::Vector2f(randomX, 0.f),      // Position at the top of the screen
        sf::Vector2f(80.f, 50.f),       // Size
        word,                           // Word
        "Roboto-Regular.ttf"            // Font file
    );
    wordIdx++; 
}

void Game::loadWords(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Error: Could not open file " + filename);
    }

    std::string word;
    while (file >> word) { // Read words separated by whitespace
        words.push_back(word);
    }

    file.close();

    if (words.empty()) {
        std::cerr << "Warning: No words found in file " << filename << std::endl;
    } else {
        std::cout << "Loaded " << words.size() << " words from file." << std::endl;
    }
}

// load words from the text file and initialize game with 5 invaders. 
// populate the Trie with the words
void Game::initialize() {
    //ensure game state is reset if playing again
    wordIdx = 0; 
    numHit = 0; 
    gameOver = false; 
    invaders.clear();
    userInput.setString(""); 
    gameTimer.restart(); 
    spawnClock.restart(); 
 

    //load words from the text file.
    loadWords("words.txt");
    for(const auto& word:words){
        wordTrie.insert(word); 
    } 
    invaders.reserve(words.size()); 
    wordIdx = 0; 
    for (; wordIdx < 5; ++wordIdx) {
        invaders.emplace_back(
            sf::Vector2f(100.f + (wordIdx * 100.f), 50.f), // Position
            sf::Vector2f(80.f, 50.f),             // Size
            words[wordIdx],           // Word
            "Roboto-Regular.ttf"                  // Font file
        );
    }
}

// Main game loop
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

// Handle user inputs and events
void Game::handleEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }

        if (event.type == sf::Event::TextEntered) {
            char typed = static_cast<char>(event.text.unicode);

            // Handle backspace
            if (typed == '\b' && !inputString.empty()) {
                inputString.pop_back();
            }
            // Append characters
            else if (std::isalpha(typed)) {
                inputString += typed;
            }
        }

        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
            // Check if the input matches any word in the Trie
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


// Update game elements (e.g., move invaders)
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

    // Draw background
    window.draw(backgroundSprite);

    for (size_t i = 0; i < invaders.size(); ++i) {
        invaders[i].draw(window);
    }
    // Draw user input
    window.draw(userInput);

    window.display();
}

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

    // Calculate WPM
    int wpm = static_cast<int>((numHit * 60) /finalElapsedTime);
    

    // WPM display
    sf::Text wpmText("WPM: " + std::to_string(wpm), font, 28);
    wpmText.setFillColor(sf::Color::Yellow);
    sf::FloatRect wpmTextBounds = wpmText.getLocalBounds();
    wpmText.setPosition(
        window.getSize().x / 2.f - wpmTextBounds.width / 2.f,
        window.getSize().y / 2.f - 50.f
    );

    // Play Again? prompt
    sf::Text promptText("Play Again?", font, 28);
    promptText.setFillColor(sf::Color::White);
    sf::FloatRect promptTextBounds = promptText.getLocalBounds();
    promptText.setPosition(
        window.getSize().x / 2.f - promptTextBounds.width / 2.f,
        window.getSize().y / 2.f + 20.f
    );

    // Yes and No options
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

    // Render everything
    window.clear();
    window.draw(overlay);
    window.draw(endText);
    window.draw(wpmText);
    window.draw(promptText);
    window.draw(yesText);
    window.draw(noText);
    window.display();
}


void Game::handlePlayAgainInput() {
    sf::Event event;
    while (true) {
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                playAgain = false; // Exit if the user closes the window
                window.close();
                return;
            }

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Y) {
                    playAgain = true;  // User wants to play again
                    return;
                }
                if (event.key.code == sf::Keyboard::N) {
                    playAgain = false; // User does not want to play again
                    return;
                }
            }
        }

        // Render the prompt while waiting for user input
        renderPlayAgainPrompt();
    }
}
