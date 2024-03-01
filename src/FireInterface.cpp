#include "FireInterface.h"
#include "addons/RTDBHelper.h"
#include "addons/TokenHelper.h"

FirebaseAuth auth;
FirebaseConfig config;
// FirebaseData stream;

bool signupOK = false;
String childPath[2] = {"/start", "/data"};

extern EventManager evtManager;

void streamCallback(FirebaseStream data)
{
    Serial.println("Data path: " + data.dataPath());
    // Print out the value
    // Stream data can be many types which can be determined from function dataType
    if (data.dataTypeEnum() == firebase_rtdb_data_type_integer)
        Serial.println(data.to<int>());
    else if (data.dataTypeEnum() == firebase_rtdb_data_type_float)
        Serial.println(data.to<float>(), 5);
    else if (data.dataTypeEnum() == firebase_rtdb_data_type_double)
        printf("%.9lf\n", data.to<double>());
    else if (data.dataTypeEnum() == firebase_rtdb_data_type_boolean)
    {
        if (data.to<bool>() == true)
        {
            Event start("run", "MEDIUM");
            evtManager.trigger(start);
        }
        else
        {
            Event stop("stop");
            evtManager.trigger(stop);
        }
    }
    else if (data.dataTypeEnum() == firebase_rtdb_data_type_string)
        Serial.println(data.to<String>());
    else if (data.dataTypeEnum() == firebase_rtdb_data_type_json)
    {
        FirebaseJson *json = data.to<FirebaseJson *>();
        Serial.println(json->raw());
    }
    else if (data.dataTypeEnum() == firebase_rtdb_data_type_array)
    {
        FirebaseJsonArray *arr = data.to<FirebaseJsonArray *>();
        Serial.println(arr->raw());
    }
}

void streamTimeoutCallback(bool timeout)
{
    if (timeout)
    {
        // Stream timeout occurred
        Serial.println("Stream timeout, resume streaming...");
    }
}

FireInterface::FireInterface(String apiKey, String databaseUrl)
{
    _apiKey = apiKey;
    _dbUrl = databaseUrl;
}

FireInterface::~FireInterface()
{
}

void FireInterface::connect()
{
    config.api_key = _apiKey;

    /* Assign the RTDB URL (required) */
    config.database_url = _dbUrl;

    /* Sign up */
    if (Firebase.signUp(&config, &auth, "", ""))
    {
        Serial.println("ok");
        signupOK = true;
    }
    else
    {
        Serial.printf("%s\n Error: ", config.signer.signupError.message.c_str());
    }

    /* Assign the callback function for the long running token generation task */
    config.token_status_callback = tokenStatusCallback; // see addons/TokenHelper.h

    Firebase.begin(&config, &auth);
    Firebase.reconnectWiFi(true);
}

void FireInterface::start()
{
    if (Firebase.ready() && signupOK)
    {
        // dummyWrite();
    }
}

void FireInterface::subscribe(FirebaseData *fbdo, String path)
{
    Serial.println("Subscribe to " + path);
    Firebase.RTDB.setStreamCallback(fbdo, streamCallback, streamTimeoutCallback);

    // In setup(), set the streaming path to "/test/data" and begin stream connection

    if (!Firebase.RTDB.beginStream(fbdo, path))
    {
        // Could not begin stream connection, then print out the error detail
        Serial.println(fbdo->errorReason());
    }
}