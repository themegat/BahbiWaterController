#include "Event.h"
#include "PumpController.h"
#include "PumpSpeed.h"

#ifndef PumpStartEvent_h
#define PumpStartEvent_h

class PumpStartEvent : public EventTask
{
private:
public:
    PumpStartEvent();
    ~PumpStartEvent();
    void execute(Event evt);
};

extern PumpController pumpCtrl;

PumpStartEvent::~PumpStartEvent()
{
}
PumpStartEvent::PumpStartEvent()
{
}

void PumpStartEvent::execute(Event evt)
{
    String speed = evt.extra;
    if (speed == pumpSpeedStr(SLOW))
    {
        pumpCtrl.run(SLOW);
        Serial.println("Event Speed: " + speed);
    }
    else if (speed == pumpSpeedStr(SMEDIUM))
    {
        pumpCtrl.run(SMEDIUM);
        Serial.println("Event Speed: " + speed);
    }
    else if (speed == pumpSpeedStr(SHIGH))
    {
        pumpCtrl.run(SHIGH);
        Serial.println("EvenEvent Speed: " + speed);
    }
}
#endif
