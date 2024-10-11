#pragma once
#include "DxLib.h"
#include <memory>

class Enemy;
class Player
{
public:
	Player();
	virtual ~Player();

	void Init();
	void Update();
	void Draw();

	//�J�����̕������擾
	void SetCameraAngle(float angle) { m_cameraAngle = angle; }

	//���a�̎擾
	float GetRadius() { return m_radius; }

	//�U���̔��a
	float GetAttackRadius() { return m_attackRadius; }


	//�v���C���[�̍��W���擾	
	const VECTOR GetPos() const { return m_pos; }
	void SetPos(const VECTOR pos) { m_pos = pos; }

	//�v���C���[��HP���擾
	const int& GetHp() const { return m_hp; }
	void SetHp(const int hp) { m_hp = hp; }

	//�v���C���[�̍U���̓����蔻��𐶐����邩�̃t���O���擾
	const bool& GetAttackGeneration() const { return m_isAttackGeneration; }
	const bool& GetSkillGeneration() const { return m_isSkillGeneration; }

	void SetCommand(const bool isCommand) { m_isCommand = isCommand; }

	//�v���C���[�̍U���̍��W���擾
	void OnGimmickHitUpdate();

	//�v���C���[�_���[�W�̃t���O�擾
	void SetDamage(const bool damage) { m_isDamage = damage; }

	//�A�j���[�V�����̃Z�b�g�t���O
	void SetAnimDamage(const bool animDamage);

	//���񂾂Ƃ��̔���
	void SetIsDown(const bool isDown) { m_isDown = isDown; }



	//�U���ƓG�̂����蔻��
	bool SphereHitFlag(std::shared_ptr<Enemy> pEnemy);


private:


	bool UpdateAnim(int attachNo);

	void ChangeAnim(int animIndex);

	//�ړ��֐�
	void Move();

	//�X�e�[�W�O�ɏo�Ȃ��悤�ɂ��鏈��
	void StageProcess();


private:
	std::shared_ptr<Enemy> m_pEnemy;
private:


	//����
	enum  direction
	{
		kRight,
		kLeft,
		kUp,
		kDown
	};


private:
	int		m_modelHandle;	//���f���n���h��

	float m_stamina;
	bool m_isStamina;

	//�U�����t���O
	bool m_isAttack;
	bool m_isSkill;
	bool m_isWalk;
	bool m_isDash;
	bool m_isDown;
	bool m_isAvoid;

	//�A�j���[�V�������
	int m_animIndex;
	int m_currentAnimNo;
	int m_prevAnimNo;
	float m_animBlendRate;


	//�A�j���[�V�����t���O
	bool m_isAnimIdle;
	bool m_isAnimAttack;
	bool m_isAnimWalk;
	bool m_isAnimDash;
	bool m_isAnimDamage;
	bool m_isAnimDown;

	//���
	int m_state;

	//�����Ă������
	int m_direction;

	//A�{�^�������񉟂�����
	int m_countAButton;

	//X�{�^�������񉟂�����
	int m_countXButton;


	//�����Ă��邩��ێ�����
	bool m_isMove;
	bool m_isCommand;
	bool m_isAttacking;


	//HP
	int m_hp;

	float m_analogX;
	float m_analogZ;

	//�\�����
	VECTOR m_pos;
	VECTOR m_attackPos;
	VECTOR m_attackDir;

	//�J�����̈ʒu
	VECTOR m_cameraPos;

	float m_angle;

	//�����蔻��̔��a
	float m_radius;
	float m_attackRadius;


	//�����蔻��̔����t���O
	bool m_isAttackGeneration;
	bool m_isSkillGeneration;

	//�J�������
	float m_cameraAngle;


	bool m_isDamage;

	//�����Ă��邩
	bool m_iskStandby;


	//�����Ă��邩
	bool m_isRun;

	//�U�����Ă��邩


};

