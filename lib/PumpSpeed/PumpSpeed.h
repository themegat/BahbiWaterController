/**
 * @author T Motsoeneng
 * @link https://github.com/themegat
 */


#include <Arduino.h>

#ifndef PumpSpeed_h
#define PumpSpeed_h

enum PumpSpeed
{
    SLOW = 1,
    SMEDIUM = 2,
    SHIGH = 3
};

static String pumpSpeedStr(PumpSpeed speed)
{
    switch (speed)
    {
    case SLOW:
        return "SLOW";
    case SMEDIUM:
        return "MEDIUM";
    case SHIGH:
        return "HIGH";
    default:
        return "";
    }
};

#endif