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

	int modelHandle;		//���f���n���h��

	//�A�j���[�V�������
	int currentAnimNo;
	int prevAnimNo;
	float animBlendRate;

	//�\�����
	VECTOR pos;
	float angle;

	int isAttack;
};

