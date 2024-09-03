#pragma once
#include "Player.h"
#include "Enemy.h"
#include "Camera.h"
#include "Gauge.h"
#include "SceneBase.h"

class SceneGame : public SceneBase
{
public:
	SceneGame();
	virtual ~SceneGame();

	virtual void Init();
	virtual std::shared_ptr<SceneBase> Update();
	virtual void Draw();
	virtual void End();


private:
	Camera	m_camera;
	Player	m_player;
	Enemy	m_enemy;
	Gauge	m_gauge;


};

