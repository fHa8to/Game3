#include "Time.h"

Time::Time(int rimitTime)
{
}

Time::~Time()
{
}

void Time::Reset()
{
	m_time = 0;
}

bool Time::Update()
{
	//時間を超えたらtrueを返す
	if (m_time >= m_rimitTime) return true;
	m_time++;

	return false;
}
