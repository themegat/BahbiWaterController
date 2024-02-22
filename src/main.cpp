#include <Arduino.h>
#include <TaskScheduler.h>
#include <ESP8266WiFi.h>
#include <aWOT.h>

#include "PumpController.h"
#include "Configuration.h"
#include "PumpSpeed.h"

PumpController pumpCtrl(4, 13, 12, 14);

WiFiServer server(80);
Application app;

void serverInitialize();
void serverListen();

Task taskServer(1, TASK_FOREVER, &serverListen);

Scheduler runner;

void setup()
{
  Serial.begin(9600);
  Serial.println("Setting up ...");

  runner.init();
  runner.addTask(taskServer);

  serverInitialize();
  taskServer.enable();
}

void loop()
{
  runner.execute();
}

void index(Request &req, Response &res)
{
  res.print("Waterer:: Active");
}

void run(Request &req, Response &res)
{
  const int charLen = 10;
  char paramSpeed[charLen];

  req.route("speed", paramSpeed, charLen);
  String result = "";
  int speed = atoi(paramSpeed);
  Serial.println("speed - " + speed);
  switch (speed)
  {
  case 1:
    pumpCtrl.run(SLOW);
    result = "Pump running - LOW";
    break;
  case 2:
    pumpCtrl.run(SMEDIUM);
    result = "Pump running - MEDIUM";
    break;
  case 3:
    pumpCtrl.run(SHIGH);
    result = "Pump running - HIGH";
    break;
  default:
    pumpCtrl.stop();
    result = "Pump stopped. Speed not 1 - 3";
    break;
  }

  res.print("Waterer :: " + result);
}

void stopPump(Request &req, Response &res)
{
  pumpCtrl.stop();
  res.print("Waterer :: Pump stopped");
}

void serverListen()
{
  WiFiClient client = server.available();

  if (client.connected())
  {
    app.process(&client);
  }
}

void serverInitialize()
{
  WiFi.begin(Configuration::wifiSSID, Configuration::wifiPassword);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println(WiFi.localIP());

  app.get("/", &index);
  app.post("/run/:speed", &run);
  app.post("/stop", &stopPump);
  server.begin();
}
