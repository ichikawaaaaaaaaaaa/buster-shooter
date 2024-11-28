
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
	//突入しているときの、プレイヤーに120まで知数いたら
	if (attacking) {  //突入しているなら
		Player* player = FindGameObject<Player>();
		VECTOR2 to = VSub(player->position, position);

		to = VNorm(to);
		//to.x = player->position.x - position.x;
		//to.y = player->position.y - position.y;

		//toがベクトル(自分が移動したい向きと距離)
		//行きたい座標から自分の座標を引く

		
//		float theta = atan2(to.y, to.x);//プレイヤーの向き
//		float speed = 1.0f;
//		position.x += cos(theta)*speed;
//		position.y += sin(theta)*speed;

		//長さバージョン
		//toベクトルの長さを求めて、float lenに代入する
		//oat len = VSize(to);
		//toベクトルのx,yをそれぞれlenで割る=>toベクトルの長さを1にする

		position = VAdd(position, VScale(to, 2.0f));
		//oat speed = 2.0f;
		//position.x += to.x;
		//position.y += to.y;
		//sition = VAdd(position, VScale(to, speed));

		VECTOR2 d = VSub(player->position, position);
		if (VSize(d) < 120) {//長さが120以下になったら
			attacking = false;//突入をやめて、水平移動する。
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
}


void Enemy::Draw()
{
	DrawRectGraph(position.x, position.y, patternX * 64, patternY * 64, 64, 64, hImage, TRUE);
}