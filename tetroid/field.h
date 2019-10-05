#ifndef FIELD_H
#define FIELD_H
#include "pixelscreen.h"
#include <SFML/Graphics/Color.hpp>

typedef unsigned short ushort;
typedef unsigned int uint;
typedef unsigned long ulong;

/// Игровое поле -- сетка 12x8, каждая ячейка которой пуста или окрашена в 1 из 3 цветов
/// Является основным местом
class Field
{
friend class Tetromino; //Не, ну по другому я просто задолблюсь делать дополнительные функции для взаимодействия с падующими тетрамино
protected:
    ushort rows[12]; //Ряды игрового поля. 1 число = 1 ряд, 2 бита = 1 ячейка. Ячейки идут справа налево.
    ushort heightMap[8]; //Карта высот. По значению на столбец. Счёт идёт снизу вверх

    ulong score; //Игровой счёт в данном поле
    void addScore(ulong bonus);

public:
    const static sf::Color COLORS[4]; //Цвета блоков: прозрачный, красный, зелёный и синий
    Field();

    ulong getScore(); //Получить текущий игровой счёт

    void clearRow(uint n); //Убрать ряд и сместить ряды выше вниз
    void checkRows(); //Проверить ряды на полноту и убрать заполненные
    bool isOverflowed(); //Проверить, не переполнено ли поле

    void fill(uint x, uint y, ushort color); //Закрасить ячейку {x, y} цветом color. При color = 0 ячейка освобождается.
    void render(PixelScreen* scr); //Вывести поле на холсте Pixeloid по адресу scr
};


#endif // FIELD_H
