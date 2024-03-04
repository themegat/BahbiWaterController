#include <Arduino.h>
#include "Event.h"
#include "PumpController.h"
#include <vector>

#ifndef SchedulePumpStopEvent_h
#define SchedulePumpStopEvent_h

class SchedulePumpStopEvent : public EventTask
{
private:
public:
    SchedulePumpStopEvent();
    ~SchedulePumpStopEvent();
    void execute(Event evt);
};

extern PumpController pumpCtrl;

SchedulePumpStopEvent::~SchedulePumpStopEvent()
{
}
SchedulePumpStopEvent::SchedulePumpStopEvent()
{
}

void SchedulePumpStopEvent::execute(Event evt)
{
}

#endif