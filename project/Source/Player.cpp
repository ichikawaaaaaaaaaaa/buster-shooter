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
	//	//��
	//	int push = s->IsWallUP(position + VECTOR2(0, 0));
	//	position.y += push;
	//	push = s->IsWallUP(position + VECTOR2(39, 0));
	//	position.y += push;
	//}

	//if (CheckHitKey(KEY_INPUT_S)) {
	//	position.y += 4;
	//	//���ɂ��ׂ����邩���ׂ�
	//	int push = s->IsWallDown(position + VECTOR2(39, 0));
	//	position.y -= push;
	//	push = s->IsWallDown(position + VECTOR2(39, 39));
	//	position.y -= push;
	//}

	if (CheckHitKey(KEY_INPUT_A)) {
		position.x -= 4;
		//��
		int push = s->IsWallLeft(position + VECTOR2(0, 0));
		position.x -= push;
		push = s->IsWallLeft(position + VECTOR2(0, 39));
		position.x += push;
	}

	if (CheckHitKey(KEY_INPUT_D)) {
		position.x += 4;
		//�E�ɕǂ����邩���ׂ�
		int push = s->IsWallRight(position + VECTOR2(39, 0));
			position.x -= push;
		push = s->IsWallRight(position + VECTOR2(39, 39));
			position.x -= push;
	}

	if (CheckHitKey(KEY_INPUT_SPACE)) {
		if (prevJumpKey == false) {
			if (onGround) {
				//�W�����v����
				velocity = V0;//���������߂�
			}
		}
		prevJumpKey = true;
	}
	else{
		prevJumpKey = false;
	}

	position.y += velocity;
	velocity += Gravity;//���x�ɂ͏d�͂𑫂�
	onGround = false;




	if (velocity >= 0) {

		//���ɕǂ����邩���ׂ�
		int push = s->IsWallDown(position + VECTOR2(0, 40));//�����̂P��
		if (push > 0) {//�n�ʂɐG�ꂽ�̂�

			velocity = 0.0f;//�n�ʂɐG�ꂽ�瑬�x���O�ɂ���
			position.y -= push - 1;//�n�ʂ̏�ɉ����Ԃ�
			onGround = true;//�ڒn���Ă�
		}

		push = s->IsWallDown(position + VECTOR2(39, 40));
		if (push > 0) {
			velocity = 0.0f;
			position.y -= push - 1;
			onGround = true;//�ڒn���Ă�
		}
	}
	else {//�u���b�N�ɓ��Ԃ����炷��������
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
	//400�܂Ńv���C���[���s������X�N���[��

	//- s->scroll���Ă��邪scroll�ɒl�����Ă��Ȃ��̂Ł@������position.x(�v���C���[��x���W�j
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
