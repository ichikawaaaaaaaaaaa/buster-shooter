#pragma once
#include "../Library/sceneBase.h"
#include "Vector2.h"

/// <summary>
/// タイトルシーン
/// 
/// タイトルを表示して、キーを押したらプレイシーンに移行する。
/// </summary>
class TitleScene : public SceneBase {
public:
	TitleScene();
	~TitleScene();
	void Update() override;
	void Draw() override;
private:
	int hBGImage;		//	画像ハンドル(タイトル画面)
	int hKeyImage;		//	画像ハンドル(PUSH SPACE KEY)

	int BackScreen;

	int Stage1Image;
	int Stage2Image;
	int Stage3Image;
	int Stage4Image;
	int Stage5Image;

	int StageFlame;
	
	int StagePositipnX;
	int StagePositipnY;

	int Stageflame;

	const float DRAW_KEY_WAIT = 1.0f;	//	[PUSH SPACE KEY]表示間隔(1.0sec)
	bool isDrawKey;			//	[PUSH SPACE KEY]を表示する/しないフラグ
	float DrawKeyTimer;		//	タイマー

	int KeyimputCount;

	int XInput;             // ジョイパッドX軸入力
	int YInput;             // ジョイパッドY軸入力

	int StageCount;
	VECTOR2 position;       // プレイヤーの座標（Vector2）
};