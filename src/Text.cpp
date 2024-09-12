#include "Text.hpp"

Text::Text(sf::RenderWindow& window, const std::string& text, const sf::Font& font, sf::Color color, int x, int y, int ID,int fontSize)     // Constructor
    : window(window), text(text), color(color), ID(ID),fontSize(fontSize) {
    this->font = font;                                                                          // Copy the font
    sfmlText.setFont(this->font);                                                               // Set the font for the SFML text object
    sfmlText.setString(this->text);                                                             // Set the string (text) to display
    sfmlText.setFillColor(this->color);                                                         // Set the color of the text
    sfmlText.setCharacterSize(this->fontSize);                                                  // Set the font size
    sfmlText.setPosition(x, y);                                                                 // Set the position of the text
}

Text::~Text() {}                                                                                // Destructor

void Text::updateText() {
    sfmlText.setString(text);                                                                   // Update the string when the text is changed
}

void Text::render() {
    window.draw(sfmlText);                                                                      // Draw the text on the window
}

void Text::setText(const std::string& newText) {                                                // Setters
    text = newText;
    updateText();                  
}

int Text::getID() {                                                                             // Getters               
    return ID;
}

std::string Text::getText() {
    return text;
}
