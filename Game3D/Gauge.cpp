#include "Gauge.h"
#include "DxLib.h"

Gauge::Gauge()
{
}

Gauge::~Gauge()
{
}

void Gauge::Init()
{
	playerHp = HP_MAX;
	playerDrawValue = playerHp * DRAW_SIZE;
	enemyHp = HP_MAX;
	enemyDrawValue = playerHp * DRAW_SIZE;
}

void Gauge::Update()
{
	GetHitKeyStateAllEx(keyState);

	if (keyState[KEY_INPUT_LEFT] == 1)
	{
		playerHp -= 1;
	}

	int pTargetValut = playerHp * DRAW_SIZE;

	if (playerDrawValue > pTargetValut)
	{
		playerDrawValue--;
	}

	if (keyState[KEY_INPUT_UP] == 1)
	{
		enemyHp -= 1;
	}

	int eTargetValut = enemyHp * DRAW_SIZE;

	if (enemyDrawValue > eTargetValut)
	{
		enemyDrawValue--;
	}

}

void Gauge::Draw()
{
	//playerDrawValue ‚Ì’l‚ð•\Ž¦
	DrawFormatString(20, 600, GetColor(0, 255, 255), "HP :%4d", playerDrawValue);

	int playerColor = GetColor(0, 255, 0);
	
	int enemyColor = GetColor(255, 0, 0);


	DrawFormatString(20, 50, GetColor(0, 255, 255), "HP :%4d", enemyDrawValue);


	DrawFillBox(100, 600, 100 + playerDrawValue, 616, playerColor);
	DrawLineBox(100, 600, 350, 616, GetColor(255, 255, 255));



	DrawFillBox(100, 50, 100 + enemyDrawValue, 66, enemyColor);
	DrawLineBox(100, 50, 350, 66, GetColor(255, 255, 255));
}
