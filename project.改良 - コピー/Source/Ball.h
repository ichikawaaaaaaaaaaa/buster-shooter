#pragma once

#include "../Library/gameObject.h"

#include "Vector2.h"

class Ball : public GameObject {

public:

    Ball();

    ~Ball();

    void Update() override;

    void Draw() override;

    int hImage;          // �ʏ�̃{�[���摜

    int hImageCollide;   // �Փˌ�̃{�[���摜

    int currentImage;

    VECTOR2 position;

    VECTOR2 velocity;

    int goaled;          // �S�[���B���t���O

    int scroll;          // �X�N���[���ʒu�i���z�j


private:

    float Gravity = 0.0f;

    float traveledDistance = 0.0f;

};