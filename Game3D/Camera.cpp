#include "Camera.h"
#include "DxLib.h"
#include "Pad.h"
#include <cmath>

namespace
{
	//ƒJƒƒ‰‚Ì•`‰æ”ÍˆÍ
	constexpr float kMinimumDrawingrange = 100.0f;
	constexpr float kMaximumDrawingrange =5000.0f;

	//ƒJƒƒ‰‚ÌÀ•W
	constexpr float kCameraPosY = 500.0f;
	constexpr float kCameraPosZ = -800.0f;

	// ù‰ñ‘¬“x
	constexpr float kAngleSpeed = 0.05f;	

	//’Ž‹“_‚ÌÀ•W
	constexpr float kCameraTargetY = 100.0f;

	//ƒJƒƒ‰‚Ì‹——£
	constexpr float kCameraDist = 1000.0f;
	//constexpr float kCameraHeight = 100;

	// Ž‹–ìŠp
	constexpr float kFov = (DX_PI_F / 180.0f) * 60.0f;
	// Žè‘OƒNƒŠƒbƒv‹——£
	constexpr float kNear = 0.1f;
	// ‰œƒNƒŠƒbƒv‹——£
	constexpr float kFar = 1000.0f;
	// ƒJƒƒ‰‚Ì‰Šú’Ž‹“_
	constexpr float kTargetX = 100.0f;        // XŽ²
	constexpr float kTargetY = 400.0f;    // YŽ²
	constexpr float kTargetZ = -870.0f;    // ZŽ²
	// ƒJƒƒ‰‚Ì’†SÀ•W
	constexpr float kScreenCenterX = 50.0f;    // XÀ•W
	constexpr float kScreenCenterY = 1000.0f;    // YÀ•W

	constexpr float AngleSpeed = 0.05f;	// ù‰ñ‘¬“x
}


Camera::Camera()
{
		

}


Camera::~Camera()
{
	// ˆ—‚È‚µ.
}

void Camera::Init()
{
	//‰œs100`5000‚Ü‚Å‚ðƒJƒƒ‰‚Ì•`‰æ”ÍˆÍ‚Æ‚·‚é
	SetCameraNearFar(kMinimumDrawingrange, kMaximumDrawingrange);


	//‰Šú‰»
	m_cameraPos = VGet(0.0f, 0.0f, 0.0f);
	
	m_cameraTarget = VGet(0.0f, 0.0f, 0.0f);

	m_cameraAngle = 0.0f;

	m_angleH = 0.0f;

	m_pad = 0;
}


void Camera::Update(VECTOR mplayerPos)
{

#if _DEBUG

	if ((GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_5))
	{
		m_cameraPos.x += 500.0f;
		m_cameraPos.z += 600.0f;
	}

#endif

		m_pad = GetJoypadDirectInputState(DX_INPUT_PAD1,&m_input);


	if (m_input.Rx > 0)
	{
		m_angleH += AngleSpeed;

		// ‚P‚W‚O“xˆÈã‚É‚È‚Á‚½‚çŠp“x’l‚ª‘å‚«‚­‚È‚è‚·‚¬‚È‚¢‚æ‚¤‚É‚R‚U‚O“x‚ðˆø‚­
		if (m_angleH > DX_PI_F)
		{
			m_angleH -= DX_TWO_PI_F;
		}
	}
	if (m_input.Rx < 0)
	{
		m_angleH -= kAngleSpeed;

		// |‚P‚W‚O“xˆÈ‰º‚É‚È‚Á‚½‚çŠp“x’l‚ª‘å‚«‚­‚È‚è‚·‚¬‚È‚¢‚æ‚¤‚É‚R‚U‚O“x‚ð‘«‚·
		if (m_angleH < -DX_PI_F)
		{
			m_angleH += DX_TWO_PI_F;
		}
	}

	
	m_cameraPos.x = cosf(m_angleH) * kCameraDist;
	m_cameraPos.y = kCameraPosY;
	m_cameraPos.z = sinf(m_angleH) * kCameraDist;

	// ƒJƒƒ‰À•W
	m_cameraPos = VAdd(mplayerPos, m_cameraPos);

	// ’Ž‹“_
	m_cameraTarget = VAdd(mplayerPos, VGet(0.0f, kCameraTargetY, 0.0f));

	SetCameraPositionAndTarget_UpVecY(m_cameraPos, m_cameraTarget);

}

void Camera::Draw()
{

#ifdef _DEBUG
	DrawFormatString(160, 200, GetColor(255, 255, 255), "ƒJƒƒ‰‚ÌÀ•W(%.2f,%.2f,%.2f)", m_cameraPos.x, m_cameraPos.y, m_cameraPos.z);

	DrawFormatString(250, 250, GetColor(255, 255, 255), "%d", m_input.Rx);
#endif
}

