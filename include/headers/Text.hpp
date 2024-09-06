#ifndef TEXT_HPP
#define TEXT_HPP

#include <../sdl/SDL.h>
#include <../sdl/SDL_ttf.h>
#include <string>
using namespace std;

class Text {
public:
    Text(SDL_Renderer* renderer, const std::string& text, TTF_Font* font, SDL_Color color, int x, int y);
    ~Text();
    void render(SDL_Renderer* renderer);
    void setText(const std::string& newText);
    string getText() { return text; }
    
private:
    std::string text;
    TTF_Font* font;
    SDL_Color color;
    SDL_Texture* texture;
    SDL_Rect rect;
    SDL_Renderer* renderer;

    void createTexture();
};

#endif
