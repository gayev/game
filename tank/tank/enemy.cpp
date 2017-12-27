#include <SFML/Graphics.hpp>
#include "entity.h"
#include "enemy.h"
#include "map.h"
using namespace sf;

Enemy::Enemy(Image &image, float X, float Y, int W, int H, std::string Name):Entity(image, X, Y, W, H, Name){
	if (name == "EasyEnemy"){
		sprite.setTextureRect(IntRect(0, 0, w, h));
	direction= rand() % (3);
			speed = 0.1;
			dx = speed;
		}
	}


void Enemy::checkCollisionWithMap(float Dx, float Dy){
	for (int i = y / 32; i < (y + h) / 32; i++)//���������� �� ��������� �����
		for (int j = x / 32; j<(x + w) / 32; j++)
		{
			if (TileMap[i][j] == '0')//���� ������� - ������ �����
			{
				if (Dy > 0) {
					y = i * 32 - h;  dy = -0.1; 
					direction = rand() % (3); //����������� �������� �����
						}//�� Y 
				if (Dy < 0) {
					y = i * 32 + 32; dy = 0.1; 
					direction = rand() % (3);//����������� �������� ����� 
						}//������������ � �������� ������ 
				if (Dx > 0) {
					x = j * 32 - w; dx = -0.1; 
						direction = rand() % (3);//����������� �������� ����� 
						}//� ������ ����� �����
				if (Dx < 0) {
					x = j * 32 + 32; dx = 0.1; 
						direction = rand() % (3); //����������� �������� �����
						}// � ����� ����� �����
				}
			}
	}
	
void Enemy::update(float time)
{
		if (name == "EasyEnemy"){//��� ��������� � ����� ������ ������ ����� �����

		if (life) {//���������, ��� �� �����
		switch (direction)//�������� ��������� �������� � ����������� �� ���������
		{
		case 0:{//��������� ���� ������
		dx = speed;
		CurrentFrame += 0.005*time;
		if (CurrentFrame > 3) CurrentFrame -= 3;
		sprite.setTextureRect(IntRect(48 * int(CurrentFrame), 48, 48, 48));
		break;
		}
		case 1:{//��������� ���� �����
		dx = -speed;
		CurrentFrame += 0.005*time;
		if (CurrentFrame > 3) CurrentFrame -= 3;
		sprite.setTextureRect(IntRect(48 * int(CurrentFrame), 96, 48, 48));
		break;
		}
		case 2:{//���� �����
		dy = -speed;
		CurrentFrame += 0.005*time;
		if (CurrentFrame > 3) CurrentFrame -= 3;
		sprite.setTextureRect(IntRect(48 * int(CurrentFrame), 0, 48, 48));
		break;
		}
		case 3:{//���� ����
		dy = speed;
		CurrentFrame += 0.005*time;
		if (CurrentFrame > 3) CurrentFrame -= 3;
		sprite.setTextureRect(IntRect(48 * int(CurrentFrame), 144, 48, 48));
		break;
		}
		}

		x += dx*time; //�������� �� �X�
		checkCollisionWithMap(dx, 0);//������������ ������������ �� �

		y += dy*time; //�������� �� �Y�
		checkCollisionWithMap(0, dy);//������������ ������������ �� Y

		sprite.setPosition(x, y); //������ � ������� (x, y).

		if (health <= 0){life = false; }//���� ������ ������ 0, ���� ����� 0, �� �������
		}
		}
	}