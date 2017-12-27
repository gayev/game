#ifndef _BULLET_H_
#define _BULLET_H_
class Bullet :public Entity{
public:
	int direction;
	Bullet(Image &image, float X, float Y, int W, int H, std::string  Name, int dir);


	void update(float time);
	
};
#endif