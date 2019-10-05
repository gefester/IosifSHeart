#ifndef PIXELSCREEN_H
#define PIXELSCREEN_H
#include <SFML/Graphics.hpp>
#include <queue>
using namespace sf;
typedef unsigned int uint;
typedef unsigned short ushort;

/// Холст -- структура, хранящая команды на отображение виртуальных пиксилей (см. ниже), которая выводит их в виде векторых квадратиков
class PixelScreen
{
    public:
    struct pixel
    {
        Vector2u pos;
        Color color; /// Структура, хранящая положение и цвет будущего виртуального пикселя
    };

    protected:
    Vector2f pixelSize; //Размер стороны одного виртуального пикселя
    Vector2f pixelMargin; //Расстояние между виртульными писелями
    std::queue<pixel> pixelQueue;//Очередь для пикселей
    void renderPixel(RenderWindow* win, pixel pix); //Отобразить конкретный пиксель в окне по адресу win

    public:
    Vector2u offset; //Расстояние от края экрана
    PixelScreen(float pixelSize, float pixelMargin, Vector2u offset = {0, 0});

    void addPixel(pixel what); //Добавить пискель в очередь
    void addPixel(Vector2u where, Color color); //Ссылка на addPixel(pixel(where, color))
    void render(RenderWindow* win); //Отобразить весь экран в окне по адресу win и отчистить очередь
    float getPixelSize(); //Вернуть стандартный размер пикселя
    float getPixelMargin(); //Вернуть стандартный размер отступов между пикселями
};

#endif // PIXELSCREEN_H
