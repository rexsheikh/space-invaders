#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <iostream>

struct TrieNode {
    bool is_end_of_word;
    TrieNode* children[26];

    TrieNode() {
        is_end_of_word = false;
        for (int i = 0; i < 26; ++i) {
            children[i] = nullptr;
        }
    }
};

class Trie {
public:
    Trie() : root(new TrieNode()) {}

    void insert(const std::string& word) {
        TrieNode* node = root;
        for (char c : word) {
            int index = c - 'a';
            if (!node->children[index]) {
                node->children[index] = new TrieNode();
            }
            node = node->children[index];
        }
        node->is_end_of_word = true;
    }

    bool search(const std::string& word) {
        TrieNode* node = root;
        for (char c : word) {
            int index = c - 'a';
            if (!node->children[index]) {
                return false;
            }
            node = node->children[index];
        }
        return node->is_end_of_word;
    }

private:
    TrieNode* root;
};

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Typing Test");
    sf::Font font;

    if (!font.loadFromFile("Roboto-Regular.ttf")) {
        std::cerr << "Error loading font\n";
        return -1;
    } else {
        std::cout << "Font loaded successfully!\n";
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

    Trie trie;
    std::vector<std::string> words = {"hello", "world", "trie", "typing", "test", "sfml"};
    for (const auto& word : words) {
        trie.insert(word);
    }

    std::string input;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::TextEntered) {
                char typed = static_cast<char>(event.text.unicode);

                if (typed == '\b' && !input.empty()) {
                    input.pop_back();
                } else if (typed == '\r') {
                    if (trie.search(input)) {
                        feedback.setString("Correct!");
                        feedback.setFillColor(sf::Color::Green);
                    } else {
                        feedback.setString("Incorrect!");
                        feedback.setFillColor(sf::Color::Red);
                    }
                    input.clear();
                } else if (std::isalpha(typed)) {
                    input += typed;
                }

                std::cout << "Current input: " << input << "\n";
            }
        }

        user_input.setString("You typed: " + input);

        window.clear(sf::Color::White);
        window.draw(prompt);
        window.draw(user_input);
        window.draw(feedback);
        window.display();
    }

    return 0;
}
