#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>
#include <string>
#include "trie.h"
#include "invader.h"
using namespace std;
using namespace sf; 

int main() {

    //initialize the game window and simple prompts. 
    RenderWindow window(VideoMode(800, 600), "Typing Test");
    Font font;
    Invader invader_one(Vector2f(200.f, 200.f), Vector2f(100.f, 50.f), "Hello", "Roboto-Regular.ttf");

    if (!font.loadFromFile("Roboto-Regular.ttf")) {
        cerr << "Error loading font\n";
        return -1;
    }
    // sf::Text prompt("Type a word:", font, 24);
    // prompt.setPosition(50, 50);
    // prompt.setFillColor(sf::Color::Black);

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
            trie.insert(word); // Insert word into the Trie
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

        // Render
        window.clear(Color::White);
        invader_one.draw(window); 
        window.draw(user_input);
        window.draw(feedback);
        window.display();
    }

    return 0;
}
