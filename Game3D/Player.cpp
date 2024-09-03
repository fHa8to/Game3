#include "Player.h"
#include "DxLib.h"
#include "Enemy.h"
#include <cmath>
#include <iostream>
#include <memory>
#include <array>

namespace
{
	//���f���̃t�@�C����
	const char* const kModelFilename = "data/model/Knight.mv1";

	// �v���C���[�T�C�Y
	constexpr float kSize = 15.0f;
	//�U������T�C�Y
	constexpr float kAttackSize = 25.0f;
	//�v���C���[�̃��f���T�C�Y
	constexpr float kModelSize = 20.0f;
	//�X�s�[�h�{��
	constexpr float kMoveSpeedDashRate = 2.2f;	// �����Ă���Ƃ��̃X�s�[�h
	constexpr float kAccelerationRate = 0.5f;	// �����x

	// �v���C���[�̐���X�s�[�h
	constexpr float kPlayerAngleSpeed = 0.2f;
	//�U���d������
	constexpr int kAttackStanTime = 6;
	//�U�����ɓ�����X�s�[�h
	constexpr float kAttackMoveSpeed = 2.0f;
	//�A���U���ő��
	constexpr int kAultiAttackNum = 3;
	//���ߍU���̔����܂ł̎���
	constexpr int kChargeAttackTime = 30;
	//���G����
	constexpr int kInvincibleTime = 60;
	// �U������
	constexpr float kAttackDistance = 20.0f;
	// �U�����Z�b�g����
	constexpr int kResetAttackFlagTime = 25;
	//�m�b�N�o�b�N�X�s�[�h
	constexpr float kKnockBackSpeed = 3.0f;
	//�m�b�N�o�b�N�X�s�[�h������
	constexpr float kKnockBackSpeedDecrease = 0.2f;
	//�U���{��
	constexpr float kMultiAttackMultiplier1 = 0.6f;		//�A���U��1
	constexpr float kMultiAttackMultiplier2 = 0.8f;		//�A���U��2
	constexpr float kMultiAttackMultiplier3 = 1.2f;		//�A���U��3
	constexpr float kMultiAttackMultiplier4 = 2.0f;		//�A���U��4

	//�U���̎��
	enum kAttackKind
	{
		Attack1,
		Attack2,
		Attack3,
		Attack4,

		AttackKindNum,
	};

	//�U���t���[���̎n�܂�̃^�C�~���O
	constexpr std::array<int, kAttackKind::AttackKindNum> kAttackFrameStart =
	{
		20,
		20,
		20,
		20,
	};
	//�U���t���[���̏I���̃^�C�~���O
	constexpr std::array<int, kAttackKind::AttackKindNum> kAttackFrameEnd =
	{
		30,
		30,
		30,
		30,
	};

	//�U���Ԃ̃v���C���[�̓����鎞��
	constexpr int kAttackIntervalMoveTime = 8;
	//�K�[�h�A�j���[�V����
	constexpr int kGuardFirst = 22;
	constexpr int kGuardNow = 25;
	constexpr int kGuardHit = 24;
	//�K�[�h���ɓ�����X�s�[�h
	constexpr float kGuardMoveSpeed = 0.5f;
	//�W���X�g�K�[�h�t���[��
	constexpr int kJustGuardFrame = 5;

	//�ړ��̕⊮�l
	constexpr float kNowVecNum = 0.8f;
	constexpr float kNextVecNum = 0.2f;

	//�A�j���[�V�������x
	enum kStateAnimSpeed
	{
		Idle = 2,				//�ҋ@
		Walk = 2,				//����
		Dash = 1,				//�_�b�V��
		KnockBack = 1,			//�m�b�N�o�b�N
		Attack = 1,				//�U��
		Gaude = 1,				//�K�[�h
		Dead = 1,				//���S
	};

	//�`��\�ȋ���
	constexpr float kDrawDistance = 50.0f;


	//�f�o�b�O�p�̃X�s�[�h
	constexpr float kDebugSpeed = 10.0f;
	//�f�o�b�O�p�̍U����
	constexpr int kDebugAtk = 300;
	//�f�o�b�O�p�̕������x
	constexpr float kDebugMoveSpeedWalk = 5.5f;	// �����Ă���Ƃ��̃X�s�[�h
	constexpr float kDebugMoveSpeedDash = 9.0f;	// �����Ă���Ƃ��̃X�s�[�h
	constexpr float kDebugMoveSpeedAcc = 1.5f;	// �����̃X�s�[�h

	//�U������T�C�Y
	constexpr float kAttacKSize = 25.0f;


	//�A�j���[�V�����ԍ�
	constexpr int kIdleAnimIndex = 1;
	constexpr int kAttackAnimIndex = 21;
	constexpr int kAnimIndex = 3;

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
}

Player::~Player()
{
}

void Player::Init()
{
	//3D���f���̓ǂݍ���
	modelHandle = MV1LoadModel(kModelFilename);

	currentAnimNo = MV1AttachAnim(modelHandle, kIdleAnimIndex, -1, false);
	prevAnimNo - 1;
	animBlendRate = 1.0f;

	//�v���C���[�̏����ʒu�ݒ�
	pos = VGet(0.0f, 0.0f, 0.0f);


}

void Player::Update()
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

	if (!isAttack)
	{

		int Key = GetJoypadInputState(DX_INPUT_KEY_PAD1);
		if ((Key & PAD_INPUT_1) && pos.y == 0)
		{
			isAttack = true;
			ChangeAnim(kAttackAnimIndex);

		}
		else
		{
			//�A�i���O�X�e�B�b�N���g���Ĉړ�
			int analogX = 0;
			int analogY = 0;

			GetJoypadAnalogInput(&analogX, &analogY, DX_INPUT_KEY_PAD1);


			//�A�i���O�X�e�B�b�N�̓��͂�10% ~ 80%�͈̔͂��g�p����

			//�x�N�g���̒������ő��1000�ɂȂ�

			//�v���C���[�̍ő�ړ����x�� 0.01f / frame

			VECTOR move = VGet(analogX, 0.0f, -analogY);	//�x�N�g���̒���0~1000
			//0.00~0.01�̒����ɂ���
			//�x�N�g���̒������擾����
			float len = VSize(move);
			//�x�N�g���̒�����0.0~1.0�Ɋ����ɕϊ�����
			float rate = len / kAnglogInputMax;

			//�A�i���O�X�e�B�b�N�����Ȕ͈͂����O����
			rate = (rate - kAnalogRaneMin) / (kAnalogRaneMax - kAnalogRaneMin);
			rate = min(rate, 1.0f);
			rate = max(rate, 0.0f);

			//���x������ł���̂ňړ��x�N�g���ɔ��f����
			move = VNorm(move);
			float speed = kMaxSpeed * rate;

			move = VScale(move, speed);



			//�ړ���������v���C���[�̌������������肷��
			if (VSquareSize(move) > 0.0f)
			{
				angle = -atan2f(move.z, move.x) - DX_PI_F / 2;
			}

			pos = VAdd(pos, move);

		}
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

void Player::HitAttack()
{

}

void Player::OnDamage(VECTOR targetPos, int damagePoint)
{
}

void Player::OnGuardingAttack()
{
}

void Player::OnJustGuardingAttack()
{
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
