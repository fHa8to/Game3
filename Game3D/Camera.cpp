#include "Camera.h"
#include "DxLib.h"
#include "Player.h"
#define _USE_MATH_DEFINES

#include <math.h>


Camera::Camera():
	fov		(60.0f),
	pos		(VGet(0,0,0))
{
	SetCameraNearFar(0.1f, 1000.0f);
}

void Camera::Update()
{
	//パッドアナログ情報取得
	DINPUT_JOYSTATE input;

	//入力状態初期化
	input.Rx = 0;
	input.Ry = 0;

	// 入力状態を取得
	GetJoypadDirectInputState(DX_INPUT_PAD1, &input);


	float cameraAngle = -DX_PI_F / 2;

	SetupCamera_Perspective(fov * (static_cast<float>(M_PI) / 180.0f));
	pos = VGet(0, 3.0f, -8.0f);
	SetCameraPositionAndTarget_UpVecY(pos, VGet(0, pos.y, 4.0f));
}
