#include "Player.h"
#include "DxLib.h"
#include "Input.h"
#include "Camera.h"
#include "Constants.h"
#include "Enemy.h"
#include "EnemyManager.h"


Player::Player():
	m_dashFlug(false),
	m_attackFlug(false),
	m_attackColFlug(false),
	m_attackFlame(0),
	m_acceptFlameCount(0),
	m_acceptFlug(false),
	m_HP(10),
	m_deathFlug(false),
	m_gameEndFlug(false)
{
	//�傫���̐ݒ�
	m_Ctransform.Scale = Constants::getInstance().PLAYER_SCALE;
	m_Ctransform.Position = 0;

	//���f���̏�������
	int model = MV1LoadModel("data/model/Barbarian.mv1");
	int texture = LoadGraph("data/image/barbarian_texture.png");
	m_Cmodel.InitModel(model, texture);

	// �A�j���[�V�����̏�������
	m_Canim.InitAnimation(m_Cmodel, Constants::getInstance().PLAYER_ANIM_IDLE);

	// �A�j���[�V�����X�V
	m_Canim.UpdateAnimation(m_Cmodel);

	// ���f���̍X�V����
	m_Cmodel.UpdateModel(m_Ctransform);

	// �J�v�Z���R���W�����̏�����
	m_Ccapsule.Init(m_Ctransform.Position, Constants::getInstance().PLAYER_COLLISION_RADIUS, Constants::getInstance().PLAYER_HEIGHT);

	// �U������̖�����
	m_CattackCapsule.Invalidation();

}

Player::~Player()
{
	DeleteSoundMem(m_attackSoundHandle);
}

void Player::Update()
{
	//����ł��Ȃ��Ƃ��̏���
	if (!m_deathFlug)
	{
		//�ړ�
		MoveControl();

		//�ړ���̓G�Ƃ̓����蔻����Ƃ�ʒu�𒲐߂���
		EnemyCollision();

		//�}�b�v�Ƃ̃R���W�������Ƃ�
		MapCollision();

		//�J�v�Z���̃Z�b�g
		m_Ccapsule.Set(m_Ctransform.Position);

		//�U������
		AttackControl();

		//�G�Ƃ̓����蔻��
		AttackCollision();

		//�A�j���[�V�����R���g���[��
		AttackControl();

		//�G�̍U���Ƃ̓����蔻��
		EnemyAttackCollision();

	}
	else
	{
		//���S�A�j���[�V�������I�������ꍇ
		if (m_Canim.GetEndAnimFlug())
		{
			m_Canim.ChangeAnimation(m_Cmodel, Constants::getInstance().PLAYER_ANIM_DEAD_IDLE, true);
			m_gameEndFlug = true;
		}
	}

	//�A�j���[�V�����X�V
	m_Canim.UpdateAnimation(m_Cmodel);

	//���f���̍X�V����
	m_Cmodel.UpdateModel(m_Ctransform);

}

void Player::Draw() const
{
	m_Cmodel.DrawModel();
	m_Ccapsule.DrawCapsule();
}

Vec3 Player::GetMoveVec()
{
	return m_moveVec;
}

bool Player::isGameOver()
{
	return m_gameEndFlug;
}

void Player::MoveControl()
{
	auto& input = Input::getInstance();

	//�ړ��x�N�g��
	Vec3 moveVec;

	//���X�e�B�b�N�ŕ��s�ړ�
	if (input.GetStickVectorLength(INPUT_LEFT_STICK) > Constants::getInstance().STICK_INVALID_VALUE && !m_attackColFlug && !m_acceptFlug)
	{
		//�J�����̉�]�𓾂�
		//m_Ctransform.AngleY = Camera::getInstance().GetAngleY();

		// Y����]�s��ɕϊ�
		MATRIX rotaMtx = MGetRotY(m_Ctransform.AngleY);

		// �X���̕������t�Ȃ̂Ŕ��]������
		Vec3 inclination = input.GetStickUnitVector(INPUT_LEFT_STICK) * -1;

		// �X�e�B�b�N�̌X�����J�����ɍ��킹��Y����]������
		moveVec = VTransform(inclination.VGet(), rotaMtx);

		// �ړ��̃^�C�~���O�ňړ����Ă�������Ƀ��f������]������
		Vec3 targetPos = m_Ctransform.Position + moveVec;
		float x = targetPos.x - m_Ctransform.Position.x;
		float z = targetPos.z - m_Ctransform.Position.z;
		float angle = atan2f(x, z);
		m_Ctransform.AngleY = angle + static_cast<float>(DX_PI);

		// �������݂Ń_�b�V�����J�n����
		if (input.IsTrigger(INPUT_LEFT_PUSH)) m_dashFlug = true;

		// �X���ƃ_�b�V���t���O�ɂ���đ��x���S�i�K�ŕω�����
		if (input.GetStickVectorLength(INPUT_LEFT_STICK) < Constants::getInstance().PLAYER_MOVE_SCALE_THRESHOLD) {	// �x��
			if (!m_dashFlug) {
				// �ړ��x�N�g���Ƀv���C���[�̈ړ����x���|�����l���|�W�V�����ɉ��Z
				m_Ctransform.Position += moveVec * Constants::getInstance().PLAYER_MOVE_SCALE_SLOW_WALK;
				m_moveVec = moveVec * Constants::getInstance().PLAYER_MOVE_SCALE_SLOW_WALK;
			}
			else {
				// �ړ��x�N�g���Ƀv���C���[�̈ړ����x���|�����l���|�W�V�����ɉ��Z
				m_Ctransform.Position += moveVec * Constants::getInstance().PLAYER_MOVE_SCALE_SLOW_DASH;
				m_moveVec = moveVec * Constants::getInstance().PLAYER_MOVE_SCALE_SLOW_DASH;
			}
		}
		else {	// ����
			if (!m_dashFlug) {
				// �ړ��x�N�g���Ƀv���C���[�̈ړ����x���|�����l���|�W�V�����ɉ��Z
				m_Ctransform.Position += moveVec * Constants::getInstance().PLAYER_MOVE_SCALE_FAST_WALK;
				m_moveVec = moveVec * Constants::getInstance().PLAYER_MOVE_SCALE_FAST_WALK;
			}
			else {
				// �ړ��x�N�g���Ƀv���C���[�̈ړ����x���|�����l���|�W�V�����ɉ��Z
				m_Ctransform.Position += moveVec * Constants::getInstance().PLAYER_MOVE_SCALE_FAST_DASH;
				m_moveVec = moveVec * Constants::getInstance().PLAYER_MOVE_SCALE_FAST_DASH;
			}
		}
	}
	else {
		m_moveVec = 0;
		m_dashFlug = false;
	}


	DrawFormatString(10, 60, 0xff0000, "%f", m_moveVec.Length());

}

void Player::MapCollision()
{
	float radius = Constants::getInstance().PLAYER_COLLISION_RADIUS;
	Vec3& pos = m_Ctransform.Position;
	DrawFormatString(10, 10, 0xff0000, "%f %f %f", pos.x, pos.y, pos.z);
	if (pos.x >= Constants::getInstance().STAGE_RANGE - radius)
	{
		pos.x = Constants::getInstance().STAGE_RANGE - radius;
	}
	if (pos.x <= -Constants::getInstance().STAGE_RANGE + radius)
	{
		pos.x = -Constants::getInstance().STAGE_RANGE + radius;
	}
	if (pos.z >= Constants::getInstance().STAGE_RANGE - radius)
	{
		pos.z = Constants::getInstance().STAGE_RANGE - radius;
	}
	if (pos.z <= -Constants::getInstance().STAGE_RANGE + radius)
	{
		pos.z = -Constants::getInstance().STAGE_RANGE + radius;
	}

}

void Player::AttackControl()
{
	//�C���v�b�g�̃C���X�^���X���擾����
	auto& input = Input::getInstance();

	//�萔�̃C���X�^���X���擾����
	auto& constant = Constants::getInstance();

	//�U�����͂�����Ă�����t���O�𗧂Ă�
	if (input.IsTrigger(INPUT_X) && !m_acceptFlug)
	{
		//�U���J�v�Z���̏��������s��
		m_attackFlame = true;

		//��]������U����l
		Vec3 base = Vec3{ constant.PLAYER_BASE_ATTACK_POS_X, constant.PLAYER_BASE_ATTACK_POS_Y,constant.PLAYER_BASE_ATTACK_POS_Z };

		//���f���̉�]����]�s��ɕϊ�
		MATRIX rotaMtx = MGetRotY(m_Ctransform.AngleY);

		//�U�������ʒu�����f���ɍ��킹��Y����]������
		Vec3 attack = VTransform(base.VGet(), rotaMtx);

		m_CattackCapsule.Init(m_Ctransform.Position + attack, constant.PLAYER_ATTACK_RADIUS, constant.PLAYER_ATTACK_HEIGHT);
		m_CattackCapsule.Invalidation();
	}

	//�U���t���O�������Ă���Ƃ��̏���
	if (m_attackFlug)
	{
		m_attackFlame++;

		//�U���\�����삪�I�������U���R���W������L��������
		if (m_attackFlame >= constant.PLAYER_ATTACK_PREPARATION)
		{
			m_CattackCapsule.Aactivation();

			//��]������U����l
			Vec3 base = Vec3{ constant.PLAYER_BASE_ATTACK_POS_X,constant.PLAYER_BASE_ATTACK_POS_Y,constant.PLAYER_BASE_ATTACK_POS_Z };

			// ���f���̉�]����]�s��ɕϊ�
			MATRIX rotaMtx = MGetRotY(m_Ctransform.AngleY);

			// �U�������ʒu�����f���ɍ��킹��Y����]������
			Vec3 attack = VTransform(base.VGet(), rotaMtx);

			m_CattackCapsule.Set(m_Ctransform.Position + attack);

		}

		// �J�E���g����萔��������U���J�v�Z���𖳌�������
		if (m_attackFlame >= constant.PLAYER_ATTACK_END)
		{
			m_CattackCapsule.Invalidation();
		}

		// �U���A�j���[�V�������I��
		if (m_Canim.GetEndAnimFlug()) {

			m_attackFlame = 0;
			// �U���t���O��������
			m_attackFlug = false;
		}

	}

	m_CattackCapsule.DrawCapsule();
}

void Player::AttackCollision()
{
	//���ׂĂ̗v�f�𒲂ׂ�
	for (std::shared_ptr<Enemy> enemy : EnemyManager::getInstance().pEnemy)
	{
		auto enemyPos = enemy->GetComponent<Transform>()->Position;

		//�G�l�~�[�Ƃ̂���肪30�ȓ��̎��̂ݔ��肷��
		if ((enemyPos - m_Ctransform.Position).Length() <= 30.0f)
		{
			//�U����
			if (m_CattackCapsule.IsActivation())
			{
				auto pointA = enemy->GetComponent<Capsule>()->PointA;
				auto pointB = enemy->GetComponent<Capsule>()->PointB;
				float dist = m_Ccapsule.CapsuleDistance(m_CattackCapsule.PointA, m_CattackCapsule.PointB, pointA, pointB);
				if (dist <= m_CattackCapsule.Radius + enemy->GetComponent<Capsule>()->Radius && !enemy->IsHit())
				{
					//�U�����������Ă���
					enemy->HitAttackPlayer(m_Ctransform.Position);
				}
			}
		}
	}
}

void Player::AnimControl()
{
	auto& constant = Constants::getInstance();

	if (m_attackFlug)
	{
		//�A�j���[�V�����̍X�V
		m_Canim.ChangeAnimation(m_Cmodel, constant.PLAYER_ANIM_SLICE, false);
	}
	else if (m_acceptFlug)
	{
		m_Canim.ChangeAnimation(m_Cmodel, constant.PLAYER_ANIM_HIT, false);
	}
	else if (constant.PLAYER_MOVE_SCALE_FAST_DASH == m_moveVec.Length())
	{
		m_Canim.ChangeAnimation(m_Cmodel, constant.PLAYER_ANIM_FAST_DASH, true);
	}
	else if (constant.PLAYER_MOVE_SCALE_SLOW_DASH == m_moveVec.Length())
	{
		m_Canim.ChangeAnimation(m_Cmodel, constant.PLAYER_ANIM_SLOW_DASH, true);
	}
	else if (constant.PLAYER_MOVE_SCALE_FAST_WALK == m_moveVec.Length())
	{
		m_Canim.ChangeAnimation(m_Cmodel, constant.PLAYER_ANIM_FAST_WALK, true);
	}
	else if (constant.PLAYER_MOVE_SCALE_SLOW_WALK == m_moveVec.Length())
	{
		m_Canim.ChangeAnimation(m_Cmodel, constant.PLAYER_ANIM_SLOW_WALK, true);
	}
	else if (m_moveVec.Length() == 0)
	{
		m_Canim.ChangeAnimation(m_Cmodel, constant.PLAYER_ANIM_IDLE, true);
	}
}

void Player::EnemyCollision()
{
	//���ׂĂ̓G�̗v�f�𒲂ׂ�
	if (std::shared_ptr<Enemy> enemy : EnemyManager::getInstance().pEnemy)
	{
		auto enemyPos = enemy->GetComponent<Transform>()->Position;

		//�G�l�~�[�Ƃ̋�����30�ȓ��̎��̂ݔ��肷��
		if ((enemyPos - m_Ctransform.Position).Length() <= 30.0f)
		{
			// �v���C���[�ƓG�̐����Ԃ̋��������߂��݂��̔��a�����������Z�������瓖�����Ă���
			auto pointA = enemy->GetComponent<Capsule>()->PointA;
			auto pointB = enemy->GetComponent<Capsule>()->PointB;
			float dist = m_Ccapsule.CapsuleDistance(m_Ccapsule.PointA, m_Ccapsule.PointB, pointA, pointB);
			if (dist <= m_Ccapsule.Radius + enemy->GetComponent<Capsule>()->Radius) {
				// �G�Ɠ������Ă���

				// �߂荞��ł��镪�̒����𒲂ׂ�
				float len = enemy->GetComponent<Capsule>()->Radius + m_Ccapsule.Radius;
				len -= dist - 0.1f;

				// ���g�̒��S����G�̒��S�܂ł̒P�ʃx�N�g�������߂�
				Vec3 direction = m_Ctransform.Position - enemy->GetComponent<Transform>()->Position;
				direction.Normalize();

				// �P�ʃx�N�g���ɂ߂荞�񂾕��̒������������ړ��x�N�g�����ēx����
				m_Ctransform.Position += direction * len;
				m_Ccapsule.Set(m_Ctransform.Position);
			}
		}
	}
}

void Player::EnemyAttackCollision()
{	
	// �U�����󂯂Ă���Q�O�t���[���͖��G���ԂƂ���
	if (m_acceptFlug) {
		m_acceptFlameCount++;
		if (m_acceptFlameCount >= 20) {
			m_acceptFlug = false;
			m_acceptFlameCount = 0;
		}
	}
	// ���G���Ԓ��͔�����s��Ȃ�
	else
	{
		// �G�l�~�[�}�l�[�W���ɕۑ�����Ă���U������̃��X�g���擾����
		auto collision = EnemyManager::getInstance().pEnemyCupsle;

		// �U������̃��X�g���񂵂čU���Ƃ̓����蔻����Ƃ�
		for (std::shared_ptr<Capsule> col : collision) {

			// �v���C���[�ƓG�̐����Ԃ̋��������߂��݂��̔��a�����������Z�������瓖�����Ă���
			auto pointA = col->PointA;
			auto pointB = col->PointB;
			float dist = m_Ccapsule.CapsuleDistance(m_Ccapsule.PointA, m_Ccapsule.PointB, pointA, pointB);

			// ���a���m�𑫂�������苗�����Z�������炠�����Ă���
			if (dist <= m_Ccapsule.Radius + col->Radius) {
				// �U�����󂯂��t���O�𗧂Ă�
				m_acceptFlug = true;

				// �U�����󂯂���HP�����炷
				m_HP -= 5;

				// HP��0����������玀��
				if (m_HP <= 0) {
					m_deathFlug = true;

					// ���S�A�j���[�V�������Đ�
					m_Canim.ChangeAnimation(m_Cmodel, Constants::getInstance().PLAYER_ANIM_DEAD, false);
				}
			}

		}
	}

}
