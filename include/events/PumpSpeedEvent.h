#include "Event.h"
#include "PumpController.h"
#include "PumpSpeed.h"

#ifndef PumpSpeedEvent_h
#define PumpSpeedEvent_h

class PumpSpeedEvent : public EventTask
{
private:
    /* data */
public:
    PumpSpeedEvent(/* args */);
    ~PumpSpeedEvent();
    void execute(Event evt);
};

extern PumpController pumpCtrl;

PumpSpeedEvent::PumpSpeedEvent(/* args */)
{
}

PumpSpeedEvent::~PumpSpeedEvent()
{
}

void PumpSpeedEvent::execute(Event evt)
{
    String value = evt.extra;
    PumpSpeed speed;
    if(value == "1"){
        speed = PumpSpeed::SLOW;
    }else  if(value == "2"){
        speed = PumpSpeed::SMEDIUM;
    }else  if(value == "3"){
        speed = PumpSpeed::SHIGH;
    }else{
        speed = PumpSpeed::SMEDIUM;
    }

    pumpCtrl.setSpeed(speed);
}

#endif