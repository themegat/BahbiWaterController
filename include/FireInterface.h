#include <Arduino.h>
#include <Firebase_ESP_Client.h>
#include "Event.h"

#ifndef FireInterface_h
#define FireInterface_h

class FireInterface
{
private:
    String _apiKey;
    String _dbUrl;
    String _deviceID;

public:
    FireInterface(String apiKey, String databaseUrl, String deviceID);
    ~FireInterface();
    void connect();
    void start();
    void subscribe(FirebaseData *fbdo, String path);
};

#endif