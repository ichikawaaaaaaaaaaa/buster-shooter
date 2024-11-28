
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
	//�˓����Ă���Ƃ��́A�v���C���[��120�܂Œm��������
	if (attacking) {  //�˓����Ă���Ȃ�
		Player* player = FindGameObject<Player>();
		VECTOR2 to = VSub(player->position, position);

		to = VNorm(to);
		//to.x = player->position.x - position.x;
		//to.y = player->position.y - position.y;

		//to���x�N�g��(�������ړ������������Ƌ���)
		//�s���������W���玩���̍��W������

		
//		float theta = atan2(to.y, to.x);//�v���C���[�̌���
//		float speed = 1.0f;
//		position.x += cos(theta)*speed;
//		position.y += sin(theta)*speed;

		//�����o�[�W����
		//to�x�N�g���̒��������߂āAfloat len�ɑ������
		//oat len = VSize(to);
		//to�x�N�g����x,y�����ꂼ��len�Ŋ���=>to�x�N�g���̒�����1�ɂ���

		position = VAdd(position, VScale(to, 2.0f));
		//oat speed = 2.0f;
		//position.x += to.x;
		//position.y += to.y;
		//sition = VAdd(position, VScale(to, speed));

		VECTOR2 d = VSub(player->position, position);
		if (VSize(d) < 120) {//������120�ȉ��ɂȂ�����
			attacking = false;//�˓�����߂āA�����ړ�����B
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