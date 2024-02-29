#include "Event.h"
#include "PumpController.h"
#include "PumpSpeed.h"

#ifndef PumpStartEvent_h
#define PumpStartEvent_h

class PumpStartEvent: public EventTask
{
private:

public:
    PumpStartEvent();
    ~PumpStartEvent();
    void execute(Event evt);
};

extern PumpController pumpCtrl;

PumpStartEvent::~PumpStartEvent() {

}
PumpStartEvent::PumpStartEvent() {
    
}

void PumpStartEvent::execute(Event evt)
{
    String speed = evt.extra;
    if (speed == "s")
    {
        pumpCtrl.run(SLOW);
        Serial.println("Event - SLOW");
    }
    else if (speed == "m")
    {
        pumpCtrl.run(SMEDIUM);
        Serial.println("Event - SMEDIUM");
    }
    else if (speed == "h")
    {
        pumpCtrl.run(SHIGH);
        Serial.println("Event - SHIGH");
    }
}
#endif
