#include <Arduino.h>
#include "Event.h"
#include "PumpController.h"
#include <vector>
#include "NetTime.h"
#include "EventNames.h"
#include <TaskSchedulerDeclarations.h>
#include "TimeUtil.h"

#ifndef SchedulePumpStartEvent_h
#define SchedulePumpStartEvent_h

extern PumpController pumpCtrl;
extern NetTime netTime;
extern Task taskStartPump;
extern Task taskStopPump;

class SchedulePumpStartEvent : public EventTask
{
private:
public:
    SchedulePumpStartEvent();
    ~SchedulePumpStartEvent();
    void execute(Event evt);
};

extern PumpController pumpCtrl;

SchedulePumpStartEvent::~SchedulePumpStartEvent()
{
}
SchedulePumpStartEvent::SchedulePumpStartEvent()
{
}

void SchedulePumpStartEvent::execute(Event evt)
{
    String currentTime = netTime.getHour() + ":" + netTime.getMinute() + ":" + netTime.getSecond();
    Serial.println("Setting schedule at : " + currentTime);
    String nextSchedule = pumpCtrl.getNextSchedule(currentTime);
    int netxRun = TimeUtil::getTimeDifference(currentTime, nextSchedule);
    taskStartPump.restartDelayed(netxRun);
    taskStopPump.restartDelayed(netxRun + (pumpCtrl.getRunDuration() * 1000));
    Serial.println("SchedulePumpStartEvent:: Next run at " + nextSchedule);
}

#endif