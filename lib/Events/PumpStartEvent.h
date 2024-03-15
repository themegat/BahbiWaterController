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
    PumpSpeed speed = pumpCtrl.getSpeed();
    pumpCtrl.run(speed);
}
#endif
