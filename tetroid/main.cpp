#include <iostream>
#include <SFML/Graphics.hpp>
#include "field.h"
#include "tetromino.h"
#include "pixelscreen.h"
#include <string>
#include <set>
#include "debugFunctions.cpp"

auto keyDown = sf::Keyboard::isKeyPressed;
std::set<sf::Keyboard::Key> downKeys; //Уже нажатые кнопки
uint keyHoldDelay = 0; //Задержка при зажатии кнопки в кадрах

bool keyPressed(sf::Keyboard::Key key) //Проверка на единичное нажатие кнопки
{
    if (keyDown(key))
        if(downKeys.find(key) == downKeys.end()) { //Если клавиша ещё не в downKeys
            downKeys.insert(key);
            return true;
        }
    return false;
}
bool releaseKeys() //Убрать уже отпущенные клавиши из downKeys
{
    for (auto key = downKeys.begin(); key != downKeys.end(); key++)
        if (!keyDown(*key))
            downKeys.erase(key);
}

std::string multiString(std::string str, uint times) //Сложить строку str с ней же times раз
{
    if (times == 0)
        return "";
    std::string out = "";
    for (uint i = 0; i < times; i++)
        out += str;
    return out;
}

std::string multiString(std::string str, int times)
{
    if (times < 0)
        return "";
    else
        return multiString(str, (uint)times);
}

int main()
{
    sf::VideoMode vm(800, 600);
    sf::RenderWindow win(vm, "Tetroid");
    win.setFramerateLimit(60); //Без этого будет в наглую отжимать весь поток на over9000 FPS

    PixelScreen pixScr(32, 4); //(Размер пиксилей, расстояние между ними)
    pixScr.offset = {30, 30};
    float borderUnit = pixScr.getPixelSize() + pixScr.getPixelMargin();
    sf::RectangleShape border({8 * borderUnit - pixScr.getPixelMargin(),
                               12 * borderUnit - pixScr.getPixelMargin()}); //Обводка поля
    border.move((sf::Vector2f)pixScr.offset);
    border.setFillColor(sf::Color::Transparent);
    border.setOutlineThickness(10.f);
    border.setOutlineColor(sf::Color::White);

    sf::Font scoreFont; //Шрифт для счёта
    scoreFont.loadFromFile("fonts/Monoid-Regular.ttf");
    sf::Text scoreText; //Тескт счёта
    scoreText.setFont(scoreFont);
    scoreText.setCharacterSize(18);
    scoreText.setFillColor(sf::Color::White);
    scoreText.move(360, 64);

    float nextBorderSize = 4 * borderUnit - pixScr.getPixelMargin();
    sf::RectangleShape nextBorder({nextBorderSize, nextBorderSize}); //Обводка следующего тетрамино
    nextBorder.move(pixScr.offset.x + borderUnit * 10,
                    pixScr.offset.y + borderUnit * 10);
    nextBorder.setFillColor(sf::Color::Transparent);
    nextBorder.setOutlineThickness(5.0f);
    nextBorder.setOutlineColor(sf::Color::White);

    bool gameOver = false;
    Field field;
    Field* fieldAddr = &field;
    Tetromino currentTetromino = Tetromino::pickRandom();
    Tetromino nextTetromino = Tetromino::pickRandom();
    bool falling = true; //Тетрамино всё ещё падает
    uint fallingDelay = 0; //Задержка перед автопадением в кадрах
    const uint FALLING_DEFAULT_DELAY = 8; //Стандартная задержка перед падением в децисекундах


    //currentTetromino.fall(2, fieldAddr);
    //currentTetromino.rotate(false);

    /*for (uint i = 0; i < 7; i++)
        field.fill(i, 11, 1);
    for (uint i = 0; i < 11; i++)
        field.fill(7, i, 2);
    field.fill(7, 11, 3);*/

    while(win.isOpen())
    {
        //Проверка на попытки закрыть окно
        sf::Event event;
        while (win.pollEvent(event)){
            if (event.type == sf::Event::Closed)
                win.close();
        }
        //Управление
        releaseKeys();
        if (keyHoldDelay > 0)
            keyHoldDelay--;
        else{
            bool pressed = true;

            if (keyDown(sf::Keyboard::D))
                currentTetromino.yaw(1, fieldAddr);
            else if (keyDown(sf::Keyboard::A))
                currentTetromino.yaw(-1, fieldAddr);
            else pressed = false;

            if (keyDown(sf::Keyboard::S)) {
                pressed = true;
                falling = currentTetromino.fall(1, fieldAddr);
            }

            if (pressed) keyHoldDelay = FALLING_DEFAULT_DELAY / 2;
        }

        if (keyPressed(sf::Keyboard::W))
            currentTetromino.rotate(fieldAddr, true);

        //Автопадение
        if (fallingDelay > 0) fallingDelay--;
        else if (falling && !gameOver) {
            falling = currentTetromino.fall(1, fieldAddr);
            fallingDelay = 6 * FALLING_DEFAULT_DELAY;
        }

        //Смена тетрамино после падения
        if (!falling && !gameOver){
            currentTetromino.project(fieldAddr);
            field.checkRows();
            currentTetromino = nextTetromino;
            nextTetromino = Tetromino::pickRandom();
            falling = true;
            gameOver = field.isOverflowed();
            if (gameOver) border.setOutlineColor(sf::Color::Red);
        }

        //Рендеринг
        field.render(&pixScr);
        if (!gameOver) currentTetromino.render(&pixScr);

        //Обновление строки счёта
        std::string scoreString = std::to_string(field.getScore());
        if (scoreString.length() < 8)
            scoreString = multiString("0", 8 - (int)scoreString.length()) + scoreString; //Добавляем нули к счёту
        scoreText.setString(sf::String("Score: " + scoreString));

        win.clear(sf::Color::Black);
        win.draw(border);
        pixScr.render(&win);
        win.draw(scoreText);
        win.display();
    }

    return 0;
}
