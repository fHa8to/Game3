#pragma once
#include "DxLib.h"

class Player;

class Camera
{
public:
	Camera();
	void Update();


private:
	float fov;
	VECTOR pos;

	constexpr static float DefaultFov = 60.0f;
	constexpr static float FovRange = 30.0f;	// fov�̕ω���
	constexpr static float PosChangeSpeed = 0.03f;	// pos�̕ω��X�s�[�h

};

