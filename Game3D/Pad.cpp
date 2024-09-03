#include "Pad.h"
#include "DxLib.h"
#include <vector>

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

	bool isPress(int button)
	{
		return (nowPad & button);
	}

	bool isTrigger(int button)
	{

		bool isNow = (nowPad & button);
		bool isLast = (lastPad & button);

		if (isNow && !isLast)
		{
			return true;
		}

		return false;
	}

	bool isRelase(int button)
	{
		bool isNow = (nowPad & button);	// このフレーム
		bool isLast = (lastPad & button);	// 前のフレーム

		if (!isNow && isLast)		// 前回のフレームは押されていた
		{
			return true;
		}

		return false;
	}
}
