#pragma once
#include "DxLib.h"
#include "Rect.h"
class Knight;
class EnemyBase
{
public:
	EnemyBase(int ModelHandle);
	virtual ~EnemyBase();

	void Init();
	
	virtual void Update(Knight* knight, VECTOR playerPos) abstract;
	
	void Draw();	//���[�v�������ǂ�����Ԃ�

	//�v���C���[�̈ʒu�ɂ���Đ�������ʒu��ς���
	virtual void SetPosX(VECTOR playerPos)abstract;

	//�_���[�W
	void OnDamage();

	void End();

	//���W�̐ݒ�
	void SetPos(VECTOR mpos) { m_pos = mpos; }
protected:

	//�G�l�~�[�̏��
	enum  state
	{
		kMove,			//�����Ă���
		kAttack,		//�U����
		kDamage,		//�_���[�W�󂯂Ă���
		kDeath			//����
	};
protected:

	//���
	int m_state;

	int	m_animFrame;

	//HP
	int m_hp;

	//�U����
	int m_attackPower;

	//���f���̃n���h��
	int m_handle;

	//�v���C���[�̍U���q�b�g��
	int m_attackHits;

	//�v���C���[�̐l��
	int m_playerNum;

	//�U���ɓ����������ǂ���
	bool m_isHitAttack;

	//�v���C���[�ɓ����������ǂ���
	bool m_isHitPlayer;


	//���W
	VECTOR	 m_pos;

	//�����蔻��
	Rect m_enemyCollision;

};

