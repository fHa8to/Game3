#include "Player.h"
#include "DxLib.h"
#include "Input.h"
#include "Camera.h"
#include "Constants.h"
#include "Enemy.h"
#include "EnemyManager.h"


Player::Player():
	m_dashFlug(false),
	m_attackFlug(false),
	m_attackColFlug(false),
	m_attackFlame(0),
	m_acceptFlameCount(0),
	m_acceptFlug(false),
	m_HP(10),
	m_deathFlug(false),
	m_gameEndFlug(false)
{
	//大きさの設定
	m_Ctransform.Scale = Constants::getInstance().PLAYER_SCALE;
	m_Ctransform.Position = 0;

	//モデルの初期処理
	int model = MV1LoadModel("data/model/Barbarian.mv1");
	int texture = LoadGraph("data/image/barbarian_texture.png");
	m_Cmodel.InitModel(model, texture);

	// アニメーションの初期処理
	m_Canim.InitAnimation(m_Cmodel, Constants::getInstance().PLAYER_ANIM_IDLE);

	// アニメーション更新
	m_Canim.UpdateAnimation(m_Cmodel);

	// モデルの更新処理
	m_Cmodel.UpdateModel(m_Ctransform);

	// カプセルコリジョンの初期化
	m_Ccapsule.Init(m_Ctransform.Position, Constants::getInstance().PLAYER_COLLISION_RADIUS, Constants::getInstance().PLAYER_HEIGHT);

	// 攻撃判定の無効化
	m_CattackCapsule.Invalidation();

}

Player::~Player()
{
	DeleteSoundMem(m_attackSoundHandle);
}

void Player::Update()
{
	//死んでいないときの処理
	if (!m_deathFlug)
	{
		//移動
		MoveControl();

		//移動後の敵との当たり判定をとり位置を調節する
		EnemyCollision();

		//マップとのコリジョンをとる
		MapCollision();

		//カプセルのセット
		m_Ccapsule.Set(m_Ctransform.Position);

		//攻撃処理
		AttackControl();

		//敵との当たり判定
		AttackCollision();

		//アニメーションコントロール
		AttackControl();

		//敵の攻撃との当たり判定
		EnemyAttackCollision();

	}
	else
	{
		//死亡アニメーションが終了した場合
		if (m_Canim.GetEndAnimFlug())
		{
			m_Canim.ChangeAnimation(m_Cmodel, Constants::getInstance().PLAYER_ANIM_DEAD_IDLE, true);
			m_gameEndFlug = true;
		}
	}

	//アニメーション更新
	m_Canim.UpdateAnimation(m_Cmodel);

	//モデルの更新処理
	m_Cmodel.UpdateModel(m_Ctransform);

}

void Player::Draw() const
{
	m_Cmodel.DrawModel();
	m_Ccapsule.DrawCapsule();
}

Vec3 Player::GetMoveVec()
{
	return m_moveVec;
}

bool Player::isGameOver()
{
	return m_gameEndFlug;
}

void Player::MoveControl()
{
	auto& input = Input::getInstance();

	//移動ベクトル
	Vec3 moveVec;

	//左スティックで平行移動
	if (input.GetStickVectorLength(INPUT_LEFT_STICK) > Constants::getInstance().STICK_INVALID_VALUE && !m_attackColFlug && !m_acceptFlug)
	{
		//カメラの回転を得る
		//m_Ctransform.AngleY = Camera::getInstance().GetAngleY();

		// Y軸回転行列に変換
		MATRIX rotaMtx = MGetRotY(m_Ctransform.AngleY);

		// 傾きの方向が逆なので反転させる
		Vec3 inclination = input.GetStickUnitVector(INPUT_LEFT_STICK) * -1;

		// スティックの傾きをカメラに合わせてY軸回転させる
		moveVec = VTransform(inclination.VGet(), rotaMtx);

		// 移動のタイミングで移動している方向にモデルを回転させる
		Vec3 targetPos = m_Ctransform.Position + moveVec;
		float x = targetPos.x - m_Ctransform.Position.x;
		float z = targetPos.z - m_Ctransform.Position.z;
		float angle = atan2f(x, z);
		m_Ctransform.AngleY = angle + static_cast<float>(DX_PI);

		// 押し込みでダッシュを開始する
		if (input.IsTrigger(INPUT_LEFT_PUSH)) m_dashFlug = true;

		// 傾きとダッシュフラグによって速度が４段階で変化する
		if (input.GetStickVectorLength(INPUT_LEFT_STICK) < Constants::getInstance().PLAYER_MOVE_SCALE_THRESHOLD) {	// 遅い
			if (!m_dashFlug) {
				// 移動ベクトルにプレイヤーの移動速度を掛けた値をポジションに加算
				m_Ctransform.Position += moveVec * Constants::getInstance().PLAYER_MOVE_SCALE_SLOW_WALK;
				m_moveVec = moveVec * Constants::getInstance().PLAYER_MOVE_SCALE_SLOW_WALK;
			}
			else {
				// 移動ベクトルにプレイヤーの移動速度を掛けた値をポジションに加算
				m_Ctransform.Position += moveVec * Constants::getInstance().PLAYER_MOVE_SCALE_SLOW_DASH;
				m_moveVec = moveVec * Constants::getInstance().PLAYER_MOVE_SCALE_SLOW_DASH;
			}
		}
		else {	// 速い
			if (!m_dashFlug) {
				// 移動ベクトルにプレイヤーの移動速度を掛けた値をポジションに加算
				m_Ctransform.Position += moveVec * Constants::getInstance().PLAYER_MOVE_SCALE_FAST_WALK;
				m_moveVec = moveVec * Constants::getInstance().PLAYER_MOVE_SCALE_FAST_WALK;
			}
			else {
				// 移動ベクトルにプレイヤーの移動速度を掛けた値をポジションに加算
				m_Ctransform.Position += moveVec * Constants::getInstance().PLAYER_MOVE_SCALE_FAST_DASH;
				m_moveVec = moveVec * Constants::getInstance().PLAYER_MOVE_SCALE_FAST_DASH;
			}
		}
	}
	else {
		m_moveVec = 0;
		m_dashFlug = false;
	}


	DrawFormatString(10, 60, 0xff0000, "%f", m_moveVec.Length());

}

void Player::MapCollision()
{
	float radius = Constants::getInstance().PLAYER_COLLISION_RADIUS;
	Vec3& pos = m_Ctransform.Position;
	DrawFormatString(10, 10, 0xff0000, "%f %f %f", pos.x, pos.y, pos.z);
	if (pos.x >= Constants::getInstance().STAGE_RANGE - radius)
	{
		pos.x = Constants::getInstance().STAGE_RANGE - radius;
	}
	if (pos.x <= -Constants::getInstance().STAGE_RANGE + radius)
	{
		pos.x = -Constants::getInstance().STAGE_RANGE + radius;
	}
	if (pos.z >= Constants::getInstance().STAGE_RANGE - radius)
	{
		pos.z = Constants::getInstance().STAGE_RANGE - radius;
	}
	if (pos.z <= -Constants::getInstance().STAGE_RANGE + radius)
	{
		pos.z = -Constants::getInstance().STAGE_RANGE + radius;
	}

}

void Player::AttackControl()
{
	//インプットのインスタンスを取得する
	auto& input = Input::getInstance();

	//定数のインスタンスを取得する
	auto& constant = Constants::getInstance();

	//攻撃入力がされていたらフラグを立てる
	if (input.IsTrigger(INPUT_X) && !m_acceptFlug)
	{
		//攻撃カプセルの初期化を行う
		m_attackFlame = true;

		//回転させる攻撃基準値
		Vec3 base = Vec3{ constant.PLAYER_BASE_ATTACK_POS_X, constant.PLAYER_BASE_ATTACK_POS_Y,constant.PLAYER_BASE_ATTACK_POS_Z };

		//モデルの回転を回転行列に変換
		MATRIX rotaMtx = MGetRotY(m_Ctransform.AngleY);

		//攻撃発生位置をモデルに合わせてY軸回転させる
		Vec3 attack = VTransform(base.VGet(), rotaMtx);

		m_CattackCapsule.Init(m_Ctransform.Position + attack, constant.PLAYER_ATTACK_RADIUS, constant.PLAYER_ATTACK_HEIGHT);
		m_CattackCapsule.Invalidation();
	}

	//攻撃フラグが立っているときの処理
	if (m_attackFlug)
	{
		m_attackFlame++;

		//攻撃予備動作が終わったら攻撃コリジョンを有効化する
		if (m_attackFlame >= constant.PLAYER_ATTACK_PREPARATION)
		{
			m_CattackCapsule.Aactivation();

			//回転させる攻撃基準値
			Vec3 base = Vec3{ constant.PLAYER_BASE_ATTACK_POS_X,constant.PLAYER_BASE_ATTACK_POS_Y,constant.PLAYER_BASE_ATTACK_POS_Z };

			// モデルの回転を回転行列に変換
			MATRIX rotaMtx = MGetRotY(m_Ctransform.AngleY);

			// 攻撃発生位置をモデルに合わせてY軸回転させる
			Vec3 attack = VTransform(base.VGet(), rotaMtx);

			m_CattackCapsule.Set(m_Ctransform.Position + attack);

		}

		// カウントが一定数超えたら攻撃カプセルを無効化する
		if (m_attackFlame >= constant.PLAYER_ATTACK_END)
		{
			m_CattackCapsule.Invalidation();
		}

		// 攻撃アニメーションが終了
		if (m_Canim.GetEndAnimFlug()) {

			m_attackFlame = 0;
			// 攻撃フラグを下げる
			m_attackFlug = false;
		}

	}

	m_CattackCapsule.DrawCapsule();
}

void Player::AttackCollision()
{
	//すべての要素を調べる
	for (std::shared_ptr<Enemy> enemy : EnemyManager::getInstance().pEnemy)
	{
		auto enemyPos = enemy->GetComponent<Transform>()->Position;

		//エネミーとのきょりが30以内の時のみ判定する
		if ((enemyPos - m_Ctransform.Position).Length() <= 30.0f)
		{
			//攻撃中
			if (m_CattackCapsule.IsActivation())
			{
				auto pointA = enemy->GetComponent<Capsule>()->PointA;
				auto pointB = enemy->GetComponent<Capsule>()->PointB;
				float dist = m_Ccapsule.CapsuleDistance(m_CattackCapsule.PointA, m_CattackCapsule.PointB, pointA, pointB);
				if (dist <= m_CattackCapsule.Radius + enemy->GetComponent<Capsule>()->Radius && !enemy->IsHit())
				{
					//攻撃が当たっている
					enemy->HitAttackPlayer(m_Ctransform.Position);
				}
			}
		}
	}
}

void Player::AnimControl()
{
	auto& constant = Constants::getInstance();

	if (m_attackFlug)
	{
		//アニメーションの更新
		m_Canim.ChangeAnimation(m_Cmodel, constant.PLAYER_ANIM_SLICE, false);
	}
	else if (m_acceptFlug)
	{
		m_Canim.ChangeAnimation(m_Cmodel, constant.PLAYER_ANIM_HIT, false);
	}
	else if (constant.PLAYER_MOVE_SCALE_FAST_DASH == m_moveVec.Length())
	{
		m_Canim.ChangeAnimation(m_Cmodel, constant.PLAYER_ANIM_FAST_DASH, true);
	}
	else if (constant.PLAYER_MOVE_SCALE_SLOW_DASH == m_moveVec.Length())
	{
		m_Canim.ChangeAnimation(m_Cmodel, constant.PLAYER_ANIM_SLOW_DASH, true);
	}
	else if (constant.PLAYER_MOVE_SCALE_FAST_WALK == m_moveVec.Length())
	{
		m_Canim.ChangeAnimation(m_Cmodel, constant.PLAYER_ANIM_FAST_WALK, true);
	}
	else if (constant.PLAYER_MOVE_SCALE_SLOW_WALK == m_moveVec.Length())
	{
		m_Canim.ChangeAnimation(m_Cmodel, constant.PLAYER_ANIM_SLOW_WALK, true);
	}
	else if (m_moveVec.Length() == 0)
	{
		m_Canim.ChangeAnimation(m_Cmodel, constant.PLAYER_ANIM_IDLE, true);
	}
}

void Player::EnemyCollision()
{
	//すべての敵の要素を調べる
	if (std::shared_ptr<Enemy> enemy : EnemyManager::getInstance().pEnemy)
	{
		auto enemyPos = enemy->GetComponent<Transform>()->Position;

		//エネミーとの距離が30以内の時のみ判定する
		if ((enemyPos - m_Ctransform.Position).Length() <= 30.0f)
		{
			// プレイヤーと敵の線分間の距離を求めお互いの半径よりも距離が短かったら当たっている
			auto pointA = enemy->GetComponent<Capsule>()->PointA;
			auto pointB = enemy->GetComponent<Capsule>()->PointB;
			float dist = m_Ccapsule.CapsuleDistance(m_Ccapsule.PointA, m_Ccapsule.PointB, pointA, pointB);
			if (dist <= m_Ccapsule.Radius + enemy->GetComponent<Capsule>()->Radius) {
				// 敵と当たっている

				// めり込んでいる分の長さを調べる
				float len = enemy->GetComponent<Capsule>()->Radius + m_Ccapsule.Radius;
				len -= dist - 0.1f;

				// 自身の中心から敵の中心までの単位ベクトルを求める
				Vec3 direction = m_Ctransform.Position - enemy->GetComponent<Transform>()->Position;
				direction.Normalize();

				// 単位ベクトルにめり込んだ分の長さを引いた移動ベクトルを再度足す
				m_Ctransform.Position += direction * len;
				m_Ccapsule.Set(m_Ctransform.Position);
			}
		}
	}
}

void Player::EnemyAttackCollision()
{	
	// 攻撃を受けてから２０フレームは無敵時間とする
	if (m_acceptFlug) {
		m_acceptFlameCount++;
		if (m_acceptFlameCount >= 20) {
			m_acceptFlug = false;
			m_acceptFlameCount = 0;
		}
	}
	// 無敵時間中は判定を行わない
	else
	{
		// エネミーマネージャに保存されている攻撃判定のリストを取得する
		auto collision = EnemyManager::getInstance().pEnemyCupsle;

		// 攻撃判定のリストを回して攻撃との当たり判定をとる
		for (std::shared_ptr<Capsule> col : collision) {

			// プレイヤーと敵の線分間の距離を求めお互いの半径よりも距離が短かったら当たっている
			auto pointA = col->PointA;
			auto pointB = col->PointB;
			float dist = m_Ccapsule.CapsuleDistance(m_Ccapsule.PointA, m_Ccapsule.PointB, pointA, pointB);

			// 半径同士を足した数より距離が短かったらあたっている
			if (dist <= m_Ccapsule.Radius + col->Radius) {
				// 攻撃を受けたフラグを立てる
				m_acceptFlug = true;

				// 攻撃を受けたらHPを減らす
				m_HP -= 5;

				// HPが0を下回ったら死ぬ
				if (m_HP <= 0) {
					m_deathFlug = true;

					// 死亡アニメーションを再生
					m_Canim.ChangeAnimation(m_Cmodel, Constants::getInstance().PLAYER_ANIM_DEAD, false);
				}
			}

		}
	}

}
