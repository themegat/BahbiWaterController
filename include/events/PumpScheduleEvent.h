#include <Arduino.h>
#include "Event.h"
#include "PumpController.h"
#include <vector>
#include <iostream>
#include <sstream>
#include "EventNames.h"

#ifndef PumpScheduleEvent_h
#define PumpScheduleEvent_h

using namespace std;

extern EventManager evtManager;

class PumpScheduleEvent : public EventTask
{
private:
public:
    PumpScheduleEvent();
    ~PumpScheduleEvent();
    void execute(Event evt);
};

extern PumpController pumpCtrl;

PumpScheduleEvent::~PumpScheduleEvent()
{
}
PumpScheduleEvent::PumpScheduleEvent()
{
}

void PumpScheduleEvent::execute(Event evt)
{
    String data = evt.extra;
    vector<String> schedules;
    String delimiter = ",";
    String value;
    do
    {
        value = data.substring(0, data.indexOf(delimiter));
        if (value != "")
        {
            schedules.push_back(value);
        }
        data.replace(value + delimiter, "");
        data.replace(delimiter + value, "");
        data.replace(value, "");
    } while (value != "");

    pumpCtrl.setSchedules(schedules);
    
    Event event(EventNames::ScheduleStart);
    evtManager.trigger(event);
}

#endif