#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

#include <SDL_image.h>
#include <string>
using namespace std;

class GameObject {
public:
    GameObject(int value, int x, int y, int width, int height);
    ~GameObject();
    string getImagePathToValue(int value);
    string getImagePath();
    int getX();
    int getY();
    int getWidth();
    int getHeight();

private:
    bool init();
    int value;
    string imagePath;
    int x;
    int y;
    int width;
    int height;
    SDL_Texture* texture;
    bool closed;

};



#endif  // GAMEOBJECT_HPP