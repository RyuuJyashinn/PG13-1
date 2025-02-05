#include "Enemy.h"
#include<Novice.h>

void Enemy::Reset(char* keys) {
	if (keys[DIK_R]) {

		Enemy::isAlive_ = true;
	}


}

void Enemy::Update() {
	if (Enemy::isAlive_) {
		posX_ += speed_;
		if (posX_ > 1260 || posX_ < 20) {
			speed_ = -speed_;
		}
	}
	
}

void Enemy::Draw() {
	if (Enemy::isAlive_) {
		Novice::DrawEllipse(static_cast<int>(Enemy::posX_), static_cast<int>(Enemy::posY_), static_cast<int>(Enemy::radius_), static_cast<int>(Enemy::radius_), 0.0f, RED, kFillModeSolid);

	}
	
}