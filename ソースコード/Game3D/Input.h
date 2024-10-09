#pragma once

#include <array>
#include "DxLib.h"
#include "Singleton.h"
#include "Vec3.h"

//各ボタンの定数
#define INPUT_A 0
#define INPUT_B 1
#define INPUT_X 2
#define INPUT_Y 3
#define INPUT_UP 4
#define INPUT_DOWN 5
#define INPUT_LEFT 6
#define INPUT_RIGHT 7
#define INPUT_START 8
#define INPUT_BACK 9
#define INPUT_LEFT_PUSH 10
#define INPUT_RIGHT_PUSH 11
#define INPUT_LEFT_SHOULDER 12
#define INPUT_RIGHT_SHOULDER 13
#define INPUT_LEFT_TRIGGER 14
#define INPUT_RIGHT_TRIGGER 15
#define INPUT_LEFT_STICK 16
#define INPUT_RIGHT_STICK 17


class Input : public Singleton<Input>
{
	friend class Singleton<Input>;

public:
	//更新処理
	void Update();

	//押した瞬間をとる
	bool IsTrigger(int input) const;

	//押している間をとる
	bool InHold(int input) const;

	//離した瞬間をとる
	bool InRelease(int input) const;

	//スティック入力の方向ベクトルを返す
	Vec3 GetStickVector(int input) const;

	//スティック入力の単位方向ベクトルを返す
	Vec3 GetStickUnitVector(int input) const;

	//スティック入力の長さを返す
	float GetStickVectorLength(int input) const;

	//スティックを傾けたX値を返す
	float GetStickThumbX(int input) const;

	//スティックを傾けたY値を返す
	float GetStickThumbY(int input) const;

private:

	//今フレームのインプットステート
	XINPUT_STATE m_padState;

	// 前フレームのインプットステート
	XINPUT_STATE m_lastPadState;

	// プライベートコンストラクタ
	Input() :m_padState(), m_lastPadState() {};

};

