#pragma once

template<typename T>
class Singleton
{
public:

    // インスタンスを提供する
    static T& getInstance() {
        static T instance;
        return instance;
    }

protected:
    // シングルトンとするため
    Singleton(const Singleton&) = delete;
    void operator=(const Singleton&) = delete;
    Singleton() {}
    ~Singleton() {}
};