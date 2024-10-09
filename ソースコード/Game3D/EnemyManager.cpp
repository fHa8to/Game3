#include "EnemyManager.h"
#include "DxLib.h"
#include "Enemy.h"
#include "Components.h"
#include "Constants.h"
#include "SceneManager.h"

void EnemyManager::Init()
{
	m_spawActiveFlug = true;
	m_level = 1;
	m_flame = 0;
	m_timeFlame = 0;

	pEnemy.clear();
	pEnemyCupsle.clear();

	// ���f���̃��[�h
	m_model = MV1LoadModel("data/model/Rabit.mv1");

	// �Q�[�����n�܂��Ă����G���X�|�[������悤�ɂ���
	m_flame = Constants::getInstance().SPAWN_INTERVAL_EASY;
}

void EnemyManager::Update(Vec3 plPos)
{
	// �萔�̃C���X�^���X���擾����
	auto& constants = Constants::getInstance();

	// ��Ɏ��Ԃ��v�����ē�Փx��ς���
	m_timeFlame++;
	if (m_timeFlame >= constants.TIME_FRAME_NIGHTMARE && m_level != constants.LEVEL_NIGHTMARE) {
		m_level = constants.LEVEL_NIGHTMARE;
	}
	else if (m_timeFlame >= constants.TIME_FRAME_HARD && m_level != constants.LEVEL_HARD) {
		m_level = constants.LEVEL_HARD;
	}
	else if (m_timeFlame >= constants.TIME_FRAME_NIGHTMARE && m_level != constants.LEVEL_NORMAL) {
		m_level = constants.LEVEL_NORMAL;
	}

	// �G�l�~�[���X�|�[��������֐����`
	auto spawn = [&](int coolTime){
		if (m_flame >= coolTime) {
			pEnemy.push_back(std::make_shared<EnemyRabbit>(MV1DuplicateModel(m_model), GetRand(3)));
			m_flame = 0;
		}
	};

	// ��Փx�ɂ���ăX�|�[������C���^�[�o����ύX����
	if (m_spawActiveFlug) {
		m_flame++;
		if (m_level == constants.LEVEL_EASY) {
			spawn(constants.SPAWN_INTERVAL_EASY);
		}
		else if (m_level == constants.LEVEL_HARD) {
			spawn(constants.SPAWN_INTERVAL_NORMAL);
		}
		else if (m_level == constants.LEVEL_NIGHTMARE){
			spawn(constants.SPAWN_INTERVAL_HARD);
		}
		else {
			spawn(constants.SPAWN_INTERVAL_NIGHTMARE);
		}
	}

	// �v�f�̍X�V����
	for (std::shared_ptr<EnemyRabbit> enemy : pEnemy) {
		enemy->Update(plPos,pEnemyCupsle);
	}

	// �G�l�~�[������ł�����폜����
	for (auto it = pEnemy.begin(); it != pEnemy.end();) {
		if ((*it)->IsDead()) {
			it = pEnemy.erase(it);	//�v�f���폜�����̗v�f���w���C�e���[�^���擾
		}
		else {
			it++;
		}
	}
}

void EnemyManager::Draw() const
{
	// �v�f�̕`�揈��
	for (std::shared_ptr<EnemyRabbit> enemy : pEnemy) {
		enemy->Draw();
	}
}

void EnemyManager::StopSpawn()
{
	m_spawActiveFlug = false;
}

void EnemyManager::CapsuleUpdate()
{
	// �U���J�v�Z���̊Ǘ�
	for (auto it = pEnemyCupsle.begin(); it != pEnemyCupsle.end();) {
		if (!(*it)->IsActivation()) {
			it = pEnemyCupsle.erase(it);
		}
		else {
			it++;
		}
	}
}

int EnemyManager::GetTime()
{
	return m_timeFlame;
}
