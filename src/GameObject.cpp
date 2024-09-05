#include "GameObject.hpp"
#include <iostream>

#include "GameObject.hpp"
#include "ResourceManager.hpp"
#include <iostream>

GameObject::GameObject(SDL_Renderer* renderer, int value, int x, int y, int width, int height)
    : x(x), y(y), width(width), height(height), texture(nullptr) {

    if (value == 0) {
        return;  
    }

    string imagePath = getImagePathToValue(value);

    SDL_Surface* surface = ResourceManager::getInstance().getSurface(imagePath);

    if (!surface) {
        cerr << "Failed to load image: " << imagePath << endl;
        return;
    }

    texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!texture) {
        cerr << "Failed to create texture: " << SDL_GetError() << endl;
    }
}


GameObject::GameObject(SDL_Renderer* renderer, const string& imagePath, int x, int y, int width, int height)
    : x(x), y(y), width(width), height(height), texture(nullptr) {
    
    loadTexture(renderer, imagePath);
}

GameObject::~GameObject() {
    if (texture) {
        SDL_DestroyTexture(texture);
    }
}

void GameObject::render(SDL_Renderer* renderer) {
    SDL_Rect dstRect = {x, y, width, height};
    SDL_RenderCopy(renderer, texture, nullptr, &dstRect);
}

string GameObject::getImagePathToValue(int value) {
    if(value > 2048) {
        return "../assets/images/other.svg";
    }
    return "../assets/images/" + to_string(value) + ".svg";
}

void GameObject::loadTexture(SDL_Renderer* renderer, const string& imagePath) {
    SDL_Surface* surface = ResourceManager::getInstance().getSurface(imagePath); 
    if (!surface) {
        cerr << "Failed to load image: " << IMG_GetError() << endl;
        return;
    }

    if (texture) {
        SDL_DestroyTexture(texture);  // Free previous texture
    }

    texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!texture) {
        cerr << "Failed to create texture: " << SDL_GetError() << endl;
    }
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