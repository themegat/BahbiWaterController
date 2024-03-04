#include <Arduino.h>
#include "Event.h"

#ifndef FireInterface_h
#define FireInterface_h

class FirebaseStream;
class FirebaseData;

class FireInterface
{
private:
    String _apiKey;
    String _dbUrl;
    String _deviceID;
    static void _streamTimeoutCallback(bool timeout);
    static void _streamCallback(FirebaseStream data);

public:
    FireInterface(String apiKey, String databaseUrl, String deviceID);
    ~FireInterface();
    void connect();
    void start();
    void subscribe(FirebaseData *fbdo, String path);
};

#endif