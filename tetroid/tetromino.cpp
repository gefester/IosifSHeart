#include "tetromino.h"
#include "debugFunctions.cpp"

Tetromino::tetroCollider Tetromino::calculateCollider(uint_fast8_t* grid)
{
    uint_fast8_t left = 4;
    uint_fast8_t right = 0;
    for (size_t y = 0; y < 4; y++)
    {
        uint_fast8_t row = grid[y];
        uint_fast8_t rowLeft = 4, rowRight = 1;
        for (uint_fast8_t x = 0; x < 4; x++, row >>= 2)
        {
            if((row & 3) == 0) continue;
            if(x < rowLeft) rowLeft = x;
            rowRight = x;
        }
        if (rowLeft < left) left = rowLeft;
        if (rowRight > right) right = rowRight;
    }
    return {left, right};
}

ushort Tetromino::projectRow(ushort row, short shift)
{
    if (shift < 0)
        return row >> (-shift * 2);
    else
        return row << (shift * 2);
}

Tetromino::Tetromino(uint_fast8_t* grid, bool explosive)
{
    for (int i = 0; i < 4; i++)
        this->grid[i] = grid[i];
    this->explosive = explosive;
    this->position = Vector2u(2, (grid[4] == 0) ? 0: -1);
    this->collider = calculateCollider(grid);
}

void Tetromino::operator=(Tetromino other)
{
    for (size_t y = 0; y < 4; y++)
        grid[y] = other.grid[y];
    collider = other.collider;
    position = other.position;
    explosive = other.explosive;
}

void Tetromino::render(PixelScreen* scr, uint ox, uint oy)
{
    for (ushort y = 0; y < 4; y++)
    {
        ushort fieldY = y + position.y - 3;
        if (fieldY >= 12) continue; //Пропуск рядов вне поля. Работает и с верхним краем из-за переполнения.
        for(uint x = position.x, row = grid[y]; row != 0; x++, row >>= 2)
        {
            ushort color = row & 3;
            scr->addPixel(sf::Vector2u(x + ox, fieldY + oy), Field::COLORS[color]);
        }
    }
}

void Tetromino::project(Field *on)
{
    for (short y = 4; y > -1; y--)
    {
        ushort fieldY = y + position.y - 3;
        if (fieldY >= 12) continue; //Пропуск рядов вне поля. Работает и с верхним краем из-за переполнения.
        ushort row = projectRow(grid[y], position.x); //Создать накладываемый ряд
        on->rows[fieldY] |= row; //Наложить ряд на поле
        for (uint_fast8_t x = 0; x < 8; x++, row >>= 2)
            if ((row & 3) != 0)
                on->heightMap[x] = 12 - fieldY; //Увеличивать heightMap[x], если ячейка не пуста
    }
}

bool Tetromino::collides(Field *on)
{
    for (ushort y = 0; y < 4; y++)
    {
        ushort fieldY = y + position.y - 3;
        if (fieldY >= 12) continue; //Пропуск рядов вне поля. Работает и с верхним краем из-за переполнения.
        ushort tetroRow = projectRow(grid[y], position.x); //Создать сверяемый ряд
        ushort fieldRow = on->rows[fieldY];
        while (tetroRow != 0 && fieldRow != 0){
            if (!((tetroRow & 3) == 0||(fieldRow & 3) == 0))
                return true;
            else {
                tetroRow >>= 2;
                fieldRow >>= 2;
            }
        }
    }
    return false;
}

ShortPair Tetromino::boundDistance(short offset)
{
    short first = (position.x + offset + collider.left);
    short second = (position.x + offset + collider.right) - 8;
    return {first, second};
}

bool Tetromino::inBounds(short offset)
{
    ShortPair bd = boundDistance(offset);
    return bd.first >= 0 && bd.second < 0;
}

bool Tetromino::yaw(short offset, Field* field)
{
    if (inBounds(offset)){
        position.x += offset;
        if (field == nullptr || !collides(field))
            return true;
        else yaw(-offset); //Откат изменений
    }
    return false;
}

bool Tetromino::fall(short offset, Field* field)
{
    uint new_y = (int)position.y + offset;
    if (new_y < 12 || grid[3 - (position.y - 11)] == 0){
        position.y = new_y;
        if (field == nullptr || !collides(field))
            return true;
        else
            fall(-offset); //Откат изменений
    }
    return false;
}

bool Tetromino::rotate(Field* field, bool clockwise)
{
    uint_fast8_t newGrid[4] = {0, 0, 0, 0};
    for (ushort y = 0; y < 4; y++)
    {
        ushort row = grid[y]; //Создать накладываемый ряд
        for (int x = 0; x < 4; x++) {
            if (!clockwise)
                newGrid[3 - x] += (row & 3) << (2 * y); //Переставляем ячейку (x;y) в (y;x)
            else
                newGrid[x] += (row & 3) << (2 * (3 - y)); //Переставляем ячейку (x;y) в (3-y;x)
            row >>= 2;
        }
    }
    for (ushort y = 0; y < 4; y++)
        grid[y] = newGrid[y];

    collider = calculateCollider(grid);
    bool inBounds = this->inBounds();
    if (!inBounds) {
        ShortPair bd = boundDistance();
        inBounds = yaw(bd.first < 0 ? -bd.first + 1: -bd.second - 1, field);
    }
    if (inBounds && (field == nullptr || !collides(field)))
        return true;
    else return rotate(nullptr, !clockwise); //Откат изменений
}

const size_t Tetromino::PREFABS_SIZE = 7;
const Tetromino Tetromino::PREFABS[] = {
    Tetromino((uint_fast8_t[4]){0, 40, 40, 0}), //Квадрат
    Tetromino((uint_fast8_t[4]){0, 0, 1, 21}), //"Г" вправо
    Tetromino((uint_fast8_t[4]){0, 0, 192, 252}), //"Г" влево
    Tetromino((uint_fast8_t[4]){0, 0, 0, 85}), //Линия
    Tetromino((uint_fast8_t[4]){0, 0, 160, 40}), //"Зигзаг" горизонтальный
    Tetromino((uint_fast8_t[4]){0, 48, 60, 12}), //"Зигзаг" вертикальный
    Tetromino((uint_fast8_t[4]){0, 16, 84, 0}), //"Т" перевёрнутая
};
Tetromino Tetromino::pickRandom()
{
    srand(time(nullptr));
    int id = rand() % PREFABS_SIZE;
    return PREFABS[id];
}
