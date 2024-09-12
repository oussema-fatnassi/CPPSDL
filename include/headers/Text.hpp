#ifndef TEXT_HPP
#define TEXT_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
using namespace std;

class Text {                                                // Text class used for creating text objects
public:
    Text(sf::RenderWindow& window, const string& text, const sf::Font& font, sf::Color color, int x, int y, int ID, int fontSize);   // Constructor
    ~Text();                                                // Destructor       
    void render();                                          // Public methods    
    void setText(const string& newText);               // Setters
    int getID();                                            // Getters    
    string getText();
    
private:
    string text;                                       // Member variables        
    sf::Font font;
    sf::Text sfmlText;
    sf::Color color;
    sf::RenderWindow& window;
    int ID;
    int fontSize;

    void updateText();                                      // Private method to update the text object
};

#endif
