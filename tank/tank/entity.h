#ifndef _ENTITY_H_
#define _ENTITY_H_
using namespace sf;
class Entity {
public:
	enum { left, right, up, down, stay} state;
	float dx, dy, x, y, speed, moveTimer;
	int w, h, health; 
	bool life; 
	Texture texture;
	Sprite sprite;
	float CurrentFrame;
	std::string name;

	Entity(Image &image, float X, float Y, int W, int H, std::string Name){
		x = X; y = Y; 
		w = W; h = H; 
		name = Name; 
		moveTimer = 0;
		dx = 0; dy = 0; 
		speed = 0;

		CurrentFrame = 0;
		health = 100;
		life = true; 
		texture.loadFromImage(image); 
		sprite.setTexture(texture); 
	}

FloatRect getRect(){//метод получения прямоугольника. его коорд, размеры (шир,высот).
	FloatRect FR(x, y, w, h);
	return FR;
	//эта ф-ция нужна для проверки пересечений 
	}
	virtual void update(float time) = 0;
};
#endif