#include "SceneOver.h"
#include "DxLib.h"
#include "Game.h"
#include "SceneTitle.h"

SceneOver::SceneOver()
{
}

SceneOver::~SceneOver()
{
}

void SceneOver::Init()
{
}

std::shared_ptr<SceneBase> SceneOver::Update()
{
	int Key = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	if (Key & PAD_INPUT_1)	// パッドの1ボタンorキーボードのZキー
	{
		return std::make_shared<SceneTitle>();
	}
	return shared_from_this();	//自身のshared_ptrを返す

}

void SceneOver::Draw()
{
	DrawString(8, 8, "SceneOver", GetColor(255, 255, 255));

}

void SceneOver::End()
{
}
