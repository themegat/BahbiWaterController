/**
 * @author T Motsoeneng
 * @email tshepomotsoeneng0@gmail.com
 * @create date 2024-03-16
 * @modify date 2024-03-16
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
    FireMap item;
    item.key = "active";
    item.value = "true";

    std::vector<FireMap> payload;
    payload.push_back(item);

    String key = "D" + netTime.getDateString() + "T" + netTime.getTimeString();

    fire.append("dateTimeOn", key, payload);
}

#endif