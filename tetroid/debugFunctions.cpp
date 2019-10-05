#include <SFML/Graphics.hpp>
#ifndef DB_FUNCTIONS
#define DB_FUNCTIONS

template <typename T>
extern void debugRect(T x, T y, T w, T h, sf::RenderWindow* win, sf::Color color = sf::Color::Magenta)
{
    sf::RectangleShape shape(Vector2f(w, h));
    shape.move(x, y);
    shape.setFillColor(sf::Color::Transparent);
    shape.setOutlineThickness(1.5f);
    shape.setOutlineColor(color);
    win->draw(shape);
}

template <typename T>
extern void debugRect(sf::Rect<T>* rect, sf::RenderWindow* win, sf::Color color = sf::Color::Magenta)
{
    return DebugRect(rect->left, rect->top, rect->width, rect->height, win, color);
}

template <typename T>
extern void debugRect(sf::Rect<T> rect, sf::RenderWindow* win, sf::Color color = sf::Color::Magenta)
{
    return DebugRect(&rect, win, color);
}

#endif
