#include "invader.h"
#include <stdexcept>
#include <sstream>

Invader::Invader(const sf::Vector2f& position, const sf::Vector2f& size, const std::string& word, const std::string& fontFile)
    : word(word), motion(getRandomMotion()), init_x(position.x), hit(false) {
    if (!font.loadFromFile(fontFile)) {
        throw std::runtime_error("Error loading font from file: " + fontFile);
    }

    // Initialize the triangle shape
    triangle.setPointCount(3); // A triangle has 3 points
    triangle.setPoint(0, sf::Vector2f(size.x / 2.f,size.y));          // Top point
    triangle.setPoint(1, sf::Vector2f(0.f, 0.f));                // Bottom-left point
    triangle.setPoint(2, sf::Vector2f(size.x, 0.f));             // Bottom-right point
    triangle.setPosition(position);
    triangle.setFillColor(sf::Color::White);

    // Initialize the text
    text.setFont(font);
    text.setString(word);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::White);

    // Center the text below the triangle
    sf::FloatRect textBounds = text.getLocalBounds();
    text.setPosition(
        position.x + (size.x / 2.f) - (textBounds.width / 2.f),
        position.y + size.y + 5.f  // Position the text 5 pixels below the triangle
    );
}

void Invader::draw(sf::RenderWindow& window) const {
    window.draw(triangle);
    window.draw(text);
}

void Invader::setWord(const std::string& word) {
    text.setString(word);

    // Update text position to keep it centered below the triangle
    sf::FloatRect textBounds = text.getLocalBounds();
    text.setPosition(
        triangle.getPosition().x + (triangle.getLocalBounds().width / 2.f) - (textBounds.width / 2.f),
        triangle.getPosition().y + triangle.getLocalBounds().height + 5.f
    );
}
std::string Invader::getWord() const{
    return word; 
}

void Invader::move(const sf::Vector2f& offset) {
    triangle.move(offset);
    text.move(offset);
}

void Invader::setPosition(const sf::Vector2f& position) {
    triangle.setPosition(position);

    // Update text position to remain below the triangle
    sf::FloatRect textBounds = text.getLocalBounds();
    text.setPosition(
        position.x + (triangle.getLocalBounds().width / 2.f) - (textBounds.width / 2.f),
        position.y + triangle.getLocalBounds().height + 5.f
    );
}

Invader::MotionType Invader::getRandomMotion() {
    static std::random_device rd;  // Seed
    static std::mt19937 gen(rd()); // Random number generator
    static std::uniform_int_distribution<> dis(0, 2); // Range: 0 to 2

    int motionIndex = dis(gen); // Generate random number
    MotionType motion = static_cast<MotionType>(motionIndex);
    return motion; 
}


void Invader::updatePosition(float deltaTime){
    float y_increment = 50.f * deltaTime; // Common downward speed
    float x_position = triangle.getPosition().x;
    float y_position = triangle.getPosition().y;

    switch (motion) {
    case MotionType::Downward:
        // Simple downward motion
        triangle.setPosition(x_position, y_position + y_increment);
        break;

    case MotionType::DownwardSine:
        // Downward sine wave oscillation
        x_position = init_x + std::sin(y_position / 50.f) * 30.f; // Sine wave oscillation
        triangle.setPosition(x_position, y_position + y_increment);
        break;

    case MotionType::Diagonal:
        // Diagonal motion trending downward
        triangle.setPosition(x_position + 20.f * deltaTime, y_position + y_increment);
        break;
    }

    // Update text position
    text.setPosition(
        triangle.getPosition().x + (triangle.getLocalBounds().width / 2.f) - (text.getLocalBounds().width / 2.f),
        triangle.getPosition().y + triangle.getLocalBounds().height + 5.f
    );
}
std::string Invader::getMotionTypeAsString() const {
    switch (motion) {
        case MotionType::Downward:
            return "Downward";
        case MotionType::DownwardSine:
            return "DownwardSine";
        case MotionType::Diagonal:
            return "Diagonal";
        default:
            return "Unknown";
    }
}
std::string Invader::getInfo() const {
    std::ostringstream info;

    // Retrieve position
    sf::Vector2f position = triangle.getPosition();

    // Retrieve size (calculated from triangle bounds)
    sf::FloatRect bounds = triangle.getGlobalBounds();

    // Append information
    info << "Invader Info:\n";
    info << "  Word: " << word << "\n";
    info << "  Position: (" << position.x << ", " << position.y << ")\n";
    info << "  Size: (" << bounds.width << ", " << bounds.height << ")\n";
    info << "  Motion Type: " << getMotionTypeAsString() << "\n";

    return info.str();
}
bool Invader::getHit() const {
    return hit;
}

void Invader::setHit(bool hitInput) {
    hit = hitInput;
}

sf::Vector2f Invader::getPosition() const{
    return triangle.getPosition(); 
}