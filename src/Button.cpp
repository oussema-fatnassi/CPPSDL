// #include "Button.hpp"

// Button::Button(SDL_Renderer* renderer, const std::string& normalImage, const std::string& hoverImage, const std::string& pressedImage,      // Constructor
//                int x, int y, int width, int height, std::function<void()> onClickCallback)
//     : GameObject(renderer, normalImage, x, y, width, height), 
//       normalImage(normalImage), hoverImage(hoverImage), pressedImage(pressedImage), 
//       currentState(ButtonState::NORMAL), onClickCallback(onClickCallback), renderer(renderer) {}

// Button::~Button() {}                                        // Destructor

// void Button::handleEvent(SDL_Event* event) {                // Handle event method      
//     if (currentState == ButtonState::DISABLED) {            // If button is disabled, return
//         return;
//     }
//     else if (event->type == SDL_MOUSEMOTION || event->type == SDL_MOUSEBUTTONDOWN || event->type == SDL_MOUSEBUTTONUP) {            
//         int mouseX, mouseY;
//         SDL_GetMouseState(&mouseX, &mouseY);

//         bool inside = (mouseX > this->getX() && mouseX < this->getX() + this->getWidth() && mouseY > this->getY() && mouseY < this->getY() + this->getHeight());

//         if (!inside) {                                      // If mouse is not inside button, change state to normal
//             changeState(ButtonState::NORMAL);
//         } else {                                            // If mouse is inside button, change state to hover
//             switch (event->type) {
//                 case SDL_MOUSEMOTION:
//                     changeState(ButtonState::HOVER);
//                     break;
//                 case SDL_MOUSEBUTTONDOWN:                   // If mouse is pressed, change state to pressed
//                     changeState(ButtonState::PRESSED);
//                     break;
//                 case SDL_MOUSEBUTTONUP:
//                     if (currentState == ButtonState::PRESSED) {
//                         onClickCallback(); 
//                     }
//                     changeState(ButtonState::HOVER);
//                     break;
//             }
//         }
//     }
// }

// void Button::render(SDL_Renderer* renderer) {               // Render method
//     GameObject::render(renderer);  
// }

// void Button::disable() {                                    // Disable method, change state to disabled
//     currentState = ButtonState::DISABLED;  
// }

// void Button::changeState(ButtonState newState) {            // Change state method and load texture based on state
//     if (currentState != newState) {
//         currentState = newState;
//         switch (newState) {
//             case ButtonState::NORMAL:
//                 loadTexture(renderer, normalImage);
//                 break;
//             case ButtonState::HOVER:
//                 loadTexture(renderer, hoverImage);
//                 break;
//             case ButtonState::PRESSED:
//                 loadTexture(renderer, pressedImage);
//                 break;
//         }
//     }
// }
