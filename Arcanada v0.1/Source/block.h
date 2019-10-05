#include <SFML/Graphics.hpp>

using namespace sf;

class Block {
public:
    int x, y;
    int w, h;
    String File;
    Image image;
    Texture texture;
    Sprite sprite;

    Block(){

    }

    int getCoordinateX(){
        return x;
    }
    int getCoordinateY(){
        return y;
    }
};
