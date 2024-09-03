#pragma once
#include "SceneBase.h"

class SceneOver : public SceneBase
{
public:
	SceneOver();
	virtual ~SceneOver();

	virtual void Init();
	virtual std::shared_ptr<SceneBase> Update();
	virtual void Draw();
	virtual void End();

};

