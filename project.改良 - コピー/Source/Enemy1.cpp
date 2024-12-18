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
	//�˓����Ă���Ƃ��́A�v���C���[��120�܂Œm��������
	if (attacking) {
		Player* player = FindGameObject<Player>();
		VECTOR2 to = VSub(player->position, position);
		to = VNorm(to);


		position = VAdd(position, VScale(to, 2.0f));

		VECTOR2 d = VSub(player->position, position);
		//if (VSize(d) < 120) {//������120�ȉ��ɂȂ�����
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

	//�E�̕ǂƂ̏Փ˔���
	{
		int push = s->IsWallRight(position + VECTOR2(63, 0));
		position.x -= push;
		push = s->IsWallRight(position + VECTOR2(63, 63));
		position.x -= push;

	}

	if (velocity >= 0) {
		// �L�����N�^�[�̈ʒu�ɉ������n�ʏՓ˔���
		int push = s->IsWallDown(position + VECTOR2(0, 63 + 1));//��(1111)�̓L�����N�^�[�̍���

		if (push > 0) { // �n�ʂɐG�ꂽ�ꍇ
			velocity = 0.0f; // ���x��0�ɂ���
			position.y -= push - 1; // �n�ʂɉ����߂�
			onGround = true;        // �n�㔻���ON
		}

		else {
			// ���̏Փ˔���
			push = s->IsWallUP(position + VECTOR2(0, 0));

			if (push > 0) {
				velocity = 0.0f;  // ���ɏՓ˂����ꍇ�A���x��0�ɂ���
				position.y += push; // ����ɉ����߂�
			}

			push = s->IsWallUP(position + VECTOR2(63, 0));//��(1111)�̓L�����N�^�[�̍���

			if (push > 0) {
				velocity = 0.0f;
				position.y += push;
			}
		}

		// �E���n�ʔ���
		push = s->IsWallDown(position + VECTOR2(63, 63));//��(1111)�̓L�����N�^�[�̍���
		if (push > 0) {
			velocity = 0.0f;
			position.y -= push - 1;
			onGround = true; // �n�ʂɒ��n�����Ƃ��A�n�㔻���ON�ɂ���
		}
	}
}

void Enemy1::Draw()
{
	Stage* s = FindGameObject<Stage>();
	DrawRectGraph(position.x - s->scroll, position.y, patternX * 64, patternY * 30, 64, 30, hImage, TRUE);
}