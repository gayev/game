#ifndef _ENBUL_H_
#define _ENBUL_H_
class Enemy_Bul :public Entity{
public:
	int direction;
	Enemy_Bul(Image &image, float X, float Y, int W, int H, std::string  Name, int dir);

	void randomBulGenerate();
	void update(float time);
};
#endif