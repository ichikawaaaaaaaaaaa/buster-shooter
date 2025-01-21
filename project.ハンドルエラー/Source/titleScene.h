#pragma once
#include "../Library/sceneBase.h"
#include "Vector2.h"

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

	const float DRAW_KEY_WAIT = 1.0f;	//	[PUSH SPACE KEY]�\���Ԋu(1.0sec)
	bool isDrawKey;			//	[PUSH SPACE KEY]��\������/���Ȃ��t���O
	float DrawKeyTimer;		//	�^�C�}�[

	int KeyimputCount;

	int XInput;             // �W���C�p�b�hX������
	int YInput;             // �W���C�p�b�hY������

	int StageCount;
	VECTOR2 position;       // �v���C���[�̍��W�iVector2�j
};