#include <Arduino.h>
#include <TaskScheduler.h>
#include <ESP8266WiFi.h>
#include <aWOT.h>

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

FirebaseData fbdo;
FireInterface fire(Configuration::fireApiKey, Configuration::fireDatabaseUrl, Configuration::fireDeviceID);

NetTime netTime(Configuration::timeZone, 0, Configuration::ntpServer);

void setup()
{
  Serial.begin(9600);
  Serial.println("Setting up ...");

  runner.init();
  runner.addTask(taskServer);

  httpServer.start();
  netTime.init();

  taskServer.enable();

  fire.connect();
  fire.subscribe(&fbdo, "state");

  evtManager.subscribe(Subscriber(EventNames::StartPump, &pumpStartEvent));
  evtManager.subscribe(Subscriber(EventNames::StopPump, &pumpStopEvent));
  evtManager.subscribe(Subscriber(EventNames::SetPumpPressure, &pumpSpeedEvent));
  evtManager.subscribe(Subscriber(EventNames::SetPumpRunDuration, &pumpRunDurationEvent));
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