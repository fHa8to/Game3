#pragma once
#include "DxLib.h"
#include "Components.h"
#include <memory>
#include <typeinfo>


class Player
{
public:
	Player();
	virtual ~Player();

	void Update();
	void Draw() const; 

	//�ړ��x�N�g����Ԃ�
	Vec3 GetMoveVec();

	//�Q�[���I�[�o�[�t���O�𓾂�
	bool isGameOver();

	// �R���|�[�l���g��n���֐�
	template<typename T>
	T* GetComponent() {

		if (typeid(T) == typeid(Transform)) {
			return reinterpret_cast<T*>(&m_Ctransform);
		}
		else if (typeid(T) == typeid(Model)) {
			return reinterpret_cast<T*>(&m_Cmodel);
		}
		else if (typeid(T) == typeid(Capsule)) {
			return reinterpret_cast<T*>(&m_Ccapsule);
		}
		return nullptr;
	}

private:

	//�ړ��֐�
	void MoveControl();

	//�}�b�v�Ƃ̃R���W����
	void MapCollision();

	//�U���֐�
	void AttackControl();

	//���g�̍U���̂����蔻����Ƃ�
	void AttackCollision();

	//�A�j���[�V�����R���g���[��
	void AnimControl();

	//�G�Ƃ̓����蔻����Ƃ�ʒu�𒲐߂���
	void EnemyCollision();

	//�G�̍U���Ƃ̓����蔻����Ƃ�
	void EnemyAttackCollision();

	//�g�����X�t�H�[���R���|�[�l���g
	Transform m_Ctransform;

	//3D���f���R���|�[�l���g
	Model m_Cmodel;

	//�A�j���[�V�����R���|�[�l���g
	Animation m_Canim;

	//�J�v�Z���R���|�[�l���g
	Capsule m_Ccapsule;

	// �U���R���W�����J�v�Z��
	Capsule m_CattackCapsule;

	//�ړ��x�N�g����ۑ����Ă���
	Vec3 m_moveVec;

	//HP
	int m_HP;

	//�U���t���O
	bool m_attackFlug;

	//�_�b�V���t���O
	bool m_dashFlug;

	//�A�^�b�N�R���W�����L�����t���O
	bool m_attackColFlug;

	//���S�t���O
	bool m_deathFlug;

	//�Q�[���I���t���O
	bool m_gameEndFlug;

	//�U���t���[���J�E���^
	int m_attackFlame;

	//�U���T�E���h�n���h��
	int m_attackSoundHandle;

	//�U���������锻��̂Ƃ��Ɏg���t���[���J�E���^
	int m_acceptFlameCount;

	//�U����������Ƃ��̃t���O
	bool m_acceptFlug;


};

