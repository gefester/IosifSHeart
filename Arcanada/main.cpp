#include <SFML/Graphics.hpp>
#include "player.h"
#include "block.h"

using namespace sf;

const int windowWeight = 928, windowHeight = 544;   //высота и ширина окна
const int playerH = 32, playerW = 128, playerFromDown = 10;  //высота и ширина спрайта игрока, расстояние спрайта от нижней части экрана
const int ballH = 32, ballW = 32; //высота и ширина спрайта мяча
const int blockH = 32, blockW = 48;

bool condition = false;

vector<Block> blocks;//вектор для хранения объектов блоков

int main()
{
	RenderWindow window(VideoMode(windowWeight, windowHeight), "ZHOPA");

	window.setFramerateLimit(60);

    ///////////////////////Объявление игровых объектов/////////////////////////////////////////////////////////////////////////
	Player p("platform.png",(windowWeight-playerW)/2,windowHeight-playerH-playerFromDown,playerW, playerH);//создаем объект p класса player,задаем "hero.png" как имя файла+расширение, далее координата Х,У, ширина, высота.
	Ball B("ball.png", (windowWeight-playerW)/2, (windowHeight-playerH)/2, ballW, ballH);   //создаем объект класса Ball

	Block b1("block.png", 96, 96, blockW, blockH);
	Block b2("block.png", 96+96, 96, blockW, blockH);
	Block b3("block.png", 96+2*96, 96, blockW, blockH);
	Block b4("block.png", 96+3*96, 96, blockW, blockH);
	Block b5("block.png", 96+4*96, 96, blockW, blockH);
	Block b6("block.png", 96+5*96, 96, blockW, blockH);
	Block b7("block.png", 96+6*96, 96, blockW, blockH);
	Block b8("block.png", 96+7*96, 96, blockW, blockH);
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Image map_image;//объект изображения для карты
	map_image.loadFromFile("images/map.png");//загружаем файл для карты
	Texture map;//объявляем текстуру карты
	map.loadFromImage(map_image);//заряжаем текстуру картинкой
	Sprite s_map;//создаём спрайт для карты
	s_map.setTexture(map);//заливаем текстуру спрайтом

    int pixelCushion = 5;

	while (window.isOpen())
	{
        ///////////////////условия столкновений/////////////////////////////////
        bool leftWall = B.x > 32 && B.x < 32+pixelCushion;
        bool rightWall = B.x < windowWeight - 64 && B.x > windowWeight - 64-pixelCushion;
        bool topWall = B.y > 32 && B.y < 32+pixelCushion;
        bool platform = (B.y+ballH) > p.y && (B.y+ballH) < p.y + pixelCushion && B.x+ballW/2 > p.x && B.x+ballW/2 < p.x + playerW;
        ////////////////////////////////////////////////////////////////////////

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}


		///////////////////////////////////////////Управление персонажем с анимацией////////////////////////////////////////////////////////////////////////
		if (Keyboard::isKeyPressed(Keyboard::Left)) {
			p.dir = 0; p.speed = 15;
		}

		if (Keyboard::isKeyPressed(Keyboard::Right)) {
			p.dir = 1; p.speed = 15;
		}

		///////////////////////////////////////////Столкновения мяча/////////////////////////////////////////////////////////////
		if(condition == false){ //Если мяч еще не отталкивался от стены после последнего приближения к ней
            if(platform){
                //Взаимодействие с игроком: если до верха платформы меньше одного пикселя
                //и если координата х центра мяча в пределах х платформы
                B.dy = -B.dy;   //разворачиваем скорость по y
            }

            if(topWall)
                B.dy = -B.dy;
            if(leftWall)
                B.dx = -B.dx;
            if(rightWall)
                B.dx = -B.dx;

            condition = true;
		}
		else if(!topWall && !leftWall && !rightWall && !platform);  //если мяч вышел из зоны отталкивания, мы разрешаем ему оттолкнуться в следующий раз
            condition = false;

        for(int i = 0; i < 8; ++i){
            bool topBlock = (B.y+ballH) > 96 && (B.y+ballH) < 96 + pixelCushion && B.x+ballW/2 > 96+96*i && B.x+ballW/2 < 96+96*i + blockW;
            bool leftBlock = 0;
            bool rightBlock = 0;
            bool bottomBlock = B.y > 96+blockH && B.y < 96+blockH + pixelCushion && B.x+ballW/2 > 96+96*i && B.x+ballW/2 < 96+96*i + blockW;
            if(topBlock || bottomBlock)
                B.dy = -B.dy;
            if(leftBlock || rightBlock)
                B.dx = -B.dx;
        }
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////


        //обновляем координаты и спрайты объектов
		p.update();
        B.update();

        b1.update();
        b2.update();
        b3.update();
        b4.update();
        b5.update();
        b6.update();
        b7.update();
        b8.update();
		/////////////////////////////////////////////////////



		window.clear();
		/////////////////////////////Рисуем карту/////////////////////
		for (int i = 0; i < HEIGHT_MAP; i++)
		for (int j = 0; j < WIDTH_MAP; j++)
		{
			if (TileMap[i][j] == ' ')  s_map.setTextureRect(IntRect(0, 0, 32, 32)); //если встретили символ пробел, то рисуем 1й квадратик тайлсета
			if ((TileMap[i][j] == '0')) s_map.setTextureRect(IntRect(32, 0, 32, 32));//если встретили символ 0, то рисуем 2й квадратик тайлсета

			s_map.setPosition(j * 32, i * 32);  //задаем координаты отрисовки тайлов

			window.draw(s_map);//рисуем тайлы
		}

		window.draw(b1.sprite);
		window.draw(b2.sprite);
		window.draw(b3.sprite);
		window.draw(b4.sprite);
		window.draw(b5.sprite);
		window.draw(b6.sprite);
		window.draw(b7.sprite);
		window.draw(b8.sprite);


		window.draw(p.sprite);//рисуем спрайт объекта p класса player
		window.draw(B.sprite); //рисуем спрайт объекта B класса Ball
		window.display();   //выводим всё нарисованное
	}

	return 0;
}
