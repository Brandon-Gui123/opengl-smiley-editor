#pragma once

#ifndef TIMER_H
#define TIMER_H

class Timer
{
private:
    __int64 countsPerSecond{0};
    __int64 startTimeInCounts{0};
    __int64 lastTimeInCounts{0};

public:

    Timer();

    /// <summary>Starts a timer.</summary>
    void StartTimer();
    
    /// <summary>Gets the time in counts since the last time this method is called.</summary>
    double GetTimeSinceLastCall();
};

#endif