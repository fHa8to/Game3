#include "Player.h"
#include "DxLib.h"
#include "Enemy.h"
#include "Pad.h"
#include <cmath>
#include <iostream>
#include <memory>
#include <array>

namespace
{
	//���f���̃t�@�C����
	const char* const kModelFilename = "data/model/Knight.mv1";



	//�A�j���[�V�����ԍ�
	constexpr int kIdleAnimIndex = 1;
	constexpr int kWalkAnimIndex = 2;
	constexpr int kRunAnimIndex = 7;
	constexpr int kAttackAnimIndex = 21;
	constexpr int kAnimIndex = 3;

	//�ړ���
	constexpr float kSpped = 15.0f;

	//�������W
	constexpr float kPosX = 40.0f;
	constexpr float kPosY = -8000.0f;

	//���f���̃T�C�Y�ύX
	constexpr float kExpansion = 100.0f;


	//�A�j���[�V�����̐؂�ւ��ɂ�����t���[����
	constexpr float kAnimChangeFrame = 8.0f;
	constexpr float kAnimChangeRateSpeed = 1.0f / kAnimChangeFrame;

	//�A�i���O�X�e�B�b�N�ɂ��ړ��֘A
	constexpr float kMaxSpeed = 0.1f;		//�v���C���[�̍ő�ړ����x
	constexpr float kAnalogRaneMin = 0.1f;	//�A�i���O�X�e�B�b�N�̓��͔���͈�
	constexpr float kAnalogRaneMax = 0.8f;
	constexpr float kAnglogInputMax = 1000.0f;	//�A�i���O�X�e�B�b�N�̓��͂����x�N�g����

}

Player::Player():
	modelHandle(-1),
	currentAnimNo(-1),
	prevAnimNo(-1),
	animBlendRate(0.0f),
	angle(0.0f),
	cameraAngle(0.0f)
{
	//3D���f���̓ǂݍ���
	modelHandle = MV1LoadModel(kModelFilename);
}

Player::~Player()
{
}

void Player::Init()
{	

	MV1SetScale(modelHandle, VGet(kExpansion, kExpansion, kExpansion));

	currentAnimNo = MV1AttachAnim(modelHandle, kIdleAnimIndex, -1, false);
	prevAnimNo - 1;
	animBlendRate = 1.0f;

	//�v���C���[�̏����ʒu�ݒ�
	pos = VGet(kPosX, kPosY, 0.0f);
	attackPos = VAdd(pos, VGet(0.0f, 7.0f, 4.0f));


}

void Player::Update(VECTOR cameraPos)
{
	//�A�j���[�V�����̐؂�ւ�
	if (prevAnimNo != -1)
	{
		animBlendRate += kAnimChangeRateSpeed;
		if (animBlendRate >= 1.0f)	animBlendRate = 1.0f;
		//�ύX�O�̃A�j���[�V����100%
		MV1SetAttachAnimBlendRate(modelHandle, prevAnimNo, 1.0f - animBlendRate);
		//�ύX��̃A�j���[�V����0%
		MV1SetAttachAnimBlendRate(modelHandle, currentAnimNo, animBlendRate);

	}



	//�A�j���[�V������i�߂�
	bool isLoop = UpdateAnim(currentAnimNo);
	UpdateAnim(prevAnimNo);
	if (Pad::isPress(PAD_INPUT_RIGHT))
	{
		m_state = kMove;
		m_direction = kDown;
		pos = VAdd(pos, VGet(0.0f,
			0.0f,
			-kSpped));


	}
	if (Pad::isRelase(PAD_INPUT_RIGHT))
	{
		m_state = kWait;
	}

	//�ړ�
	if (Pad::isPress(PAD_INPUT_LEFT))
	{
		m_state = kMove;
		m_direction = kUp;
		pos = VAdd(pos, VGet(0.0f,
			0.0f,
			kSpped));


	}
	if (Pad::isRelase(PAD_INPUT_LEFT))
	{
		m_state = kWait;
	}

	//�ړ�
	if (Pad::isPress(PAD_INPUT_UP))
	{
		m_state = kMove;
		m_direction = kRight;
		pos = VAdd(pos, VGet(kSpped,
			0.0f,
			0.0f));


	}
	if (Pad::isRelase(PAD_INPUT_UP))
	{
		m_state = kWait;
	}

	//�ړ�
	if (Pad::isPress(PAD_INPUT_DOWN))
	{
		m_state = kMove;
		m_direction = kLeft;
		pos = VAdd(pos, VGet(-kSpped,
			0.0f,
			0.0f));


	}
	if (Pad::isRelase(PAD_INPUT_DOWN))
	{
		m_state = kWait;
	}

	if (!isAttack)
	{

		if (Pad::isTrigger PAD_INPUT_1)
		{
			isAttack = true;
			ChangeAnim(kAttackAnimIndex);

		}
	//	else
	//	{
	//		//�A�i���O�X�e�B�b�N���g���Ĉړ�
	//		int analogX = 0;
	//		int analogZ = 0;

	//		GetJoypadAnalogInput(&analogX, &analogZ, DX_INPUT_KEY_PAD1);


	//		//�A�i���O�X�e�B�b�N�̓��͂�10% ~ 80%�͈̔͂��g�p����

	//		//�x�N�g���̒������ő��1000�ɂȂ�

	//		//�v���C���[�̍ő�ړ����x�� 0.01f / frame

	//		VECTOR move = VGet(analogX, 0.0f, -analogZ);	//�x�N�g���̒���0~1000
	//		//0.00~0.01�̒����ɂ���
	//		//�x�N�g���̒������擾����
	//		float len = VSize(move);
	//		//�x�N�g���̒�����0.0~1.0�Ɋ����ɕϊ�����
	//		float rate = len / kAnglogInputMax;

	//		//�A�i���O�X�e�B�b�N�����Ȕ͈͂����O����
	//		rate = (rate - kAnalogRaneMin) / (kAnalogRaneMax - kAnalogRaneMin);
	//		rate = min(rate, 1.0f);
	//		rate = max(rate, 0.0f);

	//		//���x������ł���̂ňړ��x�N�g���ɔ��f����
	//		move = VNorm(move);
	//		float speed = kMaxSpeed * rate;
	//		move = VScale(move, speed);

	//		MATRIX mtx = MGetRotY(-cameraAngle - DX_PI_F / 2);
	//		move = VTransform(move, mtx);


	//		//�ړ���������v���C���[�̌������������肷��
	//		if (VSquareSize(move) > 0.0f)
	//		{
	//			angle = -atan2f(move.z, move.x) - DX_PI_F / 2;
	//		}

	//		pos = VAdd(pos, move);

	//		if (Pad::isPress PAD_INPUT_2)
	//		{
	//			ChangeAnim(kRunAnimIndex);
	//			move = VScale(move, 1.2f);
	//			pos = VAdd(pos, move);
	//		}

	//		VECTOR attackMove = VScale(move, 15.0f);
	//		attackPos = VAdd(pos, attackMove);
	//	}
	}
	else
	{
		//�U���A�j���[�V�������I��������ҋ@�A�j���[�V�������Đ�����
		if (isLoop)
		{

			isAttack = false;
			ChangeAnim(kIdleAnimIndex);
		}
	}


	// �RD���f���̃|�W�V�����ݒ�
	MV1SetPosition(modelHandle, pos);
	MV1SetRotationXYZ(modelHandle, VGet(0, angle, 0));


}

void Player::Draw()
{
	// �R�c���f���̕`��
	MV1DrawModel(modelHandle);
}


bool Player::UpdateAnim(int attachNo)
{
	//�A�j���[�V�������ݒ肳��Ă��Ȃ��̂ŏI��
	if (attachNo == -1) return false;

	//�A�j���[�V������i�s������
	float now = MV1GetAttachAnimTime(modelHandle, attachNo);	//���݂̍Đ��J�E���g���擾
	now += 0.5f;	//�A�j���[�V�����i�߂�

	//���ݍĐ����̃A�j���[�V�����̑��J�E���g���擾
	float total = MV1GetAttachAnimTotalTime(modelHandle, attachNo);
	bool isLoop = false;
	if (now >= total)
	{
		now -= total;
		isLoop = true;
	}

	//�i�߂����Ԃ̐ݒ�
	MV1SetAttachAnimTime(modelHandle, attachNo, now);

	return isLoop;
}

void Player::ChangeAnim(int animIndex)
{
	//����ɌÂ��A�j���[�V�������A�^�b�`����Ă���ꍇ�͂��̎��_�ō폜���Ă���
	if (prevAnimNo != -1)
	{
		MV1DetachAnim(modelHandle, prevAnimNo);
	}

	//���ݍĐ����̑ҋ@�A�j���[�V�����͕ύX�O�̃A�j���[�V����������
	prevAnimNo = currentAnimNo;

	//�ύX��̃A�j���[�V�����Ƃ��čU���A�j���[�V���������߂Đݒ肷��
	currentAnimNo = MV1AttachAnim(modelHandle, animIndex, -1, false);

	//�؂�ւ��̏u�Ԃ͕ύX��̃A�j���[�V�������Đ������
	animBlendRate = 0.0f;

	//�ύX�O�̃A�j���[�V����100%
	MV1SetAttachAnimBlendRate(modelHandle, prevAnimNo, 1.0f - animBlendRate);
	//�ύX��̃A�j���[�V����0%
	MV1SetAttachAnimBlendRate(modelHandle, currentAnimNo, animBlendRate);
}
