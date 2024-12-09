#include "invader.h"
#include <stdexcept>
using namespace std; 
using namespace sf; 
// Constructor
Invader::Invader(const Vector2f& position, const Vector2f& size, const string& word, const string& fontFile) {
    // Load the font
    if (!font.loadFromFile(fontFile)) {
        throw runtime_error("Error loading font from file: " + fontFile);
    }

    // Initialize the shape
    shape.setSize(size);
    shape.setPosition(position);
    shape.setFillColor(Color::Blue);

    // Initialize the text
    text.setFont(font);
    text.setString(word);
    text.setCharacterSize(24);
    text.setFillColor(Color::Black);

    // Center the text below the shape
    FloatRect textBounds = text.getLocalBounds();
    text.setPosition(
        position.x + (size.x / 2.f) - (textBounds.width / 2.f),
        position.y + size.y + 5.f  // 5 pixels below the shape
    );
}

// Draw the sprite and text
void Invader::draw(RenderWindow& window) const {
    window.draw(shape);
    window.draw(text);
}

// Set the word
void Invader::setWord(const string& word) {
    text.setString(word);

    // Update position to keep text centered
    FloatRect textBounds = text.getLocalBounds();
    text.setPosition(
        shape.getPosition().x + (shape.getSize().x / 2.f) - (textBounds.width / 2.f),
        shape.getPosition().y + shape.getSize().y + 5.f
    );
}

// Move the sprite and text
void Invader::move(const Vector2f& offset) {
    shape.move(offset);
    text.move(offset);
}

// Set the position of the sprite and text
void Invader::setPosition(const Vector2f& position) {
    shape.setPosition(position);

    // Update text position to remain below the shape
    FloatRect textBounds = text.getLocalBounds();
    text.setPosition(
        position.x + (shape.getSize().x / 2.f) - (textBounds.width / 2.f),
        position.y + shape.getSize().y + 5.f
    );
}
