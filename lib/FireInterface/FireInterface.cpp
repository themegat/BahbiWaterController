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
#include <Configuration.h>
#include <ArduinoLog.h>

FirebaseData fbdo;

FirebaseAuth auth;
FirebaseConfig config;

FireInterface::FireInterface()
{
    _apiKey = Configuration::fireApiKey;
    _dbUrl = Configuration::fireDatabaseUrl;
    _readPath = "/" + String(Configuration::fireDeviceID) + "/state";
    _writePath = "/" + String(Configuration::fireDeviceID) + "/data";
    _userEmail = Configuration::fireUserEmail;
    _userPassword = Configuration::fireUserPassword;
    _cachedRead = "";
}

#pragma region public

void FireInterface::connect()
{
    config.api_key = _apiKey;
    config.database_url = _dbUrl;
    auth.user.email = _userEmail;
    auth.user.password = _userPassword;
    config.token_status_callback = tokenStatusCallback;
    Serial.println("Firebase connecting");
    Firebase.begin(&config, &auth);
    Firebase.reconnectWiFi(true);
    Serial.println("Firebase connected as {" + _userEmail + "}");
}

void FireInterface::ready()
{
    if (!Firebase.ready())
    {
        Log.error("Firebase not ready");
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
            Log.error("FireInterface Error: %s" CR, fbdo.errorReason().c_str());
        }
    }
}

void FireInterface::append(String node, String key, std::vector<FireMap> payload)
{
    std::vector<String> schedules;

    if (Firebase.ready())
    {
        FirebaseJson dto;
        FirebaseJson json;
        for (FireMap item : payload)
        {
            json.add(item.key, item.value);
        }
        dto.add(key, json);
        String path = _writePath + "/" + node;
        if (Firebase.RTDB.updateNode(&fbdo, path, &dto))
        {
            Log.info("Updated: %s" CR, fbdo.dataPath().c_str());
            Log.info("Update payload: %s" CR, fbdo.jsonString().c_str());
        }
        else
        {
            Log.error("FireInterface Error: %s" CR, fbdo.errorReason().c_str());
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

        Log.verbose("JSON Processed: %s" CR, _cachedRead.c_str());
    }
}

#pragma endregion