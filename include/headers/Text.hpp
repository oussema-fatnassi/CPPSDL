#ifndef TEXT_HPP
#define TEXT_HPP

#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

class Text {                                                // Text class used for creating text objects
public:
    Text(sf::RenderWindow& window, const std::string& text, const sf::Font& font, sf::Color color, int x, int y, int ID);   // Constructor
    ~Text();                                                // Destructor       
    void render();                                          // Public methods    
    void setText(const std::string& newText);               // Setters
    int getID();                                            // Getters    
    std::string getText();
    
private:
    std::string text;                                       // Member variables        
    sf::Font font;
    sf::Text sfmlText;
    sf::Color color;
    sf::RenderWindow& window;
    int ID;

    void updateText();                                      // Private method to update the text object
};

#endif
