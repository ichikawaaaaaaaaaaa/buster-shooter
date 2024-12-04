#include "Ball.h"
#include "Vector2.h"
#include "Enemy.h"
#include "config.h"
#include "Player.h"

Enemy::Enemy()
{
	hImage = LoadGraph("data/image/mob.png");
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

Enemy::~Enemy()
{
}

void Enemy::Update()
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
		if (VSize(d) < 120) {//長さが120以下になったら
			attacking = false;
		}
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
}


void Enemy::Draw()
{
	DrawRectGraph(position.x, position.y, patternX * 64, patternY * 64, 64, 64, hImage, TRUE);
}