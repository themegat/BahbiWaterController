#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <aWOT.h>
#include <TaskSchedulerDeclarations.h>

#include "PumpController.h"
#include "Configuration.h"
#include "PumpSpeed.h"
#include "HttpServer.h"
#include "Event.h"
#include "FireInterface.h"
#include <Firebase_ESP_Client.h>

#include "events/PumpStartEvent.h"
#include "events/PumpStopEvent.h"
#include "events/PumpSpeedEvent.h"
#include "events/PumpRunDurationEvent.h"
#include "events/PumpScheduleEvent.h"
#include "events/SchedulePumpStartEvent.h"
#include "events/SchedulePumpStopEvent.h"


#include "EventNames.h"

#include <string>
#include <iostream>
#include "NetTime.h"

PumpController pumpCtrl(4, 13, 12, 14);

WiFiServer server(80);
Application app;

HttpServer httpServer(Configuration::wifiSSID, Configuration::wifiPassword);
void serverListen();

Task taskServer(1, TASK_FOREVER, &serverListen);

Scheduler runner;
EventManager evtManager;

PumpStartEvent pumpStartEvent;
PumpStopEvent pumpStopEvent;
PumpSpeedEvent pumpSpeedEvent;
PumpRunDurationEvent pumpRunDurationEvent;
PumpScheduleEvent pumpScheduleEvent;
SchedulePumpStartEvent schedulePumpStartEvent;
SchedulePumpStopEvent schedulePumpStopEvent;

FirebaseData fbdo;
FireInterface fire(Configuration::fireApiKey, Configuration::fireDatabaseUrl, Configuration::fireDeviceID);

NetTime netTime(Configuration::timeZone, 0, Configuration::ntpServer);

void eventStartPump();
void eventStopPump();

Scheduler sc;

Task taskStartPump(TASK_ONCE, TASK_ONCE, &eventStartPump);
Task taskStopPump(TASK_ONCE, TASK_ONCE, &eventStopPump);

void setup()
{
  Serial.begin(9600);
  Serial.println("Setting up ...");

  runner.init();
  runner.addTask(taskServer);
  runner.addTask(taskStartPump);
  runner.addTask(taskStopPump);

  httpServer.start();
  netTime.init();

  taskServer.enable();

  fire.connect();
  fire.subscribe(&fbdo, "state");

  evtManager.subscribe(Subscriber(EventNames::StartPump, &pumpStartEvent));
  evtManager.subscribe(Subscriber(EventNames::StopPump, &pumpStopEvent));
  evtManager.subscribe(Subscriber(EventNames::SetPumpPressure, &pumpSpeedEvent));
  evtManager.subscribe(Subscriber(EventNames::SetPumpRunDuration, &pumpRunDurationEvent));
  evtManager.subscribe(Subscriber(EventNames::SetPumpSchedule, &pumpScheduleEvent));
  evtManager.subscribe(Subscriber(EventNames::ScheduleStart, &schedulePumpStartEvent));
  evtManager.subscribe(Subscriber(EventNames::ScheduleStop, &schedulePumpStopEvent));
}

void loop()
{
  fire.start();
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
  Event eventStart(EventNames::StopPump);
  evtManager.trigger(eventStart);
  Event eventSchedule(EventNames::ScheduleStart);
  evtManager.trigger(eventSchedule);
}