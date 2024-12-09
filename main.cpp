#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>
#include <string>
#include "trie.h"
using namespace std;

int main() {

    //initialize the game window and simple prompts. 
    sf::RenderWindow window(sf::VideoMode(800, 600), "Typing Test");
    sf::Font font;

    if (!font.loadFromFile("Roboto-Regular.ttf")) {
        cerr << "Error loading font\n";
        return -1;
    }
    sf::Text prompt("Type a word:", font, 24);
    prompt.setPosition(50, 50);
    prompt.setFillColor(sf::Color::Black);

    sf::Text user_input("", font, 24);
    user_input.setPosition(50, 100);
    user_input.setFillColor(sf::Color::Blue);

    sf::Text feedback("", font, 24);
    feedback.setPosition(50, 150);
    feedback.setFillColor(sf::Color::Red);

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
            trie.insert(word); // Insert word into the Trie
        }
    }
    words_file.close();

    //capture user input and check using the trie
    string input;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            // Handle Key Presses (Enter key logic)
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Enter) { // Check for Enter key
                    if (trie.search(input)) {
                        feedback.setString("Correct!");
                        feedback.setFillColor(sf::Color::Green);
                    } else {
                        feedback.setString("Incorrect!");
                        feedback.setFillColor(sf::Color::Red);
                    }
                    input.clear(); // Reset input
                }
            }

            // Handle Text Input (Typing)
            if (event.type == sf::Event::TextEntered) {
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

        // Render
        window.clear(sf::Color::White);
        window.draw(prompt);
        window.draw(user_input);
        window.draw(feedback);
        window.display();
    }

    return 0;
}
