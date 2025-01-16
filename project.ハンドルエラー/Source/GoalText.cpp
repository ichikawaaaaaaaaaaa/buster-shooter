#include "GoalText.h"
#include "../Library/time.h"
#include "Fader.h"
#include "Player.h"
#include "Stage.h"


GoalText::GoalText()
{
	hImage = LoadGraph("data/image/Goal.png");
	GameclearText = LoadGraph("data/image/GameClear.png");
	PushSpaceKey = LoadGraph("data/image/PushSpace.png");

	IsGoal = false;
	timer = 0.0f;

	scroll = 0;  //�X�N���[���ʒu������
}

GoalText::~GoalText()
{
}

void GoalText::Update()
{

	Stage* s = FindGameObject<Stage>(); // �X�e�[�W�I�u�W�F�N�g�擾

	//�����蔻��
	Player* p = FindGameObject<Player>();//����̃C���X�^���X���擾
	VECTOR2 playerPos = p->position;//����̍��W���擾

	if (CircleHit(playerPos, position, 20)) {//�~�̓����蔻��
		//DestroyMe();

		IsGoal = true;
	}
	if (IsGoal)
	{
		if (fadeStarted) {
			Fader* f = FindGameObject <Fader>();
			if (f->IsFinish()) {
				SceneManager::ChangeScene("TitleScene");
			}
			return;
		}

		timer += Time::DeltaTime();
		if (timer >= 2.5f) {
			if (CheckHitKey(KEY_INPUT_B)) {
				Fader* f = FindGameObject <Fader>();
				f->FadeOut(GetColor(0, 0, 0), 0.5f);
				fadeStarted = true;
				SceneManager::ChangeScene("TitleScene");
			}
		}
	}
}


void GoalText::Draw()
{
	Stage* s = FindGameObject<Stage>();//�G�̕\��������

	DrawGraph(position.x - s->scroll, position.y, hImage, TRUE);

	if(IsGoal)
	{
		
		DrawGraph(200, 200, GameclearText, TRUE);
		if (timer >= 1.0f) {


		
		}
		if (timer >= 2.0f) {
			DrawGraph(0, 0, PushSpaceKey, TRUE);
		}
	
	}
}