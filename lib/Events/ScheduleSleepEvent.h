/**
 * @author T Motsoeneng
 * @link https://github.com/themegat
 */

#include <Arduino.h>
#include <TimeUtil.h>
#include <NetTime.h>
#include <TaskSchedulerDeclarations.h>
#include <Event.h>
#include <ArduinoLog.h>
#include <FireInterface.h>

#ifndef ScheduleSleepEvent_h
#define ScheduleSleepEvent_h

extern NetTime netTime;
extern EventManager evtManager;
extern Task taskSleep;
extern FireInterface fire;
extern HttpServer httpServer;

uint64 wakeAt = 0;
String wakeTime = "";
String sleepReason = "";

void doSleep()
{
    String sleepTime = netTime.getTimeString();
    Log.info("Going to sleep current time: %s. Wake up at: %s" CR, sleepTime.c_str(), wakeTime.c_str());

    std::vector<FireStringMap> payload;

    FireStringMap item;
    item.key = "sleep-time";
    item.value = sleepTime;
    payload.push_back(item);

    item.key = "sleep-reason";
    item.value = sleepReason;
    payload.push_back(item);

    item.key = "sleep-duration";
    item.value = TimeUtil::toTimeString(wakeAt);
    payload.push_back(item);

    String key = netTime.getTimeString();
    String date = netTime.getDateString();

    fire.append(FireInterface::SLEEP_INFO_PATH + "/" + date, key, payload);

    uint64 maxSleep = 40 * TimeUtil::SECONDS * TimeUtil::MICROSECONDS;
    uint64 wakeTimeMicros = wakeAt * TimeUtil::MILLISECONDS;

    if (wakeTimeMicros > maxSleep)
    {
        Log.info("Sleep duration too long: %l. Resetting duration." CR, wakeTimeMicros / 1000);
        wakeTimeMicros = maxSleep;
    }
    Log.info("Sleep duration: %l." CR, wakeTimeMicros);
    ESP.deepSleep(wakeTimeMicros, RF_DEFAULT);
}

class ScheduleSleepEvent : public EventTask
{
private:
public:
    ScheduleSleepEvent();
    ~ScheduleSleepEvent();
    void execute(Event evt);
};

ScheduleSleepEvent::~ScheduleSleepEvent()
{
}
ScheduleSleepEvent::ScheduleSleepEvent()
{
}

void ScheduleSleepEvent::execute(Event evt)
{
    String extra = String(evt.extra);
    String sleepTime = extra.substring(0, extra.indexOf("-"));
    extra.replace(sleepTime + "-", " ");
    extra.trim();
    wakeTime = extra;

    long currentTimestamp = TimeUtil::toTimeStamp(netTime.getTimeString());
    long wakeTimestamp = TimeUtil::toTimeStamp(wakeTime);
    long sleepTimestamp = TimeUtil::toTimeStamp(sleepTime);

    long sleepAt = TimeUtil::getTimeDifference(netTime.getTimeString(), sleepTime);
    wakeAt = TimeUtil::getTimeDifference(sleepTime, wakeTime);
    sleepReason = "Scheduled Sleep";

    if (currentTimestamp > sleepTimestamp && currentTimestamp <= wakeTimestamp)
    {
        sleepAt = 0;
        wakeAt = TimeUtil::getTimeDifference(netTime.getTimeString(), wakeTime);
        sleepReason = "Deep-Sleep Cycle";
    }

    Log.info("Scheduling sleep at: %s - Wake at: %s" CR, sleepTime.c_str(), wakeTime.c_str());

    taskSleep.cancel();
    taskSleep.setCallback(&doSleep);
    taskSleep.restartDelayed(sleepAt);
}

#endif