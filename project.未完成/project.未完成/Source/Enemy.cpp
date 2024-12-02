#include "Stone.h"
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
	//�˓����Ă���Ƃ��́A�v���C���[��120�܂Œm��������
	if (attacking) {  
		Player* player = FindGameObject<Player>();
		VECTOR2 to = VSub(player->position, position);
		to = VNorm(to);


		position = VAdd(position, VScale(to, 2.0f));

		VECTOR2 d = VSub(player->position, position);
		if (VSize(d) < 120) {//������120�ȉ��ɂȂ�����
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
	// �΂Ɠ����蔻�������
	std::list<Stone*> stones = FindGameObjects<Stone>(); // �S���̐�
	for (Stone* st : stones) { // st�ɂP���΂̃|�C���^�[������
		// �@�΂̓����蔻��̒��S���W�����߂�
		VECTOR2 sCenter;
		sCenter.x = st->position.x + 8;
		sCenter.y = st->position.y + 8;
		// �A���̓����蔻��̒��S���W�����߂�
		VECTOR2 bCenter;
		bCenter.x = position.x + 32;
		bCenter.y = position.y + 32;
		// �@�ƇA�̉~�̓����蔻�������
		if (CircleHit(sCenter, bCenter, 32 + 8)) {
			dead = true;
			deadCounter = 0;
			patternY = 4;
			st->DestroyMe();
		}
	}
}


void Enemy::Draw()
{
	DrawRectGraph(position.x, position.y, patternX * 64, patternY * 64, 64, 64, hImage, TRUE);
}