/**
 * @author T Motsoeneng
 * @link https://github.com/themegat
 */


#include <Arduino.h>
#include "Event.h"
#include <FireInterface.h>
#include <ArduinoLog.h>
#include <vector>
#include <NetTime.h>

#ifndef LogSartUpEvent_h
#define LogSartUpEvent_h

extern FireInterface fire;
extern NetTime netTime;

class LogSartUpEvent : public EventTask
{
private:
public:
    LogSartUpEvent();
    ~LogSartUpEvent();
    void execute(Event evt);
};

LogSartUpEvent::~LogSartUpEvent()
{
}
LogSartUpEvent::LogSartUpEvent()
{
}

void LogSartUpEvent::execute(Event evt)
{
    std::vector<FireStringMap> payload;

    FireStringMap item;
    item.key = "operating-voltage";
    item.value = ESP.getVcc();
    payload.push_back(item);

    item.key = "restart-reason";
    item.value = ESP.getResetReason();
    payload.push_back(item);

    item.key = "sketch-version-md5";
    item.value = ESP.getSketchMD5();
    payload.push_back(item);

    String date = netTime.getDateString();
    String key = netTime.getTimeString();

    fire.append(FireInterface::WAKE_INFO_PATH + "/" + date, key, payload);
}

#endif