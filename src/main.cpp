#include <Arduino.h>
#include <TaskScheduler.h>
#include <ESP8266WiFi.h>
#include <aWOT.h>

#include "PumpController.h"
#include "Configuration.h"
#include "PumpSpeed.h"
#include "HttpServer.h"
#include "Event.h"

#include "PumpStartEvent.h"
#include "PumpStopEvent.h"

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

void setup()
{
  Serial.begin(9600);
  Serial.println("Setting up ...");

  runner.init();
  runner.addTask(taskServer);

  httpServer.start();
  taskServer.enable();

  evtManager.subscribe(Subscriber("run", &pumpStartEvent));
  evtManager.subscribe(Subscriber("stop", &pumpStopEvent));
}

void loop()
{
  runner.execute();
}

void serverListen()
{
  httpServer.serverListen();
}
