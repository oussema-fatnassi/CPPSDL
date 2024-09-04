#include "GameObject.hpp"
#include <iostream>

GameObject::GameObject(int value, int x, int y, int width, int height)
    : value(value), x(x), y(y), width(width), height(height) {
    texture = nullptr;
    closed = !init();
    imagePath = getImagePathToValue(value);
}

GameObject::~GameObject() {
    if (texture) {
        SDL_DestroyTexture(texture);
    }
    
    SDL_Quit();
    IMG_Quit();
}

bool GameObject::init() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return false;
    }

    if (IMG_Init(IMG_INIT_PNG) == 0) {
        std::cerr << "IMG_Init Error: " << IMG_GetError() << std::endl;
        return false;
    }

    return true;
}

string GameObject::getImagePathToValue(int value) {
    string path = "../assets/images/" + to_string(value) + ".svg";
    return path;
}

string GameObject::getImagePath() {
    return imagePath;
}

int GameObject::getX() {
    return x;
}

int GameObject::getY() {
    return y;
}

int GameObject::getWidth() {
    return width;
}

int GameObject::getHeight() {
    return height;
}