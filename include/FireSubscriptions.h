#include <Arduino.h>
#include <string>
#include "Event.h"

#ifndef FireSubscriptions_h
#define FireSubscriptions_h

class FireSubscriptions {
    public:
        static boolean switchOn(String path, boolean state);
        static boolean pumpPressure(String path, String state);
    private:
};

#endif