/**
 * @author T Motsoeneng
 * @email tshepomotsoeneng0@gmail.com
 * @create date 2024-03-15
 * @modify date 2024-03-15
 */

#include "FireInterface.h"
#include <Firebase_ESP_Client.h>
#include <addons/TokenHelper.h>
#include <addons/RTDBHelper.h>
#include <FireSubscriptions.h>

FirebaseData fbdo;

FirebaseAuth auth;
FirebaseConfig config;

FireInterface::FireInterface(String apiKey, String dbUrl, String readPath, String userEmail, String userPassword)
{
    _apiKey = apiKey;
    _dbUrl = dbUrl;
    _readPath = readPath;
    _userEmail = userEmail;
    _userPassword = userPassword;
    _cachedRead = "";
}

#pragma region public

void FireInterface::connect()
{
    delay(1000);
    config.api_key = _apiKey;
    config.database_url = _dbUrl;
    auth.user.email = _userEmail;
    auth.user.password = _userPassword;
    config.token_status_callback = tokenStatusCallback;
    Serial.println("Firebase connecting");
    Firebase.begin(&config, &auth);
    Firebase.reconnectWiFi(true);
    Serial.println("Firebase connected");
}

void FireInterface::ready()
{
    if (!Firebase.ready())
    {
        Serial.println("Firebase not ready");
    }
}

void FireInterface::read()
{
    if (Firebase.ready())
    {
        if (Firebase.RTDB.getJSON(&fbdo, _readPath))
        {

            if (fbdo.dataTypeEnum() == firebase_rtdb_data_type_json)
            {
                _processJson();
            }
        }
        else
        {
            Serial.println(fbdo.errorReason());
        }
    }
}

#pragma endregion

#pragma region private

void FireInterface::_processJson()
{
    String cache = fbdo.to<String>();
    if (_cachedRead != cache)
    {
        _cachedRead = cache;

        FirebaseJson *json = fbdo.to<FirebaseJson *>();

        FirebaseJsonData scheduleData;
        json->get(scheduleData, "scheduledRunTimes");
        FireSubscriptions::pumpSchedule("scheduledRunTimes", scheduleData.to<String>());
        
        FirebaseJsonData durationData;
        json->get(durationData, "runDurationSeconds");
        FireSubscriptions::runDurationSeconds("runDurationSeconds", durationData.to<String>());

        FirebaseJsonData pressureData;
        json->get(pressureData, "pumpPressure");
        FireSubscriptions::pumpPressure("pumpPressure", pressureData.to<String>());

        Serial.println("JSON Processed: ");
        Serial.println(_cachedRead);
    }
}

#pragma endregion