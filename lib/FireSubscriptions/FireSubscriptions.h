/**
 * @author T Motsoeneng
 * @email tshepomotsoeneng0@gmail.com
 * @create date 2024-03-15
 * @modify date 2024-03-15
 */


#include <Arduino.h>
#include <string>
#include "Event.h"
#include <vector>

#ifndef FireSubscriptions_h
#define FireSubscriptions_h

class FireSubscriptions {
    public:
        static void switchOn(String path, boolean state);
        static void pumpPressure(String path, String state);
        static void runDurationSeconds(String path, String state);
        static void pumpSchedule(String path, String state);
    private:
};

#endif