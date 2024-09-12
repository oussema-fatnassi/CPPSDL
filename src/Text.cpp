#include "Text.hpp"

Text::Text(sf::RenderWindow& window, const std::string& text, const sf::Font& font, sf::Color color, int x, int y, int ID,int fontSize) 
    : window(window), text(text), color(color), ID(ID),fontSize(fontSize) {
    this->font = font;              // Copy the font
    sfmlText.setFont(this->font);   // Set the font for the SFML text object
    sfmlText.setString(this->text); // Set the string (text) to display
    sfmlText.setFillColor(this->color);  // Set the color of the text
    sfmlText.setCharacterSize(this->fontSize);  // Set the font size
    sfmlText.setPosition(x, y);     // Set the position of the text
}

Text::~Text() {
    // No need for manual cleanup, SFML handles resource management.
}

void Text::updateText() {
    sfmlText.setString(text);       // Update the string when the text is changed
}

void Text::render() {
    window.draw(sfmlText);          // Draw the text on the window
}

void Text::setText(const std::string& newText) {
    text = newText;
    updateText();                   // Update the displayed text when the text is changed
}

int Text::getID() {
    return ID;
}

std::string Text::getText() {
    return text;
}
