#pragma once

template<typename T>
class Singleton
{
public:

    // �C���X�^���X��񋟂���
    static T& getInstance() {
        static T instance;
        return instance;
    }

protected:
    // �V���O���g���Ƃ��邽��
    Singleton(const Singleton&) = delete;
    void operator=(const Singleton&) = delete;
    Singleton() {}
    ~Singleton() {}
};