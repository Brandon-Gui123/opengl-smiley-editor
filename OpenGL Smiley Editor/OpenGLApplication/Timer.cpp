#include "Timer.h"

#include "framework.h"  // for querying performance counts and frequency

Timer::Timer()
{}

void Timer::StartTimer()
{
    __int64 currentTimeInCounts{0};

    if (!QueryPerformanceFrequency((LARGE_INTEGER*) &countsPerSecond))
    {
        MessageBox(NULL, L"QueryPerformanceFrequency failed!", L"ERROR", MB_OK | MB_ICONINFORMATION);
        return;
    }

    QueryPerformanceCounter((LARGE_INTEGER*) &currentTimeInCounts);

    startTimeInCounts = currentTimeInCounts;
    lastTimeInCounts = currentTimeInCounts;
}

double Timer::GetTimeSinceLastCall()
{
    __int64 currentTimeInCounts{0};
    __int64 timePassedSinceLastTimeInCounts{0};

    QueryPerformanceCounter((LARGE_INTEGER*) &currentTimeInCounts);

    timePassedSinceLastTimeInCounts = currentTimeInCounts - lastTimeInCounts;

    double timePassedSinceLastTimeInSeconds{(currentTimeInCounts - lastTimeInCounts) / static_cast<double>(countsPerSecond)};

    lastTimeInCounts = currentTimeInCounts;

    return timePassedSinceLastTimeInSeconds;
}
