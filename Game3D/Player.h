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

	//���a�̎擾
	float GetRadius() { return m_radius; }


	//�v���C���[
	const VECTOR& GetPos() const { return pos; }




private:

	bool UpdateAnim(int attachNo);
	void ChangeAnim(int animIndex);
	


private:
	int		modelHandle;	//���f���n���h��

	//�A�j���[�V�������
	int currentAnimNo;
	int prevAnimNo;
	float animBlendRate;


	//�\�����
	VECTOR pos;
	VECTOR attackPos;

	float angle;

	//�����蔻��̔��a
	float m_radius;

	//�J�������
	float cameraAngle;

	int isAttack;

};

