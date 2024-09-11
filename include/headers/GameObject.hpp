#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

#include <SFML/Graphics.hpp>
#include <string>

class GameObject {  // GameObject class used for creating game objects (tiles, images)        
public:
    GameObject(sf::RenderWindow& window, int value, int x, int y, int width, int height); // Constructor with value (for tiles)        
    GameObject(sf::RenderWindow& window, const std::string& imagePath, int x, int y, int width, int height); // Constructor without value (for images)
    ~GameObject(); // Destructor    

    void loadTexture(const std::string& imagePath); // Public methods
    virtual void render();
    int getX() const; // Getters
    int getY() const;
    int getWidth() const;
    int getHeight() const;

    void setTexture(const std::string& imagePath);

private:
    std::string getImagePathToValue(int value); // Private method         

    int x; // Member variables
    int y;
    int width;
    int height;
    sf::Texture texture;
    sf::Sprite sprite;
    sf::RenderWindow& window; // Reference to the SFML window
};

#endif  // GAMEOBJECT_HPP
