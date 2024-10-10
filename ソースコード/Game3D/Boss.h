#pragma once
#include "EnemyBase.h"
#include "Rect.h"
class Boss :public EnemyBase
{
public:
	Boss(int handle,VECTOR playerPos);
	virtual ~Boss();

	void Update(Knight* knight, VECTOR playerPos)override;

	//�v���C���[�̈ʒu�ɂ���Đ�������ʒu��ς���
	void SetPosX(VECTOR playerPos)override;

private:

	//�U���p�^�[��
	void AttackPattern(VECTOR playerPos);

	//�ߐڍU��
	void Attack(VECTOR playerPos);

	//�������U��
	void LongRangeAttack(VECTOR playerPos);

	//�ړ��֘A
	void Move(Knight* knight);

	//�A�j���[�V�����֘A
	void  Animation();

	//���[�v�������ǂ�����Ԃ�
	bool UpdateAnim(int attachNo);

	//�A�j���[�V�����̕ύX
	void ChangeAnim(int animIndex);

private:;

	//�C�e�̃��f��
	int m_cannonballHandle;

	//�J�E���g
	int m_count;

	//�A�j���[�V�������
	int m_currentAnimNo;	//���݂̃A�j���[�V����
	int m_prevAnimNo;		//�ύX�O�̃A�j���[�V����
	float m_animBlendRate;	//�A�j���[�V������������

	//��󂩂痎���Ă���
	float m_skyAboveY;

	//�v���C���[�Ƃ̋���
	VECTOR m_distance;

	//�C�e�̒��e�ʒu
	VECTOR m_impactPos;

	//�ߐڍU���̓����蔻��
	Rect m_attackCollision;

	//�������U���̓����蔻��
	Rect m_longRangeAttackCollision;
};

