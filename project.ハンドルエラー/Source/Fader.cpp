#include "Fader.h"
#include "config.h"

Fader::Fader()
{
	alpha = 0;
	fadeTime = 0;
	timer = 0;
}

Fader::~Fader()
{
}

void Fader::Update()
{
	if (timer < fadeTime) {//�I�����Ԃ𒴂��Ȃ��悤��
		timer += 1.0f / 60.0f;
		alpha = 255 / fadeTime * timer;//alpha�����߂�
	}
	
}

void Fader::Draw()
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);//�������ɂ���
	DrawBox(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT,
		fadeColor, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);//��������߂�
}

void Fader::FadeOut(unsigned int color, float time)
{
	alpha = 0;
	fadeColor = color;
	fadeTime = time;
	timer = 0;
}

bool Fader::IsFinish() const
{
	if (timer >= fadeTime) {
		return true;
	}
	
}
