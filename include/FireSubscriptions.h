#include <Arduino.h>
#include <string>
#include "Event.h"
#include <vector>

#ifndef FireSubscriptions_h
#define FireSubscriptions_h

class FireSubscriptions {
    public:
        static boolean switchOn(String path, boolean state);
        static boolean pumpPressure(String path, int state);
        static boolean runDurationSeconds(String path, int state);
        static boolean pumpSchedule(String path, String state);
    private:
};

#endif