#pragma once
class Enemy {
public:
	static int isAlive_;
	int posX_;
	int posY_;
	int radius_;
	int speed_;
public:
	Enemy(int posX, int posY, int speed, int radius) : posX_(posX), posY_(posY), speed_(speed), radius_(radius) {};
	void Update();
	void Draw();
	void Reset(char* keys);
};