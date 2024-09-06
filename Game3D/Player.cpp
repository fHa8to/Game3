#include "Player.h"
#include "DxLib.h"
#include "Enemy.h"
#include "Pad.h"
#include <cmath>
#include <iostream>
#include <memory>

namespace
{
	//モデルのファイル名
	const char* const kModelFilename = "data/model/Knight.mv1";



	//アニメーション番号
	constexpr int kIdleAnimIndex = 1;		//待機
	constexpr int kWalkAnimIndex = 2;		//歩き
	constexpr int kRunAnimIndex = 7;		//走り
	constexpr int kAttackAnimIndex = 21;	//攻撃
	constexpr int kAnimIndex = 3;

	

	//走る速さ
	constexpr float kDash = 15.0f;

	//初期座標
	constexpr float kPosX = 400.0f;
	constexpr float kPosY = 0.0f;

	//モデルのサイズ変更
	constexpr float kExpansion = 100.0f;


	//アニメーションの切り替えにかかるフレーム数
	constexpr float kAnimChangeFrame = 8.0f;
	constexpr float kAnimChangeRateSpeed = 1.0f / kAnimChangeFrame;

	//アナログスティックによる移動関連
	constexpr float kMaxSpeed = 5.0f;		//プレイヤーの最大移動速度
	constexpr float kAnalogRangeMin = 0.1;	//アナログスティックの入力判定範囲
	constexpr float kAnalogRangeMax = 0.8;
	constexpr float kAnalogInputMax = 1000.0f;	//アナログスティックから入力されるベクトルの最大値


}

Player::Player() :
	modelHandle(-1),
	m_currentAnimNo(-1),
	m_prevAnimNo(-1),
	m_animBlendRate(0.0f),
	m_isAttack(false),
	m_pos(VGet(0.0f, 0.0f, 0.0f)),
	angle(0.0f),
	m_cameraAngle(0.0f),
	m_radius(100.0f)
{
	//3Dモデルの読み込み
	modelHandle = MV1LoadModel(kModelFilename);
}

Player::~Player()
{
}

void Player::Init()
{	

	m_currentAnimNo = MV1AttachAnim(modelHandle, kIdleAnimIndex, -1, false);
	m_prevAnimNo - 1;
	m_animBlendRate = 1.0f;





	MV1SetPosition(modelHandle, m_pos);
	MV1SetScale(modelHandle, VGet(kExpansion, kExpansion, kExpansion));
	m_isAttack = false;

}

void Player::Update(VECTOR cameraPos)
{
	//MoveUpdate(cameraPos);

	Animation(cameraPos);

	MV1SetPosition(modelHandle, m_pos);
	MV1SetRotationXYZ(modelHandle, VGet(0, angle, 0));

	// ３Dモデルのポジション設定
	MV1SetPosition(modelHandle, m_pos);


	
}

void Player::Draw()
{
	// ３Ｄモデルの描画
	MV1DrawModel(modelHandle);

	DrawSphere3D(VAdd(m_pos, VGet(0, 100, 0)), m_radius, 8, 0xffffff, 0xffffff, false);
	DrawSphere3D(VAdd(m_attackPos, VGet(0, 8, 0)), m_radius, 8, 0xffffff, 0xff00ff, true);


}


void Player::MoveUpdate(VECTOR cameraPos)
{
	int analogX = 0;
	int analogZ = 0;

	GetJoypadAnalogInput(&analogX, &analogZ, DX_INPUT_PAD1);

	//アナログスティックの入力の10% ~ 80%の範囲を使用する

	//ベクトルの長さが最大で1000になる
	//プレイヤーの最大移動速度は0.01f / frame

	VECTOR move = VGet(analogX, 0.0f, -analogZ);	//ベクトルの長さは0～1000

	//0.00 ~ 0.01の長さにする
	//ベクトルの長さを取得する
	float len = VSize(move);
	//ベクトルの長さを0.0~1.0の割合に変換する
	float rate = len / kAnalogInputMax;

	//アナログスティック無効な範囲を除外する
	rate = (rate - kAnalogRangeMin) / (kAnalogRangeMax - kAnalogRangeMin);
	rate = min(rate, 1.0f);
	rate = max(rate, 0.0f);

	//速度が決定できるので移動ベクトルに反映する
	move = VNorm(move);
	float speed = kMaxSpeed * rate;
	move = VScale(move, speed);

	MATRIX mtx = MGetRotY(-m_cameraAngle - DX_PI_F / 2);
	move = VTransform(move, mtx);

	if (VSquareSize(move) > 0.0f)
	{
		angle = -atan2f(move.z, move.x) - DX_PI_F / 2;
			ChangeAnim(kWalkAnimIndex);
	}


	m_pos = VAdd(m_pos, move);



	if (Pad::IsPress(PAD_INPUT_2))
	{
		move = VScale(move, 1.5f);

		m_pos = VAdd(m_pos, move);
	}


}


void Player::Animation(VECTOR cameraPos)
{
	//アニメーションの切り替え
	if (m_prevAnimNo != -1)
	{
		m_animBlendRate += kAnimChangeRateSpeed;
		if (m_animBlendRate >= 1.0f)	m_animBlendRate = 1.0f;
		//変更前のアニメーション100%
		MV1SetAttachAnimBlendRate(modelHandle, m_prevAnimNo, 1.0f - m_animBlendRate);
		//変更後のアニメーション0%
		MV1SetAttachAnimBlendRate(modelHandle, m_currentAnimNo, m_animBlendRate);

	}

	//アニメーションを進める
	bool isLoop = UpdateAnim(m_currentAnimNo);
	UpdateAnim(m_prevAnimNo);

	if (!m_isAttack)
	{
		if (Pad::IsTrigger PAD_INPUT_1)
		{
			m_isAttack = true;
			ChangeAnim(kAttackAnimIndex);
		}
		else
		{
			MoveUpdate(cameraPos);

		}
	}
	else
	{
		if (isLoop)
		{
			m_isAttack = false;
			ChangeAnim(kIdleAnimIndex);
		}

	}
	
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
	if (m_prevAnimNo != -1)
	{
		MV1DetachAnim(modelHandle, m_prevAnimNo);
	}

	//現在再生中の待機アニメーションは変更前のアニメーション扱いに
	m_prevAnimNo = m_currentAnimNo;

	//変更後のアニメーションとして攻撃アニメーションを改めて設定する
	m_currentAnimNo = MV1AttachAnim(modelHandle, animIndex, -1, false);

	//切り替えの瞬間は変更後のアニメーションが再生される
	m_animBlendRate = 0.0f;

	//変更前のアニメーション100%
	MV1SetAttachAnimBlendRate(modelHandle, m_prevAnimNo, 1.0f - m_animBlendRate);
	//変更後のアニメーション0%
	MV1SetAttachAnimBlendRate(modelHandle, m_currentAnimNo, m_animBlendRate);
}
