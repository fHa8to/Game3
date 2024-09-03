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
}

void Gauge::Update()
{
	GetHitKeyStateAllEx(keyState);

	if (keyState[KEY_INPUT_LEFT] == 1)
	{
		playerHp -= 1;
	}

	int TargetValut = playerHp * DRAW_SIZE;

	if (playerDrawValue > TargetValut)
	{
		playerDrawValue--;
	}
	
}

void Gauge::Draw()
{
	//playerDrawValue ‚Ì’l‚ð•\Ž¦
	DrawFormatString(20, 600, GetColor(0, 255, 255), "playerHp :%4d", playerDrawValue);

	int color = GetColor(0, 255, 0);

	if (playerDrawValue < HP_MAX * DRAW_SIZE / 2)
	{
		color = GetColor(255, 255, 0);
	}

	if (playerDrawValue <= 1 * DRAW_SIZE)
	{
		color = GetColor(255, 0, 0);
	}

	DrawFillBox(100, 600, 100 + playerDrawValue, 616, color);
	DrawLineBox(100, 600, 350, 616, GetColor(255, 255, 255));
}
