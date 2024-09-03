#pragma once
#include "DxLib.h"

class Enemy
{
public:
	Enemy();
	virtual ~Enemy();

	void Init();
	void Update();
	void Draw();


private:

	int modelHandle;		//モデルハンドル

	//アニメーション情報
	int currentAnimNo;
	int prevAnimNo;
	float animBlendRate;

	//表示情報
	VECTOR pos;
	float angle;

	int isAttack;
};

