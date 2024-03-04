#include "FireInterface.h"
#include "addons/RTDBHelper.h"
#include "addons/TokenHelper.h"
#include "FireSubscriptions.h"

FirebaseAuth auth;
FirebaseConfig config;

bool signupOK = false;

#pragma region private
void FireInterface::_streamCallback(FirebaseStream data)
{
    // Serial.println("Data path: " + data.dataPath());
    // Print out the value
    // Stream data can be many types which can be determined from function dataType
    if (data.dataTypeEnum() == firebase_rtdb_data_type_integer)
    {
        // Serial.println(data.to<int>());
        FireSubscriptions::pumpPressure(data.dataPath(), data.to<int>());
        FireSubscriptions::runDurationSeconds(data.dataPath(), data.to<int>());
    }
    else if (data.dataTypeEnum() == firebase_rtdb_data_type_float)
        Serial.println(data.to<float>(), 5);
    else if (data.dataTypeEnum() == firebase_rtdb_data_type_double)
        printf("%.9lf\n", data.to<double>());
    else if (data.dataTypeEnum() == firebase_rtdb_data_type_boolean)
    {
        FireSubscriptions::switchOn(data.dataPath(), data.to<bool>());
    }
    else if (data.dataTypeEnum() == firebase_rtdb_data_type_string)
    {
        Serial.println(data.to<String>());
        // FireSubscriptions::pumpPressure(data.dataPath(), data.to<String>());
        // FireSubscriptions::runDurationSeconds(data.dataPath(), data.to<String>());
    }
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

void FireInterface::_streamTimeoutCallback(bool timeout)
{
    if (timeout)
    {
        // Stream timeout occurred
        Serial.println("Stream timeout, resume streaming...");
    }
}
#pragma endregion

#pragma region public
FireInterface::FireInterface(String apiKey, String databaseUrl, String deviceID)
{
    _apiKey = apiKey;
    _dbUrl = databaseUrl;
    _deviceID = deviceID;
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
        Serial.println("Connected to Firebase");
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
    String fullPath = "/" + _deviceID + "/" + path;
    Serial.println("Subscribed to " + fullPath);
    Firebase.RTDB.setStreamCallback(fbdo, _streamCallback, _streamTimeoutCallback);

    // In setup(), set the streaming path to "/test/data" and begin stream connection

    if (!Firebase.RTDB.beginStream(fbdo, fullPath))
    {
        // Could not begin stream connection, then print out the error detail
        Serial.println(fbdo->errorReason());
    }
}
#pragma endregion
