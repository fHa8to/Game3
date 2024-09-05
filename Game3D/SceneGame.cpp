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

void DrawGrid()
{
	for (int x = -800; x <= 800; x += 100)
	{
		DrawLine3D(VGet(static_cast<float>(x), 0, -800), VGet(static_cast<float>(x), 0, 800), 0xffff00);
	}
	for (int z = -800; z <= 800; z += 100)
	{
		DrawLine3D(VGet(-800, 0, static_cast<float>(z)), VGet(800, 0, static_cast<float>(z)), 0xff0000);
	}

	// X+-,Z+-の方向が分かりやすいように表示を追加する
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

	DrawGrid();

	if (Pad::IsTrigger PAD_INPUT_10)
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
	m_pCamera->Draw();
	DrawString(8, 8, "SceneGame", GetColor(255, 255, 255));
}

void SceneGame::End()
{
}

