#include <SFML/Graphics.hpp>
#include "map.h"
using namespace std;

using namespace sf;

////////////////////////////////////////////////////КЛАСС МЯЧА////////////////////////
class Ball { // класс мяча
public:
    float x, y;
    float w, h, dx, dy, speed ;
    String File; //файл с расширением
    Image image;//сфмл изображение
    Texture texture;//сфмл текстура
    Sprite sprite;//сфмл спрайт

    Ball(String F, float X, float Y, float W, float H){ //Конструктор класса
        dx=-5;dy =-5;
        File = F;//имя файла+расширение
        w = W; h = H;//высота и ширина
        image.loadFromFile("images/" + File);
        texture.loadFromImage(image);//закидываем наше изображение в текстуру
        sprite.setTexture(texture);//заливаем спрайт текстурой
        x = X; y = Y;//координата появления спрайта
    }



    void update(){ //функция "оживления" объекта класса. update - обновление.
        interactionWithMap();//вызываем функцию, отвечающую за взаимодействие с картой
        x += dx;//смещение координат за кадр
        y += dy;
        sprite.setPosition(x,y);
        }

    void interactionWithMap()//ф-ция взаимодействия с картой
	{
            //for (int i = y / 32; i < (y + h) / 32 + 1; i++)//координата y тайла, в котором находится мяч
            //for (int j = x / 32; j<(x + w) / 32 + 1; j++)//координата x тайла, в котором находится мяч
            //{
               // if (TileMap[i][j] == '0')//Если "край карты"
               // {
                  //  if(i == 0 || i == 16)
                  //      dy = -dy;
                 //   else if(j == 0 || j == 28)
               //         dx = -dx;
               // }
           // }

	}

};
