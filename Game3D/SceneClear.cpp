#include "SceneClear.h"
#include "DxLib.h"
#include "Game.h"
#include "SceneTitle.h"

SceneClear::SceneClear()
{
}

SceneClear::~SceneClear()
{
}

void SceneClear::Init()
{
}

std::shared_ptr<SceneBase>  SceneClear::Update()
{
	int Key = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	if (Key & PAD_INPUT_1)	// �p�b�h��1�{�^��or�L�[�{�[�h��Z�L�[
	{
		return std::make_shared<SceneTitle>();
	}
	return shared_from_this();	//���g��shared_ptr��Ԃ�

}

void SceneClear::Draw()
{
	DrawString(8, 8, "SceneClear", GetColor(255, 255, 255));

}

void SceneClear::End()
{
}
