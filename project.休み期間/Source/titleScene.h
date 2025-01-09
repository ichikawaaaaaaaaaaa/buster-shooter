#pragma once
#include "../Library/sceneBase.h"

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

	int Stage1Image;
	int Stage2Image;
	int Stage3Image;
	int Stage4Image;
	int Stage5Image;

	const float DRAW_KEY_WAIT = 1.0f;	//	[PUSH SPACE KEY]表示間隔(1.0sec)
	bool isDrawKey;			//	[PUSH SPACE KEY]を表示する/しないフラグ
	float DrawKeyTimer;		//	タイマー
};