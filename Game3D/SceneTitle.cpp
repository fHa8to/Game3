#include "SceneTitle.h"
#include "DxLib.h"
#include "SceneGame.h"
#include "Game.h"


SceneTitle::SceneTitle()
{
}

SceneTitle::~SceneTitle()
{
}

void SceneTitle::Init()
{
}

std::shared_ptr<SceneBase> SceneTitle::Update()
{
	int Key = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	if (Key & PAD_INPUT_1)	// パッドの1ボタンorキーボードのZキー
	{

		return std::make_shared<SceneGame>();

	}
	return shared_from_this();
}


void SceneTitle::Draw()
{
	DrawString(0, 0, "SceneTitle", GetColor(255, 255, 255));
}

void SceneTitle::End()
{
}
