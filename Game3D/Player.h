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

	//半径の取得
	float GetRadius() { return m_radius; }


	//プレイヤー
	const VECTOR& GetPos() const { return pos; }




private:

	bool UpdateAnim(int attachNo);
	void ChangeAnim(int animIndex);
	


private:
	enum  state
	{
		kWait,			//待機中
		kMove,			//動いている
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
	int currentAnimNo;
	int prevAnimNo;
	float animBlendRate;

	//状態
	int m_state;

	//向いている方向
	int m_direction;

	//Aボタンを何回押したか
	int m_countAButton;

	//Xボタンを何回押したか
	int m_countXButton;



	//表示情報
	VECTOR pos;
	VECTOR attackPos;
	//カメラの位置
	VECTOR m_cameraPos;

	float angle;

	//当たり判定の半径
	float m_radius;

	//カメラ情報
	float cameraAngle;

	int isAttack;


};

