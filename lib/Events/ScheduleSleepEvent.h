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

void doSleep()
{
    String sleepTime = netTime.getTimeString();
    Log.info("Going to sleep current time: %s. Wake up at: %s" CR, sleepTime.c_str(), wakeTime.c_str());

    std::vector<FireStringMap> payload;

    FireStringMap item;
    item.key = "sleep-time";
    item.value = sleepTime;
    payload.push_back(item);

    item.key = "sleep-duration";
    item.value = TimeUtil::toTimeString(wakeAt);
    payload.push_back(item);

    String key = netTime.getTimeString();
    String date = netTime.getDateString();

    uint64 maxSleep = 30 * TimeUtil::SECONDS * TimeUtil::MICROSECONDS;
    uint64 wakeTimeMicros = wakeAt * TimeUtil::MILLISECONDS;
    String sleepReason = "Scheduled Sleep";

    if (wakeTimeMicros > maxSleep)
    {
        Log.info("Sleep duration too long: %l. Resetting duration." CR, wakeTimeMicros / 1000);
        wakeTimeMicros = maxSleep;

        item.key = "sleep-duration-adjusted";
        item.value = TimeUtil::toTimeString(wakeTimeMicros / TimeUtil::MILLISECONDS);
        sleepReason = "Deep-Sleep Cycle";
        payload.push_back(item);
    }

    item.key = "sleep-reason";
    item.value = sleepReason;
    payload.push_back(item);

    fire.append(FireInterface::SLEEP_INFO_PATH + "/" + date, key, payload);
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
    String currentTime = netTime.getHour() + ":" + netTime.getMinute() + ":" + netTime.getSecond();
    long sleepAt = TimeUtil::getTimeBetween(currentTime, sleepTime) * TimeUtil::MILLISECONDS;
    wakeAt = TimeUtil::getTimeBetween(currentTime, wakeTime) * TimeUtil::MILLISECONDS;

    if (TimeUtil::isBetween(sleepTime, wakeTime, currentTime))
    {
        sleepAt = 0;
        sleepTime = currentTime;
    }

    Log.info("Scheduling sleep at: %s - Wake at: %s" CR, sleepTime.c_str(), wakeTime.c_str());

    taskSleep.cancel();
    taskSleep.setCallback(&doSleep);
    taskSleep.restartDelayed(sleepAt);
}

#endif