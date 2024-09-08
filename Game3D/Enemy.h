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
	//�U���ƓG�̓����蔻��
	bool SphereHitFlag2(std::shared_ptr<Player> pPlayer);



	float GetRadius() { return m_radius; }
	VECTOR GetPos() { return m_pos; }
	void SetPos(VECTOR pos) { m_pos = pos; }

private:
	std::shared_ptr<Player> m_pPlayer;

private:

	int modelHandle;		//���f���n���h��

	//�A�j���[�V�������
	int currentAnimNo;
	int prevAnimNo;
	float animBlendRate;

	//�����蔻��̔��a
	float m_radius;

	//�\�����
	VECTOR m_pos;
	VECTOR SubVector;

	float Angle;

	float angle;

	int isAttack;

	//�i�ދ���
	VECTOR m_distance;

};

