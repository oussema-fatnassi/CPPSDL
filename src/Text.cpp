#include "Text.hpp"
#include <iostream>
using namespace std;

Text::Text(SDL_Renderer* renderer, const std::string& text, TTF_Font* font, SDL_Color color, int x, int y)
    : text(text), font(font), color(color), renderer(renderer) {

    rect.x = x;
    rect.y = y;
    createTexture();
}

Text::~Text() {
    if (texture) {
        SDL_DestroyTexture(texture);
    }
}

void Text::createTexture() {
    SDL_Surface* textSurface = TTF_RenderText_Blended(font, text.c_str(), color);
    if (!textSurface) {
        std::cerr << "Unable to render text surface! TTF_Error: " << TTF_GetError() << std::endl;
        return;
    }

    texture = SDL_CreateTextureFromSurface(renderer, textSurface);
    if (!texture) {
        std::cerr << "Unable to create texture from rendered text! SDL_Error: " << SDL_GetError() << std::endl;
        return;
    }

    rect.w = textSurface->w;
    rect.h = textSurface->h;
    SDL_FreeSurface(textSurface);
}

void Text::render(SDL_Renderer* renderer) {
    SDL_RenderCopy(renderer, texture, nullptr, &rect);
}

void Text::setText(const std::string& newText) {
    text = newText;
    if (texture) {
        SDL_DestroyTexture(texture);  // Free previous texture
    }
    createTexture();
}