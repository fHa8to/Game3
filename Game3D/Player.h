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

	//半径の取得
	float GetRadius() { return m_radius; }


	//プレイヤー
	const VECTOR& GetPos() const { return pos; }




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
	VECTOR attackPos;

	float angle;

	//当たり判定の半径
	float m_radius;

	//カメラ情報
	float cameraAngle;

	int isAttack;

};

