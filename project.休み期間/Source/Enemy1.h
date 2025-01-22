#pragma once
#include "../Library/gameObject.h"
#include "Vector2.h"

class Enemy1 : public GameObject {
public:
	Enemy1(); // �R���X�g���N�^�[ (�ŏ��Ɉ�񂾂��Ă΂��)
	~Enemy1(); // �f�X�g���N�^�[�i�Ō�Ɉ�񂾂��Ă΂��)
	void Update() override;
	void Draw() override;

	int hImage; // �摜
	VECTOR2 position;
	VECTOR2 speed;

	int patternX; //�\���p�^�[���̉��̔ԍ�
	int patternY; //�\���p�^�[���̏c�̔ԍ�

	int frameCounter;

	int timer; //���Ԃ𑪂邽��
	bool attacking; //�˓����Ă܂��B

	bool dead;
	int deadCounter;

	float velocity;
	bool onGround;
};
