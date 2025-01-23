#pragma once
#include "../Library/sceneBase.h"
#include "Stage.h"

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
};