/**
 * @author T Motsoeneng
 * @link https://github.com/themegat
 */

#include <Arduino.h>
#include "Event.h"
#include <vector>
#include <NetTime.h>
#include <FireInterface.h>
#include <PumpController.h>
#include <PumpSpeed.h>
#include <TaskSchedulerDeclarations.h>

#ifndef LogPumpRunEvent_h
#define LogPumpRunEvent_h

extern FireInterface fire;
extern NetTime netTime;
extern PumpController pumpCtrl;
extern Scheduler runner;
extern Task taskLogPumpRuns;

void logData()
{
    std::vector<FireStringMap> payload;

    FireStringMap item;
    item.key = "startDateTime";
    item.value = pumpCtrl.getStartDateTime();
    payload.push_back(item);

    item.key = "stopDateTime";
    item.value = pumpCtrl.getStopDateTime();
    payload.push_back(item);

    item.key = "duration";
    item.value = String(pumpCtrl.getRunDuration());
    payload.push_back(item);

    item.key = "pressure";
    item.value = pumpSpeedStr(pumpCtrl.getSpeed());
    payload.push_back(item);

    String key = netTime.getTimeString();
    String date = netTime.getDateString();

    fire.append(FireInterface::RUN_INFO_PATH + "/" + date, key, payload);
}

class LogPumpRunEvent : public EventTask
{
public:
    LogPumpRunEvent();
    ~LogPumpRunEvent();
    void execute(Event evt);
};

LogPumpRunEvent::~LogPumpRunEvent()
{
}
LogPumpRunEvent::LogPumpRunEvent()
{
}

void LogPumpRunEvent::execute(Event evt)
{
    taskLogPumpRuns.setCallback(&logData);
    taskLogPumpRuns.restartDelayed(5000);
}

#endif