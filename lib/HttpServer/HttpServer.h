/**
 * @author T Motsoeneng
 * @email tshepomotsoeneng0@gmail.com
 * @create date 2024-03-15
 * @modify date 2024-03-15
 */


#include <Arduino.h>
#if defined(ESP32)
#include <WiFi.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#endif
#include <aWOT.h>
#include "Event.h"

#ifndef HttpServer_h
#define HttpServer_h

class HttpServer
{
private:
    String _ssid;
    String _password;
    void _index(Request &req, Response &res);

public:
    HttpServer(String ssid, String password);
    ~HttpServer();
    void start();
    void serverListen();
};

#endif