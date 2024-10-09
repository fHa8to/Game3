#include "EnemyManager.h"
#include "DxLib.h"
#include "Enemy.h"
#include "Components.h"
#include "Constants.h"
#include "SceneManager.h"

void EnemyManager::Init()
{
	m_spawActiveFlug = true;
	m_level = 1;
	m_flame = 0;
	m_timeFlame = 0;

	pEnemy.clear();
	pEnemyCupsle.clear();

	// モデルのロード
	m_model = MV1LoadModel("data/model/Rabit.mv1");

	// ゲームが始まってすぐ敵がスポーンするようにする
	m_flame = Constants::getInstance().SPAWN_INTERVAL_EASY;
}

void EnemyManager::Update(Vec3 plPos)
{
	// 定数のインスタンスを取得する
	auto& constants = Constants::getInstance();

	// 常に時間を計測して難易度を変える
	m_timeFlame++;
	if (m_timeFlame >= constants.TIME_FRAME_NIGHTMARE && m_level != constants.LEVEL_NIGHTMARE) {
		m_level = constants.LEVEL_NIGHTMARE;
	}
	else if (m_timeFlame >= constants.TIME_FRAME_HARD && m_level != constants.LEVEL_HARD) {
		m_level = constants.LEVEL_HARD;
	}
	else if (m_timeFlame >= constants.TIME_FRAME_NIGHTMARE && m_level != constants.LEVEL_NORMAL) {
		m_level = constants.LEVEL_NORMAL;
	}

	// エネミーをスポーンさせる関数を定義
	auto spawn = [&](int coolTime){
		if (m_flame >= coolTime) {
			pEnemy.push_back(std::make_shared<EnemyRabbit>(MV1DuplicateModel(m_model), GetRand(3)));
			m_flame = 0;
		}
	};

	// 難易度によってスポーンするインターバルを変更する
	if (m_spawActiveFlug) {
		m_flame++;
		if (m_level == constants.LEVEL_EASY) {
			spawn(constants.SPAWN_INTERVAL_EASY);
		}
		else if (m_level == constants.LEVEL_HARD) {
			spawn(constants.SPAWN_INTERVAL_NORMAL);
		}
		else if (m_level == constants.LEVEL_NIGHTMARE){
			spawn(constants.SPAWN_INTERVAL_HARD);
		}
		else {
			spawn(constants.SPAWN_INTERVAL_NIGHTMARE);
		}
	}

	// 要素の更新処理
	for (std::shared_ptr<EnemyRabbit> enemy : pEnemy) {
		enemy->Update(plPos,pEnemyCupsle);
	}

	// エネミーが死んでいたら削除する
	for (auto it = pEnemy.begin(); it != pEnemy.end();) {
		if ((*it)->IsDead()) {
			it = pEnemy.erase(it);	//要素を削除し次の要素を指すイテレータを取得
		}
		else {
			it++;
		}
	}
}

void EnemyManager::Draw() const
{
	// 要素の描画処理
	for (std::shared_ptr<EnemyRabbit> enemy : pEnemy) {
		enemy->Draw();
	}
}

void EnemyManager::StopSpawn()
{
	m_spawActiveFlug = false;
}

void EnemyManager::CapsuleUpdate()
{
	// 攻撃カプセルの管理
	for (auto it = pEnemyCupsle.begin(); it != pEnemyCupsle.end();) {
		if (!(*it)->IsActivation()) {
			it = pEnemyCupsle.erase(it);
		}
		else {
			it++;
		}
	}
}

int EnemyManager::GetTime()
{
	return m_timeFlame;
}
