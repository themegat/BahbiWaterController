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
    String _childPath[2];
    EventManager _evManager;

public:
    FireInterface(String apiKey, String databaseUrl);
    ~FireInterface();
    void connect();
    void start();
    void subscribe(FirebaseData *fbdo, String path);
};

#endif