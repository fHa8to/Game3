#include "SceneGame.h"
#include "DxLib.h"
#include "Camera.h"
#include "SceneClear.h"
#include "Game.h"
#include "Gauge.h"
#include "Pad.h"

namespace
{
	//��������̈ʒu
	constexpr int kOperationX = 1110;
	constexpr int kOperationY = 100;

	//�t�F�[�h�C���A�t�F�[�h�A�E�g�̐��l
	constexpr int kFadeValue = 255;

	//�t�F�[�h�l�̑���
	constexpr int kFadeUpDown = 8;

}

SceneGame::SceneGame()
{
	m_pEnemy = std::make_shared<Enemy>();
	m_pGauge = std::make_shared<Gauge>();

}

SceneGame::~SceneGame()
{
	delete m_pPlayer;
	m_pPlayer = nullptr;


	delete m_pCamera;
	m_pCamera = nullptr;

}

void SceneGame::Init()
{
	m_pPlayer = new Player;
	m_pPlayer->Init();
	m_pEnemy->Init();
	m_pGauge->Init();
	m_pCamera = new Camera;
	m_pCamera->Init();


}

std::shared_ptr<SceneBase> SceneGame::Update()
{
	m_cameraPos = m_pCamera->GetCameraPos();

	m_pPlayer->Update(m_cameraPos);

	m_playerPos = m_pPlayer->GetPos();

	m_pEnemy->Update(*m_pPlayer);
	m_pGauge->Update();
	m_pCamera->Update(m_playerPos);
	if (Pad::IsTrigger PAD_INPUT_4)
	{
		return std::make_shared<SceneClear>();

	}
	return shared_from_this();	//���g��shared_ptr��Ԃ�
}

void SceneGame::Draw()
{
	m_pPlayer->Draw();
	m_pEnemy->Draw();
	m_pGauge->Draw();
	m_pCamera->Draw();
	DrawString(8, 8, "SceneGame", GetColor(255, 255, 255));
}

void SceneGame::End()
{
}
