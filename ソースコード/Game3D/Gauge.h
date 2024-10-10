#pragma once

#define HP_MAX		5
#define DRAW_SIZE	50

class Gauge
{
public:
	Gauge();
	virtual ~Gauge();

	void Init();
	void Update();
	void Draw();

	bool DrawValue() const { return playerDrawValue; }

private:
	int playerHp;
	int playerDrawValue;
	int keyState[256] = { 0 };

	int enemyHp;
	int enemyDrawValue;
	int enemykeyState[256] = { 0 };

};

