#include "Coin.h"
#include "Player.h"
#include "Stage.h"

Coin::Coin()
{
	//�R���X�g���N�^�[�ŊG�����[�h����
	hImage = LoadGraph("data/image/parts.png");
	got = false;
}

Coin::~Coin()
{
}

void Coin::Update()
{
	if (got) {
		position.y += v;
		v += 0.8f; //�����鑬��
		counter -= 1;
		if (counter == 0) {
			DestroyMe();
		}
		return;
	}

		//�����蔻��
		Player* p = FindGameObject<Player>();//����̃C���X�^���X���擾
		VECTOR2 playerPos = p->position;//����̍��W���擾

		if (CircleHit(playerPos, position, 40)) {//�~�̓����蔻��
			//DestroyMe();

			got = true;
			counter = 20;
			v = -9.0f; //���˂鍂��
	}
}

void Coin::Draw()
{
	Stage* s = FindGameObject<Stage>();
	//�G�̕\��������
	DrawRectGraph(position.x - s->scroll, position.y, 120, 0, 40, 40, hImage, TRUE);
}
