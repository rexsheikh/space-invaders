#include "Game.h"
#include <iostream>
#include <stdexcept>
#include <vector>

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
}

// Initialize game with 5 invaders. 
void Game::initialize() {
    invaders.reserve(5); 
    for (int i = 0; i < 5; ++i) {
        invaders.emplace_back(
            sf::Vector2f(100.f + i * 100.f, 50.f), // Position
            sf::Vector2f(80.f, 50.f),             // Size
            "Word" + std::to_string(i),           // Word
            "Roboto-Regular.ttf"                  // Font file
        );
        std::cout << "Invader " << i << " created: " << invaders.back().getInfo() << std::endl;
    }
}

// Main game loop
void Game::run() {
    initialize(); // Ensure invaders are initialized
    while (window.isOpen()) {
        float deltaTime = clock.restart().asSeconds();
        handleEvents();
        update(deltaTime);
        render();
    }
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
            // Check for collisions or interactions (e.g., user typed a correct word)
            for (auto it = invaders.begin(); it != invaders.end();) {
                if (it->getWord() == inputString) {
                    it = invaders.erase(it); // Remove the invader
                } else {
                    ++it;
                }
            }
            inputString.clear();
        }
    }
}

// Update game elements (e.g., move invaders)
void Game::update(float deltaTime) {
    for (auto& invader : invaders) {
        invader.updatePosition(deltaTime);
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
