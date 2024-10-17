#include "Player.h"
#include "Stage.h"

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

	if (CheckHitKey(KEY_INPUT_W))
	{
		position.y -= 2;

		int push = s->IswallUp(position + VECTOR2(0,0));
		posision.y -= push;

		int push = s->IswallUp(position + VECTOR2(39,0));
		posision.y -= push;

	}

	if (CheckHitKey(KEY_INPUT_S))
	{
		position.y += 2;
		//‰º‚É•Ç‚ª‚ ‚é‚©’²‚×‚é

		
		int push = s->IswallDown(position + VECTOR2(0, 39));
		posision.y -= push;

		int push = s->IswallDown(position + VECTOR2(39,39));
		posision.y -= push;
	}

	if (CheckHitKey(KEY_INPUT_A))
	{
		position.x -= 2;
		int push = s->IswallLeft(position + VECTOR2(0, 0));
		posision.x -= push;

		int push = s->IswallLeft(position + VECTOR2(0, 39));
		posision.x -= push;
	}

	if (CheckHitKey(KEY_INPUT_D))
	{
		position.x += 2;
		//‰E‚É•Ç‚ª‚ ‚é‚©’²‚×‚é
		int push = s->IswallRigth(position + VECTOR2(39, 0));
			posision.x -= push;
		
		int push = s->IswallRigth(position + VECTOR2(39, 39));
			posision.x -= push;
	}
}

void Player::Draw()
{
	DrawRectGraph(0, 0, 0, 0, 40, 40, hImage, TRUE);
}
