/**
 * @author T Motsoeneng
 * @email tshepomotsoeneng0@gmail.com
 * @create date 2024-03-15
 * @modify date 2024-03-15
 * @desc [description]
 */


#include <cstring>
#include <string>
#include "HttpServer.h"
#include <ESP8266WiFi.h>
#include <aWOT.h>
#include "PumpSpeed.h"
#include "EventNames.h"

extern WiFiServer server;
extern Application app;
extern EventManager evtManager;

void index(Request &req, Response &res)
{
    res.print("Waterer:: Active");
}

void run(Request &req, Response &res)
{
    Event startPumpEvt(EventNames::StartPump);
    Event evt(EventNames::SetPumpPressure);

    const int charLen = 10;
    char paramSpeed[charLen];

    req.route("speed", paramSpeed, charLen);
    String result = "";
    int speed = atoi(paramSpeed);
    Serial.println("HttpServer run: Speed - " + String(paramSpeed));
    switch (speed)
    {
    case 1:
    {
        result = pumpSpeedStr(SLOW);
        evt.extra = paramSpeed;
        evtManager.trigger(evt);
        evtManager.trigger(startPumpEvt);
        break;
    }
    case 2:
    {
        result = pumpSpeedStr(SHIGH);
        evt.extra = paramSpeed;
        evtManager.trigger(evt);
        evtManager.trigger(startPumpEvt);
        break;
    }
    case 3:
    {
        result = pumpSpeedStr(SHIGH);
        evt.extra = paramSpeed;
        evtManager.trigger(evt);
        evtManager.trigger(startPumpEvt);
        break;
    }
    default:
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