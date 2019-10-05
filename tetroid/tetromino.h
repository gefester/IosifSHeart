#ifndef TETROMINO_H
#define TETROMINO_H
#include "pixelscreen.h"
#include "field.h"
#include <utility> //Для std::pair
#include <cstdlib>
#include<ctime>

typedef std::pair<short, short> ShortPair;

/// Тетрамино -- фигуры из 4 квадратных блоков, падением которых управляет игрок
/// Скрипт для генерации параметров и сетки тетрамино используется скрипт scripts/tetro_gen.py
class Tetromino
{
protected:
    struct tetroCollider {
        uint_fast8_t left, right;
    };
    uint_fast8_t grid[4]; //Сетка тетрамино. 1 char = 1 строка со структурой, аналогичной структуре строк Field
    tetroCollider collider; //Коллайдер тетрамино -- реальная ширина и отступ тетрамино от левого конца сетки
    Vector2u position; //Положение сетки относительно левого верхнего угла поля
    bool explosive; //Тетрамино (точнее, октамино) является бомбой (it's a fucking Brick Game reference)
    tetroCollider calculateCollider(uint_fast8_t* grid); //Расчитать значения коллайдера
    ushort projectRow(ushort row, short shift); //Сроецировать ряд сетки тетрамино на пустой ряд поля с сдвигом вправо на shift

public:
    const float FALL_INTERVAL = 0.5; //Стандартный интервал в секундах между падением тетрамино вниз
    Tetromino(uint_fast8_t grid[4], bool explosive = false);
    void operator=(Tetromino other); //Копирование тетрамино для их сменяемости

    void render(PixelScreen* scr, uint ox = 0, uint oy = 0); //Отобразить тетрамино на холсте Pixeloid по адресу scr
    void project(Field* on); //Спроецировать тетрамино на поле on
    bool collides(Field* with); //Проверить, сталкивается ли тетрамино с блоками на поле with
    ShortPair boundDistance(short offset = 0); //Расстояние между соответсвующими сторонами концами коллайдера в положении (position + {offset, 0}) и горизонтальными краями поля
    bool inBounds(short offset = 0); //Проверка на нахождение тетрамино внутри поля
    bool yaw(short offset, Field* field = nullptr); //Подвинуть фигуру вправо на offset. true при успешном перемещении.
    bool fall(short offset = 1, Field* field = nullptr); //Подвинуть фигуру вниз на offset. true при успешном падении.
    bool rotate(Field* field = nullptr, bool clockwise = false); //Попытаться перевернуть фигуре на 90º против часовой (по часовой при clockwise == true) стрелки. Вернуть true или false в зависимости от успешности поворота.
    //Примичание: поворот не возможен, если перевёрнутая фигура застревает в щели между уже уложенными блоками.
    void explode(unsigned char range = 3); //Взорвать все блоки в квадрате range на range вокруг центра сетки

    const static size_t PREFABS_SIZE; //Размер Tetromino::PREFABS (см. ниже)
    const static Tetromino PREFABS[]; //Шаблоны тетрамино для случайного выбора игрой
    static Tetromino pickRandom();
};

#endif // TETROMINO_H
