#pragma once
#include "DxLib.h"

class Player
{
public:
	Player();
	virtual ~Player();

	void Init();
	void Update(VECTOR cameraPos);
	void Draw();


	void MoveUpdate(VECTOR cameraPos);

	void Animation(VECTOR cameraPos);


	//���a�̎擾
	float GetRadius() { return m_radius; }


	//�v���C���[�̍��W���擾	
	const VECTOR& GetPos() const { return m_pos; }
	void SetPos(const VECTOR pos) { m_pos = pos; }
		



private:

	bool UpdateAnim(int attachNo);
	void ChangeAnim(int animIndex);
	


private:
	enum  state
	{
		kStandby,		//�ҋ@��
		kWalk,			//����
		kRun,			//����
		kAttack			//�U��

	};


private:
	int		modelHandle;	//���f���n���h��

	//�A�j���[�V�������
	int m_currentAnimNo;
	int m_prevAnimNo;
	float m_animBlendRate;

	//���
	int m_state;

	//�����Ă������
	int m_direction;

	//A�{�^�������񉟂�����
	int m_countAButton;

	//X�{�^�������񉟂�����
	int m_countXButton;



	//�\�����
	VECTOR m_pos;
	VECTOR m_attackPos;
	//�J�����̈ʒu
	VECTOR m_cameraPos;

	float angle = 90.0f * DX_PI_F / 180.0f;

	//�����蔻��̔��a
	float m_radius;

	//�J�������
	float m_cameraAngle;


	//�����Ă��邩
	bool m_iskStandby;

	//�����Ă��邩
	bool m_isWalk;

	//�����Ă��邩
	bool m_isRun;

	//�U�����Ă��邩
	bool m_isAttack;


};

