#include "GameObject.hpp"
#include <iostream>

GameObject::GameObject(SDL_Renderer* renderer, int value, int x, int y, int width, int height)                          // Constructor with value (for tiles)
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


GameObject::GameObject(SDL_Renderer* renderer, const string& imagePath, int x, int y, int width, int height)            // Constructor without value (for images)    
    : x(x), y(y), width(width), height(height), texture(nullptr) {
    
    loadTexture(renderer, imagePath);
}

GameObject::~GameObject() {                                                                                             // Destructor        
    if (texture) {
        SDL_DestroyTexture(texture);
    }
}

void GameObject::render(SDL_Renderer* renderer) {                                                                       // Render method for GameObject
    SDL_Rect dstRect = {x, y, width, height};                                                                           // Destination rectangle              
    SDL_RenderCopy(renderer, texture, nullptr, &dstRect);                                                               // Copy texture to renderer
}

string GameObject::getImagePathToValue(int value) {                                                                     // Get image path based on value
    if(value > 2048) {
        return "../assets/images/other.svg";
    }
    return "../assets/images/" + to_string(value) + ".svg";
}

void GameObject::loadTexture(SDL_Renderer* renderer, const string& imagePath) {                                         // Load texture from image path          
    SDL_Surface* surface = ResourceManager::getInstance().getSurface(imagePath); 
    if (!surface) {
        cerr << "Failed to load image: " << IMG_GetError() << endl;
        return;
    }

    if (texture) {
        SDL_DestroyTexture(texture);                                                                                    // Free previous texture
    }

    texture = SDL_CreateTextureFromSurface(renderer, surface);                                                          // Create texture from surface        
    if (!texture) {
        cerr << "Failed to create texture: " << SDL_GetError() << endl;
    }
}

void GameObject::setTexture(SDL_Renderer* renderer, const string& imagePath) {                                          // Set texture from image path            
    loadTexture(renderer, imagePath);
}

int GameObject::getX() {                                                                                                // Getters
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