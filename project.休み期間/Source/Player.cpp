#include "Player.h"
#include "GoalText.h"
#include "Stage.h"
#include "Ball.h"
#include "config.h"
#include "Enemy.h"
#include "Vector2.h"

float Gravity = 0.5f;     //�d�͉����x
float jumpHeight = 20 * 2;  //�W�����v�̍���
float V0 = -sqrtf(3.0f * Gravity * jumpHeight);//�����v�Z

// �v���C���[�̃��C�t�ƓG�ɐG�ꂽ��
int life = 2;  // �������C�t��3
int enemyCollisionCount = 0; // �G�ɐG�ꂽ��

// �R���X�g���N�^

Player::Player()

{
    hImage = LoadGraph("data/image/Player.png");//�L�����摜�̓ǂݍ���
    hImageRightClick = LoadGraph("data/image/kenright.png");
    hImageLeftClick = LoadGraph("data/image/kenleft.png");
    position.x = 10;  //����X���W
    position.y = 100; //�������W
    velocity = 0; //�������x
    prevJumpKey = false;   //�����W�����v�L�[���
    onGround = false;  //�n�㔻�菉����
    IsGoal = 0; //�S�[���t���O������
    goaled = 0;  //�S�[���B���t���O������
    scroll = 0;  //�X�N���[���ʒu������
}

// �X�V����

void Player::Update()

{
    GetJoypadInputState(DX_INPUT_KEY_PAD1);
    int PadInput;

    GetJoypadAnalogInput(&XInput, &YInput, DX_INPUT_KEY_PAD1);
    PadInput = GetJoypadInputState(DX_INPUT_KEY_PAD1);

    // �E�N���b�N��������Ă��邩�����o
    if (GetMouseInput() & MOUSE_INPUT_RIGHT) {
        if (!prevRightClick) {  // �N���b�N���V���Ɏn�܂�����
            isRightClicked = true;
        }
        prevRightClick = true;
    }
    else {
        prevRightClick = false;
        isRightClicked = false;  // �E�N���b�N�����ꂽ��
    }

    // ���N���b�N��������Ă��邩�����o
    if (GetMouseInput() & MOUSE_INPUT_LEFT) {
        if (!prevLeftClick) {  // �N���b�N���V���Ɏn�܂�����
            isLeftClicked = true;
        }
        prevLeftClick = true;
    }
    else {
        prevLeftClick = false;
        isLeftClicked = false;  // ���N���b�N�����ꂽ��
    }

    Stage* s = FindGameObject<Stage>(); // �X�e�[�W�I�u�W�F�N�g�擾
    if (goaled) return; // �S�[���ς݂̏ꍇ�A�������I��

    // �v���C���[�ƓG�̏Փ˔���

    std::list<Enemy*> enemys = FindGameObjects<Enemy>();

    for (Enemy* e : enemys) {
        if (CircleHit(position, e->position, 56)) { // �Փ˂����ꍇ
            enemyCollisionCount++; // �Փˉ񐔂𑝉�

            // �Փˉ񐔂�2��ɂȂ����烉�C�t�����炷
            if (enemyCollisionCount >= 2) {

                life--; // ���C�t��1���炷

                enemyCollisionCount = 0; // �Փˉ񐔃��Z�b�g

                // ���C�t��0�ɂȂ�����Q�[���I�[�o�[
                if (life <= 0) {
                    // �Q�[���I�[�o�[�����i�����Ŏ��ۂɃQ�[���I�[�o�[�����������j
                    // �Ⴆ�΁A�Q�[���I�[�o�[��ʂ�\��������A�Q�[�����I�������肷��
                    // GameOver(); // �Q�[���I�[�o�[�������Ăяo��
                    return; // �Q�[���I�[�o�[��̏������I��
                }
            }
        }
    }

    // ���̈ړ�����

    if (CheckHitKey(KEY_INPUT_A)) {
        position.x -= 2;  //���ɁZ(����)�s�N�Z���ړ�

        //���̕ǂƂ̏Փ˔���

        int push = s->IsWallLeft(position + VECTOR2(0, 0));
        position.x += push; //�ǂ̉��ɐi�܂Ȃ��悤�Ɉʒu�𒲐�
        push = s->IsWallLeft(position + VECTOR2(0, 39));  //�L�����N�^�[�̉������ŏՓˊm�F
        position.x += push;
    }

    // ���̈ړ�����(PAD)

    if (XInput < -100) {
        position.x -= 2;
        //�L�����N�^�[�̍�����ŏՓ˃`�F�b�N

        int push = s->IsWallLeft(position + VECTOR2(0, 0));
        position.x += push;
        push = s->IsWallLeft(position + VECTOR2(0, 39));
        position.x += push;
    }

    // �E�̈ړ�����

    if (CheckHitKey(KEY_INPUT_D)) {

        position.x += 2;  //�E�ɁZ(����)�s�N�Z���ړ�

        //�E�̕ǂƂ̏Փ˔���

        int push = s->IsWallRight(position + VECTOR2(39, 0));

        position.x -= push;
        push = s->IsWallRight(position + VECTOR2(39, 39));
        position.x -= push;
    }

    // �E�̈ړ�����(PAD)

    if (XInput > 100) {
        position.x += 2;
        int push = s->IsWallRight(position + VECTOR2(39, 0));
        position.x -= push;
        push = s->IsWallRight(position + VECTOR2(39, 39));
        position.x -= push;
    }

    // �W�����v����

    if (CheckHitKey(KEY_INPUT_SPACE)) {
        if (!prevJumpKey && onGround) { //�n��ɂ��ăW�����v�L�[�������ꂽ�ꍇ
            velocity = V0;             //������ݒ�
        }
    }

    // �W�����v����(PAD)

    if (PadInput & PAD_INPUT_B) {
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
        int push = s->IsWallDown(position + VECTOR2(0, 39 + 1)); //�n�ʔ���

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
            push = s->IsWallUP(position + VECTOR2(39, 0));

            if (push > 0) {
                velocity = 0.0f;
                position.y += push;
            }
        }
        // �E���n�ʔ���

        push = s->IsWallDown(position + VECTOR2(39, 39));

        if (push > 0) {
            velocity = 0.0f;
            position.y -= push - 1;
            onGround = true; // �n�ʂɒ��n�����Ƃ��A�n�㔻���ON�ɂ���
        }
    }


    // Ball�𓊂��鏈��(PAD)
    if (PadInput & PAD_INPUT_Y || GetMouseInput() & MOUSE_INPUT_RIGHT) {

        if (!prevRightMouse) {
            Ball* ba = Instantiate<Ball>();   // �{�[���𐶐�
            ba->position = position;          // �v���C���[�̈ʒu�ɐ���
            ba->position.y += 5;              // �������ɂ��炷
            ba->velocity = VECTOR2(5.0f, 0.0f); // �E�����̑��x
        }
        prevRightMouse = true;
    }

    else {
        prevRightMouse = false;
    }
    // ������

    if (PadInput & PAD_INPUT_A || GetMouseInput() & MOUSE_INPUT_LEFT) {

        if (!prevLeftMouse) {
            Ball* ba = Instantiate<Ball>();  // �{�[���𐶐�
            ba->position = position;
            ba->position.y += 5;
            ba->velocity = VECTOR2(-5.0f, 0.0f); // �������̑��x

        }
        prevLeftMouse = true;
    }

    else {
        prevLeftMouse = false;
    }

    // �X�N���[������

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
    if (isRightClicked) {
        // �E�N���b�N����Ă���ꍇ�A�E�N���b�N�p�̉摜��`��
        DrawRectGraph(position.x - s->scroll, position.y, 0, 0, 32, 40, hImageRightClick, TRUE);
    }
    else {
        // �ʏ펞�̉摜��`��
        DrawRectGraph(position.x - s->scroll, position.y, 0, 0, 32, 40, hImage, TRUE);
        // ���C�t��\���i�Ⴆ�΁A��ʂ̏㕔�Ƀ��C�t�̃A�C�R����\������j

        if (isLeftClicked) {
            DrawRectGraph(position.x - s->scroll, position.y, 0, 0, 32, 40, hImageLeftClick, TRUE);
        }
        else {
            // �ʏ펞�̉摜��`��
            DrawRectGraph(position.x - s->scroll, position.y, 0, 0, 32, 40, hImage, TRUE);
            // ���C�t��\���i�Ⴆ�΁A��ʂ̏㕔�Ƀ��C�t�̃A�C�R����\������j

            for (int i = 0; i < life; i++) {
                // �����Ń��C�t�A�C�R����`�悷��R�[�h��ǉ�
                // ��: DrawGraph(10 + i * 30, 10, lifeIconImage, TRUE);
            }
        }
    }
}