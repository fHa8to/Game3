#pragma once
#include <vector>
#include <memory>
#include "Rect.h"
class Knight;
class Bee;
class Slime;
class EnemyManager
{
public:
	EnemyManager();
	virtual ~EnemyManager();

	void Init();

	void Update(Knight* knight, VECTOR playerPos, Rect playerCollision,Rect playerAttackCollision);

	//�`��
	void Draw();	

	//�N���A��������n��
	bool GetStageClear() const noexcept { return m_isStageClear; }
private:

	//�G�̐���
	void CreateEnemy(VECTOR playerPos);

	//�n�`�̐���
	void CreateBee(VECTOR playerPos);

	//�X���C���̐���
	void CreateSlime(VECTOR playerPos);

	//�c��̐l����\��
	void DrawEnemys();

	//�N���A�������ǂ���
	void StageClear(VECTOR playerPos);

private:
	static constexpr int kEnemyNum = 10;

private:

	Bee * m_pBee[kEnemyNum];

	Slime* m_pSlime[kEnemyNum];

	//����
	//�n�`�̓����蔻��
	Rect m_beeCollision[kEnemyNum];

	//�X���C���̓����蔻��
	Rect m_slimeCollision[kEnemyNum];

	//HP��ۑ�
	//�n�`��HP
	int m_beeHp[kEnemyNum];

	//�X���C����HP
	int m_slimeHp[kEnemyNum];

private:
	//�I�̃��f��
	int m_beeHandle;

	//�X���C���̃��f��
	int m_slimeHandle;

	//�ǂ���̓G�𐶐����邩
	int m_randomEnemy;

	//���݂̓G�̐�
	int m_enemyNum;

	//�X�e�[�W1�̓G�̐�
	int m_enemyNumRetention1;

	//�X�e�[�W2�̓G�̐�
	int m_enemyNumRetention2;

	//�X�e�[�W3�̓G�̐�
	int m_enemyNumRetention3;

	//�X�e�[�W4�̓G�̐�
	int m_enemyNumRetention4;

	//�^�C�}�[
	int m_timer;

	//�X�e�[�W��Clear������
	bool m_isStageClear;

	//�X�e�[�W1���N���A����
	bool m_isClear1;

	//�X�e�[�W2���N���A����
	bool m_isClear2;

	//�X�e�[�W3���N���A����
	bool m_isClear3;

	//�X�e�[�W4���N���A����
	bool m_isClear4;

	//�v���C���[�̍��W�ێ�
	VECTOR m_playerPos;

};

