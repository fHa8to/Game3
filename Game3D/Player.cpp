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
	m_currentAnimNo(-1),
	m_prevAnimNo(-1),
	m_animBlendRate(0.0f),
	angle(0.0f),
	m_cameraAngle(0.0f)
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

	m_currentAnimNo = MV1AttachAnim(modelHandle, kIdleAnimIndex, -1, false);
	m_prevAnimNo - 1;
	m_animBlendRate = 1.0f;

	//�v���C���[�̏����ʒu�ݒ�
	m_pos = VGet(kPosX, kPosY, 0.0f);
	m_attackPos = VAdd(m_pos, VGet(0.0f, 7.0f, 4.0f));


}

void Player::Update(VECTOR cameraPos)
{
	//�A�j���[�V�����̐؂�ւ�
	if (m_prevAnimNo != -1)
	{
		m_animBlendRate += kAnimChangeRateSpeed;
		if (m_animBlendRate >= 1.0f)	m_animBlendRate = 1.0f;
		//�ύX�O�̃A�j���[�V����100%
		MV1SetAttachAnimBlendRate(modelHandle, m_prevAnimNo, 1.0f - m_animBlendRate);
		//�ύX��̃A�j���[�V����0%
		MV1SetAttachAnimBlendRate(modelHandle, m_currentAnimNo, m_animBlendRate);

	}



	//�A�j���[�V������i�߂�
	bool isLoop = UpdateAnim(m_currentAnimNo);
	UpdateAnim(m_prevAnimNo);
	if (Pad::IsPress(PAD_INPUT_RIGHT))
	{
		m_state = kMove;
		m_direction = kDown;
		m_pos = VAdd(m_pos, VGet(0.0f,
			0.0f,
			-kSpped));


	}
	if (Pad::IsRelase(PAD_INPUT_RIGHT))
	{
		m_state = kWait;
	}

	//�ړ�
	if (Pad::IsPress(PAD_INPUT_LEFT))
	{
		m_state = kMove;
		m_direction = kUp;
		m_pos = VAdd(m_pos, VGet(0.0f,
			0.0f,
			kSpped));


	}
	if (Pad::IsRelase(PAD_INPUT_LEFT))
	{
		m_state = kWait;
	}

	//�ړ�
	if (Pad::IsPress(PAD_INPUT_UP))
	{
		m_state = kMove;
		m_direction = kRight;
		m_pos = VAdd(m_pos, VGet(kSpped,
			0.0f,
			0.0f));


	}
	if (Pad::IsRelase(PAD_INPUT_UP))
	{
		m_state = kWait;
	}

	//�ړ�
	if (Pad::IsPress(PAD_INPUT_DOWN))
	{
		m_state = kMove;
		m_direction = kLeft;
		m_pos = VAdd(m_pos, VGet(-kSpped,
			0.0f,
			0.0f));


	}
	if (Pad::IsRelase(PAD_INPUT_DOWN))
	{
		m_state = kWait;
	}

	if (Pad::IsPress(PAD_INPUT_2))
	{

	}

	if (!m_isAttack)
	{

		if (Pad::IsTrigger PAD_INPUT_1)
		{
			m_isAttack = true;
			ChangeAnim(kAttackAnimIndex);

		}
		else
		{
			//�U���A�j���[�V�������I��������ҋ@�A�j���[�V�������Đ�����
			if (isLoop)
			{

				m_isAttack = false;
				ChangeAnim(kIdleAnimIndex);
			}
		}

	}
	// �RD���f���̃|�W�V�����ݒ�
	MV1SetPosition(modelHandle, m_pos);
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
	if (m_prevAnimNo != -1)
	{
		MV1DetachAnim(modelHandle, m_prevAnimNo);
	}

	//���ݍĐ����̑ҋ@�A�j���[�V�����͕ύX�O�̃A�j���[�V����������
	m_prevAnimNo = m_currentAnimNo;

	//�ύX��̃A�j���[�V�����Ƃ��čU���A�j���[�V���������߂Đݒ肷��
	m_currentAnimNo = MV1AttachAnim(modelHandle, animIndex, -1, false);

	//�؂�ւ��̏u�Ԃ͕ύX��̃A�j���[�V�������Đ������
	m_animBlendRate = 0.0f;

	//�ύX�O�̃A�j���[�V����100%
	MV1SetAttachAnimBlendRate(modelHandle, m_prevAnimNo, 1.0f - m_animBlendRate);
	//�ύX��̃A�j���[�V����0%
	MV1SetAttachAnimBlendRate(modelHandle, m_currentAnimNo, m_animBlendRate);
}
