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

	//�v���C���[�ƓG�̓����蔻��
	bool SphereHitFlag(std::shared_ptr<Player> pPlayer);
	//�v���C���[�̍U���ƓG�̓����蔻��
	bool AttackSphereHitFlag(std::shared_ptr<Player> pPlayer);

private:

	int modelHandle;		//���f���n���h��

	//�A�j���[�V�������
	int currentAnimNo;
	int prevAnimNo;
	float animBlendRate;

	//�����蔻��̔��a
	float m_radius;

	//�\�����
	VECTOR pos;
	float angle;

	int isAttack;
};

