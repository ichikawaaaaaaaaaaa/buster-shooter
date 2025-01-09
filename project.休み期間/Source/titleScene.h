#pragma once
#include "../Library/sceneBase.h"

/// <summary>
/// �^�C�g���V�[��
/// 
/// �^�C�g����\�����āA�L�[����������v���C�V�[���Ɉڍs����B
/// </summary>
class TitleScene : public SceneBase {
public:
	TitleScene();
	~TitleScene();
	void Update() override;
	void Draw() override;
private:
	int hBGImage;		//	�摜�n���h��(�^�C�g�����)
	int hKeyImage;		//	�摜�n���h��(PUSH SPACE KEY)

	int Stage1Image;
	int Stage2Image;
	int Stage3Image;
	int Stage4Image;
	int Stage5Image;

	const float DRAW_KEY_WAIT = 1.0f;	//	[PUSH SPACE KEY]�\���Ԋu(1.0sec)
	bool isDrawKey;			//	[PUSH SPACE KEY]��\������/���Ȃ��t���O
	float DrawKeyTimer;		//	�^�C�}�[
};