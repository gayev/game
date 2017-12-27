#ifndef _ENEMY_H_
#define _ENEMY_H_
class Enemy :public Entity{
public:
	int direction;
	Enemy(Image &image, float X, float Y, int W, int H, std::string Name);
		
void checkCollisionWithMap(float Dx, float Dy);
	
	void update(float time);
	
};
#endif;