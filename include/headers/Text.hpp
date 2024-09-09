#ifndef TEXT_HPP
#define TEXT_HPP

#include <../sdl/SDL.h>
#include <../sdl/SDL_ttf.h>
#include <string>
using namespace std;

class Text {
public:
    Text(SDL_Renderer* renderer, const std::string& text, TTF_Font* font, SDL_Color color, int x, int y, int ID);
    ~Text();
    void render(SDL_Renderer* renderer);
    void setText(const std::string& newText);
    string getText() { return text; }
    int getID() { return ID; }
    
private:
    std::string text;
    TTF_Font* font;
    SDL_Color color;
    SDL_Texture* texture;
    SDL_Rect rect;
    SDL_Renderer* renderer;
    int ID;

    void createTexture();
};

#endif
