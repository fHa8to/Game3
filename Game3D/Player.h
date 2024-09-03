#pragma once
#include "DxLib.h"

class Player
{
public:
	Player();
	virtual ~Player();

	void Init();
	void Update();
	void Draw();

	//攻撃がヒットしたとき
	void HitAttack();

	const VECTOR& GetPos() const { return pos; }

	// ダメージを食らったとき
	void OnDamage(VECTOR targetPos, int damagePoint);

	//ガード中に攻撃されたとき
	void OnGuardingAttack();

	//ジャストガード中に攻撃されたとき
	void OnJustGuardingAttack();



private:

	bool UpdateAnim(int attachNo);
	void ChangeAnim(int animIndex);
	


private:
	int		modelHandle;	//モデルハンドル

	//アニメーション情報
	int currentAnimNo;
	int prevAnimNo;
	float animBlendRate;


	//表示情報
	VECTOR pos;
	float angle;

	//カメラ情報
	float cameraAngle;

	int isAttack;

};

