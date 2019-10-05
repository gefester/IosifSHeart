#include "field.h"

typedef unsigned short ushort;
typedef unsigned int uint;
typedef unsigned long ulong;

const sf::Color Field::COLORS[] = {sf::Color::Transparent, sf::Color::Red, sf::Color::Green, sf::Color::Blue};

Field::Field()
{
    //Обнуляем переменные
    for (int i = 0; i < 12; i++)
        rows[i] = 0;
    for (int i = 0; i < 8; i++)
        heightMap[i] = 0;
    score = 0;
}

ulong Field::getScore()
{
    return score;
}

void Field::addScore(ulong bonus)
{
    score += bonus;
}

void Field::clearRow(uint n)
{
    do
    {
        rows[n] = rows[n-1]; //Копируем в ряд n содержимое ряда выше
        rows[--n] = 0; //Эквивалентно rows[n - 1] = 0; n--;
    }
    while(n > 0);
}

void Field::checkRows()
{
    uint bonus = 100; //Очки за удалённый ряд
    int i = 11;
    while (i >= 0)
    {
        ushort row = rows[i];
        bool full = true; //Заполнен ли ряд
        /*Проверка ячеек ряда.
        Если за 8 итераций не будет найдена пустая ячейка, ряд считается заполненным.*/
        for (int j = 0; j < 8 && full; j++){
            full = (row & 3) != 0; //Если ячейка пуста, full = false
            row >>= 2; //Переход к следующей ячейки
        }
        if (full) {
            clearRow(i);
            addScore(bonus);
            bonus += 100;
        }
        else i--;
    }
}

bool Field::isOverflowed()
{
    for (int i = 0; i < 8; i++)
        if (heightMap[i] > 11) return true;
    return false;
}

void Field::fill(uint x, uint y, ushort color)
{
    color <<= x*2; //Смещаем цвет на координату x
    rows[y] |= color; //Накладываем цвет по побитовому ИЛИ. Предпологается, что заполняемая ячейка изначально пуста.
}

void Field::render(PixelScreen* scr){
    for (ushort y = 0; y < 12; y++)
    {
        for(ushort x = 0, row = rows[y]; row != 0; x++, row >>= 2)
        {
            ushort color = row & 3;
            scr->addPixel(sf::Vector2u(x, y), COLORS[color]);
        }
    }
}
