#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <SFML/Graphics.hpp>
#include <string>
using namespace std;

class Window {
public:
    Window(const string& title, int width, int height);         // Constructor
    ~Window();                                                  // Destructor

    void pollEvents();                                          // Public methods      
    bool isClosed() const;                                    
    void clear();                                      
    void present();                                           
    void renderImage(const string& imagePath, int x, int y, int width, int height);  
    sf::RenderWindow& getRenderWindow();                        // Getters

private:
    bool init();                                                // Private methods                       

    sf::RenderWindow window;                                    // Member variables          
    sf::Texture texture;                                      
    sf::Sprite sprite;                                        
    bool closed;                                             
    string title;                                        
    int width, height;                                        
};

#endif // WINDOW_HPP
