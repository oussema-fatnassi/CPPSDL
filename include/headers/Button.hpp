#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "GameObject.hpp"
#include <functional>
#include <../sdl/SDL.h>
using namespace std;

class Button : public GameObject {
public:
    enum class ButtonState { NORMAL, HOVER, PRESSED };

    Button(SDL_Renderer* renderer, const string& normalImage, const string& hoverImage, const string& pressedImage, 
           int x, int y, int width, int height, function<void()> onClickCallback);

    void handleEvent(SDL_Event* event);
    void render(SDL_Renderer* renderer) override;

private:
    function<void()> onClickCallback;
    ButtonState currentState;
    
    string normalImage;
    string hoverImage;
    string pressedImage;

    SDL_Renderer* renderer; 

    void changeState(ButtonState newState);
};

#endif // BUTTON_HPP
