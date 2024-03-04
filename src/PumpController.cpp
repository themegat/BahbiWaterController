#include "PumpController.h"
#include <Arduino.h>
#include "PumpSpeed.h"
#include "TimeUtil.h"

PumpController::PumpController(int transistor1, int transistor2, int transistor3, int transistor4)
{
    pinMode(transistor1, OUTPUT);
    _transistor1 = transistor1;
    pinMode(transistor2, OUTPUT);
    _transistor2 = transistor2;
    pinMode(transistor3, OUTPUT);
    _transistor3 = transistor3;
    pinMode(transistor4, OUTPUT);
    _transistor4 = transistor4;
    _speed = PumpSpeed::SMEDIUM;
    _runDuration = 5;
}

void PumpController::run(PumpSpeed speed)
{
    _speed = speed;
    if (_running)
    {
        stop();
    }

    if (_speed == SLOW)
    {
        digitalWrite(_transistor1, HIGH);
        digitalWrite(_transistor2, HIGH);
    }
    else if (_speed == SMEDIUM)
    {
        digitalWrite(_transistor1, HIGH);
        digitalWrite(_transistor2, HIGH);
        digitalWrite(_transistor3, HIGH);
    }
    else if (_speed == SHIGH)
    {
        digitalWrite(_transistor1, HIGH);
        digitalWrite(_transistor2, HIGH);
        digitalWrite(_transistor3, HIGH);
        digitalWrite(_transistor4, HIGH);
    }
    _running = true;
    Serial.println("PumpController - Running at : " + pumpSpeedStr(_speed));
}

void PumpController::stop()
{
    digitalWrite(_transistor1, LOW);
    digitalWrite(_transistor2, LOW);
    digitalWrite(_transistor3, LOW);
    digitalWrite(_transistor4, LOW);
    _running = false;
    Serial.println("PumpController - Stopped");
}

void PumpController::setSpeed(PumpSpeed speed)
{
    _speed = speed;
    Serial.println("PumpController - Speed set to : " + pumpSpeedStr(_speed));
}

PumpSpeed PumpController::getSpeed()
{
    return _speed;
}

void PumpController::setRunDuration(int duration)
{
    _runDuration = duration;
    Serial.println("PumpController - Run duration set to : " + String(duration));
}

int PumpController::getRunDuration()
{
    return _runDuration;
}

void PumpController::setSchedules(std::vector<String> schedules)
{
    _schedules = schedules;
    Serial.println("PumpController - Following schedules added");
    for (String sc : _schedules)
    {
        Serial.println("Schedule :: " + sc);
    }
}

std::vector<String> PumpController::getSchedules()
{
    return _schedules;
}

String PumpController::getNextSchedule(String currentTime)
{
    int currentTimeStamp = TimeUtil::toTimeStamp(currentTime);
    std::vector<String> temp;
    for (String sc : _schedules)
    {
        temp.push_back(sc);
    }
    std::sort(temp.begin(), temp.end());
    String result = temp.at(0);
    for (String sc : temp)
    {
        int timeStamp = TimeUtil::toTimeStamp(sc);
        if (currentTimeStamp <= timeStamp)
        {
            result = sc;
        }
    }
    return result;
}