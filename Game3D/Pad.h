#pragma once

// テトリス専用パッド処理
namespace Pad
{
	// パッドの入力状態取得
	void Update();

	// 押し下げ判定
	bool isPress(int key);
	// トリガー判定
	bool isTrigger(int key);
	//離した判定
	bool isRelase(int key);

}
