#include "Event.h"
#include "PumpController.h"
#include "PumpSpeed.h"

#ifndef PumpStopEvent_h
#define PumpStopEvent_h

class PumpStopEvent: public EventTask
{
private:
    /* data */
public:
    PumpStopEvent(/* args */);
    ~PumpStopEvent();
     void execute(Event evt);
};

extern PumpController pumpCtrl;

PumpStopEvent::PumpStopEvent(/* args */)
{
}

PumpStopEvent::~PumpStopEvent()
{
}

void PumpStopEvent::execute(Event evt)
{
    pumpCtrl.stop();
    Serial.println("Event - STOP");
}


#endif