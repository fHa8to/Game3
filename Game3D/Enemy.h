#pragma once
#include "DxLib.h"
#include <memory>

class Player;
class Enemy
{
public:
	Enemy();
	virtual ~Enemy();

	void Init();
	void Update(Player& player);
	void Draw();

	//プレイヤーと敵の当たり判定
	bool SphereHitFlag(std::shared_ptr<Player> pPlayer);
	//プレイヤーの攻撃と敵の当たり判定
	bool AttackSphereHitFlag(std::shared_ptr<Player> pPlayer);

private:

	int modelHandle;		//モデルハンドル

	//アニメーション情報
	int currentAnimNo;
	int prevAnimNo;
	float animBlendRate;

	//当たり判定の半径
	float m_radius;

	//表示情報
	VECTOR pos;
	float angle;

	int isAttack;
};

