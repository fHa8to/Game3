#include "Enemy.h"
#include "DxLib.h"
#include "Player.h"
#include <cmath>

namespace
{
	//モデルのファイル名
	const char* const kModelFilename = "data/model/Knight.mv1";

	//モデルのサイズ変更
	constexpr float kExpansion = 100.0f;


	//アニメーション番号
	constexpr int kIdleAnimIndex = 1;
	//攻撃判定が発生するまでにかかる時間
	constexpr float kAttackFrameStart = 20;
	//攻撃判定が終了するまでにかかる時間
	constexpr float kAttackFrameEnd = 30;

	//アニメーションの切り替えにかかるフレーム数
	constexpr float kAnimChangeFrame = 8.0f;
	constexpr float kAnimChangeRateSpeed = 1.0f / kAnimChangeFrame;

	//当たり判定
	constexpr float kAddPosY = 8.0f;
}

Enemy::Enemy():
	modelHandle(-1),
	currentAnimNo(-1),
	prevAnimNo(-1),
	animBlendRate(0.0f),
	angle(0.0f)

{
	//3Dモデルの読み込み
	modelHandle = MV1LoadModel(kModelFilename);
}

Enemy::~Enemy()
{
}

void Enemy::Init()
{
	MV1SetScale(modelHandle, VGet(kExpansion, kExpansion, kExpansion));

	currentAnimNo = MV1AttachAnim(modelHandle, kIdleAnimIndex, -1, false);
	prevAnimNo - 1;
	animBlendRate = 1.0f;

	//プレイヤーの初期位置設定
	pos = VGet(200.0f, -8000.0f, 0.0f);


}

void Enemy::Update(Player& player)
{	
	VECTOR enemyToPlayer = VSub(player.GetPos(), pos);

	// ３Dモデルのポジション設定
	MV1SetPosition(modelHandle, pos);
}

void Enemy::Draw()
{
	// ３Ｄモデルの描画
	MV1DrawModel(modelHandle);

#ifdef _DEBUG

	DrawSphere3D(VAdd(pos, VGet(0, 8, 0)), m_radius, 8, 0xffffff, 0xffffff, false);
	DrawFormatString(0, 32, 0xffffff, "Enemy(x:%f,y:%f,z:%f)", pos.x, pos.y, pos.z);

#endif

}

//球の当たり判定
bool Enemy::SphereHitFlag(std::shared_ptr<Player> pPlayer)
{
	float delX = (pos.x - pPlayer->GetPos().x) * (pos.x - pPlayer->GetPos().x);
	float delY = ((pos.y + kAddPosY) - (pPlayer->GetPos().y + kAddPosY)) *
		((pos.y + kAddPosY) - (pPlayer->GetPos().y + kAddPosY));
	float delZ = (pos.z - pPlayer->GetPos().z) * (pos.z - pPlayer->GetPos().z);

	//球と球の距離
	float Distance = sqrt(delX + delY + delZ);

	//球と球の距離がプレイヤとエネミーの半径よりも小さい場合
	if (Distance < m_radius + pPlayer->GetRadius())
	{
		return true;
	}

	return false;
}

bool Enemy::AttackSphereHitFlag(std::shared_ptr<Player> pPlayer)
{
	return false;
}
