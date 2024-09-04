#pragma once
#include "DxLib.h"

class Player;

class Camera
{


public:
    Camera();
    virtual ~Camera();

    void Init();

    void Update(VECTOR mplayerPos);

    void Draw();

    VECTOR GetCameraPos() const noexcept { return m_cameraPos; }

private:

    //�W���C�p�b�h�̏o��
    DINPUT_JOYSTATE m_input;

    //�W���C�p�b�h�̏o�͂̕ێ�
    int m_pad;

    // �����p�x
    float m_angleH;


    float m_cameraAngle;

    //�J�����̍��W
    VECTOR m_cameraPos;

    //�J�����̒����_
    VECTOR m_cameraTarget;

    //�v���C���[�̍��W
    VECTOR m_playerTarget;


//public:
//	Camera();
//	void Update();
//
//
//private:
//	float fov;
//	VECTOR pos;
//
//	constexpr static float DefaultFov = 60.0f;
//	constexpr static float FovRange = 30.0f;	// fov�̕ω���
//	constexpr static float PosChangeSpeed = 0.03f;	// pos�̕ω��X�s�[�h

};

