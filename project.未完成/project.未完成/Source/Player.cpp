#include "Player.h"
#include "Stage.h"
#include "VECTOR2.h"

float Gravity = 0.1f;     //�d�͉����x
float jumpHeight = 20*2;  //�W�����v�̍���
float V0 = -sqrtf(3.0f * Gravity * jumpHeight);//�����v�Z

//�R���X�g���N�^
Player::Player()
{
	hImage = LoadGraph("data/image/chara.png");//�L�����摜�̓ǂݍ���
	position.x = 0;  //����X���W
	position.y = 0;  //����Y���W
	velocity = 0;    //�������x
	prevJumpKey = false;   //�����W�����v�L�[���
	onGround = false;  //�n�㔻�菉����
	IsGoal = 0;//�S�[���t���O������
	goaled = 0;  //�S�[���B���t���O������
	scroll = 0;  //�X�N���[���ʒu������
}

//�f�X�g���N�^
Player::~Player()
{
}

//�X�V����
void Player::Update()
{
	Stage* s = FindGameObject<Stage>();// �X�e�[�W�I�u�W�F�N�g�擾
	if (goaled)return;  // �S�[���ς݂̏ꍇ�A�������I��

	//���E�̈ړ�����

		//���̈ړ�����
	if (CheckHitKey(KEY_INPUT_A)) {
		position.x -= 2;  //���ɁZ(����)�s�N�Z���ړ�

		//���̕ǂƂ̏Փ˔���
		//�L�����N�^�[�̍�����̂ŏՓ˂��`�F�b�N����ꍇ
		int push = s->IsWallLeft(position + VECTOR2(0, 0));

		//�Փ˂����ꍇ�A���̉����Ԃ��ʁ@(�ǂɂԂ���Ȃ��悤�ɂ���)

		position.x += push; //�ǂ̉��ɐi�܂Ȃ��悤�Ɉʒu�𒲐�

		//�L�����N�^�[�̉��[�̈ʒu�ł��Փ˔�����s���ꍇ
		//�L�����N�^�[�̉������ŏՓ˂��m�F
		push = s->IsWallLeft(position + VECTOR2(0, 39));  //��(1111)�̓L�����N�^�[�̍���

		//�����ŕǂɂԂ����Ă����ꍇ�A���̉����Ԃ��ʂ��l�����Ĉʒu�𒲐�
		position.x += push;
	}

	//�E�̈ړ�����
	if (CheckHitKey(KEY_INPUT_D)) {
		position.x += 2;  //�E�ɁZ(����)�s�N�Z���ړ�

		//�E�̕ǂƂ̏Փ˔���
		//�L�����N�^�[�̉E����̈ʒu�ł̏Փ˂��`�F�b�N����ꍇ
		int push = s->IsWallRight(position + VECTOR2(39, 0)); //��(1111)�̓L�����N�^�[�̍���

		//�Փ˂����ꍇ�A���̉����Ԃ��ʁ@(�ǂɂԂ���Ȃ��悤�ɂ���)

		position.x -= push; //�ǂ̎�O�Ɉʒu��߂��Ē���

		//�L�����N�^�[�̉��[�̈ʒu�ł��Փ˔�����s���ꍇ
		//�L�����N�^�[�̉������Փ˂̊m�F
		push = s->IsWallRight(position + VECTOR2(39, 39)); //��(1111)�̓L�����N�^�[�̍���

		//�����ŕǂɂԂ����Ă����ꍇ�A���̉����Ԃ��ʂ��l�����Ĉʒu�𒲐�
		position.x -= push;
	}
	// �W�����v����
	if (CheckHitKey(KEY_INPUT_SPACE)) {
		if (!prevJumpKey && onGround) { //�n��ɂ��ăW�����v�L�[�������ꂽ�ꍇ

			velocity = V0;             //������ݒ�
		}
	}
	prevJumpKey = CheckHitKey(KEY_INPUT_SPACE); //���݂̃W�����v�L�[��Ԃ��L�^

	// ���������̈ړ��Əd�͏���
	position.y += velocity;  //���W�ɑ��x�����Z
	velocity += Gravity;     //���x�ɏd�͂����Z
	onGround = false;        //�n�ʐڐG�t���O�����Z�b�g

	// �n�ʏՓ˔���
	if (velocity >= 0) {
		// �L�����N�^�[�̈ʒu�ɉ������n�ʏՓ˔���
		int push = s->IsWallDown(position + VECTOR2(0, 39 + 1));//��(1111)�̓L�����N�^�[�̍���

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

			push = s->IsWallUP(position + VECTOR2(39, 0));//��(1111)�̓L�����N�^�[�̍���

			if (push > 0) {
				velocity = 0.0f;
				position.y += push;
			}
		}

		// �E���n�ʔ���
		push = s->IsWallDown(position + VECTOR2(39, 39));//��(1111)�̓L�����N�^�[�̍���
		if (push > 0) {
			velocity = 0.0f;
			position.y -= push - 1;
			onGround = true; // �n�ʂɒ��n�����Ƃ��A�n�㔻���ON�ɂ���
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
