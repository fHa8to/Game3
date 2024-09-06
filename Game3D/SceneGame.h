#pragma once
#include "Player.h"
#include "Enemy.h"
#include "Camera.h"
#include "Gauge.h"
#include "SceneBase.h"

class Camera;
class Player;
class Enemy;
class Gauge;

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
	std::shared_ptr<Enemy> m_pEnemy;
	std::shared_ptr<Gauge> m_pGauge;
	std::shared_ptr<Player> m_pPlayer;
	std::shared_ptr<Camera> m_pCamera;


private:
	//フェードイン、アウト
	int m_fadeAlpha;

	//シーン終了フラグ
	bool m_isSceneEnd;

	//ゲームクリアなのかのフラグ
	bool m_isGameClear;

	//プレイヤーに当たったかのフラグ
	bool m_isHitPlayer;

	//プレイヤーのHPが0になったかのフラグ
	bool m_isHp0;

	//ステージをクリアしたか
	bool m_isStageClear;

	//プレイヤーの座標
	VECTOR m_playerPos;

	//カメラの座標
	VECTOR m_cameraPos;

	//当たり判定
	bool m_isPlayerHit;
	bool m_isAttackHit;
	bool m_isGimmickHit;



};

