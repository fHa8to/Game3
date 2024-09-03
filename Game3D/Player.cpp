#include "Player.h"
#include "DxLib.h"
#include "Enemy.h"
#include <cmath>
#include <iostream>
#include <memory>
#include <array>

namespace
{
	//モデルのファイル名
	const char* const kModelFilename = "data/model/Knight.mv1";

	// プレイヤーサイズ
	constexpr float kSize = 15.0f;
	//攻撃判定サイズ
	constexpr float kAttackSize = 25.0f;
	//プレイヤーのモデルサイズ
	constexpr float kModelSize = 20.0f;
	//スピード倍率
	constexpr float kMoveSpeedDashRate = 2.2f;	// 走っているときのスピード
	constexpr float kAccelerationRate = 0.5f;	// 加速度

	// プレイヤーの旋回スピード
	constexpr float kPlayerAngleSpeed = 0.2f;
	//攻撃硬直時間
	constexpr int kAttackStanTime = 6;
	//攻撃中に動けるスピード
	constexpr float kAttackMoveSpeed = 2.0f;
	//連続攻撃最大回数
	constexpr int kAultiAttackNum = 3;
	//ため攻撃の発生までの時間
	constexpr int kChargeAttackTime = 30;
	//無敵時間
	constexpr int kInvincibleTime = 60;
	// 攻撃距離
	constexpr float kAttackDistance = 20.0f;
	// 攻撃リセット時間
	constexpr int kResetAttackFlagTime = 25;
	//ノックバックスピード
	constexpr float kKnockBackSpeed = 3.0f;
	//ノックバックスピード減少量
	constexpr float kKnockBackSpeedDecrease = 0.2f;
	//攻撃倍率
	constexpr float kMultiAttackMultiplier1 = 0.6f;		//連続攻撃1
	constexpr float kMultiAttackMultiplier2 = 0.8f;		//連続攻撃2
	constexpr float kMultiAttackMultiplier3 = 1.2f;		//連続攻撃3
	constexpr float kMultiAttackMultiplier4 = 2.0f;		//連続攻撃4

	//攻撃の種類
	enum kAttackKind
	{
		Attack1,
		Attack2,
		Attack3,
		Attack4,

		AttackKindNum,
	};

	//攻撃フレームの始まりのタイミング
	constexpr std::array<int, kAttackKind::AttackKindNum> kAttackFrameStart =
	{
		20,
		20,
		20,
		20,
	};
	//攻撃フレームの終わりのタイミング
	constexpr std::array<int, kAttackKind::AttackKindNum> kAttackFrameEnd =
	{
		30,
		30,
		30,
		30,
	};

	//攻撃間のプレイヤーの動ける時間
	constexpr int kAttackIntervalMoveTime = 8;
	//ガードアニメーション
	constexpr int kGuardFirst = 22;
	constexpr int kGuardNow = 25;
	constexpr int kGuardHit = 24;
	//ガード中に動けるスピード
	constexpr float kGuardMoveSpeed = 0.5f;
	//ジャストガードフレーム
	constexpr int kJustGuardFrame = 5;

	//移動の補完値
	constexpr float kNowVecNum = 0.8f;
	constexpr float kNextVecNum = 0.2f;

	//アニメーション速度
	enum kStateAnimSpeed
	{
		Idle = 2,				//待機
		Walk = 2,				//歩き
		Dash = 1,				//ダッシュ
		KnockBack = 1,			//ノックバック
		Attack = 1,				//攻撃
		Gaude = 1,				//ガード
		Dead = 1,				//死亡
	};

	//描画可能な距離
	constexpr float kDrawDistance = 50.0f;


	//デバッグ用のスピード
	constexpr float kDebugSpeed = 10.0f;
	//デバッグ用の攻撃力
	constexpr int kDebugAtk = 300;
	//デバッグ用の歩き速度
	constexpr float kDebugMoveSpeedWalk = 5.5f;	// 歩いているときのスピード
	constexpr float kDebugMoveSpeedDash = 9.0f;	// 走っているときのスピード
	constexpr float kDebugMoveSpeedAcc = 1.5f;	// 加速のスピード

	//攻撃判定サイズ
	constexpr float kAttacKSize = 25.0f;


	//アニメーション番号
	constexpr int kIdleAnimIndex = 1;
	constexpr int kAttackAnimIndex = 21;
	constexpr int kAnimIndex = 3;

	//アニメーションの切り替えにかかるフレーム数
	constexpr float kAnimChangeFrame = 8.0f;
	constexpr float kAnimChangeRateSpeed = 1.0f / kAnimChangeFrame;

	//アナログスティックによる移動関連
	constexpr float kMaxSpeed = 0.1f;		//プレイヤーの最大移動速度
	constexpr float kAnalogRaneMin = 0.1f;	//アナログスティックの入力判定範囲
	constexpr float kAnalogRaneMax = 0.8f;
	constexpr float kAnglogInputMax = 1000.0f;	//アナログスティックの入力されるベクトルに

}

Player::Player():
	modelHandle(-1),
	currentAnimNo(-1),
	prevAnimNo(-1),
	animBlendRate(0.0f),
	angle(0.0f),
	cameraAngle(0.0f)
{
}

Player::~Player()
{
}

void Player::Init()
{
	//3Dモデルの読み込み
	modelHandle = MV1LoadModel(kModelFilename);

	currentAnimNo = MV1AttachAnim(modelHandle, kIdleAnimIndex, -1, false);
	prevAnimNo - 1;
	animBlendRate = 1.0f;

	//プレイヤーの初期位置設定
	pos = VGet(0.0f, 0.0f, 0.0f);


}

void Player::Update()
{
	//アニメーションの切り替え
	if (prevAnimNo != -1)
	{
		animBlendRate += kAnimChangeRateSpeed;
		if (animBlendRate >= 1.0f)	animBlendRate = 1.0f;
		//変更前のアニメーション100%
		MV1SetAttachAnimBlendRate(modelHandle, prevAnimNo, 1.0f - animBlendRate);
		//変更後のアニメーション0%
		MV1SetAttachAnimBlendRate(modelHandle, currentAnimNo, animBlendRate);

	}



	//アニメーションを進める
	bool isLoop = UpdateAnim(currentAnimNo);
	UpdateAnim(prevAnimNo);

	if (!isAttack)
	{

		int Key = GetJoypadInputState(DX_INPUT_KEY_PAD1);
		if ((Key & PAD_INPUT_1) && pos.y == 0)
		{
			isAttack = true;
			ChangeAnim(kAttackAnimIndex);

		}
		else
		{
			//アナログスティックを使って移動
			int analogX = 0;
			int analogY = 0;

			GetJoypadAnalogInput(&analogX, &analogY, DX_INPUT_KEY_PAD1);


			//アナログスティックの入力の10% ~ 80%の範囲を使用する

			//ベクトルの長さが最大で1000になる

			//プレイヤーの最大移動速度は 0.01f / frame

			VECTOR move = VGet(analogX, 0.0f, -analogY);	//ベクトルの長さ0~1000
			//0.00~0.01の長さにする
			//ベクトルの長さを取得する
			float len = VSize(move);
			//ベクトルの長さを0.0~1.0に割合に変換する
			float rate = len / kAnglogInputMax;

			//アナログスティック無効な範囲を除外する
			rate = (rate - kAnalogRaneMin) / (kAnalogRaneMax - kAnalogRaneMin);
			rate = min(rate, 1.0f);
			rate = max(rate, 0.0f);

			//速度が決定できるので移動ベクトルに反映する
			move = VNorm(move);
			float speed = kMaxSpeed * rate;

			move = VScale(move, speed);



			//移動方向からプレイヤーの向く方向を決定する
			if (VSquareSize(move) > 0.0f)
			{
				angle = -atan2f(move.z, move.x) - DX_PI_F / 2;
			}

			pos = VAdd(pos, move);

		}
	}
	else
	{
		//攻撃アニメーションが終了したら待機アニメーションを再生する
		if (isLoop)
		{

			isAttack = false;
			ChangeAnim(kIdleAnimIndex);
		}
	}


	// ３Dモデルのポジション設定
	MV1SetPosition(modelHandle, pos);
	MV1SetRotationXYZ(modelHandle, VGet(0, angle, 0));


}

void Player::Draw()
{
	// ３Ｄモデルの描画
	MV1DrawModel(modelHandle);
}

void Player::HitAttack()
{

}

void Player::OnDamage(VECTOR targetPos, int damagePoint)
{
}

void Player::OnGuardingAttack()
{
}

void Player::OnJustGuardingAttack()
{
}

bool Player::UpdateAnim(int attachNo)
{
	//アニメーションが設定されていないので終了
	if (attachNo == -1) return false;

	//アニメーションを進行させる
	float now = MV1GetAttachAnimTime(modelHandle, attachNo);	//現在の再生カウントを取得
	now += 0.5f;	//アニメーション進める

	//現在再生中のアニメーションの総カウントを取得
	float total = MV1GetAttachAnimTotalTime(modelHandle, attachNo);
	bool isLoop = false;
	if (now >= total)
	{
		now -= total;
		isLoop = true;
	}

	//進めた時間の設定
	MV1SetAttachAnimTime(modelHandle, attachNo, now);

	return isLoop;
}

void Player::ChangeAnim(int animIndex)
{
	//さらに古いアニメーションがアタッチされている場合はこの時点で削除しておく
	if (prevAnimNo != -1)
	{
		MV1DetachAnim(modelHandle, prevAnimNo);
	}

	//現在再生中の待機アニメーションは変更前のアニメーション扱いに
	prevAnimNo = currentAnimNo;

	//変更後のアニメーションとして攻撃アニメーションを改めて設定する
	currentAnimNo = MV1AttachAnim(modelHandle, animIndex, -1, false);

	//切り替えの瞬間は変更後のアニメーションが再生される
	animBlendRate = 0.0f;

	//変更前のアニメーション100%
	MV1SetAttachAnimBlendRate(modelHandle, prevAnimNo, 1.0f - animBlendRate);
	//変更後のアニメーション0%
	MV1SetAttachAnimBlendRate(modelHandle, currentAnimNo, animBlendRate);
}
