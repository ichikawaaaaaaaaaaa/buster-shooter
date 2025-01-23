#include "Player.h"
#include "GoalText.h"
#include "Stage.h"
#include "Ball.h"
#include "config.h"
#include "Enemy.h"
#include "Vector2.h"

float Gravity = 0.5f;     //重力加速度
float jumpHeight = 20 * 2;  //ジャンプの高さ
float V0 = -sqrtf(3.0f * Gravity * jumpHeight);//初速計算

// プレイヤーのライフと敵に触れた回数
int life = 2;  // 初期ライフは3
int enemyCollisionCount = 0; // 敵に触れた回数

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
    IsGoal = 0; //ゴールフラグ初期化
    goaled = 0;  //ゴール達成フラグ初期化
    scroll = 0;  //スクロール位置初期化
}

// 更新処理

void Player::Update()

{
    GetJoypadInputState(DX_INPUT_KEY_PAD1);
    int PadInput;

    GetJoypadAnalogInput(&XInput, &YInput, DX_INPUT_KEY_PAD1);
    PadInput = GetJoypadInputState(DX_INPUT_KEY_PAD1);

    // 右クリックが押されているかを検出
    if (GetMouseInput() & MOUSE_INPUT_RIGHT) {
        if (!prevRightClick) {  // クリックが新たに始まった時
            isRightClicked = true;
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
            isLeftClicked = true;
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

    std::list<Enemy*> enemys = FindGameObjects<Enemy>();

    for (Enemy* e : enemys) {
        if (CircleHit(position, e->position, 56)) { // 衝突した場合
            enemyCollisionCount++; // 衝突回数を増加

            // 衝突回数が2回になったらライフを減らす
            if (enemyCollisionCount >= 2) {

                life--; // ライフを1減らす

                enemyCollisionCount = 0; // 衝突回数リセット

                // ライフが0になったらゲームオーバー
                if (life <= 0) {
                    // ゲームオーバー処理（ここで実際にゲームオーバー処理を書く）
                    // 例えば、ゲームオーバー画面を表示したり、ゲームを終了したりする
                    // GameOver(); // ゲームオーバー処理を呼び出す
                    return; // ゲームオーバー後の処理を終了
                }
            }
        }
    }

    // 左の移動処理

    if (CheckHitKey(KEY_INPUT_A)) {
        position.x -= 2;  //左に〇(数字)ピクセル移動

        //左の壁との衝突判定

        int push = s->IsWallLeft(position + VECTOR2(0, 0));
        position.x += push; //壁の奥に進まないように位置を調節
        push = s->IsWallLeft(position + VECTOR2(0, 39));  //キャラクターの下半分で衝突確認
        position.x += push;
    }

    // 左の移動処理(PAD)

    if (XInput < -100) {
        position.x -= 2;
        //キャラクターの左上隅で衝突チェック

        int push = s->IsWallLeft(position + VECTOR2(0, 0));
        position.x += push;
        push = s->IsWallLeft(position + VECTOR2(0, 39));
        position.x += push;
    }

    // 右の移動処理

    if (CheckHitKey(KEY_INPUT_D)) {

        position.x += 2;  //右に〇(数字)ピクセル移動

        //右の壁との衝突判定

        int push = s->IsWallRight(position + VECTOR2(39, 0));

        position.x -= push;
        push = s->IsWallRight(position + VECTOR2(39, 39));
        position.x -= push;
    }

    // 右の移動処理(PAD)

    if (XInput > 100) {
        position.x += 2;
        int push = s->IsWallRight(position + VECTOR2(39, 0));
        position.x -= push;
        push = s->IsWallRight(position + VECTOR2(39, 39));
        position.x -= push;
    }

    // ジャンプ処理

    if (CheckHitKey(KEY_INPUT_SPACE)) {
        if (!prevJumpKey && onGround) { //地上にいてジャンプキーが押された場合
            velocity = V0;             //初速を設定
        }
    }

    // ジャンプ処理(PAD)

    if (PadInput & PAD_INPUT_B) {
        if (!prevJumpKey && onGround) { //地上にいてジャンプキーが押された場合
            velocity = V0;             //初速を設定
        }
    }

    prevJumpKey = CheckHitKey(KEY_INPUT_SPACE); //現在のジャンプキー状態を記録

    // 垂直方向の移動と重力処理
    position.y += velocity;  //座標に速度を加算
    velocity += Gravity;     //速度に重力を加算
    onGround = false;        //地面接触フラグをリセット

    // 地面衝突判定

    if (velocity >= 0) {
        int push = s->IsWallDown(position + VECTOR2(0, 39 + 1)); //地面判定

        if (push > 0) { // 地面に触れた場合
            velocity = 0.0f; // 速度を0にする
            position.y -= push - 1; // 地面に押し戻す
            onGround = true;        // 地上判定をON
        }

        else {
            // 頭の衝突判定
            push = s->IsWallUP(position + VECTOR2(0, 0));

            if (push > 0) {
                velocity = 0.0f;  // 頭に衝突した場合、速度を0にする
                position.y += push; // 頭上に押し戻す
            }
            push = s->IsWallUP(position + VECTOR2(39, 0));

            if (push > 0) {
                velocity = 0.0f;
                position.y += push;
            }
        }
        // 右足地面判定

        push = s->IsWallDown(position + VECTOR2(39, 39));

        if (push > 0) {
            velocity = 0.0f;
            position.y -= push - 1;
            onGround = true; // 地面に着地したとき、地上判定をONにする
        }
    }


    // Ballを投げる処理(PAD)
    if (PadInput & PAD_INPUT_Y || GetMouseInput() & MOUSE_INPUT_RIGHT) {

        if (!prevRightMouse) {
            Ball* ba = Instantiate<Ball>();   // ボールを生成
            ba->position = position;          // プレイヤーの位置に生成
            ba->position.y += 5;              // 少し下にずらす
            ba->velocity = VECTOR2(5.0f, 0.0f); // 右方向の速度
        }
        prevRightMouse = true;
    }

    else {
        prevRightMouse = false;
    }
    // 左方向

    if (PadInput & PAD_INPUT_A || GetMouseInput() & MOUSE_INPUT_LEFT) {

        if (!prevLeftMouse) {
            Ball* ba = Instantiate<Ball>();  // ボールを生成
            ba->position = position;
            ba->position.y += 5;
            ba->velocity = VECTOR2(-5.0f, 0.0f); // 左方向の速度

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

            for (int i = 0; i < life; i++) {
                // ここでライフアイコンを描画するコードを追加
                // 例: DrawGraph(10 + i * 30, 10, lifeIconImage, TRUE);
            }
        }
    }
}