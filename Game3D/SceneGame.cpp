#include "SceneGame.h"
#include "DxLib.h"
#include "Camera.h"
#include "SceneClear.h"
#include "Game.h"
#include "Gauge.h"
#include "Pad.h"


SceneGame::SceneGame()
{
}

SceneGame::~SceneGame()
{
}

void SceneGame::Init()
{
	m_player.Init();
	m_enemy.Init();
	m_gauge.Init();

}

std::shared_ptr<SceneBase> SceneGame::Update()
{

	m_camera.Update();
	m_player.Update();
	m_enemy.Update();
	m_gauge.Update();
	if (Pad::isTrigger PAD_INPUT_4)
	{
		return std::make_shared<SceneClear>();

	}
	return shared_from_this();	//é©êgÇÃshared_ptrÇï‘Ç∑
}

void SceneGame::Draw()
{
	m_player.Draw();
	m_enemy.Draw();
	m_gauge.Draw();
	DrawString(8, 8, "SceneGame", GetColor(255, 255, 255));
}

void SceneGame::End()
{
}
