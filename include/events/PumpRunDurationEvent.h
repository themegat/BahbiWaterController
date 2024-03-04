#include <Arduino.h>
#include "Event.h"
#include "PumpController.h"

#ifndef PumpRunDurationEvent_h
#define PumpRunDurationEvent_h

class PumpRunDurationEvent : public EventTask
{
private:
public:
    PumpRunDurationEvent();
    ~PumpRunDurationEvent();
    void execute(Event evt);
};

extern PumpController pumpCtrl;

PumpRunDurationEvent::~PumpRunDurationEvent()
{
}
PumpRunDurationEvent::PumpRunDurationEvent()
{
}

void PumpRunDurationEvent::execute(Event evt)
{
    
    int duration = atoi(evt.extra);
    pumpCtrl.setRunDuration(duration);
}

#endif