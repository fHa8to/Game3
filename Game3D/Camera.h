#pragma once
#include "DxLib.h"

class Player;

class Camera
{


public:
    Camera();
    virtual ~Camera();

    void Init();

    void Update(VECTOR mplayerPos);

    void Draw();

    VECTOR GetCameraPos() const noexcept { return m_cameraPos; }

private:

    //ジョイパッドの出力
    DINPUT_JOYSTATE m_input;

    //ジョイパッドの出力の保持
    int m_pad;

    // 水平角度
    float m_angleH;


    float m_cameraAngle;

    //カメラの座標
    VECTOR m_cameraPos;

    //カメラの注視点
    VECTOR m_cameraTarget;

    //プレイヤーの座標
    VECTOR m_playerTarget;


//public:
//	Camera();
//	void Update();
//
//
//private:
//	float fov;
//	VECTOR pos;
//
//	constexpr static float DefaultFov = 60.0f;
//	constexpr static float FovRange = 30.0f;	// fovの変化幅
//	constexpr static float PosChangeSpeed = 0.03f;	// posの変化スピード

};

