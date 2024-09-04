#include "Player.h"
#include "DxLib.h"
#include "Enemy.h"
#include "Pad.h"
#include <cmath>
#include <iostream>
#include <memory>
#include <array>

namespace
{
	//モデルのファイル名
	const char* const kModelFilename = "data/model/Knight.mv1";



	//アニメーション番号
	constexpr int kIdleAnimIndex = 1;
	constexpr int kWalkAnimIndex = 2;
	constexpr int kRunAnimIndex = 7;
	constexpr int kAttackAnimIndex = 21;
	constexpr int kAnimIndex = 3;

	//移動量
	constexpr float kSpped = 15.0f;

	//初期座標
	constexpr float kPosX = 40.0f;
	constexpr float kPosY = -8000.0f;

	//モデルのサイズ変更
	constexpr float kExpansion = 100.0f;


	//アニメーションの切り替えにかかるフレーム数
	constexpr float kAnimChangeFrame = 8.0f;
	constexpr float kAnimChangeRateSpeed = 1.0f / kAnimChangeFrame;

	//アナログスティックによる移動関連
	constexpr float kMaxSpeed = 0.1f;		//プレイヤーの最大移動速度
	constexpr float kAnalogRaneMin = 0.1f;	//アナログスティックの入力判定範囲
	constexpr float kAnalogRaneMax = 0.8f;
	constexpr float kAnglogInputMax = 1000.0f;	//アナログスティックの入力されるベクトルに

}

Player::Player():
	modelHandle(-1),
	currentAnimNo(-1),
	prevAnimNo(-1),
	animBlendRate(0.0f),
	angle(0.0f),
	cameraAngle(0.0f)
{
	//3Dモデルの読み込み
	modelHandle = MV1LoadModel(kModelFilename);
}

Player::~Player()
{
}

void Player::Init()
{	

	MV1SetScale(modelHandle, VGet(kExpansion, kExpansion, kExpansion));

	currentAnimNo = MV1AttachAnim(modelHandle, kIdleAnimIndex, -1, false);
	prevAnimNo - 1;
	animBlendRate = 1.0f;

	//プレイヤーの初期位置設定
	pos = VGet(kPosX, kPosY, 0.0f);
	attackPos = VAdd(pos, VGet(0.0f, 7.0f, 4.0f));


}

void Player::Update(VECTOR cameraPos)
{
	//アニメーションの切り替え
	if (prevAnimNo != -1)
	{
		animBlendRate += kAnimChangeRateSpeed;
		if (animBlendRate >= 1.0f)	animBlendRate = 1.0f;
		//変更前のアニメーション100%
		MV1SetAttachAnimBlendRate(modelHandle, prevAnimNo, 1.0f - animBlendRate);
		//変更後のアニメーション0%
		MV1SetAttachAnimBlendRate(modelHandle, currentAnimNo, animBlendRate);

	}



	//アニメーションを進める
	bool isLoop = UpdateAnim(currentAnimNo);
	UpdateAnim(prevAnimNo);
	if (Pad::isPress(PAD_INPUT_RIGHT))
	{
		m_state = kMove;
		m_direction = kDown;
		pos = VAdd(pos, VGet(0.0f,
			0.0f,
			-kSpped));


	}
	if (Pad::isRelase(PAD_INPUT_RIGHT))
	{
		m_state = kWait;
	}

	//移動
	if (Pad::isPress(PAD_INPUT_LEFT))
	{
		m_state = kMove;
		m_direction = kUp;
		pos = VAdd(pos, VGet(0.0f,
			0.0f,
			kSpped));


	}
	if (Pad::isRelase(PAD_INPUT_LEFT))
	{
		m_state = kWait;
	}

	//移動
	if (Pad::isPress(PAD_INPUT_UP))
	{
		m_state = kMove;
		m_direction = kRight;
		pos = VAdd(pos, VGet(kSpped,
			0.0f,
			0.0f));


	}
	if (Pad::isRelase(PAD_INPUT_UP))
	{
		m_state = kWait;
	}

	//移動
	if (Pad::isPress(PAD_INPUT_DOWN))
	{
		m_state = kMove;
		m_direction = kLeft;
		pos = VAdd(pos, VGet(-kSpped,
			0.0f,
			0.0f));


	}
	if (Pad::isRelase(PAD_INPUT_DOWN))
	{
		m_state = kWait;
	}

	if (!isAttack)
	{

		if (Pad::isTrigger PAD_INPUT_1)
		{
			isAttack = true;
			ChangeAnim(kAttackAnimIndex);

		}
	//	else
	//	{
	//		//アナログスティックを使って移動
	//		int analogX = 0;
	//		int analogZ = 0;

	//		GetJoypadAnalogInput(&analogX, &analogZ, DX_INPUT_KEY_PAD1);


	//		//アナログスティックの入力の10% ~ 80%の範囲を使用する

	//		//ベクトルの長さが最大で1000になる

	//		//プレイヤーの最大移動速度は 0.01f / frame

	//		VECTOR move = VGet(analogX, 0.0f, -analogZ);	//ベクトルの長さ0~1000
	//		//0.00~0.01の長さにする
	//		//ベクトルの長さを取得する
	//		float len = VSize(move);
	//		//ベクトルの長さを0.0~1.0に割合に変換する
	//		float rate = len / kAnglogInputMax;

	//		//アナログスティック無効な範囲を除外する
	//		rate = (rate - kAnalogRaneMin) / (kAnalogRaneMax - kAnalogRaneMin);
	//		rate = min(rate, 1.0f);
	//		rate = max(rate, 0.0f);

	//		//速度が決定できるので移動ベクトルに反映する
	//		move = VNorm(move);
	//		float speed = kMaxSpeed * rate;
	//		move = VScale(move, speed);

	//		MATRIX mtx = MGetRotY(-cameraAngle - DX_PI_F / 2);
	//		move = VTransform(move, mtx);


	//		//移動方向からプレイヤーの向く方向を決定する
	//		if (VSquareSize(move) > 0.0f)
	//		{
	//			angle = -atan2f(move.z, move.x) - DX_PI_F / 2;
	//		}

	//		pos = VAdd(pos, move);

	//		if (Pad::isPress PAD_INPUT_2)
	//		{
	//			ChangeAnim(kRunAnimIndex);
	//			move = VScale(move, 1.2f);
	//			pos = VAdd(pos, move);
	//		}

	//		VECTOR attackMove = VScale(move, 15.0f);
	//		attackPos = VAdd(pos, attackMove);
	//	}
	}
	else
	{
		//攻撃アニメーションが終了したら待機アニメーションを再生する
		if (isLoop)
		{

			isAttack = false;
			ChangeAnim(kIdleAnimIndex);
		}
	}


	// ３Dモデルのポジション設定
	MV1SetPosition(modelHandle, pos);
	MV1SetRotationXYZ(modelHandle, VGet(0, angle, 0));


}

void Player::Draw()
{
	// ３Ｄモデルの描画
	MV1DrawModel(modelHandle);
}


bool Player::UpdateAnim(int attachNo)
{
	//アニメーションが設定されていないので終了
	if (attachNo == -1) return false;

	//アニメーションを進行させる
	float now = MV1GetAttachAnimTime(modelHandle, attachNo);	//現在の再生カウントを取得
	now += 0.5f;	//アニメーション進める

	//現在再生中のアニメーションの総カウントを取得
	float total = MV1GetAttachAnimTotalTime(modelHandle, attachNo);
	bool isLoop = false;
	if (now >= total)
	{
		now -= total;
		isLoop = true;
	}

	//進めた時間の設定
	MV1SetAttachAnimTime(modelHandle, attachNo, now);

	return isLoop;
}

void Player::ChangeAnim(int animIndex)
{
	//さらに古いアニメーションがアタッチされている場合はこの時点で削除しておく
	if (prevAnimNo != -1)
	{
		MV1DetachAnim(modelHandle, prevAnimNo);
	}

	//現在再生中の待機アニメーションは変更前のアニメーション扱いに
	prevAnimNo = currentAnimNo;

	//変更後のアニメーションとして攻撃アニメーションを改めて設定する
	currentAnimNo = MV1AttachAnim(modelHandle, animIndex, -1, false);

	//切り替えの瞬間は変更後のアニメーションが再生される
	animBlendRate = 0.0f;

	//変更前のアニメーション100%
	MV1SetAttachAnimBlendRate(modelHandle, prevAnimNo, 1.0f - animBlendRate);
	//変更後のアニメーション0%
	MV1SetAttachAnimBlendRate(modelHandle, currentAnimNo, animBlendRate);
}
