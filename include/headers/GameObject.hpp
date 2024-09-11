#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

#include <../sdl/SDL_image.h>
#include "ResourceManager.hpp"
#include <string>
using namespace std;

class GameObject {                                                                                          // GameObject class used for creating game objects (tiles, images)        
public:
    GameObject(SDL_Renderer* renderer, int value, int x, int y, int width, int height);                     // Constructor with value (for tiles)        
    GameObject(SDL_Renderer* renderer, const string& imagePath, int x, int y, int width, int height);       // Constructor without value (for images)
    ~GameObject();                                                                                          // Destructor    

    void loadTexture(SDL_Renderer* renderer, const string& imagePath);                                      // Public methods
    virtual void render(SDL_Renderer* renderer);
    int getX();                                                                                             // Getters
    int getY();
    int getWidth();
    int getHeight();

    void setTexture(SDL_Renderer* renderer, const string& imagePath);

private:
    string getImagePathToValue(int value);                                                                  // Private method         
    
    int x;                                                                                                  // Member variables
    int y;
    int width;
    int height;
    SDL_Texture* texture;
};

#endif  // GAMEOBJECT_HPP
