#include "GoalText.h"
#include "../Library/time.h"
#include "Fader.h"
#include "Player.h"
#include "Stage.h"


GoalText::GoalText()
{
	hImage = LoadGraph("data/image/Goal.png");
	GameclearText = LoadGraph("data/image/GameClear.png");
	PushBbutton = LoadGraph("data/image/PushBbutton.png");
	PushBKey = LoadGraph("data/image/PushBkey.png");

	int PlaySoundFile(char* FileName, int PlayType);

	IsGoal = false;
	timer = 0.0f;

	scroll = 0;  //スクロール位置初期化
}

GoalText::~GoalText()
{
}

void GoalText::Update()
{
	GetJoypadInputState(DX_INPUT_KEY_PAD1);
	int PadInput;

	GetJoypadAnalogInput(&XInput, &YInput, DX_INPUT_KEY_PAD1);
	PadInput = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	Stage* s = FindGameObject<Stage>(); // ステージオブジェクト取得

	//当たり判定
	Player* p = FindGameObject<Player>();//相手のインスタンスを取得
	VECTOR2 playerPos = p->position;//相手の座標を取得

	if (CircleHit(playerPos, position, 20)) {//円の当たり判定
		//DestroyMe();
		PlaySoundCounter++;
		
		IsGoal = true;
	}
	if (IsGoal)
	{
		if (PlaySoundCounter == 1) {
			PlaySoundFile("data/sound/GameClear.mp3", DX_PLAYTYPE_BACK);
		}

		timer += 1.0f / 60;
		if (fadeStarted) {
			Fader* f = FindGameObject <Fader>();
					SceneManager::ChangeScene("TitleScene");
			return;
		}

		timer  += Time::DeltaTime();
		if (timer >= 2.5f) {
			if (PadInput & PAD_INPUT_2)  {
				Fader* f = FindGameObject <Fader>();
				f->FadeOut(GetColor(0, 0, 0), 0.5f);
				fadeStarted = true;
				SceneManager::ChangeScene("TitleScene");
			}


			if (PadInput & PAD_INPUT_2 || CheckHitKey(KEY_INPUT_B)) {
				{
					PlaySoundFile("data/sound/GameClear_TitileBack.mp3", DX_PLAYTYPE_NORMAL);
					Fader* f = FindGameObject <Fader>();
					f->FadeOut(GetColor(0, 0, 0), 0.5f);
					fadeStarted = true;
					SceneManager::ChangeScene("TitleScene");
				}
			}
		}
	}
	
}


void GoalText::Draw()
{
	Stage* s = FindGameObject<Stage>();//絵の表示をする

	DrawGraph(position.x - s->scroll, position.y, hImage, TRUE);

	if(IsGoal)
	{
		
		DrawGraph(160, 200, GameclearText, TRUE);
		if (timer >= 1.0f) {


		
		}
		if (timer >= 6.0f) {
			DrawGraph(397, 500, PushBKey, TRUE);
			DrawGraph(320, 600, PushBbutton, TRUE);
		}
	
	}
}
