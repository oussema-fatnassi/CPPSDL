#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "GameObject.hpp"
#include <functional>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
using namespace std;
#include <iostream>

class Button : public GameObject {                                  // Button class inherits from GameObject
public: 
    enum class ButtonState { NORMAL, HOVER, PRESSED, DISABLED };    // ButtonState enum class with 4 states

    Button(sf::RenderWindow& window, const string& normalImage, const string& hoverImage, const string& pressedImage,     // Constructor
           int x, int y, int width, int height, function<void()> onClickCallback);
    ~Button();                                                      // Destructor

    void handleEvent(sf::Event& event, sf::RenderWindow& window);                             //Public methods
    void render() override;                      
    void disable();                                                 

private:
    function<void()> onClickCallback;                               // Private member variables
    void changeState(ButtonState newState);

    ButtonState currentState;
    string normalImage;
    string hoverImage;
    string pressedImage;
    sf::RenderWindow& window; 
};

#endif // BUTTON_HPP
