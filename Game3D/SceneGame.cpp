#include "SceneGame.h"
#include "DxLib.h"
#include "Camera.h"
#include "SceneClear.h"
#include "Game.h"
#include "Gauge.h"
#include "Pad.h"

namespace
{
	//操作説明の位置
	constexpr int kOperationX = 1110;
	constexpr int kOperationY = 100;

	//フェードイン、フェードアウトの数値
	constexpr int kFadeValue = 255;

	//フェード値の増減
	constexpr int kFadeUpDown = 8;

}

SceneGame::SceneGame()
{
	m_pCamera = std::make_shared<Camera>();
	m_pPlayer = std::make_shared<Player>();
	m_pEnemy = std::make_shared<Enemy>();
	m_pGauge = std::make_shared<Gauge>();

}

SceneGame::~SceneGame()
{
}

void SceneGame::Init()
{
	m_pPlayer->Init();
	m_pEnemy->Init();
	m_pGauge->Init();

}

std::shared_ptr<SceneBase> SceneGame::Update()
{

	m_pCamera->Update();
	m_pPlayer->Update();
	m_pEnemy->Update(*m_pPlayer);
	m_pGauge->Update();
	if (Pad::isTrigger PAD_INPUT_4)
	{
		return std::make_shared<SceneClear>();

	}
	return shared_from_this();	//自身のshared_ptrを返す
}

void SceneGame::Draw()
{
	m_pPlayer->Draw();
	m_pEnemy->Draw();
	m_pGauge->Draw();
	DrawString(8, 8, "SceneGame", GetColor(255, 255, 255));
}

void SceneGame::End()
{
}
