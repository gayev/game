#include <sstream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cstdlib>
#include <list>
#include "map.h"
#include "entity.h"
#include "player.h"
#include "enemy.h"
#include "bullet.h"

int main()
	

{srand (time(NULL));

	sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
	sf::RenderWindow window(sf::VideoMode(1366, 768, desktop.bitsPerPixel), "Tank");
	sf::SoundBuffer buffer; 

	Font font;
	font.loadFromFile("CyrilicOld.ttf");
	Text text("", font, 30);
	text.setColor(Color::Blue);

	Image map_image;
	map_image.loadFromFile("images/map.png");
	Texture map;
	map.loadFromImage(map_image);
	Sprite s_map;
	s_map.setTexture(map);

	Clock clock;
	Clock gameTimeClock;
	int gameTime = 0;


	Image heroImage;
	heroImage.loadFromFile("images/tank.png"); 

	Image easyEnemyImage;
	easyEnemyImage.loadFromFile("images/tank2.png"); 

	Image BulletImage;
	BulletImage.loadFromFile("images/bullet.png");

	SoundBuffer shootBuffer;
	shootBuffer.loadFromFile("shoot.ogg");
	Sound shoot(shootBuffer);

	SoundBuffer killBuffer;
	killBuffer.loadFromFile("kill.ogg");
	Sound kill(killBuffer);

	SoundBuffer winBuffer;
	winBuffer.loadFromFile("win.ogg");
    Sound win(winBuffer);

	SoundBuffer loseBuffer;
	loseBuffer.loadFromFile("lose.ogg");
    Sound lose(loseBuffer);

	Music music;
    music.openFromFile("music.ogg");
    music.play();

	Player p(heroImage, 50, 50, 48, 48, "Player1");

	std::list<Entity*>  enemies; 
	std::list<Entity*>  Bullets; 
	std::list<Entity*>::iterator it; 
	std::list<Entity*>::iterator it_enemy; 
	 
	const int EnemyCount = 10;	
	int enemiesCount = 0;
	int kills = 0;

	//Заполняем список объектами врагами
	for (int i = 0; i < EnemyCount; i++)
	{
	float xr = 150 + rand() % 1000; 
	float yr = 150 + rand() % 400; 

		//создаем врагов и помещаем в список
		enemies.push_back(new Enemy(easyEnemyImage, xr, yr, 48, 48, "EasyEnemy"));
		enemiesCount += 1;
	}

	
while (window.isOpen())
{
	float time = clock.getElapsedTime().asMicroseconds();

	if (p.life) gameTime = gameTimeClock.getElapsedTime().asSeconds();

		clock.restart();
		time = time / 800;

		
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Space)
				{
					if (!p.health==0){
		Bullets.push_back(new Bullet(BulletImage, p.x, p.y, 24, 24, "Bullet", p.state));
					shoot.play();
					}
				}
			}
		}
	 
		p.update(time); 
		for (it_enemy = enemies.begin(); it_enemy != enemies.end(); it_enemy++)
		{
            (*it_enemy)->update(time);
							
		}
	
		
		for (it = Bullets.begin(); it != Bullets.end(); it++)
		{
			(*it)->update(time); 
		}

			// Столкновение врага с игроком
        if (p.life == true){
		for (it = enemies.begin(); it != enemies.end(); it++){
		if ((p.getRect().intersects((*it)->getRect())) && ((*it)->name == "EasyEnemy"))			
		            {p.health = 0;
					music.pause();
					lose.play();}
		}
        }

	
		// Проверяем попадание во врага
for (it_enemy = enemies.begin(); it_enemy != enemies.end(); it_enemy++){
for (it = Bullets.begin(); it != Bullets.end(); it++){
    if ((*it_enemy)->getRect().intersects((*it)->getRect()))
      { (*it_enemy)->health-=50;
        (*it)->health=0;
        (*it)->life=false;
		kill.play();}
}
}

if ( kills==EnemyCount){
			win.play();
			music.pause();}

		window.clear();


//Рисуем карту
for (int i = 0; i < HEIGHT_MAP; i++)
	for (int j = 0; j < WIDTH_MAP; j++)
	{
	if (TileMap[i][j] == ' ')  s_map.setTextureRect(IntRect(0, 0, 32, 32));
	if ((TileMap[i][j] == '0')) s_map.setTextureRect(IntRect(64, 0, 32, 32));

		s_map.setPosition(j * 32, i * 32);
		window.draw(s_map);
	}

	
		std::ostringstream playerHealthString, gameTimeString, killsString, encString;

		playerHealthString << p.health; gameTimeString << gameTime; killsString << kills, encString << EnemyCount;
		
		text.setString("Здоровье: " + playerHealthString.str() + "\nВремя игры: " + gameTimeString.str());
		text.setPosition(50, 0);
				if (p.health==0){
			text.setString(" GAME OVER!\n\nУбито врагов: " + killsString.str() + " из " + encString.str());
			text.setPosition(683, 384);
			text.setStyle(Text::Bold);}
				
				if ( kills==EnemyCount){
			text.setString(" WIN!\n\nУбито врагов: " + killsString.str());
			text.setPosition(683, 384);
			text.setStyle(Text::Bold);}
				
		window.draw(text);
		window.draw(p.sprite);

		
		//рисуем врагов
		for (it_enemy = enemies.begin(); it_enemy != enemies.end(); it_enemy++)
		{
			if ((*it_enemy)->life) 
			window.draw((*it_enemy)->sprite); 
		}


		for (it_enemy = enemies.begin(); it_enemy != enemies.end(); )
	{
		if ((*it_enemy)-> life == false)	{ it_enemy =enemies.erase(it_enemy);
		kills++;} 
			else  it_enemy++;		
	}

		
		//рисуем пули
		for (it = Bullets.begin(); it != Bullets.end(); it++)
		{
			if ((*it)->life) 
			window.draw((*it)->sprite); 
		}

		for (it = Bullets.begin(); it != Bullets.end(); )
	{
		if ((*it)-> life == false)	{ it = Bullets.erase(it); } 
			else  it++;		
	}


		window.display();
		
	}
	return 0;
}
