#include <SFML/Graphics.hpp>
#include "map.h"
#include "block.h"
#include <sstream>
#include "player.h"
#include <iostream>

using namespace sf;

////////////////////////////////////////////////////КЛАСС МЯЧА////////////////////////
class Ball { // класс мяча
public:
    int x, y;
    int w, h, dx, dy, speed ;
    String File; //файл с расширением
    Image image;//сфмл изображение
    Texture texture;//сфмл текстура
    Sprite sprite;//сфмл спрайт

    Ball(String F, int X, int Y, int W, int H){ //Конструктор класса
        dx=-8;dy =-8;
        File = F;//имя файла+расширение
        w = W; h = H;//высота и ширина
        image.loadFromFile("images/" + File);
        texture.loadFromImage(image);//закидываем наше изображение в текстуру
        sprite.setTexture(texture);//заливаем спрайт текстурой
        x = X; y = Y;//координата появления спрайта
    }



    void update(){ //функция "оживления" объекта класса. update - обновление.
        x += dx;//смещение координат за кадр
        y += dy;
        sprite.setPosition(x,y);
        }

    void interactionWithBlock(Block& b, Player& p)//метод взаимодействия с блоками
    //bX и bY - координаты блока, которые мы передаем в метод
	{
	    if((y+h) == b.y && (x >= b.x && x <= b.x + b.w || x+w >= b.x && x+w <= b.x + b.w)){
        //условия столкновения с верхней поверхностью блока. Столкновение регистрируется от любого пикселя нижней поверхности мяча
        //аналогично другие условия
            dy = -8;
            b.File = "broken";
            b.sprite.setPosition(-64, -64);
            ++p.playerScore;
            std::cout << "Up" << std::endl;
        }
        if(y == b.y+b.h && (x >= b.x && x <= b.x + b.w || x+w >= b.x && x+w <= b.x + b.w)){  //Нижняя поверхность
            dy = 8;
            b.File = "broken";
            b.sprite.setPosition(-64, -64);
            ++p.playerScore;
            std::cout << "Down" << std::endl;
        }
        if(x + w == b.x && (y >= b.y && y <= b.y + b.h || y + h >= b.y && y + h <= b.y + b.h)){ //Левая поверхность
            dx = -8;
            b.File = "broken";
            b.sprite.setPosition(-64, -64);
            ++p.playerScore;
            std::cout << "Left" << std::endl;
        }
        if(x == b.x + b.w && (y >= b.y && y <= b.y + b.h || y + h >= b.y && y + h <= b.y + b.h)){ //Правая поверхность
            dx = 8;
            b.File = "broken";
            b.sprite.setPosition(-64, -64);
            ++p.playerScore;
            std::cout << "Right" << std::endl;
        }
	}


	void interactionWithWall(int leftWall, int rightWall, int topWall){
        if(y == topWall)
            dy = -dy;
        if(x == leftWall || x == rightWall){
            dx = -dx;
            std::cout << "Wall" << std::endl;
        }
	}

	void interactionWithPlayer(int playerX, int playerY, int playerW, int playerH){
        if( (y+h) == playerY && (x >= playerX && x <= playerX+playerW || x+w >= playerX && x+w <= playerX+playerW) )
            dy = -dy;
	}
};
