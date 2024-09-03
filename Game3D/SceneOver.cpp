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
	if (Key & PAD_INPUT_1)	// �p�b�h��1�{�^��or�L�[�{�[�h��Z�L�[
	{
		return std::make_shared<SceneTitle>();
	}
	return shared_from_this();	//���g��shared_ptr��Ԃ�

}

void SceneOver::Draw()
{
	DrawString(8, 8, "SceneOver", GetColor(255, 255, 255));

}

void SceneOver::End()
{
}
