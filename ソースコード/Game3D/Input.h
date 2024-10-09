#pragma once

#include <array>
#include "DxLib.h"
#include "Singleton.h"
#include "Vec3.h"

//�e�{�^���̒萔
#define INPUT_A 0
#define INPUT_B 1
#define INPUT_X 2
#define INPUT_Y 3
#define INPUT_UP 4
#define INPUT_DOWN 5
#define INPUT_LEFT 6
#define INPUT_RIGHT 7
#define INPUT_START 8
#define INPUT_BACK 9
#define INPUT_LEFT_PUSH 10
#define INPUT_RIGHT_PUSH 11
#define INPUT_LEFT_SHOULDER 12
#define INPUT_RIGHT_SHOULDER 13
#define INPUT_LEFT_TRIGGER 14
#define INPUT_RIGHT_TRIGGER 15
#define INPUT_LEFT_STICK 16
#define INPUT_RIGHT_STICK 17


class Input : public Singleton<Input>
{
	friend class Singleton<Input>;

public:
	//�X�V����
	void Update();

	//�������u�Ԃ��Ƃ�
	bool IsTrigger(int input) const;

	//�����Ă���Ԃ��Ƃ�
	bool InHold(int input) const;

	//�������u�Ԃ��Ƃ�
	bool InRelease(int input) const;

	//�X�e�B�b�N���͂̕����x�N�g����Ԃ�
	Vec3 GetStickVector(int input) const;

	//�X�e�B�b�N���͂̒P�ʕ����x�N�g����Ԃ�
	Vec3 GetStickUnitVector(int input) const;

	//�X�e�B�b�N���͂̒�����Ԃ�
	float GetStickVectorLength(int input) const;

	//�X�e�B�b�N���X����X�l��Ԃ�
	float GetStickThumbX(int input) const;

	//�X�e�B�b�N���X����Y�l��Ԃ�
	float GetStickThumbY(int input) const;

private:

	//���t���[���̃C���v�b�g�X�e�[�g
	XINPUT_STATE m_padState;

	// �O�t���[���̃C���v�b�g�X�e�[�g
	XINPUT_STATE m_lastPadState;

	// �v���C�x�[�g�R���X�g���N�^
	Input() :m_padState(), m_lastPadState() {};

};

