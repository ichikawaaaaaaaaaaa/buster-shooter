#pragma once
#include "Vector2.h"
class Ball  {
public:
	Ball(float startX, float startY, float speedX, float speedY);  // �R���X�g���N�^
	void Update();  // �ʂ̈ʒu���X�V
	void Draw();    // �ʂ�`��
	VECTOR2 position;  // �ʂ̈ʒu
	VECTOR2 velocity;  // �ʂ̑��x
	bool active;       // �ʂ��L�����ǂ���
};