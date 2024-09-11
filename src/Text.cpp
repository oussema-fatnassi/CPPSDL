// #include "Text.hpp"

// Text::Text(SDL_Renderer* renderer, const std::string& text, TTF_Font* font, SDL_Color color, int x, int y, int ID)      // Constructor
//     : text(text), font(font), color(color), renderer(renderer) , ID(ID) {

//     rect.x = x;
//     rect.y = y;
//     createTexture();
// }

// Text::~Text() {                                                                         // Destructor      
//     if (texture) {
//         SDL_DestroyTexture(texture);
//     }
// }

// void Text::createTexture() {                                                            // Create texture of text with font and color
//     SDL_Surface* textSurface = TTF_RenderText_Blended(font, text.c_str(), color);
//     if (!textSurface) {
//         std::cerr << "Unable to render text surface! TTF_Error: " << TTF_GetError() << std::endl;
//         return;
//     }

//     texture = SDL_CreateTextureFromSurface(renderer, textSurface);                      // Create texture from surface
//     if (!texture) {
//         std::cerr << "Unable to create texture from rendered text! SDL_Error: " << SDL_GetError() << std::endl;
//         return;
//     }

//     rect.w = textSurface->w;
//     rect.h = textSurface->h;
//     SDL_FreeSurface(textSurface);                                                       
// }

// void Text::render(SDL_Renderer* renderer) {                                             // Render text                   
//     if (!renderer || !font) {
//         std::cerr << "Renderer or font is null!" << std::endl;
//         return;
//     }
//     SDL_RenderCopy(renderer, texture, nullptr, &rect);                                  // Copy texture to renderer        
// }

// void Text::setText(const std::string& newText) {                                        // Setters
//     text = newText;
//     if (texture) {
//         SDL_DestroyTexture(texture);  
//     }
//     createTexture();
// }

// int Text::getID() {                                                                     // Getters
//     return ID;
// }

// string Text::getText() {
//     return text;
// }