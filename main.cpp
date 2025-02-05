#include <Novice.h>
#include"Enemy.h"
#include"Player.h"
#include"Bullet.h"
#include<cmath>
const char kWindowTitle[] = "学籍番号";
int Enemy::isAlive_ = 1;


bool isBulletHitEnemy(Enemy enemy, Bullet bullet) {
	double dis = sqrt((enemy.posX_ - bullet.posX_) * (enemy.posX_ - bullet.posX_) + (enemy.posY_ - bullet.posY_) * (enemy.posY_ - bullet.posY_));
	bool result;
	if ((int)dis <= (enemy.radius_ + bullet.radius_)) {
		result = true;

	} else {
		result = false;
	}
	return result;
}

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};


	Enemy *enemy[2];

	enemy[0] = new Enemy(300, 60, 5, 15);
	enemy[1] = new Enemy(640, 360, 5, 20);

	Player* player = new Player(600,600,5,20);
	for (int i = 0; i < MAX_BULLETS; i++) {
		player->bullets_[i]->isShot_ = false;
		player->bullets_[i]->posX_ = 0;
		player->bullets_[i]->posY_ = 0;
		player->bullets_[i]->speed_ = 20;
		player->bullets_[i]->radius_ = 10;
}
	
	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///
		for (int i = 0; i < 2; i++) {
			enemy[i]->Update();

		}
		player->Update(keys,preKeys);

		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < MAX_BULLETS; j++) {
				if (isBulletHitEnemy(*enemy[i], *player->bullets_[j])) {
					Enemy::isAlive_ = false;
				}

			}

		}
		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///
		for (int i = 0; i < 2; i++) {
			enemy[i]->Draw();

		}
		player->Draw();

		if (keys[DIK_R] && !preKeys[DIK_R]) {

			Enemy::isAlive_ = true;

		}

		Novice::ScreenPrintf(10, 10, "enemyA isAlive=%d", enemy[0]->isAlive_);
		Novice::ScreenPrintf(10, 30, "enemyB isAlive=%d", enemy[1]->isAlive_);
		Novice::ScreenPrintf(10, 50, "WASD:player move");
		Novice::ScreenPrintf(10, 70, "SHOT:SPACE");
		Novice::ScreenPrintf(10, 90, "enemy respawn:R");
		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	delete enemy[0];
	delete enemy[1];

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
