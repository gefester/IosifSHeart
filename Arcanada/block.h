#include <SFML/Graphics.hpp>

using namespace sf;

class Block {
private: float x, y;
public:
    float w, h;
    String File;
    Image image;
    Texture texture;
    Sprite sprite;

    Block(String F, float X, float Y, float W, float H){
        File = F;
        w = W; h = H;
        image.loadFromFile("images/" + File);
        texture.loadFromImage(image);
        sprite.setTexture(texture);
        x = X;
        y = Y;
    }

    void update(){
        sprite.setPosition(x, y);
    }
};
