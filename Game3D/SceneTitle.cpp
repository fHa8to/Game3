#include "SceneTitle.h"
#include "DxLib.h"
#include "SceneGame.h"
#include "Game.h"
#include "Pad.h"

namespace
{
	//フェードイン、フェードアウトの数値
	constexpr int kFadeValue = 255;

	//フェード値の増減
	constexpr int kFadeUpDown = 8;
}

SceneTitle::SceneTitle():m_state(kWait)
{
}

SceneTitle::~SceneTitle()
{
}

void SceneTitle::Init()
{
	isSceneEnd = false;

}

std::shared_ptr<SceneBase> SceneTitle::Update()
{
	if (Pad::isTrigger(PAD_INPUT_A))	// パッドの1ボタンorキーボードのZキー
	{

		isSceneEnd = true;

	}

	if(isSceneEnd && fadeAlpha >= kFadeValue)
	{
		return std::make_shared<SceneGame>();

	}

	m_state = kWait;

	//フレームイン、アウト
	if (isSceneEnd)
	{
		fadeAlpha += kFadeUpDown;
		if (fadeAlpha > kFadeValue)
		{
			fadeAlpha = kFadeValue;
		}
	}
	else
	{
		fadeAlpha -= kFadeUpDown;
		if (fadeAlpha < 0)
		{
			fadeAlpha = 0;
		}
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
