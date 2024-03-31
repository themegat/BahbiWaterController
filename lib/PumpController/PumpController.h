/**
 * @author T Motsoeneng
 */


#include "PumpSpeed.h"
#include <vector>
#include <Arduino.h>
#include <NetTime.h>
#include "Event.h"

#ifndef PumpController_h
#define PumpController_h

extern NetTime netTime;
extern EventManager evtManager;

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
    void setScheduleAtIndex(String schedule, int index);
    std::vector<String> getSchedules();
    String getNextSchedule(String currentTime);
    String getStartDateTime();
    String getStopDateTime();

private:
    int _transistor1;
    int _transistor2;
    int _transistor3;
    int _transistor4;
    bool _running;
    PumpSpeed _speed;
    int _runDuration;
    std::vector<String> _schedules;
    void _printSchedules();
    String _startDateTime;
    String _stopDateTime;
};

#endif