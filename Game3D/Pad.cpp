#include "Pad.h"
#include "DxLib.h"

namespace
{
	int lastPad = 0;

	int nowPad = 0;
}

namespace Pad
{

	void Update()
	{
		lastPad = nowPad;

		nowPad = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	}

	bool isPress(int key)
	{
		return (nowPad & key);
	}

	bool isTrigger(int key)
	{

		bool isNow = (nowPad & key);
		bool isLast = (lastPad & key);

		if (isNow && !isLast)
		{
			return true;
		}
		return false;
	}

	bool isRelase(int key)
	{
		bool isNow = (nowPad & key);	// このフレーム
		bool isLast = (lastPad & key);	// 前のフレーム

		if (!isNow && isLast)		// 前回のフレームは押されていた
		{
			return true;
		}
		return false;
	}
}
