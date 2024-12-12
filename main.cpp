#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>
#include <cmath>
#include <string>
#include "trie.h"
#include "invader.h"
using namespace std;
using namespace sf; 

int main() {

    //initialize the game window and simple prompts. 
    RenderWindow window(VideoMode(800, 600), "Typing Test");
    Font font;
    //initialize five invaders
    std::vector<Invader> invaders;
    for (int i = 0; i < 5; ++i) {
        invaders.emplace_back(
            sf::Vector2f(100.f + i * 100.f, 50.f), // Position
            sf::Vector2f(80.f, 50.f),             // Size
            "Word" + std::to_string(i),           // Word
            "Roboto-Regular.ttf"                  // Font file
        );
    }

    // Print their motion types
    for (const auto& invader : invaders) {
        std::cout << invader.getInfo() << std::endl;
    }
    Clock clock; 
    float invader_speed = 20.f; 
    if (!font.loadFromFile("Roboto-Regular.ttf")) {
        cerr << "Error loading font\n";
        return -1;
    }

    Text user_input("", font, 24);
    user_input.setPosition(50, 100);
    user_input.setFillColor(Color::Blue);

    Text feedback("", font, 24);
    feedback.setPosition(50, 150);
    feedback.setFillColor(Color::Red);

    //initialize the trie and load words from words.txt
    Trie trie;
    ifstream words_file("words.txt"); 
    if (!words_file.is_open()) {
        cerr << "Error: Could not open words file\n";
        return -1;
    }

    string word;
    while (getline(words_file, word)) {
        if (!word.empty()) {
            trie.insert(word); 
        }
    }
    words_file.close();

    //capture user input and check using the trie
    string input;

    
    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }

            // Handle Key Presses (Enter key logic)
            if (event.type == Event::KeyPressed) {
                if (event.key.code == Keyboard::Enter) { // Check for Enter key
                    if (trie.search(input)) {
                        feedback.setString("Correct!");
                        feedback.setFillColor(Color::Green);
                    } else {
                        feedback.setString("Incorrect!");
                        feedback.setFillColor(Color::Red);
                    }
                    input.clear(); // Reset input
                }
            }

            // Handle Text Input (Typing)
            if (event.type == Event::TextEntered) {
                char typed = static_cast<char>(event.text.unicode);

                // Handle Backspace
                if (typed == '\b' && !input.empty()) {
                    input.pop_back();
                }
                // Append Characters (Only Alphabetic)
                else if (isalpha(typed)) {
                    input += typed;
                }
            }
        }

        // Update User Input Display
        user_input.setString("You typed: " + input);
        float deltaTime = clock.restart().asSeconds();
        for (auto& invader : invaders) {
            invader.updatePosition(deltaTime);
        }
        // Render
        window.clear(Color::White);
        for (const auto& invader : invaders) {
            invader.draw(window); // Render each invader
        }
        window.draw(user_input);
        window.draw(feedback);
        window.display();
    }

    return 0;
}
