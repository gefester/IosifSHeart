#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "start_menu.h"
#include "ball.h"


using namespace sf;

const int windowWeight = 1408, windowHeight = 928;   //высота и ширина окна
const int playerH = 32, playerW = 128, playerFromDown = 16;  //высота и ширина спрайта игрока, расстояние спрайта от нижней части экрана
const int ballH = 32, ballW = 32; //высота и ширина спрайта мяча
const int blockH = 32, blockW = 32;

RenderWindow window(VideoMode(windowWeight, windowHeight), "Arcanada, tak i nada");

void start_menu(){
    Font font;//шрифт
    font.loadFromFile("pixel.ttf");
    Text text("", font, 80);
    text.setStyle(sf::Text::Bold);

    Music music;
    music.openFromFile("audio/riot.ogg");
    music.setVolume(15);
    music.play();

    int n = 0;
    while(window.isOpen()){
        Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed || (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape) )
				window.close();
		}

		switch(n%7){
        case 0:
            text.setColor(Color::Green);
            break;
        case 1:
            text.setColor(Color::Red);
            break;
        case 2:
            text.setColor(Color::Blue);
            break;
        case 3:
            text.setColor(Color::Yellow);
            break;
        case 4:
            text.setColor(Color::Magenta);
            break;
        case 5:
            text.setColor(Color::White);
            break;
        case 6:
            text.setColor(Color::Cyan);
            break;
		}
		++n;

		if(Keyboard::isKeyPressed(Keyboard::F))
            break;

		window.clear();

		text.setString("PRESS 'F' TO START GAME");
		text.setPosition(270, windowHeight/3+70);
		window.draw(text);//рисую этот текст

		window.display();
    }
}

void game_over(){
    Font font;//шрифт
    font.loadFromFile("pixel.ttf");
    Text text("", font, 80);
    text.setColor(Color::White);
    text.setStyle(sf::Text::Bold);

    Music music;
    music.openFromFile("audio/predead.ogg");
    music.setVolume(15);
    music.play();
    Time t1 = milliseconds(3500);
    sleep(t1);
    music.openFromFile("audio/dead.ogg");
    music.setVolume(15);
    music.play();

    while(window.isOpen()){
        Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed || (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape) )
				window.close();
		}

		window.clear();

		text.setString("U r lOoOosEr\npress Esc to exit");
		text.setPosition(400, windowHeight/3);
		window.draw(text);//рисую этот текст

		window.display();
    }
}

std::vector<Block> blocks(99);

int main()
{
    window.setFramerateLimit(60);
	start_menu();

	Music music;
    music.openFromFile("audio/sample.ogg");
    music.setVolume(15);
    music.play();
    Time t1 = milliseconds(1000);
    sleep(t1);
    music.openFromFile("audio/tales.ogg");
    music.setVolume(15);
    music.play();

    ///////////////////////Объявление игровых объектов/////////////////////////////////////////////////////////////////////////
	Player p("platform.png", windowWeight-playerW*4,windowHeight-playerH-playerFromDown,playerW, playerH);//создаем объект p класса player,задаем "hero.png" как имя файла+расширение, далее координата Х,У, ширина, высота.
	Ball B("ball.png", (windowWeight-playerW), (windowHeight-playerH), ballW, ballH);   //создаем объект класса Ball

	int n = 0;
	for(int i = 0; i < WIDTH_MAP; ++i)
    for(int j = 0; j < HEIGHT_MAP; ++j){
            if(TileMap[j][i] == 's'){
                blocks[n].x = 32*i;
                blocks[n].y = 32*j;
                ++n;
            }
    }
    for(int i = 0; i < blocks.size(); ++i){
        blocks[i].File = "block.png";
        blocks[i].w = blockW;
        blocks[i].h = blockH;
        blocks[i].image.loadFromFile("images/" + blocks[i].File);
        blocks[i].texture.loadFromImage(blocks[i].image);
        blocks[i].sprite.setTexture(blocks[i].texture);
        blocks[i].sprite.setPosition(blocks[i].x, blocks[i].y);
    }

    Font font;//шрифт
    font.loadFromFile("pixel.ttf");
    Text text("", font, 30);
    text.setColor(Color::Green);
    text.setStyle(sf::Text::Bold | sf::Text::Underlined);
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Image map_image;//объект изображения для карты
	map_image.loadFromFile("images/map.png");//загружаем файл для карты
	Texture map;//объявляем текстуру карты
	map.loadFromImage(map_image);//заряжаем текстуру картинкой
	Sprite s_map;//создаём спрайт для карты
	s_map.setTexture(map);//заливаем текстуру спрайтом

	while (window.isOpen())
	{
        Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed || (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape) )
				window.close();
		}


		///////////////////////////////////////////Управление персонажем с анимацией////////////////////////////////////////////////////////////////////////
		if (Keyboard::isKeyPressed(Keyboard::Left)) {
			p.dir = 0;
		}
        else if (Keyboard::isKeyPressed(Keyboard::Right)) {
			p.dir = 1;
		}
		else
        {
            p.dir = 2;
        }


		///////////////////////////////////////////Столкновения мяча/////////////////////////////////////////////////////////////
        B.interactionWithWall(32, windowWeight-64, 32);
        B.interactionWithPlayer(p.getCoordinateX(), p.getCoordinateY(), playerW, playerH);

        for(int i = 0; i < blocks.size(); ++i){
            if(blocks[i].File != "broken")
                B.interactionWithBlock(blocks[i], p);
        }

        if(B.y > windowHeight){
            music.stop();
            game_over();
        }
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////
        p.interactionWithWall(32, windowWeight-64);

        //обновляем координаты и спрайты объектов
		p.update();
        B.update();
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

		for(int i = 0; i < blocks.size(); ++i)
            window.draw(blocks[i].sprite);

		window.draw(p.sprite);//рисуем спрайт объекта p класса player

		std::ostringstream playerScoreString;
		playerScoreString << p.playerScore;
		text.setString("Score:" + playerScoreString.str());
		text.setPosition(50, windowHeight-50);
		window.draw(text);//рисую этот текст

		window.draw(B.sprite); //рисуем спрайт объекта B класса Ball
		window.display();   //выводим всё нарисованное
	}

	return 0;
}
