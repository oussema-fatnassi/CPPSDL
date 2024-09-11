// #ifndef BUTTON_HPP
// #define BUTTON_HPP

// #include "GameObject.hpp"
// #include <functional>
// #include <../sdl/SDL.h>
// using namespace std;
// #include <iostream>

// class Button : public GameObject {                                  // Button class inherits from GameObject
// public: 
//     enum class ButtonState { NORMAL, HOVER, PRESSED, DISABLED };    // ButtonState enum class with 4 states

//     Button(SDL_Renderer* renderer, const string& normalImage, const string& hoverImage, const string& pressedImage,     // Constructor
//            int x, int y, int width, int height, function<void()> onClickCallback);
//     ~Button();                                                      // Destructor

//     void handleEvent(SDL_Event* event);                             //Public methods
//     void render(SDL_Renderer* renderer) override;                      
//     void disable();                                                 

// private:
//     function<void()> onClickCallback;                               // Private member variables
//     void changeState(ButtonState newState);

//     ButtonState currentState;
//     string normalImage;
//     string hoverImage;
//     string pressedImage;
//     SDL_Renderer* renderer; 
// };

// #endif // BUTTON_HPP
