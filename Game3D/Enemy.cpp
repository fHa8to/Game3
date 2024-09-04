#include "Enemy.h"
#include "DxLib.h"
#include "Player.h"
#include <cmath>

namespace
{
	//���f���̃t�@�C����
	const char* const kModelFilename = "data/model/Knight.mv1";

	//���f���̃T�C�Y�ύX
	constexpr float kExpansion = 100.0f;


	//�A�j���[�V�����ԍ�
	constexpr int kIdleAnimIndex = 1;
	//�U�����肪��������܂łɂ����鎞��
	constexpr float kAttackFrameStart = 20;
	//�U�����肪�I������܂łɂ����鎞��
	constexpr float kAttackFrameEnd = 30;

	//�A�j���[�V�����̐؂�ւ��ɂ�����t���[����
	constexpr float kAnimChangeFrame = 8.0f;
	constexpr float kAnimChangeRateSpeed = 1.0f / kAnimChangeFrame;

	//�����蔻��
	constexpr float kAddPosY = 8.0f;
}

Enemy::Enemy():
	modelHandle(-1),
	currentAnimNo(-1),
	prevAnimNo(-1),
	animBlendRate(0.0f),
	angle(0.0f)

{
	//3D���f���̓ǂݍ���
	modelHandle = MV1LoadModel(kModelFilename);
}

Enemy::~Enemy()
{
}

void Enemy::Init()
{
	MV1SetScale(modelHandle, VGet(kExpansion, kExpansion, kExpansion));

	currentAnimNo = MV1AttachAnim(modelHandle, kIdleAnimIndex, -1, false);
	prevAnimNo - 1;
	animBlendRate = 1.0f;

	//�v���C���[�̏����ʒu�ݒ�
	pos = VGet(200.0f, -8000.0f, 0.0f);


}

void Enemy::Update(Player& player)
{	
	VECTOR enemyToPlayer = VSub(player.GetPos(), pos);

	// �RD���f���̃|�W�V�����ݒ�
	MV1SetPosition(modelHandle, pos);
}

void Enemy::Draw()
{
	// �R�c���f���̕`��
	MV1DrawModel(modelHandle);

#ifdef _DEBUG

	DrawSphere3D(VAdd(pos, VGet(0, 8, 0)), m_radius, 8, 0xffffff, 0xffffff, false);
	DrawFormatString(0, 32, 0xffffff, "Enemy(x:%f,y:%f,z:%f)", pos.x, pos.y, pos.z);

#endif

}

//���̓����蔻��
bool Enemy::SphereHitFlag(std::shared_ptr<Player> pPlayer)
{
	float delX = (pos.x - pPlayer->GetPos().x) * (pos.x - pPlayer->GetPos().x);
	float delY = ((pos.y + kAddPosY) - (pPlayer->GetPos().y + kAddPosY)) *
		((pos.y + kAddPosY) - (pPlayer->GetPos().y + kAddPosY));
	float delZ = (pos.z - pPlayer->GetPos().z) * (pos.z - pPlayer->GetPos().z);

	//���Ƌ��̋���
	float Distance = sqrt(delX + delY + delZ);

	//���Ƌ��̋������v���C���ƃG�l�~�[�̔��a�����������ꍇ
	if (Distance < m_radius + pPlayer->GetRadius())
	{
		return true;
	}

	return false;
}

bool Enemy::AttackSphereHitFlag(std::shared_ptr<Player> pPlayer)
{
	return false;
}
