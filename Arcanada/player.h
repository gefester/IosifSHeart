#include <SFML/Graphics.hpp>


using namespace sf;

////////////////////////////////////////////////////Класс игрока////////////////////////
class Player { // класс Игрока
private: int x, y; //координаты игрока
public:
    int w, h, dx, speed ;
    int dir, playerScore; //направление (direction) движения игрока
    String File; //файл с расширением
    Image image;//сфмл изображение
    Texture texture;//сфмл текстура
    Sprite sprite;//сфмл спрайт

    Player(String F, int X, int Y, int W, int H){ //Конструктор с параметрами для класса Player. При создании объекта класса мы будем задавать имя файла, координату Х и У, ширину и высоту
        dx=0;dir=0;playerScore = 0;
        File = F;//имя файла+расширение
        w = W; h = H;//высота и ширина
        image.loadFromFile("images/" + File);//запихиваем в image наше изображение вместо File мы передадим то, что пропишем при создании объекта. В нашем случае "hero.png" и получится запись идентичная image.loadFromFile("images/hero/png");
        texture.loadFromImage(image);//закидываем наше изображение в текстуру
        sprite.setTexture(texture);//заливаем спрайт текстурой
        x = X; y = Y;//координата появления спрайта
    }


    void update() //обновляем переменные объекта (новые координаты, с
        {
        switch (dir)//реализуем поведение в зависимости от направления. (каждая цифра соответствует направлению)
        {
        case 0: dx = -16; break;//по иксу задаем положительную скорость, по игреку зануляем. получаем, что персонаж идет только вправо
        case 1: dx = 16; break;//по иксу задаем отрицательную скорость, по игреку зануляем. получается, что персонаж идет только влево
        case 2: dx = 0; break;
        }
        x += dx;//то движение из прошлого урока. наше ускорение на время получаем смещение координат и как следствие движение
        sprite.setPosition(x,y);
        }

    void interactionWithWall(int leftWall, int rightWall){
        if(x > leftWall && x < leftWall+8)
            x = leftWall+4;
        if(x < rightWall && x > rightWall-8)
            x = rightWall-w-4;
	}

    int getCoordinateX(){
        return x;
    }
    int getCoordinateY(){
        return y;
    }
};
