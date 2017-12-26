#ifndef _PLAYER_H_
#define _PLAYER_H_
class Player :public Entity {
public:
	Player(Image &image, float X, float Y, int W, int H, std::string Name) :Entity(image, X, Y, W, H, Name){
		state = stay;
		if (name == "Player1"){
			//Задаем спрайту один прямоугольник для вывода одного игрока. IntRect – для приведения типов
			sprite.setTextureRect(IntRect(0, 0, w, h));
		}
	}

	void control(){
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

//Метод проверки столкновений с элементами карты
void checkCollisionWithMap(float Dx, float Dy)	{
	for (int i = y / 32; i < (y + h) / 32; i++)
		for (int j = x / 32; j<(x + w) / 32; j++)
		{
			if (TileMap[i][j] == '0')
			{
			if (Dy > 0) { y = i * 32 - h;  dy = 0; }
			if (Dy < 0) { y = i * 32 + 32; dy = 0; }
			if (Dx > 0) { x = j * 32 - w; dx = 0; }
			if (Dx < 0) { x = j * 32 + 32; dx = 0; }
				}
				
			}
	}

void update(float time) //метод "оживления/обновления" объекта класса.
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
};
#endif