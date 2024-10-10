#pragma once
#include "EnemyBase.h"
#include "Rect.h"
class Knight;
class Bee : public EnemyBase
{
public:
	Bee(int m_handle, VECTOR playerPos);
	virtual ~Bee();

	void Update(Knight* knight,VECTOR playerPos) override;

	//�v���C���[�̈ʒu�ɂ���Đ�������ʒu��ς���
	void SetPosX(VECTOR playerPos)override;

	//�U���������������̏���
	void HitAttack(Rect playerAttack);

	//�v���C���[�ɂ�����
	void HitPlayer(Knight* knight, Rect playerCollision);
	
	//�n�`�̗̑͂�^����
	int GetBeeHp() const noexcept { return m_hp; }

	//�n�`�̓����蔻���^����
	Rect GetBeeCollision() const noexcept { return m_enemyCollision; }

	//�����������ǂ�����^����
	bool GetHitPlayer() const noexcept { return m_isHitPlayer; }


private:
	//�v���C���[�ɏ����Â߂Â�
	void ComingPlayer(Knight* knight);

	//�v���C���[�ɋ߂Â�����U��
	void Attack();

	//�A�j���[�V�����֘A
	void  Animation();

	//���[�v�������ǂ�����Ԃ�
	bool UpdateAnim(int attachNo);

	//�A�j���[�V�����̕ύX
	void ChangeAnim(int animIndex);


private:
	MV1_COLL_RESULT_POLY* m_pPlayerNum[1];	// �v���C���[�Ɣ��f���ꂽ�|���S���̍\���̂̃A�h���X��ۑ����Ă������߂̃|�C���^�z��
private:
	//�A�j���[�V�������
	int m_currentAnimNo;	//���݂̃A�j���[�V����
	int m_prevAnimNo;		//�ύX�O�̃A�j���[�V����
	float m_animBlendRate;	//�A�j���[�V������������

	//�v���C���[�̐l��
	int m_playerNum;

	//�����_���Ȉʒu
	float m_randomPosX;

	//�U�����Ă��邩��ێ�����
	bool m_isAttacking;

	//�U�����Ă��邩�ǂ���
	bool m_isAttack;

	//�`�悳���I�̍��W
	VECTOR m_beePos;

	//�i�ދ���
	VECTOR m_distance;

};

