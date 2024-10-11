#pragma once
#include "DxLib.h"
#include <memory>

class Enemy;
class Player
{
public:
	Player();
	virtual ~Player();

	void Init();
	void Update();
	void Draw();

	//カメラの方向を取得
	void SetCameraAngle(float angle) { m_cameraAngle = angle; }

	//半径の取得
	float GetRadius() { return m_radius; }

	//攻撃の半径
	float GetAttackRadius() { return m_attackRadius; }


	//プレイヤーの座標を取得	
	const VECTOR GetPos() const { return m_pos; }
	void SetPos(const VECTOR pos) { m_pos = pos; }

	//プレイヤーのHPを取得
	const int& GetHp() const { return m_hp; }
	void SetHp(const int hp) { m_hp = hp; }

	//プレイヤーの攻撃の当たり判定を生成するかのフラグを取得
	const bool& GetAttackGeneration() const { return m_isAttackGeneration; }
	const bool& GetSkillGeneration() const { return m_isSkillGeneration; }

	void SetCommand(const bool isCommand) { m_isCommand = isCommand; }

	//プレイヤーの攻撃の座標を取得
	void OnGimmickHitUpdate();

	//プレイヤーダメージのフラグ取得
	void SetDamage(const bool damage) { m_isDamage = damage; }

	//アニメーションのセットフラグ
	void SetAnimDamage(const bool animDamage);

	//死んだときの判定
	void SetIsDown(const bool isDown) { m_isDown = isDown; }



	//攻撃と敵のあたり判定
	bool SphereHitFlag(std::shared_ptr<Enemy> pEnemy);


private:


	bool UpdateAnim(int attachNo);

	void ChangeAnim(int animIndex);

	//移動関数
	void Move();

	//ステージ外に出ないようにする処理
	void StageProcess();


private:
	std::shared_ptr<Enemy> m_pEnemy;
private:


	//方向
	enum  direction
	{
		kRight,
		kLeft,
		kUp,
		kDown
	};


private:
	int		m_modelHandle;	//モデルハンドル

	float m_stamina;
	bool m_isStamina;

	//攻撃中フラグ
	bool m_isAttack;
	bool m_isSkill;
	bool m_isWalk;
	bool m_isDash;
	bool m_isDown;
	bool m_isAvoid;

	//アニメーション情報
	int m_animIndex;
	int m_currentAnimNo;
	int m_prevAnimNo;
	float m_animBlendRate;


	//アニメーションフラグ
	bool m_isAnimIdle;
	bool m_isAnimAttack;
	bool m_isAnimWalk;
	bool m_isAnimDash;
	bool m_isAnimDamage;
	bool m_isAnimDown;

	//状態
	int m_state;

	//向いている方向
	int m_direction;

	//Aボタンを何回押したか
	int m_countAButton;

	//Xボタンを何回押したか
	int m_countXButton;


	//動いているかを保持する
	bool m_isMove;
	bool m_isCommand;
	bool m_isAttacking;


	//HP
	int m_hp;

	float m_analogX;
	float m_analogZ;

	//表示情報
	VECTOR m_pos;
	VECTOR m_attackPos;
	VECTOR m_attackDir;

	//カメラの位置
	VECTOR m_cameraPos;

	float m_angle;

	//当たり判定の半径
	float m_radius;
	float m_attackRadius;


	//当たり判定の発生フラグ
	bool m_isAttackGeneration;
	bool m_isSkillGeneration;

	//カメラ情報
	float m_cameraAngle;


	bool m_isDamage;

	//動いているか
	bool m_iskStandby;


	//走っているか
	bool m_isRun;

	//攻撃しているか


};

