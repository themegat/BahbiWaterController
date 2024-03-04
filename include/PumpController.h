
#include "PumpSpeed.h"
#include <vector>
#include <Arduino.h>

#ifndef PumpController_h
#define PumpController_h

class PumpController
{
public:
    PumpController(int transistor1, int transistor2, int transistor3, int transistor4);
    void run(PumpSpeed speed);
    void stop();
    void setSpeed(PumpSpeed speed);
    PumpSpeed getSpeed();
    void setRunDuration(int duration);
    int getRunDuration();
    void setSchedules(std::vector<String> schedules);
    std::vector<String> getSchedules();
    String getNextSchedule(String currentTime);

private:
    int _transistor1;
    int _transistor2;
    int _transistor3;
    int _transistor4;
    bool _running;
    PumpSpeed _speed;
    int _runDuration;
    std::vector<String> _schedules;
};

#endif