#pragma once
#include <list>
#include <memory>
#include "Singleton.h"
#include "Vec3.h"
#include "Components.h"

class Player;
class EnemyRabbit;
// �G�l�~�[�̊Ǘ����s���V���O���g���N���X
class EnemyManager : public Singleton<EnemyManager>
{
	friend class Singleton<EnemyManager>;
public:

	void Init();

	void Update(Vec3 plPos);

	void Draw() const;

	// �G�l�~�[�̃X�|�[�����~�߂�
	void StopSpawn();

	// �U���J�v�Z�����X�V����
	// �G�l�~�[���J�v�Z���̏�Ԃ��X�V���邽�тɌĂяo��
	void CapsuleUpdate();

	// �G�l�~�[��ێ����郊�X�g�z��
	std::list<std::shared_ptr<EnemyRabbit>> pEnemy;

	// �G�l�~�[�̍U���J�v�Z���̃��X�g�z��
	std::list<std::shared_ptr<Capsule>> pEnemyCupsle;

	// ���Ԃ�Ԃ�
	int GetTime();

private:
	// �v���C�x�[�g�R���X�g���N�^
	EnemyManager() {};

	// ���f���n���h��
	int m_model = 0;

	// �t���[���J�E���^
	int m_flame = 0;
	int m_timeFlame = 0;

	// �G�l�~�[�X�|�[�����s�t���O
	bool m_spawActiveFlug = true;

	// �Q�[���̓�Փx
	int m_level = 1;
};
