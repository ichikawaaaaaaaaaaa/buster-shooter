#include "Player.h"
#include "GoalText.h"
#include "Stage.h"
#include "Ball.h"
#include "config.h"
#include "Enemy.h"
#include "Vector2.h"
#include "GameOver.h"
#include "Jet.h"
#include "Spring.h"
#include "Walker.h"
#include "../Library/time.h"
#include <iostream>

float Gravity = 0.5f;     //重力加速度
float jumpHeight = 40 * 1.5;  //ジャンプの高さ
float V0 = -sqrtf(3.0f * Gravity * jumpHeight);//初速計算

// プレイヤーのライフと敵に触れた回数
//int life = 3;  // 初期ライフは3
//int enemyCollisionCount = 1; // 敵に触れた回数

// コンストラクタ

Player::Player()

{
    hImage = LoadGraph("data/image/Player.png");//キャラ画像の読み込み
    hImageMoveRight = LoadGraph("data/image/run.png");
    hImageMoveLeft = LoadGraph("data/image/run.png");
    hImageRightClick = LoadGraph("data/image/kenright.png");
    hImageLeftClick = LoadGraph("data/image/kenleft.png");
    position.x = 10;  //初期X座標
    position.y = 100; //初期座標
    velocity = 0; //初期速度
    prevJumpKey = false;   //初期ジャンプキー状態
    onGround = false;  //地上判定初期化
    // IsGoal = 0; //ゴールフラグ初期化
    goaled = 0;  //ゴール達成フラグ初期化
    scroll = 0;  //スクロール位置初期化

    //プレイヤーのライフ
    hImagelife = LoadGraph("data/image/heart.png");
    //blinkCounter = 0;
    life = 3;

	blinkCounter = 0;  // プレイヤーの点滅処理用カウンター
}

// 更新処理

void Player::Update()

{
    //<<<<<<< HEAD
   // std::list<GoalText*> gls = FindGameObjects<GoalText>(); // ゴール処理取得

    //=======
    //>>>>>> 22785fc63763e0367779acd117806a6a2e23f18e
    GetJoypadInputState(DX_INPUT_KEY_PAD1);
    int PadInput;

    GetJoypadAnalogInput(&XInput, &YInput, DX_INPUT_KEY_PAD1);
    PadInput = GetJoypadInputState(DX_INPUT_KEY_PAD1);

    // 右クリックが押されているかを検出
    if (GetMouseInput() & MOUSE_INPUT_RIGHT) {
        if (!prevRightClick) {  // クリックが新たに始まった時
            //isRightClicked = true;
        }
        prevRightClick = true;
    }
    else {
        prevRightClick = false;
        isRightClicked = false;  // 右クリックが離れた時
    }

    // 左クリックが押されているかを検出
    if (GetMouseInput() & MOUSE_INPUT_LEFT) {
        if (!prevLeftClick) {  // クリックが新たに始まった時
            //isLeftClicked = true;
        }
        prevLeftClick = true;
    }
    else {
        prevLeftClick = false;
        isLeftClicked = false;  // 左クリックが離れた時
    }

    Stage* s = FindGameObject<Stage>(); // ステージオブジェクト取得
    if (goaled) return; // ゴール済みの場合、処理を終了

    std::list<GoalText*> gls = FindGameObjects<GoalText>(); // ゴール処理取得
    for (auto g : gls) {
        //ゴールしていたら全ての処理を停止
        if (g->IsGoal == true)
        {
            return;
        }
    }

    // 画面外に出たらゲームオーバー
    int x = position.x;
    int y = position.y;
    if (y < 0 || y >= SCREEN_HEIGHT) {
        PlaySoundFile("data/sound/GameOver.mp3", DX_PLAYTYPE_NORMAL);
        SceneManager::ChangeScene("GameOver");
        return; // ゲームオーバー後の処理を終了
    }


    {
        Stage* s = FindGameObject<Stage>();
        if (goaled == false) {
            isMoving = false; // 毎フレーム初期化
            // 右移動（キーボード）
            if (CheckHitKey(KEY_INPUT_D)) {
                position.x += 5;
                int push = s->IsWallRight(position + VECTOR2(39, 0));
                position.x -= push;
                push = s->IsWallRight(position + VECTOR2(39, 39));
                position.x -= push;
                isMoving = true;
            }
            // 右移動（パッド）
            if (XInput > 100) {
                position.x += 5;
                int push = s->IsWallRight(position + VECTOR2(39, 0));
                position.x -= push;
                push = s->IsWallRight(position + VECTOR2(39, 39));
                position.x -= push;
                isMoving = true;
            }
            // 左移動（キーボード）
            if (CheckHitKey(KEY_INPUT_A)) {
                position.x -= 5;
                int push = s->IsWallLeft(position + VECTOR2(0, 0));
                position.x += push;
                push = s->IsWallLeft(position + VECTOR2(0, 29));
                position.x += push;
                isMoving = true;
            }
            // 左移動（パッド）
            if (XInput < -100) {
                position.x -= 5;
                int push = s->IsWallLeft(position + VECTOR2(0, 0));
                position.x += push;
                push = s->IsWallLeft(position + VECTOR2(0, 39));
                position.x += push;
                isMoving = true;
            }
        }
        // アニメーションの更新
        //animationCounter++;
        if (animationCounter >= animationSpeed) {
            animationCounter = 0;
            if (isMoving) {
                animationFrame = (animationFrame + 1) % 2;  // 移動時の2フレームアニメーション
            }
           else {
                animationFrame = (animationFrame + 1) % 2;  // 停止時も2フレームアニメーション
           }
       }


        //ジャンプ
        if (PadInput & PAD_INPUT_1 || CheckHitKey(KEY_INPUT_SPACE)) {
            if (prevJumpKey == false) {
                if (onGround) {
                    PlaySoundFile("data/sound/Jump.mp3", DX_PLAYTYPE_BACK);
                    // ジャンプ開始
                    velocity = V0; // 初速を決める
                }
            }
            prevJumpKey = true;
        }
        else {
            prevJumpKey = false;
        }

        position.y += velocity; // 座標には速度を足す
        velocity += Gravity; // 速度には重力を足す
        onGround = false;
        if (velocity >= 0) {
            int push = s->IsWallDown(position + VECTOR2(1, 38));
            // ジャンプの足元チェックは、１ドット下を見て、
            // 押し返す量は、-1する
            if (push > 0) { // 地面に触れたので
                velocity = 0.0f; // 地面に触ったら速度を0にする
                position.y -= push - 1; // 地面の上に押し返す
                onGround = true;
            }

            push = s->IsWallDown(position + VECTOR2(39, 40));
            if (push > 0) {
                velocity = 0.0f;
                position.y -= push - 1;
                onGround = true;
            }
        }
        else {
            int push = s->IsWallUP(position + VECTOR2(0, 0));
            if (push > 0) {
                velocity = 0.0f;
                position.y += push;
            }
            push = s->IsWallUP(position + VECTOR2(39, 0));
            if (push > 0) {
                velocity = 0.0f;
                position.y += push;
            }
        }
        if (position.x - s->scroll > 400) {
            s->scroll = position.x - 400;
        }
        if (position.x - s->scroll < 0) {
            s->scroll = position.x;
        }

        if (s->IsGoal(position + VECTOR2(20, 20))) {
            goaled = true;
            Instantiate<GoalText>();
        }
    }
    // 右にBallを投げる(PAD)
    // Xボタン PAD_INPUT_3
    if (PadInput & PAD_INPUT_2 || GetMouseInput() & MOUSE_INPUT_RIGHT) {

        if (!prevRightMouse) {
            PlaySoundFile("data/sound/Attack.mp3", DX_PLAYTYPE_BACK);
            Ball* ba = Instantiate<Ball>();   // ボールを生成
            ba->position = position;          // プレイヤーの位置に生成
            ba->position.y += 2;              // 少し下にずらす
            ba->velocity = VECTOR2(10.0f, 0.0f); // 右方向の速度
        }
        prevRightMouse = true;
    }

    else {
        prevRightMouse = false;
    }
    // 左にBallを投げる(PAD)
      // Aボタン PAD_INPUT_1
    if (PadInput & PAD_INPUT_3 || GetMouseInput() & MOUSE_INPUT_LEFT) {

        if (!prevLeftMouse) {
            PlaySoundFile("data/sound/Attack.mp3", DX_PLAYTYPE_BACK);
            Ball* ba = Instantiate<Ball>();  // ボールを生成
            ba->position = position;
            ba->position.y += 2;
            ba->velocity = VECTOR2(-10.0f, 0.0f); // 左方向の速度
        }
        prevLeftMouse = true;
    }

    else {
        prevLeftMouse = false;
    }

    // スクロール処理

    if (position.x - s->scroll > 400) {
        s->scroll = position.x - 400;
    }

    if (position.x - s->scroll < 200) {
        s->scroll = position.x - 200;
    }
    //衝突後の処理遅延時間
    if (blinkCounter > 0) {
        blinkCounter--;
        return; // 衝突判定を行わない
    }

    // 敵と衝突したかどうかを判定するフラグ
    bool collided = false;
    // プレイヤーと敵の衝突判定
    if (blinkCounter == 0) {
        std::list<Jet*> Jets = FindGameObjects<Jet>();
        for (Jet* j : Jets) {
            if (CircleHit(position, j->position, 45)) {
                // 1回だけライフを減らす
                if (!collided) {
                    collided = true;
                    life--; // ライフを1減らす
                    // ライフが0になったらゲームオーバー
                    if (life <= 0) {
                        SceneManager::ChangeScene("GameOver");
                        return; // ゲームオーバー後の処理を終了
                    }
                    blinkCounter = 50;
                    isBlinking = true;
                }
            }
        }
    }
    // 他の敵（SpringやWalker）に対する衝突判定も同様に行う
    std::list<Spring*> Springs = FindGameObjects<Spring>();
    for (Spring* s : Springs) {
        if (CircleHit(position, s->position, 37)) {
            if (!collided) {
                collided = true;
                life--; // ライフを1減らす
                if (life <= 0) {
                    SceneManager::ChangeScene("GameOver");
                    return; // ゲームオーバー後の処理を終了
                }
                blinkCounter = 50;
                isBlinking = true;
            }
        }
    }
    // 他の敵（Walker）に対する衝突判定
    std::list<Walker*> Walkers = FindGameObjects<Walker>();
    for (Walker* w : Walkers) {
        if (CircleHit(position, w->position, 34)) {
            if (!collided) {
                collided = true;
                life--; // ライフを1減らす
                if (life <= 0) {
                    SceneManager::ChangeScene("GameOver");
                    return; // ゲームオーバー後の処理を終了
                }
                blinkCounter = 50;
                isBlinking = true;
            }
        }
    }



}



void Player::Draw()


{
// ライフアイコンを描画（右から左に減らす）
    for (int i = 0; i < 3; i++) {
        // 最大3つのハート
        if (i < life) {
            // 左上に配置するため、(i * 40)で横位置を決定
            // 右から消えるようにするため、(i)を使って右から配置
            DrawGraph(40 * i, 34, hImagelife, TRUE);  // 左上に配置
        }

        if (blinkCounter % 5 != 0) {
            return;
        }


        Stage* s = FindGameObject<Stage>();

        int spriteWidth = 32;  // 画像の幅
        int spriteHeight = 40; // 画像の高さ
        int spriteX = animationFrame * spriteWidth; // アニメーションのX座標
        int imageToDraw = hImage;  // デフォルトの立ち状態画像



        // 横移動している場合、移動用アニメーションを適用
        if (XInput > 100 || CheckHitKey(KEY_INPUT_D)) {
            imageToDraw = hImageMoveRight; // 右移動の画像
        }
        else if (XInput < -100 || CheckHitKey(KEY_INPUT_A)) {
            imageToDraw = hImageMoveLeft; // 左移動の画像
        }
        DrawRectGraph(position.x - s->scroll, position.y, spriteX, 0, spriteWidth, spriteHeight, imageToDraw, TRUE);
    
    // クリック状態を優先
    if (isRightClicked) {
        imageToDraw = hImageRightClick;
    }
    else if (isLeftClicked) {
        imageToDraw = hImageLeftClick;
    }
    // 画像を描画（アニメーションフレーム考慮）
    DrawRectGraph(position.x - s->scroll, position.y, spriteX, 0, spriteWidth, spriteHeight, imageToDraw, TRUE);

   
    }
}

