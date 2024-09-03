#include "Enemy.h"
#include "DxLib.h"
#include <cmath>

namespace
{
	//���f���̃t�@�C����
	const char* const kModelFilename = "data/model/Knight.mv1";

	//�A�j���[�V�����ԍ�
	constexpr int kIdleAnimIndex = 1;
	//�U�����肪��������܂łɂ����鎞��
	constexpr float kAttackFrameStart = 20;
	//�U�����肪�I������܂łɂ����鎞��
	constexpr float kAttackFrameEnd = 30;

	//�A�j���[�V�����̐؂�ւ��ɂ�����t���[����
	constexpr float kAnimChangeFrame = 8.0f;
	constexpr float kAnimChangeRateSpeed = 1.0f / kAnimChangeFrame;

	//�A�i���O�X�e�B�b�N�ɂ��ړ��֘A
	constexpr float kMaxSpeed = 0.1f;		//�v���C���[�̍ő�ړ����x
	constexpr float kAnalogRaneMin = 0.1f;	//�A�i���O�X�e�B�b�N�̓��͔���͈�
	constexpr float kAnalogRaneMax = 0.8f;
	constexpr float kAnglogInputMax = 1000.0f;	//�A�i���O�X�e�B�b�N�̓��͂����x�N�g����

}

Enemy::Enemy():
	modelHandle(-1),
	currentAnimNo(-1),
	prevAnimNo(-1),
	animBlendRate(0.0f),
	angle(0.0f)

{
}

Enemy::~Enemy()
{
}

void Enemy::Init()
{
	//3D���f���̓ǂݍ���
	modelHandle = MV1LoadModel(kModelFilename);

	currentAnimNo = MV1AttachAnim(modelHandle, kIdleAnimIndex, -1, false);
	prevAnimNo - 1;
	animBlendRate = 1.0f;

	//�v���C���[�̏����ʒu�ݒ�
	pos = VGet(0.0f, 0.0f, 5.0f);


}

void Enemy::Update()
{	

	// �RD���f���̃|�W�V�����ݒ�
	MV1SetPosition(modelHandle, pos);
}

void Enemy::Draw()
{
	// �R�c���f���̕`��
	MV1DrawModel(modelHandle);
}
