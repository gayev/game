#include <SFML/Graphics.hpp>
#include "entity.h"
#include "player.h"
#include "map.h"
using namespace sf;

Player::Player(Image &image, float X, float Y, int W, int H, std::string Name):Entity(image, X, Y, W, H, Name){
		state = stay;
		if (name == "Player1"){
			//Задаем спрайту один прямоугольник для вывода одного игрока. IntRect – для приведения типов
			sprite.setTextureRect(IntRect(0, 0, w, h));
		}
}

		void Player::control(){
		if (Keyboard::isKeyPressed(Keyboard::Left)) {
			state = left;
			speed = 0.1;
		}
		if (Keyboard::isKeyPressed(Keyboard::Right)) {
			state = right;
			speed = 0.1;
		}

		if (Keyboard::isKeyPressed(Keyboard::Up)) {
			state = up;
			speed = 0.1;
		}

		if (Keyboard::isKeyPressed(Keyboard::Down)) {
			state = down;
			speed = 0.1;
		}
		
	}

		void Player::checkCollisionWithMap(float Dx, float Dy)	{
	for (int i = y / 32; i < (y + h) / 32; i++)//проходимся по элементам карты
		for (int j = x / 32; j<(x + w) / 32; j++)
		{
			if (TileMap[i][j] == '0')//если элемент тайлик земли
			{
			if (Dy > 0) { y = i * 32 - h;  dy = 0; }//по Y 
			if (Dy < 0) { y = i * 32 + 32; dy = 0; }//столкновение с верхними краями 
			if (Dx > 0) { x = j * 32 - w; dx = 0; }//с правым краем карты
			if (Dx < 0) { x = j * 32 + 32; dx = 0; }// с левым краем карты
				}
				
			}
	}

void Player::update(float time) //метод "оживления/обновления" объекта класса.
	{
	if (life) {
		control();
		switch (state)
		{
		case right:{
			dx = speed;
			CurrentFrame += 0.005*time;
			if (CurrentFrame > 3) CurrentFrame -= 3;
			sprite.setTextureRect(IntRect(48 * int(CurrentFrame), 48, 48, 48));
				break;
			}
		case left:{
			dx = -speed;
			CurrentFrame += 0.005*time;
			if (CurrentFrame > 3) CurrentFrame -= 3;
			sprite.setTextureRect(IntRect(48 * int(CurrentFrame), 96, 48, 48));
			break;
			}
		case up:{
			dy = -speed;
			CurrentFrame += 0.005*time;
			if (CurrentFrame > 3) CurrentFrame -= 3;
			sprite.setTextureRect(IntRect(48 * int(CurrentFrame), 0, 48, 48));
			break;
			}
		case down:{
			dy = speed;
			CurrentFrame += 0.005*time;
			if (CurrentFrame > 3) CurrentFrame -= 3;
			sprite.setTextureRect(IntRect(48 * int(CurrentFrame), 144, 48, 48));
			break;
			}
		case stay:{
			dy = speed;
			dx = speed;
			break;
			}
			}

			x += dx*time;
			checkCollisionWithMap(dx, 0);
			y += dy*time;
			checkCollisionWithMap(0, dy);
			speed = 0;   
			sprite.setPosition(x, y); 

		if (health <= 0){ life = false; }

	}
}