#include "Camera.h"
#include "DxLib.h"
#include "Player.h"
#include "Pad.h"
#define _USE_MATH_DEFINES

#include <math.h>

namespace
{
	//カメラの描画範囲
	constexpr float kMinimumDrawingrange = 100.0f;
	constexpr float kMaximumDrawingrange =5000.0f;

	//カメラの座標
	constexpr float kCameraPosY = 500.0f;
	constexpr float kCameraPosZ = -800.0f;

	// 旋回速度
	constexpr float kAngleSpeed = 0.05f;	

	//注視点の座標
	constexpr float kCameraTargetY = 100.0f;

	//カメラの距離
	constexpr float kCameraDist = 1000.0f;
	//constexpr float kCameraHeight = 100;

	// 視野角
	constexpr float kFov = (DX_PI_F / 180.0f) * 60.0f;
	// 手前クリップ距離
	constexpr float kNear = 0.1f;
	// 奥クリップ距離
	constexpr float kFar = 1000.0f;
	// カメラの初期注視点
	constexpr float kTargetX = 100.0f;        // X軸
	constexpr float kTargetY = 400.0f;    // Y軸
	constexpr float kTargetZ = -870.0f;    // Z軸
	// カメラの中心座標
	constexpr float kScreenCenterX = 50.0f;    // X座標
	constexpr float kScreenCenterY = 1000.0f;    // Y座標

	constexpr float AngleSpeed = 0.05f;	// 旋回速度
}


Camera::Camera()
{
		

}


Camera::~Camera()
{
	// 処理なし.
}

void Camera::Init()
{
	//奥行100～5000までをカメラの描画範囲とする
	SetCameraNearFar(kMinimumDrawingrange, kMaximumDrawingrange);


	//初期化
	m_cameraPos = VGet(0.0f, 0.0f, 0.0f);
	
	m_cameraTarget = VGet(0.0f, 0.0f, 0.0f);

	m_cameraAngle = 0.0f;

	m_angleH = 0.0f;

	m_pad = 0;
}


void Camera::Update(VECTOR mplayerPos)
{

#if _DEBUG

	if ((GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_5))
	{
		m_cameraPos.x += 500.0f;
		m_cameraPos.z += 600.0f;
	}

#endif

	Pad::Update();


	if (Pad::isPress PAD_INPUT_6)
	{
		m_angleH += AngleSpeed;

		// １８０度以上になったら角度値が大きくなりすぎないように３６０度を引く
		if (m_angleH > DX_PI_F)
		{
			m_angleH -= DX_TWO_PI_F;
		}
	}
	if (Pad::isPress PAD_INPUT_5)
	{
		m_angleH -= kAngleSpeed;

		// －１８０度以下になったら角度値が大きくなりすぎないように３６０度を足す
		if (m_angleH < -DX_PI_F)
		{
			m_angleH += DX_TWO_PI_F;
		}
	}

	
	m_cameraPos.x = cosf(m_angleH) * kCameraDist;
	m_cameraPos.y = kCameraPosY;
	m_cameraPos.z = sinf(m_angleH) * kCameraDist;

	// カメラ座標
	m_cameraPos = VAdd(mplayerPos, m_cameraPos);

	// 注視点
	m_cameraTarget = VAdd(mplayerPos, VGet(0.0f, kCameraTargetY, 0.0f));

	SetCameraPositionAndTarget_UpVecY(m_cameraPos, m_cameraTarget);

}

void Camera::Draw()
{

#ifdef _DEBUG
	DrawFormatString(160, 200, GetColor(255, 255, 255), "カメラの座標(%.2f,%.2f,%.2f)", m_cameraPos.x, m_cameraPos.y, m_cameraPos.z);

	DrawFormatString(250, 250, GetColor(255, 255, 255), "%d", m_input.Rx);
#endif
}

//Camera::Camera():
//	fov		(60.0f),
//	pos		(VGet(0,0,0))
//{
//	SetCameraNearFar(0.1f, 1000.0f);
//}
//
//void Camera::Update()
//{
//	//パッドアナログ情報取得
//	DINPUT_JOYSTATE input;
//
//	//入力状態初期化
//	input.Rx = 0;
//	input.Ry = 0;
//
//	// 入力状態を取得
//	GetJoypadDirectInputState(DX_INPUT_PAD1, &input);
//
//
//	//float cameraAngle = -DX_PI_F / 2;
//
//	//if ((GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_5))
//	//{
//	//	cameraAngle += 0.05f;
//	//}
//	//if ((GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_6))
//	//{
//	//	cameraAngle -= 0.05f;
//	//}
//
//	SetupCamera_Perspective(fov * (static_cast<float>(M_PI) / 180.0f));
//	pos = VGet(0, 3.0f, -8.0f);
//	SetCameraPositionAndTarget_UpVecY(pos, VGet(0, pos.y, 4.0f));
//
//}
