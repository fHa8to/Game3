#pragma once
#include "SceneBase.h"

class SceneTitle : public SceneBase
{
public:
	SceneTitle();
	virtual ~SceneTitle();

	virtual void Init();
	virtual std::shared_ptr<SceneBase> Update();
	virtual void Draw();
	virtual void End();

private:
	enum state
	{
		kWait,
	};

private:

	int m_state;

	int handle;

	int fadeAlpha;

	bool isSceneEnd;


};

