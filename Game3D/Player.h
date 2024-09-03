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

	//�U�����q�b�g�����Ƃ�
	void HitAttack();

	const VECTOR& GetPos() const { return pos; }

	// �_���[�W��H������Ƃ�
	void OnDamage(VECTOR targetPos, int damagePoint);

	//�K�[�h���ɍU�����ꂽ�Ƃ�
	void OnGuardingAttack();

	//�W���X�g�K�[�h���ɍU�����ꂽ�Ƃ�
	void OnJustGuardingAttack();



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
	float angle;

	//�J�������
	float cameraAngle;

	int isAttack;

};

