#pragma once
#include "Player.h"
#include "Enemy.h"
#include "Camera.h"
#include "Gauge.h"
#include "SceneBase.h"

class Camera;
class Player;
class Enemy;
class Gauge;

class SceneGame : public SceneBase
{
public:
	SceneGame();
	virtual ~SceneGame();

	virtual void Init();
	virtual std::shared_ptr<SceneBase> Update();
	virtual void Draw();
	virtual void End();


private:
	std::shared_ptr<Enemy> m_pEnemy;
	std::shared_ptr<Gauge> m_pGauge;
	std::shared_ptr<Player> m_pPlayer;
	std::shared_ptr<Camera> m_pCamera;


private:
	//�t�F�[�h�C���A�A�E�g
	int m_fadeAlpha;

	//�V�[���I���t���O
	bool m_isSceneEnd;

	//�Q�[���N���A�Ȃ̂��̃t���O
	bool m_isGameClear;

	//�v���C���[�ɓ����������̃t���O
	bool m_isHitPlayer;

	//�v���C���[��HP��0�ɂȂ������̃t���O
	bool m_isHp0;

	//�X�e�[�W���N���A������
	bool m_isStageClear;

	//�v���C���[�̍��W
	VECTOR m_playerPos;

	//�J�����̍��W
	VECTOR m_cameraPos;

	//�����蔻��
	bool m_isPlayerHit;
	bool m_isAttackHit;
	bool m_isGimmickHit;



};

