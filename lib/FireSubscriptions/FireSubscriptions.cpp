/**
 * @author T Motsoeneng
 * @link https://github.com/themegat
 */

#include "FireSubscriptions.h"
#include "EventNames.h"
#include <iostream>

using namespace std;

extern EventManager evtManager;

void FireSubscriptions::switchOn(String path, boolean state)
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
    }
};

void FireSubscriptions::pumpPressure(String path, String state)
{
    if (path.indexOf("pumpPressure") != -1)
    {
        Event event(EventNames::SetPumpPressure, state.c_str());
        evtManager.trigger(event);
    }
}

void FireSubscriptions::runDurationSeconds(String path, String state)
{
    if (path.indexOf("runDurationSeconds") != -1)
    {
        Event event(EventNames::SetPumpRunDuration, state.c_str());
        evtManager.trigger(event);
    }
}

void FireSubscriptions::pumpSchedule(String path, String state)
{
    String allowedPath = "scheduledRunTimes";
    if (path.indexOf(allowedPath) != -1)
    {
        path.replace(allowedPath, " ");
        if (path.indexOf("/") > -1)
        {
            path.replace("/", " ");
            path.trim();
            if (path.toInt() && path.toInt() > -1)
            {
                state = state + "?" + path.toInt();
                Event event(EventNames::SetPumpSchedule, state.c_str());
                evtManager.trigger(event);
            }
        }
        else
        {
            state.replace("[", "");
            state.replace("]", "");
            state.replace("\"", "");
            Event event(EventNames::SetPumpSchedule, state.c_str());
            evtManager.trigger(event);
        }
    }
}

void FireSubscriptions::scheduleSleep(String path, String state)
{
    if (path.indexOf("scheduleSleep") != -1)
    {
        Event event(EventNames::ScheduleSleepEvent, state.c_str());
        evtManager.trigger(event);
    }
}
