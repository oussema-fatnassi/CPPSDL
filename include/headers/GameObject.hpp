#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

#include <../sdl/SDL_image.h>
#include <string>
using namespace std;

class GameObject {
public:
    GameObject(SDL_Renderer* renderer, int value, int x, int y, int width, int height);
    ~GameObject();

    void render(SDL_Renderer* renderer);

private:
    string getImagePathToValue(int value);
    
    int x;
    int y;
    int width;
    int height;
    SDL_Texture* texture;
};

#endif  // GAMEOBJECT_HPP
