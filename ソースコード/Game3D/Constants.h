#pragma once
#include "Singleton.h"

// �V���O���g���̒萔�Ǘ��N���X
class Constants : public Singleton<Constants> 
{
    friend class Singleton<Constants>;

public:
    // ��ʌn�萔
    static constexpr int SCREEN_WIDTH = 1280;  // ��ʂ̉��T�C�Y
    static constexpr int SCREEN_HEIGHT = 720;  // ��ʂ̏c�T�C�Y
    static constexpr int COLOR_BIT = 16;   // �J���[�r�b�g��
    static constexpr int RESOLUTION_WIDTH = 1920;  // �𑜓x�̉�����
    static constexpr int RESOLUTION_HEIGHT = 1080; // �𑜓x�̏c����

    // �X�e�[�W�萔
    static constexpr int STAGE_RANGE = 150;    // �X�e�[�W�͈̔�

    // �J�����萔
    static constexpr float CAMERA_BASE_POS_X = 0.0f;   // �J�����̍��W��lX
    static constexpr float CAMERA_BASE_POS_Y = 40.0f;  // �J�����̍��W��lY
    static constexpr float CAMERA_BASE_POS_Z = 30.0f;  // �J�����̍��W��lZ
    static constexpr float CAMERA_NEAR = 1.0f;     // �J������Near�l
    static constexpr float CAMERA_FAR = 512.0f;    //�J������Far�l
    static constexpr float CAMERA_ANGLE_VARIATION = 0.000001f; // �J�����̉�]�l
    static constexpr float CAMERA_ANGLE_RANGE = 0.6f;  // �J�����̉�]�͈�

    // �v���C���[�萔
    static constexpr float PLAYER_BASE_POS_X = 0.0f;   // �v���C���[�̍��W��lX
    static constexpr float PLAYER_BASE_POS_Y = 0.0f;   // �v���C���[�̍��W��lY
    static constexpr float PLAYER_BASE_POS_Z = 0.0f;   // �v���C���[�̍��W��lZ
    static constexpr float PLAYER_SCALE = 5.0f;    // �v���C���[�̊g��l
    static constexpr float PLAYER_MOVE_SCALE_SLOW_WALK = 0.1f; // �v���C���[�̈ړ����x
    static constexpr float PLAYER_MOVE_SCALE_FAST_WALK = 0.3f; // �v���C���[�̈ړ����x
    static constexpr float PLAYER_MOVE_SCALE_SLOW_DASH = 0.45f; // �v���C���[�̈ړ����x
    static constexpr float PLAYER_MOVE_SCALE_FAST_DASH = 0.6f; // �v���C���[�̈ړ����x
    static constexpr float PLAYER_MOVE_SCALE_THRESHOLD = 30000.0f; // �ړ����x���ω����邵�����l
    static constexpr float PLAYER_COLLISION_RADIUS = 3.5f;    // �v���C���[�̓����蔻��̔��a
    static constexpr float PLAYER_GRAVITY = 0.25f;   // �d��
    static constexpr float PLAYER_JUMP_SCALE = 3.0f;    // �W�����v��
    static constexpr float PLAYER_HP = 100.0f;  // �v���C���[�̗̑�
    static constexpr float PLAYER_ATTACK_DAMAGE = 50.0f;    // �_���[�W��
    static constexpr float PLAYER_HEIGHT = 5.0f; // �v���C���[�̍���
    static constexpr float PLAYER_BASE_ATTACK_POS_X = 0.0f; // �U�������ʒu
    static constexpr float PLAYER_BASE_ATTACK_POS_Y = 1.0f; // �U�������ʒu
    static constexpr float PLAYER_BASE_ATTACK_POS_Z = -6.0f; // �U�������ʒu
    static constexpr float PLAYER_ATTACK_RADIUS = 5.0;  // �U�����蔼�a
    static constexpr float PLAYER_ATTACK_HEIGHT = 2.0;  // �U�����荂��
    static constexpr int PLAYER_ATTACK_PREPARATION = 23;    // �U���\������t���[����
    static constexpr int PLAYER_ATTACK_END = 26;    // �U���I���t���[����

    // �R���g���[���[�萔
    static constexpr int STICK_INVALID_VALUE = 8000;   // �X�e�B�b�N�̖����͈�

    // �A�j���[�V�����^�O�萔
    static constexpr int PLAYER_ANIM_IDLE = 1; // �A�C�h���A�j���^�O
    static constexpr int PLAYER_ANIM_SLOW_WALK = 4;    // �X���[�E�H�[�N�A�j���^�O
    static constexpr int PLAYER_ANIM_FAST_WALK = 3;    // �t�@�X�g�E�H�[�N�A�j���^�O
    static constexpr int PLAYER_ANIM_SLOW_DASH = 7;    // �X���[�_�b�V���A�j���^�O
    static constexpr int PLAYER_ANIM_FAST_DASH = 6;    // �t�@�X�g�_�b�V���A�j���^�O
    static constexpr int PLAYER_ANIM_SLICE = 31;  // �m�[�}���A�b�^�N�A�j���^�O
    static constexpr int PLAYER_ANIM_STAB = 33;    // �X�^�u�A�^�b�N�A�j���^�O
    static constexpr int PLAYER_ANIM_SAD = 73;  // �c�O�����Ă��̃^�O
    static constexpr int PLAYER_ANIM_HIT = 24;  // �q�b�g�A�j���^�O
    static constexpr int PLAYER_ANIM_DEAD = 28; // ���S�A�j���[�V����
    static constexpr int PLAYER_ANIM_DEAD_IDLE = 29; // ���S�A�C�h���A�j���[�V����

    static constexpr int ENEMY_ANIM_WALK = 14;  // �����A�j���[�V����
    static constexpr int ENEMY_ANIM_IDLE = 3;  // �A�C�h���A�j���[�V����
    static constexpr int ENEMY_ANIM_ATTACK = 10;  // �U���A�j���[�V����
    static constexpr int ENEMY_ANIM_DEAD = 0;   // ���S�A�j���[�V����

    // �G�l�~�[�萔
    static constexpr float ENEMY_SCALE = 0.04f;  // �G�l�~�[�̃��f���̊g��l
    static constexpr float ENEMY_SPAWN_POINT = 170.0f;   // �G�l�~�[���X�|�[������ʒu
    static constexpr float ENEMY_HP = 100.0f;   // �G�l�~�[�̗̑�
    static constexpr float ENEMY_ATTACK_DAMAGE = 20.0f; // �G�l�~�[�̍U����
    static constexpr float ENEMY_COLLISION_RADIUS = 4.0f;   // �G�l�~�[�̓����蔻��̔��a
    static constexpr float ENEMY_HEIGHT = 4.5f; // �G�l�~�[�̍���
    static constexpr float ENEMY_DASH_SPEED = 0.5;  // �ł������G�l�~�[�̈ړ����x
    static constexpr float ENEMY_DEAD_LINE = -20.0f;    // �G�l�~�[�����������鍂��
    static constexpr float ENEMY_BLOW_AWAY_SCALE = 8.0f;    // �G�l�~�[��������ԕ��s���x
    static constexpr int ENEMY_COOL_TIME = 60;  // �U���̃N�[���^�C��

    // �A�j���[�V�����t���[�����萔
    static constexpr int PLAYER_ANIM_SLICE_FLAME = 30; // �ʏ�U���t���[����

    // �Q�[���V�[���ł̋�̎��Ԍo�ߗp�萔
    static constexpr int SKY_COLOR_DAY_RED = 36;    // ���邢��
    static constexpr int SKY_COLOR_DAY_GREEN = 139; // ���邢��
    static constexpr int SKY_COLOR_DAY_BLUE = 255;  // ���邢��
    static constexpr int SKY_COLOR_EVENING_RED = 255;  // ���邢��
    static constexpr int SKY_COLOR_EVENING_GREEN = 140;  // ���邢��
    static constexpr int SKY_COLOR_EVENING_BLUE = 0;  // ���邢��
    static constexpr int SKY_COLOR_NIGHT_RED = 0;  // �Â���
    static constexpr int SKY_COLOR_NIGHT_GREEN = 0;  // �Â���
    static constexpr int SKY_COLOR_NIGHT_BLUE = 139;  // �Â���
    static constexpr int FRAME_PER_CYCLE = 12000; // �ʒu�T�C�N���̃t���[����
    static constexpr int FRAME_PER_TRAMSITION = FRAME_PER_CYCLE / 4;    // �e��ԃt���[��

    // ��Փx�Ɋւ���萔
    static constexpr int SPAWN_INTERVAL_EASY = 300; // easy�̃X�|�[���̃C���^�[�o��
    static constexpr int SPAWN_INTERVAL_NORMAL = 200; // normal�̃X�|�[���̃C���^�[�o��
    static constexpr int SPAWN_INTERVAL_HARD = 100; // hard�̃X�|�[���̃C���^�[�o��
    static constexpr int SPAWN_INTERVAL_NIGHTMARE = 50; // nightmare�̃X�|�[���̃C���^�[�o��

    static constexpr int LEVEL_EASY = 1;    // ��Փxeasy�̒l
    static constexpr int LEVEL_NORMAL = 2;    // ��Փxeasy�̒l
    static constexpr int LEVEL_HARD = 3;    // ��Փxeasy�̒l
    static constexpr int LEVEL_NIGHTMARE = 4;    // ��Փxeasy�̒l
    
    static constexpr int TIME_FRAME_NORMAL = 3600;  // ��Փx���C�[�W�[�ɕς���t���[����
    static constexpr int TIME_FRAME_HARD = 5400;  // ��Փx���n�[�h�ɕς���t���[����
    static constexpr int TIME_FRAME_NIGHTMARE = 7200;  // ��Փx���i�C�g���A�ɕς���t���[����
    
private:
    // �v���C�x�[�g�R���X�g���N�^
    Constants() {}
};