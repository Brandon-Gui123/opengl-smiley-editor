#include "Time.h"

#include "Timer.h"  // for using the Timer itself

double Time::deltaTime{0};
Timer Time::internalTimer{};

void Time::StartInternalTimer()
{
    internalTimer.StartTimer();
}

void Time::QueryDeltaTimeFromInternalTimer()
{
    deltaTime = internalTimer.GetTimeSinceLastCall();
}

double Time::GetDeltaTime()
{
    return deltaTime;
}
