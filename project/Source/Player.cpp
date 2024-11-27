#include "Player.h"
#include "Stage.h"
#include "VECTOR2.h"

const float Gravity = 0.3f;
const float JumpHeight = 40 * 2;
const float V0 = -sqrtf(2.0f * Gravity * JumpHeight);

Player::Player()
{
	hImage = LoadGraph("data/image/chara.png");
	position.x = 0;
	position.y = 0;
}

Player::~Player()
{
}

void Player::Update()
{
	Stage* s = FindGameObject<Stage>();
	//if (CheckHitKey(KEY_INPUT_W)) {
	//	position.y -= 4;
	//	//上
	//	int push = s->IsWallUP(position + VECTOR2(0, 0));
	//	position.y += push;
	//	push = s->IsWallUP(position + VECTOR2(39, 0));
	//	position.y += push;
	//}

	//if (CheckHitKey(KEY_INPUT_S)) {
	//	position.y += 4;
	//	//下にかべがあるか調べる
	//	int push = s->IsWallDown(position + VECTOR2(39, 0));
	//	position.y -= push;
	//	push = s->IsWallDown(position + VECTOR2(39, 39));
	//	position.y -= push;
	//}

	if (CheckHitKey(KEY_INPUT_A)) {
		position.x -= 4;
		//左
		int push = s->IsWallLeft(position + VECTOR2(0, 0));
		position.x -= push;
		push = s->IsWallLeft(position + VECTOR2(0, 39));
		position.x += push;
	}

	if (CheckHitKey(KEY_INPUT_D)) {
		position.x += 4;
		//右に壁があるか調べる
		int push = s->IsWallRight(position + VECTOR2(39, 0));
			position.x -= push;
		push = s->IsWallRight(position + VECTOR2(39, 39));
			position.x -= push;
	}

	if (CheckHitKey(KEY_INPUT_SPACE)) {
		if (prevJumpKey == false) {
			if (onGround) {
				//ジャンプする
				velocity = V0;//初速を決める
			}
		}
		prevJumpKey = true;
	}
	else{
		prevJumpKey = false;
	}

	position.y += velocity;
	velocity += Gravity;//速度には重力を足す
	onGround = false;




	if (velocity >= 0) {

		//下に壁があるか調べる
		int push = s->IsWallDown(position + VECTOR2(0, 40));//足元の１つ下
		if (push > 0) {//地面に触れたので

			velocity = 0.0f;//地面に触れたら速度を０にする
			position.y -= push - 1;//地面の上に押し返す
			onGround = true;//接地してる
		}

		push = s->IsWallDown(position + VECTOR2(39, 40));
		if (push > 0) {
			velocity = 0.0f;
			position.y -= push - 1;
			onGround = true;//接地してる
		}
	}
	else {//ブロックに頭ぶつけたらすぐ落ちる
		int push = s->IsWallUP(position + VECTOR2(0, 0));
		if (push > 0) {
			velocity = 0.0f;
			position.y += push;
		}

		push = s->IsWallUP(position + VECTOR2(39, 0));
		if (push > 0) {
			velocity = 0.0f;
			position.y += push;
		}
	}
	//400までプレイヤーが行ったらスクロール

	//- s->scrollしているがscrollに値を入れていないので　ただのposition.x(プレイヤーのx座標）
	if (position.x - s->scroll > 400) {
		s->scroll = position.x - 400;
	}


	if (position.x - s->scroll < 200) {
		s->scroll = position.x - 200;
	}

}

void Player::Draw()
{
	Stage* s = FindGameObject<Stage>();
	DrawRectGraph(position.x - s->scroll, position.y , 0, 0, 40, 40, hImage, TRUE);
}
