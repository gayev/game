#include <SFML/Graphics.hpp>
#include "entity.h"
#include "bullet.h"
#include "map.h"
using namespace sf;
Bullet::Bullet(Image &image, float X, float Y, int W, int H, std::string  Name, int dir) :Entity(image, X, Y, W, H, Name){
		x = X;
		y = Y;
		direction = dir;
		speed = 0.5;
		w = h = 24;
		life = true;
		if (health <= 0){ life = false; }
		//���� ������������� � ������������
	}
void Bullet::update(float time)
	{
		switch (direction)
		{
		case 0: dx = -speed; dy = 0;   break;// state = left
		case 1: dx = speed; dy = 0;   break;// state = right
		case 2: dx = 0; dy = -speed;   break;// state = up
		case 3: dx = 0; dy = speed;   break;// state = down
		}

		if (life){
			x += dx*time;//���� �������� ���� �� �
			y += dy*time;//�� �

		if (x <= 0) x = 20;// �������� ���� � ����� �����, ����� ��� ���������� ������ ��� �������� �� �������� �� ������ ����� � �� ���� ������ (������ ����� ���������!)
		if (y <= 0) y = 20;

		if (x >= 1366) x = 1346;// �������� ���� � ������ �����, ����� ��� ���������� ������ ��� �������� �� �������� �� ������ ����� � �� ���� ������ (������ ����� ���������!)
		if (y >= 768) y = 748;
				
		}


			for (int i = y / 32; i < (y + h) / 32; i++)//���������� �� ��������� �����
				for (int j = x / 32; j < (x + w) / 32; j++)
				{
					if (TileMap[i][j] == '0')//���� ������� ��� ������ �����, ��
						life = false;// �� ���� �������
				}

			sprite.setPosition(x + w / 2, y + h / 2);//�������� ������� ����
		}