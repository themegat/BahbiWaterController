#include "FireSubscriptions.h"
#include <iostream>
using namespace std;

extern EventManager evtManager;

boolean FireSubscriptions::switchOn(String path, boolean state)
{
    if (path.indexOf("switchOn") != -1)
    {
        if (state)
        {
            Event event("run", "MEDIUM");
            evtManager.trigger(event);
        }
        else
        {
            Event event("stop");
            evtManager.trigger(event);
        }
        return true;
    }
    return false;
};

boolean FireSubscriptions::pumpPressure(String path, String state)
{
    if (path.indexOf("pumpPressure") != -1)
    {
        Event event("setSpeed", state.c_str());
        evtManager.trigger(event);
        return true;
    }
    return false;
}