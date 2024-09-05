#pragma once
#include "DxLib.h"

class Player
{
public:
	Player();
	virtual ~Player();

	void Init();
	void Update(VECTOR cameraPos);
	void Draw();

	void Botton(VECTOR cameraPos);

	void Animation();


	//半径の取得
	float GetRadius() { return m_radius; }


	//プレイヤーの座標を取得	
	const VECTOR& GetPos() const { return m_pos; }
	void Set(const VECTOR pos) { m_pos = pos; }
		 



private:

	bool UpdateAnim(int attachNo);
	void ChangeAnim(int animIndex);
	


private:
	enum  state
	{
		kStandby,		//待機中
		kWalk,			//歩く
		kRun,			//走る
		kAttack			//攻撃

	};

	//プレイヤーがどちらを向いているか
	enum direction
	{
		kRight,
		kLeft,
		kUp,
		kDown
	};

private:
	int		modelHandle;	//モデルハンドル

	//アニメーション情報
	int m_currentAnimNo;
	int m_prevAnimNo;
	float m_animBlendRate;

	//状態
	int m_state;

	//向いている方向
	int m_direction;

	//Aボタンを何回押したか
	int m_countAButton;

	//Xボタンを何回押したか
	int m_countXButton;



	//表示情報
	VECTOR m_pos;
	VECTOR m_attackPos;
	//カメラの位置
	VECTOR m_cameraPos;

	float angle;

	//当たり判定の半径
	float m_radius;

	//カメラ情報
	float m_cameraAngle;


	//動いているか
	bool m_iskStandby;

	//歩いているか
	bool m_isWalk;

	//走っているか
	bool m_isRun;

	//攻撃しているか
	bool m_isAttack;


};

