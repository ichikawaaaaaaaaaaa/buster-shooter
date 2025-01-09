#include "Ball.h"
#include "Vector2.h"
#include "Enemy1.h"
#include "config.h"
#include "Player.h"
#include "Stage.h"

Enemy1::Enemy1()
{
	hImage = LoadGraph("data/image/komori.png");
	position.x = rand() % 1000;
	position.y = rand() % 700;
	speed.x = 0.0f;
	speed.y = 0.0f;
	patternX = 0;
	patternY = 0;
	frameCounter = 0;

	timer = 60;
	attacking = false;
}

Enemy1::~Enemy1()
{
}

void Enemy1::Update()
{
	if (dead) {
		deadCounter++;
		if (deadCounter >= 20) {
			DestroyMe();
		}
		return;
	}
	//突入しているときの、プレイヤーに120まで知数いたら
	if (attacking) {
		Player* player = FindGameObject<Player>();
		VECTOR2 to = VSub(player->position, position);
		to = VNorm(to);


		position = VAdd(position, VScale(to, 2.0f));

		VECTOR2 d = VSub(player->position, position);
		//if (VSize(d) < 120) {//長さが120以下になったら
			//attacking = false;
		//}
	}
	else {
		timer -= 1;
		if (timer == 0) {
			attacking = true;
			timer = rand() % (5 * 60) + 60;
		}
		position.x -= 3.0f;
		if (position.x < -64) {
			position.x = SCREEN_WIDTH;
			position.y = rand() % 700;
		}

		if (frameCounter += 1) {
			if (frameCounter % 10 == 0)
				patternY = (patternY + 1) % 4;
		}
	}

	std::list<Ball*> balls = FindGameObjects<Ball>();
	for (Ball* Ba : balls) {

		VECTOR2 sCenter;
		sCenter.x = Ba->position.x + 8;
		sCenter.y = Ba->position.y + 8;

		VECTOR2 bCenter;
		bCenter.x = position.x + 32;
		bCenter.y = position.y + 32;

		if (CircleHit(sCenter, bCenter, 32 + 8)) {
			dead = true;
			deadCounter = 0;
			patternY = 4;
			Ba->DestroyMe();
		}
	}
	Stage* s = FindGameObject<Stage>();

	{
		int push = s->IsWallLeft(position + VECTOR2(0, 0));
		position.x += push;
		push = s->IsWallLeft(position + VECTOR2(0, 63));
		position.x += push;
	}

	//右の壁との衝突判定
	{
		int push = s->IsWallRight(position + VECTOR2(63, 0));
		position.x -= push;
		push = s->IsWallRight(position + VECTOR2(63, 63));
		position.x -= push;

	}

	if (velocity >= 0) {
		// キャラクターの位置に応じた地面衝突判定
		int push = s->IsWallDown(position + VECTOR2(0, 63 + 1));//例(1111)はキャラクターの高さ

		if (push > 0) { // 地面に触れた場合
			velocity = 0.0f; // 速度を0にする
			position.y -= push - 1; // 地面に押し戻す
			onGround = true;        // 地上判定をON
		}

		else {
			// 頭の衝突判定
			push = s->IsWallUP(position + VECTOR2(0, 0));

			if (push > 0) {
				velocity = 0.0f;  // 頭に衝突した場合、速度を0にする
				position.y += push; // 頭上に押し戻す
			}

			push = s->IsWallUP(position + VECTOR2(63, 0));//例(1111)はキャラクターの高さ

			if (push > 0) {
				velocity = 0.0f;
				position.y += push;
			}
		}

		// 右足地面判定
		push = s->IsWallDown(position + VECTOR2(63, 63));//例(1111)はキャラクターの高さ
		if (push > 0) {
			velocity = 0.0f;
			position.y -= push - 1;
			onGround = true; // 地面に着地したとき、地上判定をONにする
		}
	}
}

void Enemy1::Draw()
{
	Stage* s = FindGameObject<Stage>();
	DrawRectGraph(position.x - s->scroll, position.y, patternX * 64, patternY * 30, 64, 30, hImage, TRUE);
}