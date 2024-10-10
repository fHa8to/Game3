#pragma once
#include "DxLib.h"
#include <memory>

class Player;
class Enemy;

class Camera
{


public:
    Camera();
    virtual ~Camera();

    void Init();

    void TitleCameraUpdate();
    void PlayCameraUpdate(Player& player);		//�Q�[���v���C�p�̃J�����ݒ�

    //�J�����̃A���O�����擾
    const float GetAngle() const { return m_angle; }

    //�J�����̍��W���擾
    const VECTOR& GetPos() const { return m_pos; }
    //�����_�̍��W���擾
    const VECTOR& GetTargetPos() const { return m_targetPos; }

private:

    std::shared_ptr<Player> m_pPlayer;

    void DrawGrid();

    VECTOR m_pos;			//�J�������W
    VECTOR m_targetPos;		//�����_���W
    VECTOR m_cameraangle;			//�J�����̃A���O��


    float m_angle;	//�J�����p�x


};

