#include "FireSubscriptions.h"
#include "EventNames.h"
#include <iostream>

using namespace std;

extern EventManager evtManager;

boolean FireSubscriptions::switchOn(String path, boolean state)
{
    if (path.indexOf("switchOn") != -1)
    {
        if (state)
        {
            Event event(EventNames::StartPump);
            evtManager.trigger(event);
        }
        else
        {
            Event event(EventNames::StopPump);
            evtManager.trigger(event);
        }
        return true;
    }
    return false;
};

boolean FireSubscriptions::pumpPressure(String path, int state)
{
    if (path.indexOf("pumpPressure") != -1)
    {
        char *value = "";
        itoa(state, value, 10);
        Event event(EventNames::SetPumpPressure, value);
        evtManager.trigger(event);
        return true;
    }
    return false;
}

boolean FireSubscriptions::runDurationSeconds(String path, int state)
{
    if (path.indexOf("runDurationSeconds") != -1)
    {
        char *value = "";
        itoa(state, value, 10);
        Event event(EventNames::SetPumpRunDuration, value);
        evtManager.trigger(event);
        return true;
    }
    return false;
}

boolean FireSubscriptions::pumpSchedule(String path, String state)
{
    if (path.indexOf("scheduledRunTimes") != -1)
    {
        state.replace("[", "");
        state.replace("]", "");
        state.replace("\"", "");
        Event event(EventNames::SetPumpSchedule, state.c_str());
        evtManager.trigger(event);

        return true;
    }
    return false;
}
