#include <SFML/Graphics.hpp>
#ifndef _PLAYER_H_
#define _PLAYER_H_
using namespace sf;
class Player :public Entity {
public:
	Player(Image &image, float X, float Y, int W, int H, std::string Name);
		

	void control();
//Метод проверки столкновений с элементами карты
void checkCollisionWithMap(float Dx, float Dy);	

void update(float time);
};
#endif