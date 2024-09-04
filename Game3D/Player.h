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

	//���a�̎擾
	float GetRadius() { return m_radius; }


	//�v���C���[
	const VECTOR& GetPos() const { return pos; }




private:

	bool UpdateAnim(int attachNo);
	void ChangeAnim(int animIndex);
	


private:
	enum  state
	{
		kWait,			//�ҋ@��
		kMove,			//�����Ă���
	};

	//�v���C���[���ǂ���������Ă��邩
	enum direction
	{
		kRight,
		kLeft,
		kUp,
		kDown
	};

private:
	int		modelHandle;	//���f���n���h��

	//�A�j���[�V�������
	int currentAnimNo;
	int prevAnimNo;
	float animBlendRate;

	//���
	int m_state;

	//�����Ă������
	int m_direction;

	//A�{�^�������񉟂�����
	int m_countAButton;

	//X�{�^�������񉟂�����
	int m_countXButton;



	//�\�����
	VECTOR pos;
	VECTOR attackPos;
	//�J�����̈ʒu
	VECTOR m_cameraPos;

	float angle;

	//�����蔻��̔��a
	float m_radius;

	//�J�������
	float cameraAngle;

	int isAttack;


};

