#include "GameObject.hpp"
#include <iostream>

GameObject::GameObject(SDL_Renderer* renderer, int value, int x, int y, int width, int height)
    : x(x), y(y), width(width), height(height), texture(nullptr) {
    
    if (value == 0) {
        return;
    }
    
    string imagePath = getImagePathToValue(value);

    SDL_Surface* surface = IMG_Load(imagePath.c_str());
    if (!surface) {
        cerr << "Failed to load image: " << IMG_GetError() << endl;
        return;
    }

    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

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
    return "../assets/images/" + to_string(value) + ".svg";
}

void GameObject::loadTexture(SDL_Renderer* renderer, const string& imagePath) {
    SDL_Surface* surface = IMG_Load(imagePath.c_str());
    if (!surface) {
        cerr << "Failed to load image: " << IMG_GetError() << endl;
        return;
    }

    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    if (!texture) {
        cerr << "Failed to create texture: " << SDL_GetError() << endl;
    }
}
