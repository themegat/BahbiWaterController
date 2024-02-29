#include "HttpServer.h"
#include <ESP8266WiFi.h>
#include <aWOT.h>

extern WiFiServer server;
extern Application app;

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
        // pumpCtrl.run(SLOW);
        result = "Pump running - LOW";
        break;
    case 2:
        // pumpCtrl.run(SMEDIUM);
        result = "Pump running - MEDIUM";
        break;
    case 3:
        // pumpCtrl.run(SHIGH);
        result = "Pump running - HIGH";
        break;
    default:
        // pumpCtrl.stop();
        result = "Pump stopped. Speed not 1 - 3";
        break;
    }

    Serial.println(result);
    res.print("Waterer :: " + result);
}

void stopPump(Request &req, Response &res)
{
    // pumpCtrl.stop();
    String result = "Pump stopped";
    Serial.println(result);
    res.print("Waterer :: " + result);
}

HttpServer::~HttpServer()
{
}

HttpServer::HttpServer(String ssid, String password)
{
    _ssid = ssid;
    _password = password;
}

void HttpServer::start()
{
    WiFi.begin(_ssid, _password);
    Serial.print("Connecting to Wi-Fi");
    while (WiFi.status() != WL_CONNECTED)
    {
        Serial.print(".");
        delay(300);
    }
    Serial.println();
    Serial.print("Connected with IP: ");
    Serial.println(WiFi.localIP());
    Serial.println();

    app.get("/", &index);
    app.post("/run/:speed", &run);
    app.post("/stop", &stopPump);
    server.begin();
}

void HttpServer::serverListen(){
 WiFiClient client = server.available();

  if (client.connected())
  {
    app.process(&client);
  }
}