#pragma once
#include "Singleton.h"

// シングルトンの定数管理クラス
class Constants : public Singleton<Constants> 
{
    friend class Singleton<Constants>;

public:
    // 画面系定数
    static constexpr int SCREEN_WIDTH = 1280;  // 画面の横サイズ
    static constexpr int SCREEN_HEIGHT = 720;  // 画面の縦サイズ
    static constexpr int COLOR_BIT = 16;   // カラービット数
    static constexpr int RESOLUTION_WIDTH = 1920;  // 解像度の横成分
    static constexpr int RESOLUTION_HEIGHT = 1080; // 解像度の縦成分

    // ステージ定数
    static constexpr int STAGE_RANGE = 150;    // ステージの範囲

    // カメラ定数
    static constexpr float CAMERA_BASE_POS_X = 0.0f;   // カメラの座標基準値X
    static constexpr float CAMERA_BASE_POS_Y = 40.0f;  // カメラの座標基準値Y
    static constexpr float CAMERA_BASE_POS_Z = 30.0f;  // カメラの座標基準値Z
    static constexpr float CAMERA_NEAR = 1.0f;     // カメラのNear値
    static constexpr float CAMERA_FAR = 512.0f;    //カメラのFar値
    static constexpr float CAMERA_ANGLE_VARIATION = 0.000001f; // カメラの回転値
    static constexpr float CAMERA_ANGLE_RANGE = 0.6f;  // カメラの回転範囲

    // プレイヤー定数
    static constexpr float PLAYER_BASE_POS_X = 0.0f;   // プレイヤーの座標基準値X
    static constexpr float PLAYER_BASE_POS_Y = 0.0f;   // プレイヤーの座標基準値Y
    static constexpr float PLAYER_BASE_POS_Z = 0.0f;   // プレイヤーの座標基準値Z
    static constexpr float PLAYER_SCALE = 5.0f;    // プレイヤーの拡大値
    static constexpr float PLAYER_MOVE_SCALE_SLOW_WALK = 0.1f; // プレイヤーの移動速度
    static constexpr float PLAYER_MOVE_SCALE_FAST_WALK = 0.3f; // プレイヤーの移動速度
    static constexpr float PLAYER_MOVE_SCALE_SLOW_DASH = 0.45f; // プレイヤーの移動速度
    static constexpr float PLAYER_MOVE_SCALE_FAST_DASH = 0.6f; // プレイヤーの移動速度
    static constexpr float PLAYER_MOVE_SCALE_THRESHOLD = 30000.0f; // 移動速度が変化するしきい値
    static constexpr float PLAYER_COLLISION_RADIUS = 3.5f;    // プレイヤーの当たり判定の半径
    static constexpr float PLAYER_GRAVITY = 0.25f;   // 重力
    static constexpr float PLAYER_JUMP_SCALE = 3.0f;    // ジャンプ力
    static constexpr float PLAYER_HP = 100.0f;  // プレイヤーの体力
    static constexpr float PLAYER_ATTACK_DAMAGE = 50.0f;    // ダメージ量
    static constexpr float PLAYER_HEIGHT = 5.0f; // プレイヤーの高さ
    static constexpr float PLAYER_BASE_ATTACK_POS_X = 0.0f; // 攻撃発生位置
    static constexpr float PLAYER_BASE_ATTACK_POS_Y = 1.0f; // 攻撃発生位置
    static constexpr float PLAYER_BASE_ATTACK_POS_Z = -6.0f; // 攻撃発生位置
    static constexpr float PLAYER_ATTACK_RADIUS = 5.0;  // 攻撃判定半径
    static constexpr float PLAYER_ATTACK_HEIGHT = 2.0;  // 攻撃判定高さ
    static constexpr int PLAYER_ATTACK_PREPARATION = 23;    // 攻撃予備動作フレーム数
    static constexpr int PLAYER_ATTACK_END = 26;    // 攻撃終了フレーム数

    // コントローラー定数
    static constexpr int STICK_INVALID_VALUE = 8000;   // スティックの無効範囲

    // アニメーションタグ定数
    static constexpr int PLAYER_ANIM_IDLE = 1; // アイドルアニメタグ
    static constexpr int PLAYER_ANIM_SLOW_WALK = 4;    // スローウォークアニメタグ
    static constexpr int PLAYER_ANIM_FAST_WALK = 3;    // ファストウォークアニメタグ
    static constexpr int PLAYER_ANIM_SLOW_DASH = 7;    // スローダッシュアニメタグ
    static constexpr int PLAYER_ANIM_FAST_DASH = 6;    // ファストダッシュアニメタグ
    static constexpr int PLAYER_ANIM_SLICE = 31;  // ノーマルアッタクアニメタグ
    static constexpr int PLAYER_ANIM_STAB = 33;    // スタブアタックアニメタグ
    static constexpr int PLAYER_ANIM_SAD = 73;  // 残念がってるやつのタグ
    static constexpr int PLAYER_ANIM_HIT = 24;  // ヒットアニメタグ
    static constexpr int PLAYER_ANIM_DEAD = 28; // 死亡アニメーション
    static constexpr int PLAYER_ANIM_DEAD_IDLE = 29; // 死亡アイドルアニメーション

    static constexpr int ENEMY_ANIM_WALK = 14;  // 歩くアニメーション
    static constexpr int ENEMY_ANIM_IDLE = 3;  // アイドルアニメーション
    static constexpr int ENEMY_ANIM_ATTACK = 10;  // 攻撃アニメーション
    static constexpr int ENEMY_ANIM_DEAD = 0;   // 死亡アニメーション

    // エネミー定数
    static constexpr float ENEMY_SCALE = 0.04f;  // エネミーのモデルの拡大値
    static constexpr float ENEMY_SPAWN_POINT = 170.0f;   // エネミーがスポーンする位置
    static constexpr float ENEMY_HP = 100.0f;   // エネミーの体力
    static constexpr float ENEMY_ATTACK_DAMAGE = 20.0f; // エネミーの攻撃力
    static constexpr float ENEMY_COLLISION_RADIUS = 4.0f;   // エネミーの当たり判定の半径
    static constexpr float ENEMY_HEIGHT = 4.5f; // エネミーの高さ
    static constexpr float ENEMY_DASH_SPEED = 0.5;  // 最も早いエネミーの移動速度
    static constexpr float ENEMY_DEAD_LINE = -20.0f;    // エネミーが落下死する高さ
    static constexpr float ENEMY_BLOW_AWAY_SCALE = 8.0f;    // エネミーが吹っ飛ぶ平行速度
    static constexpr int ENEMY_COOL_TIME = 60;  // 攻撃のクールタイム

    // アニメーションフレーム数定数
    static constexpr int PLAYER_ANIM_SLICE_FLAME = 30; // 通常攻撃フレーム数

    // ゲームシーンでの空の時間経過用定数
    static constexpr int SKY_COLOR_DAY_RED = 36;    // 明るい青
    static constexpr int SKY_COLOR_DAY_GREEN = 139; // 明るい青
    static constexpr int SKY_COLOR_DAY_BLUE = 255;  // 明るい青
    static constexpr int SKY_COLOR_EVENING_RED = 255;  // 明るい赤
    static constexpr int SKY_COLOR_EVENING_GREEN = 140;  // 明るい赤
    static constexpr int SKY_COLOR_EVENING_BLUE = 0;  // 明るい赤
    static constexpr int SKY_COLOR_NIGHT_RED = 0;  // 暗い青
    static constexpr int SKY_COLOR_NIGHT_GREEN = 0;  // 暗い青
    static constexpr int SKY_COLOR_NIGHT_BLUE = 139;  // 暗い青
    static constexpr int FRAME_PER_CYCLE = 12000; // 位置サイクルのフレーム数
    static constexpr int FRAME_PER_TRAMSITION = FRAME_PER_CYCLE / 4;    // 各区間フレーム

    // 難易度に関する定数
    static constexpr int SPAWN_INTERVAL_EASY = 300; // easyのスポーンのインターバル
    static constexpr int SPAWN_INTERVAL_NORMAL = 200; // normalのスポーンのインターバル
    static constexpr int SPAWN_INTERVAL_HARD = 100; // hardのスポーンのインターバル
    static constexpr int SPAWN_INTERVAL_NIGHTMARE = 50; // nightmareのスポーンのインターバル

    static constexpr int LEVEL_EASY = 1;    // 難易度easyの値
    static constexpr int LEVEL_NORMAL = 2;    // 難易度easyの値
    static constexpr int LEVEL_HARD = 3;    // 難易度easyの値
    static constexpr int LEVEL_NIGHTMARE = 4;    // 難易度easyの値
    
    static constexpr int TIME_FRAME_NORMAL = 3600;  // 難易度をイージーに変えるフレーム数
    static constexpr int TIME_FRAME_HARD = 5400;  // 難易度をハードに変えるフレーム数
    static constexpr int TIME_FRAME_NIGHTMARE = 7200;  // 難易度をナイトメアに変えるフレーム数
    
private:
    // プライベートコンストラクタ
    Constants() {}
};