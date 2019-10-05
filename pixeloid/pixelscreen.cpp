#include "pixelscreen.h"
using namespace sf;

PixelScreen::PixelScreen(float pixelSize, float pixelMargin, Vector2u offset)
{
    this->pixelSize = Vector2f(pixelSize, pixelSize);
    this->pixelMargin = Vector2f(pixelMargin, pixelMargin);
    this->offset = offset;
    this->pixelQueue = std::queue<pixel>();
}

void PixelScreen::renderPixel(RenderWindow* win, pixel pix)
{
    RectangleShape pixelShape(pixelSize); //Фигура отображаемого пикселя
    Vector2f pos = pixelSize + pixelMargin; //Расстояние от края холста. Здесь пока что единичное.
    pos = Vector2f(pos.x * pix.pos.x + offset.x,
                   pos.y * pix.pos.y + offset.y); //Превращаем единичное рсстояние в итоговое
    pixelShape.move(pos); //Двигаем пиксель куда надо
    pixelShape.setFillColor(pix.color); //Красим
    win->draw(pixelShape); //Выводим на экран
}

void PixelScreen::render(RenderWindow *win)
{
    while(!pixelQueue.empty())
    {
        renderPixel(win, pixelQueue.front());
        pixelQueue.pop();
    }
}

void PixelScreen::addPixel(pixel pix) { pixelQueue.push(pix); }
void PixelScreen::addPixel(Vector2u where, Color color)
{
    pixel pix = {where, color};
    addPixel(pix);
}

float PixelScreen::getPixelSize() { return pixelSize.x; }
float PixelScreen::getPixelMargin() { return pixelMargin.x; }
