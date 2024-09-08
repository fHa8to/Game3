#include "SceneGame.h"
#include "DxLib.h"
#include "Camera.h"
#include "SceneClear.h"
#include "SceneOver.h"
#include "Game.h"
#include "Pad.h"

namespace
{

	//�t�F�[�h�C���A�t�F�[�h�A�E�g�̐��l
	constexpr int kFadeValue = 255;

	//�t�F�[�h�l�̑���
	constexpr int kFadeUpDown = 8;

	//���f���̃t�@�C����
	const char* const kModelFilename = "data/model/tileHigh_forest.mv1";

	//���f���̃T�C�Y�ύX
	constexpr float kExpansion = 150.0f;
}

void DrawGrid()
{
	for (int x = -80; x <= 80; x += 10)
	{
		DrawLine3D(VGet(static_cast<float>(x), 0, -80), VGet(static_cast<float>(x), 0, 80), 0xffff00);
	}
	for (int z = -80; z <= 80; z += 10)
	{
		DrawLine3D(VGet(-80, 0, static_cast<float>(z)), VGet(80, 0, static_cast<float>(z)), 0xff0000);
	}

	// X+-,Z+-�̕�����������₷���悤�ɕ\����ǉ�����
	VECTOR dispPos = ConvWorldPosToScreenPos(VGet(500, 0, 0));
	if (dispPos.z >= 0.0f && dispPos.z <= 1.0f)
	{
		DrawStringF(dispPos.x, dispPos.y, "X+", 0xffffff);
	}

	dispPos = ConvWorldPosToScreenPos(VGet(-500, 0, 0));
	if (dispPos.z >= 0.0f && dispPos.z <= 1.0f)
	{
		DrawStringF(dispPos.x, dispPos.y, "X-", 0xffffff);
	}

	dispPos = ConvWorldPosToScreenPos(VGet(0, 0, 500));
	if (dispPos.z >= 0.0f && dispPos.z <= 1.0f)
	{
		DrawStringF(dispPos.x, dispPos.y, "Z+", 0xffffff);
	}

	dispPos = ConvWorldPosToScreenPos(VGet(0, 0, -500));
	if (dispPos.z >= 0.0f && dispPos.z <= 1.0f)
	{
		DrawStringF(dispPos.x, dispPos.y, "Z-", 0xffffff);
	}
}


SceneGame::SceneGame():
	m_isPlayerHit(false),
	m_isEnemyHit(false),
	m_isAttackHit(false),
	m_pos(VGet(0.0f, -300.0f, 0.0f))
{
	m_pEnemy = std::make_shared<Enemy>();
	m_pPlayer = std::make_shared<Player>();
	m_pCamera = std::make_shared<Camera>();
	//3D���f���̓ǂݍ���
	modelHandle = MV1LoadModel(kModelFilename);



}

SceneGame::~SceneGame()
{

}

void SceneGame::Init()
{
	MV1SetScale(modelHandle, VGet(kExpansion, kExpansion, kExpansion));
	m_pPlayer->Init();
	m_pEnemy->Init();
	m_pCamera->Init();


	playerHp = P_HP_MAX;
	playerDrawValue = playerHp * P_DRAW_SIZE;

	enemyHp = E_HP_MAX;
	enemyDrawValue = enemyHp * E_DRAW_SIZE;

}

std::shared_ptr<SceneBase> SceneGame::Update()
{
	
	Pad::Update();

	int pTargetValut = playerHp * P_DRAW_SIZE;

	if (playerDrawValue > pTargetValut)
	{
		playerDrawValue--;
	}
	int eTargetValut = enemyHp * E_DRAW_SIZE;

	if (enemyDrawValue > eTargetValut)
	{
		enemyDrawValue--;
	}

	m_cameraPos = m_pCamera->GetCameraPos();

	m_pPlayer->Update(m_cameraPos);

	m_playerPos = m_pPlayer->GetPos();

	m_isPlayerHit = m_pEnemy->SphereHitFlag(m_pPlayer);

	//m_isEnemyHit = m_pEnemy->SphereHitFlag2(m_pPlayer);


	m_pEnemy->Update(*m_pPlayer);
	m_pCamera->Update(m_playerPos);

	MV1SetPosition(modelHandle, m_pos);



	VECTOR toEnemy = VSub(m_pEnemy->GetPos(), m_pPlayer->GetPos());


	float length = VSize(toEnemy);

	//�v���C���[�ƓG�����������ꍇ
	if (m_isPlayerHit)
	{

		VECTOR posVec;
		VECTOR moveVec;


		//�G�l�~�[�̃x�N�g�����W����v���C���[�̃x�N�g�����W���������x�N�g��
		posVec = VSub(m_pEnemy->GetPos(), m_pPlayer->GetPos());

		moveVec = VScale(posVec, length - (m_pPlayer->GetRadius() + m_pEnemy->GetRadius()));
		m_pPlayer->SetPos(VAdd(m_pPlayer->GetPos(), moveVec));

		playerHp -= 1;

	}

	//if (m_isEnemyHit)
	//{
	//	VECTOR posVec2;
	//	VECTOR moveVec2;

	//	//�G�l�~�[�̃x�N�g�����W����v���C���[�̃x�N�g�����W���������x�N�g��
	//	posVec2 = VSub(m_pEnemy->GetPos(), m_pPlayer->GetPos());

	//	moveVec2 = VScale(posVec2, length - (m_pPlayer->GetRadius() + m_pEnemy->GetRadius()));
	//	m_pPlayer->SetPos(VAdd(m_pPlayer->GetPos(), moveVec2));

	//	enemyHp -= 1;
	//}


	//�v���C���[��HP���[���ɂȂ�����
	if (playerHp <= 0)
	{
		{
			return std::make_shared<SceneOver>();
		}
	}

	if (enemyHp <= 0)
	{
		return std::make_shared<SceneClear>();

	}
	return shared_from_this();	//���g��shared_ptr��Ԃ�


}

void SceneGame::Draw()
{
	// �R�c���f���̕`��
	MV1DrawModel(modelHandle);
	//DrawGrid();
	m_pPlayer->Draw();
	m_pEnemy->Draw();
	m_pCamera->Draw();

	int playerColor = GetColor(0, 255, 0);
	DrawFormatString(20, 600, GetColor(0, 255, 255), "HP ", playerDrawValue);
	DrawFillBox(50, 600, 100 + playerHp * P_DRAW_SIZE, 616, playerColor);
	DrawLineBox(50, 600, 350, 616, GetColor(255, 255, 255));
	int enemyColor = GetColor(255, 0, 0);
	DrawFormatString(20, 50, GetColor(0, 255, 255), "HP ", enemyDrawValue);
	DrawFillBox(50, 50, 100 + enemyHp * E_DRAW_SIZE, 66, enemyColor);
	DrawLineBox(50, 50, 350, 66, GetColor(255, 255, 255));


	//DrawString(8, 8, "SceneGame", GetColor(255, 255, 255));
}

void SceneGame::End()
{
}

