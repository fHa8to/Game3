#include "Enemy.h"
#include "DxLib.h"
#include <cmath>

namespace
{
	//モデルのファイル名
	const char* const kModelFilename = "data/model/Knight.mv1";

	//アニメーション番号
	constexpr int kIdleAnimIndex = 1;
	//攻撃判定が発生するまでにかかる時間
	constexpr float kAttackFrameStart = 20;
	//攻撃判定が終了するまでにかかる時間
	constexpr float kAttackFrameEnd = 30;

	//アニメーションの切り替えにかかるフレーム数
	constexpr float kAnimChangeFrame = 8.0f;
	constexpr float kAnimChangeRateSpeed = 1.0f / kAnimChangeFrame;

	//アナログスティックによる移動関連
	constexpr float kMaxSpeed = 0.1f;		//プレイヤーの最大移動速度
	constexpr float kAnalogRaneMin = 0.1f;	//アナログスティックの入力判定範囲
	constexpr float kAnalogRaneMax = 0.8f;
	constexpr float kAnglogInputMax = 1000.0f;	//アナログスティックの入力されるベクトルに

}

Enemy::Enemy():
	modelHandle(-1),
	currentAnimNo(-1),
	prevAnimNo(-1),
	animBlendRate(0.0f),
	angle(0.0f)

{
}

Enemy::~Enemy()
{
}

void Enemy::Init()
{
	//3Dモデルの読み込み
	modelHandle = MV1LoadModel(kModelFilename);

	currentAnimNo = MV1AttachAnim(modelHandle, kIdleAnimIndex, -1, false);
	prevAnimNo - 1;
	animBlendRate = 1.0f;

	//プレイヤーの初期位置設定
	pos = VGet(0.0f, 0.0f, 5.0f);


}

void Enemy::Update()
{	

	// ３Dモデルのポジション設定
	MV1SetPosition(modelHandle, pos);
}

void Enemy::Draw()
{
	// ３Ｄモデルの描画
	MV1DrawModel(modelHandle);
}
