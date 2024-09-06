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
	constexpr float kAddm_posY = 1.0f;

	//�p�x
	constexpr float kAngle = 270.0f * DX_PI_F / 180.0f;

}

Enemy::Enemy():
	modelHandle(-1),
	currentAnimNo(-1),
	prevAnimNo(-1),
	animBlendRate(0.0f),
	angle(0.0f),
	m_radius(100.0f)

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

	//�G�l�~�[�̏����ʒu�ݒ�
	m_pos = VGet(-5.0f, 0.0f, 0.0f);


}

void Enemy::Update(Player& player)
{	

	MV1SetRotationXYZ(modelHandle, VGet(0, kAngle, 0));

	VECTOR enemyToPlayer = VSub(player.GetPos(), m_pos);

	// �RD���f���̃|�W�V�����ݒ�
	MV1SetPosition(modelHandle, m_pos);
}

void Enemy::Draw()
{
	// �R�c���f���̕`��
	MV1DrawModel(modelHandle);

#ifdef _DEBUG

	DrawSphere3D(VAdd(m_pos, VGet(0, 100, 0)), m_radius, 8, 0xffffff, 0xffffff, false);
	DrawFormatString(0, 32, 0xffffff, "Enemy(x:%f,y:%f,z:%f)", m_pos.x, m_pos.y, m_pos.z);

#endif

}

//���̓����蔻��
bool Enemy::SphereHitFlag(std::shared_ptr<Player> pPlayer)
{
	float delX = (m_pos.x - pPlayer->GetPos().x) * (m_pos.x - pPlayer->GetPos().x);
	float delY = ((m_pos.y + kAddm_posY) - (pPlayer->GetPos().y + kAddm_posY)) *
		((m_pos.y + kAddm_posY) - (pPlayer->GetPos().y + kAddm_posY));
	float delZ = (m_pos.z - pPlayer->GetPos().z) * (m_pos.z - pPlayer->GetPos().z);

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
