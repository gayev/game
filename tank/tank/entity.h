#include <SFML/Graphics.hpp>
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

	Entity(Image &image, float X, float Y, int W, int H, std::string Name);
	
FloatRect getRect();
	virtual void update(float)=0;
};
#endif