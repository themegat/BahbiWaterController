/**
 * @author T Motsoeneng
 * @link https://github.com/themegat
 */

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <aWOT.h>
#include <TaskSchedulerDeclarations.h>
#include <ArduinoLog.h>

#include "PumpController.h"
#include "Configuration.h"
#include "PumpSpeed.h"
#include "HttpServer.h"
#include "Event.h"
#include <FireInterface.h>

#include "PumpStartEvent.h"
#include "PumpStopEvent.h"
#include "PumpSpeedEvent.h"
#include "PumpRunDurationEvent.h"
#include "PumpScheduleEvent.h"
#include "SchedulePumpStartEvent.h"
#include "LogSartUpEvent.h"
#include "LogPumpRunEvent.h"
#include "ScheduleSleepEvent.h"

#include "EventNames.h"

#include <string>
#include <iostream>
#include "NetTime.h"

ADC_MODE(ADC_VCC);

PumpController pumpCtrl(4, 13, 12, 14);

WiFiServer server(80);
Application app;

HttpServer httpServer(Configuration::wifiSSID, Configuration::wifiPassword);
void serverListen();

Scheduler runner;
EventManager evtManager;

PumpStartEvent pumpStartEvent;
PumpStopEvent pumpStopEvent;
PumpSpeedEvent pumpSpeedEvent;
PumpRunDurationEvent pumpRunDurationEvent;
PumpScheduleEvent pumpScheduleEvent;
SchedulePumpStartEvent schedulePumpStartEvent;
LogSartUpEvent logSartUpEvent;
LogPumpRunEvent logPumpRunEvent;
ScheduleSleepEvent scheduleSleepEvent;

NetTime netTime(Configuration::timeZone, 0, Configuration::ntpServer);

void eventStartPump();
void eventStopPump();

Task taskServer(1, TASK_FOREVER, &serverListen, &runner, true);
Task taskStartPump(TASK_SCHEDULE_NC, TASK_ONCE, &eventStartPump, &runner, false);
Task taskStopPump(TASK_SCHEDULE_NC, TASK_ONCE, &eventStopPump, &runner, false);
Task taskLogPumpRuns(TASK_SCHEDULE_NC, TASK_ONCE, NULL, &runner, false);
Task taskSleep(TASK_SCHEDULE_NC, TASK_ONCE, NULL, &runner, false);

void readFromFire();
void connectWifi();
void firebaseReady();

#define PERIOD_READ 30
#define PERIOD_READY_STATUS 10
#define DURATION 1000000

Task taskRead(PERIOD_READ *TASK_SECOND, (DURATION / 10) / PERIOD_READ, &readFromFire, &runner, true);
Task taskFirebaseReady(PERIOD_READY_STATUS *TASK_MINUTE, DURATION / PERIOD_READY_STATUS, &firebaseReady, &runner, true);
FireInterface fire;

void setup()
{
  Serial.begin(9600);
  Log.begin(LOG_LEVEL_ERROR, &Serial);

  Serial.println();
  Serial.println("Setting up ...");

  httpServer.start();
  netTime.init();

  fire.connect();

  evtManager.subscribe(Subscriber(EventNames::StartPump, &pumpStartEvent));
  evtManager.subscribe(Subscriber(EventNames::StopPump, &pumpStopEvent));
  evtManager.subscribe(Subscriber(EventNames::SetPumpPressure, &pumpSpeedEvent));
  evtManager.subscribe(Subscriber(EventNames::SetPumpRunDuration, &pumpRunDurationEvent));
  evtManager.subscribe(Subscriber(EventNames::SetPumpSchedule, &pumpScheduleEvent));
  evtManager.subscribe(Subscriber(EventNames::ScheduleStart, &schedulePumpStartEvent));
  evtManager.subscribe(Subscriber(EventNames::LogSartUpEvent, &logSartUpEvent));
  evtManager.subscribe(Subscriber(EventNames::LogPumpRunEvent, &logPumpRunEvent));
  evtManager.subscribe(Subscriber(EventNames::ScheduleSleepEvent, &scheduleSleepEvent));

  Event event(EventNames::LogSartUpEvent);
  evtManager.trigger(event);
}

void loop()
{
  runner.execute();
}

void serverListen()
{
  httpServer.serverListen();
}

void eventStartPump()
{
  Event event(EventNames::StartPump);
  evtManager.trigger(event);
}

void eventStopPump()
{
  Event eventStop(EventNames::StopPump);
  evtManager.trigger(eventStop);
  Event eventSchedule(EventNames::ScheduleStart);
  evtManager.trigger(eventSchedule);
}

void readFromFire()
{
  fire.read();
}

void firebaseReady()
{
  fire.ready();
}