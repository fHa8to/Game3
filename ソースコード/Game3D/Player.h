#pragma once
#include "DxLib.h"
#include "Components.h"
#include <memory>
#include <typeinfo>


class Player
{
public:
	Player();
	virtual ~Player();

	void Update();
	void Draw() const; 

	//移動ベクトルを返す
	Vec3 GetMoveVec();

	//ゲームオーバーフラグを得る
	bool isGameOver();

	// コンポーネントを渡す関数
	template<typename T>
	T* GetComponent() {

		if (typeid(T) == typeid(Transform)) {
			return reinterpret_cast<T*>(&m_Ctransform);
		}
		else if (typeid(T) == typeid(Model)) {
			return reinterpret_cast<T*>(&m_Cmodel);
		}
		else if (typeid(T) == typeid(Capsule)) {
			return reinterpret_cast<T*>(&m_Ccapsule);
		}
		return nullptr;
	}

private:

	//移動関数
	void MoveControl();

	//マップとのコリジョン
	void MapCollision();

	//攻撃関数
	void AttackControl();

	//自身の攻撃のあたり判定をとる
	void AttackCollision();

	//アニメーションコントロール
	void AnimControl();

	//敵との当たり判定をとり位置を調節する
	void EnemyCollision();

	//敵の攻撃との当たり判定をとる
	void EnemyAttackCollision();

	//トランスフォームコンポーネント
	Transform m_Ctransform;

	//3Dモデルコンポーネント
	Model m_Cmodel;

	//アニメーションコンポーネント
	Animation m_Canim;

	//カプセルコンポーネント
	Capsule m_Ccapsule;

	// 攻撃コリジョンカプセル
	Capsule m_CattackCapsule;

	//移動ベクトルを保存しておく
	Vec3 m_moveVec;

	//HP
	int m_HP;

	//攻撃フラグ
	bool m_attackFlug;

	//ダッシュフラグ
	bool m_dashFlug;

	//アタックコリジョン有効化フラグ
	bool m_attackColFlug;

	//死亡フラグ
	bool m_deathFlug;

	//ゲーム終了フラグ
	bool m_gameEndFlug;

	//攻撃フレームカウンタ
	int m_attackFlame;

	//攻撃サウンドハンドル
	int m_attackSoundHandle;

	//攻撃が当たる判定のときに使うフレームカウンタ
	int m_acceptFlameCount;

	//攻撃が当たるときのフラグ
	bool m_acceptFlug;


};

