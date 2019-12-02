#pragma once

#ifndef TIME_H
#define TIME_H

#include "Timer.h"  // for using a Timer

class Time
{
private:

    /// <summary>An internal timer which helps to keep track of time inside the class.</summary>
    static Timer internalTimer;

    /// <summary>The time in seconds past since the last frame update.</summary>
    static double deltaTime;

public:

    /// <summary>Starts the interal timer inside this class.</summary>
    static void StartInternalTimer();

    /// <summary>Obtains the time in seconds that has passed since the last call to get the delta time from the internal timer.</summary>
    static void QueryDeltaTimeFromInternalTimer();
    
    /// <summary>Gets the time in seconds past since the last frame update.</summary>
    static double GetDeltaTime();
};

#endif