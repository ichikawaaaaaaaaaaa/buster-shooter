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





float Gravity = 2.0f;     //重力加速度
float jumpHeight = 40* 2.0;  //ジャンプの高さ
float V0 = -sqrtf(3.0f * Gravity * jumpHeight);//初速計算

// プレイヤーのライフと敵に触れた回数
int life = 2;  // 初期ライフは3
int enemyCollisionCount = 1; // 敵に触れた回数

// コンストラクタ

Player::Player()

{
    hImage = LoadGraph("data/image/Player.png");//キャラ画像の読み込み
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
    blinkCounter = 0;
    life = 3;
}

// 更新処理

void Player::Update()

{




    //<<<<<<< HEAD


    std::list<GoalText*> gls = FindGameObjects<GoalText>(); // ゴール処理取得
    for (auto g : gls) {
        //ゴールしていたら全ての処理を停止
        if (g->IsGoal == true)
        {
            return;
        }
    }






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

    // プレイヤーと敵の衝突判定

    //std::list<Enemy*> enemys = FindGameObjects<Enemy>();
    if (blinkCounter == 0) {
        std::list<Jet*> Jets = FindGameObjects<Jet>();
        for (Jet* j : Jets) {
            if (CircleHit(position, j->position, 56)) {

                //	アルファ値の計算
                blinkCounter = 30;
                // 衝突回数が2回になったらライフを減らす
                if (enemyCollisionCount >= 2) {

                    life--; // ライフを1減らす

                    enemyCollisionCount = 0; // 衝突回数リセット

                    // ライフが0になったらゲームオーバー
                    if (life <= 0) {
                        // ゲームオーバー処理（ここで実際にゲームオーバー処理を書く）
                        // 例えば、ゲームオーバー画面を表示したり、ゲームを終了したりする
                        // GameOver(); // ゲームオーバー処理を呼び出す
                        SceneManager::ChangeScene("GameOver");
                        return; // ゲームオーバー後の処理を終了
                    }
                    std::list<GoalText*> gls = FindGameObjects<GoalText>(); // ゴール処理取得
                    for (auto g : gls) {
                        //ゴールしていたら全ての処理を停止
                        if (g->IsGoal == true)
                        {
                            return;
                        }
                    }
                }
            }
        }
        std::list<Spring*> Springs = FindGameObjects<Spring>();
        for (Spring* s : Springs) {
            if (CircleHit(position, s->position, 56)) {

                //	アルファ値の計算
                blinkCounter = 30;
                // 衝突回数が2回になったらライフを減らす
                if (enemyCollisionCount >= 2) {

                    life--; // ライフを1減らす

                    enemyCollisionCount = 0; // 衝突回数リセット

                    // ライフが0になったらゲームオーバー
                    if (life <= 0) {
                        // ゲームオーバー処理（ここで実際にゲームオーバー処理を書く）
                        // 例えば、ゲームオーバー画面を表示したり、ゲームを終了したりする
                        // GameOver(); // ゲームオーバー処理を呼び出す
                        SceneManager::ChangeScene("GameOver");
                        return; // ゲームオーバー後の処理を終了
                    }
                    std::list<GoalText*> gls = FindGameObjects<GoalText>(); // ゴール処理取得
                    for (auto g : gls) {
                        //ゴールしていたら全ての処理を停止
                        if (g->IsGoal == true)
                        {
                            return;
                        }
                    }
                }
            }
        }        std::list<Walker*> Walkers = FindGameObjects<Walker>();
        for (Walker* w : Walkers) {
            if (CircleHit(position, w->position, 56)) {

                //	アルファ値の計算
                blinkCounter = 30;
                // 衝突回数が2回になったらライフを減らす
                if (enemyCollisionCount >= 2) {

                    life--; // ライフを1減らす

                    enemyCollisionCount = 0; // 衝突回数リセット

                    // ライフが0になったらゲームオーバー
                    if (life <= 0) {
                        // ゲームオーバー処理（ここで実際にゲームオーバー処理を書く）
                        // 例えば、ゲームオーバー画面を表示したり、ゲームを終了したりする
                        // GameOver(); // ゲームオーバー処理を呼び出す
                        SceneManager::ChangeScene("GameOver");
                        return; // ゲームオーバー後の処理を終了
                    }
                    std::list<GoalText*> gls = FindGameObjects<GoalText>(); // ゴール処理取得
                    for (auto g : gls) {
                        //ゴールしていたら全ての処理を停止
                        if (g->IsGoal == true)
                        {
                            return;
                        }
                    }
                }
            }
        }
    }
    // 画面外に出たらゲームオーバー
    int x = position.x;
    int y = position.y;
    if (y < 0 || y >= SCREEN_HEIGHT) {
        SceneManager::ChangeScene("GameOver");
        return; // ゲームオーバー後の処理を終了
    }

    {
        Stage* s = FindGameObject<Stage>();
        if (goaled == false) {

            //右移動
            if (CheckHitKey(KEY_INPUT_A)) {
                position.x -= 7;
                int push = s->IsWallLeft(position + VECTOR2(0, 0));
                position.x += push;
                push = s->IsWallLeft(position + VECTOR2(0, 29));
                position.x += push;
            }

            // 右の移動処理(PAD)

            if (XInput > 100) {
                position.x += 7;
                int push = s->IsWallRight(position + VECTOR2(39, 0));
                position.x -= push;
                push = s->IsWallRight(position + VECTOR2(39, 39));
                position.x -= push;
            }

            //左移動
            if (CheckHitKey(KEY_INPUT_D)) {
                position.x += 7;
                // 右に壁があるか調べる
                int push = s->IsWallRight(position + VECTOR2(39, 0));
                position.x -= push;
                push = s->IsWallRight(position + VECTOR2(39, 39));
                position.x -= push;
            }

            // 左の移動処理(PAD)

            if (XInput < -100) {
                position.x -= 7;
                //キャラクターの左上隅で衝突チェック

                int push = s->IsWallLeft(position + VECTOR2(0, 0));
                position.x += push;
                push = s->IsWallLeft(position + VECTOR2(0, 39));
                position.x += push;
            }


        }

        //ジャンプ
        if (PadInput & PAD_INPUT_1 || CheckHitKey(KEY_INPUT_SPACE)) {
            if (prevJumpKey == false) {
                if (onGround) {
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
}


void Player::Draw()

{
    for (int i = 0; i < life; i++) {
        DrawGraph(i * 40, 34, hImagelife, TRUE);
        // ここでライフアイコンを描画するコードを追加
        // 例: DrawGraph(10 + i * 30, 10, lifeIconImage, TRUE);
    }
    if (blinkCounter > 0) {
        blinkCounter--;
    }
    if (blinkCounter % 2 != 0) {
        return;
    }



    Stage* s = FindGameObject<Stage>();
    if (isRightClicked) {
        // 右クリックされている場合、右クリック用の画像を描画
        DrawRectGraph(position.x - s->scroll, position.y, 0, 0, 32, 40, hImageRightClick, TRUE);
    }
    else {
        // 通常時の画像を描画
        DrawRectGraph(position.x - s->scroll, position.y, 0, 0, 32, 40, hImage, TRUE);
        // ライフを表示（例えば、画面の上部にライフのアイコンを表示する）

        if (isLeftClicked) {
            DrawRectGraph(position.x - s->scroll, position.y, 0, 0, 32, 40, hImageLeftClick, TRUE);
        }
        else {
            // 通常時の画像を描画
            DrawRectGraph(position.x - s->scroll, position.y, 0, 0, 32, 40, hImage, TRUE);
            // ライフを表示（例えば、画面の上部にライフのアイコンを表示する）
            
            }
           
        }

    }


    //alpha += (int)(ofset * Time::DeltaTime());

    //	前フレームからの経過時間を取得
    //DrawStertTimer += Time::DeltaTime();
    //	一定時間(DRAW_STERT_WAIT)経過したら、アルファ値の加算・減算を切りかえる
    //if (DrawStertTimer >= DRAW_STERT_WAIT)
    //{
    //    ofset = -ofset;;
    //    DrawStertTimer = 0.5f;
    //}



