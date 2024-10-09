#pragma once
#include <list>
#include <memory>
#include "Singleton.h"
#include "Vec3.h"
#include "Components.h"

class Player;
class EnemyRabbit;
// エネミーの管理を行うシングルトンクラス
class EnemyManager : public Singleton<EnemyManager>
{
	friend class Singleton<EnemyManager>;
public:

	void Init();

	void Update(Vec3 plPos);

	void Draw() const;

	// エネミーのスポーンを止める
	void StopSpawn();

	// 攻撃カプセルを更新する
	// エネミーがカプセルの状態を更新するたびに呼び出す
	void CapsuleUpdate();

	// エネミーを保持するリスト配列
	std::list<std::shared_ptr<EnemyRabbit>> pEnemy;

	// エネミーの攻撃カプセルのリスト配列
	std::list<std::shared_ptr<Capsule>> pEnemyCupsle;

	// 時間を返す
	int GetTime();

private:
	// プライベートコンストラクタ
	EnemyManager() {};

	// モデルハンドル
	int m_model = 0;

	// フレームカウンタ
	int m_flame = 0;
	int m_timeFlame = 0;

	// エネミースポーン実行フラグ
	bool m_spawActiveFlug = true;

	// ゲームの難易度
	int m_level = 1;
};
