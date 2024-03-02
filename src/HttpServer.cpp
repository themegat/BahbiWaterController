#include <cstring>
#include <string>
#include "HttpServer.h"
#include <ESP8266WiFi.h>
#include <aWOT.h>
#include "PumpSpeed.h"

extern WiFiServer server;
extern Application app;
extern EventManager evtManager;

void index(Request &req, Response &res)
{
    res.print("Waterer:: Active");
}

void run(Request &req, Response &res)
{
    Event slow("run", "SLOW");
    Event medium("run", "MEDIUM");
    Event high("run", "HIGH");

    const int charLen = 10;
    char paramSpeed[charLen];

    req.route("speed", paramSpeed, charLen);
    String result = "";
    int speed = atoi(paramSpeed);
    Serial.println("speed - " + speed);
    switch (speed)
    {
    case 1:
        result = pumpSpeedStr(SLOW);
        evtManager.trigger(slow);
        break;
    case 2:
        result = pumpSpeedStr(SHIGH);
        evtManager.trigger(medium);
        break;
    case 3:
        result = pumpSpeedStr(SHIGH);
        evtManager.trigger(high);
        break;
    default:
        // pumpCtrl.stop();
        result = "Pump stopped. Speed not 1 - 3";
        break;
    }

    res.print("Waterer :: " + result);
}

void stopPump(Request &req, Response &res)
{
    Event stop("stop");
    String result = "Pump stopped";
    evtManager.trigger(stop);
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

    app.get("/", &index);
    app.post("/run/:speed", &run);
    app.post("/stop", &stopPump);
    server.begin();
}

void HttpServer::serverListen()
{
    WiFiClient client = server.available();

    if (client.connected())
    {
        app.process(&client);
    }
}