#pragma once

#include "../Library/gameObject.h"

#include "Vector2.h"

class Ball : public GameObject {

public:

    Ball();

    ~Ball();

    void Update() override;

    void Draw() override;

    int hImage;          // 通常のボール画像

    int hImageCollide;   // 衝突後のボール画像

    int currentImage;

    VECTOR2 position;

    VECTOR2 velocity;

    int goaled;          // ゴール達成フラグ

    int scroll;          // スクロール位置（仮想）


private:

    float Gravity = 0.0f;

    float traveledDistance = 0.0f;

};