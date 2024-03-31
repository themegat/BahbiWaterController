/**
 * @author T Motsoeneng
 * @email tshepomotsoeneng0@gmail.com
 * @create date 2024-03-15
 * @modify date 2024-03-15
 */

#include "PumpController.h"
#include <Arduino.h>
#include "PumpSpeed.h"
#include "TimeUtil.h"
#include "ArduinoLog.h"
#include <EventNames.h>

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
    _runDuration = 10;
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
    _startDateTime = netTime.getDateTimeString();

    Log.info("PumpController - Running at : %s" CR, pumpSpeedStr(_speed).c_str());
}

void PumpController::stop()
{
    digitalWrite(_transistor1, LOW);
    digitalWrite(_transistor2, LOW);
    digitalWrite(_transistor3, LOW);
    digitalWrite(_transistor4, LOW);

    if (_running)
    {
        Event event(EventNames::LogPumpRunEvent);
        evtManager.trigger(event);
    }

    _running = false;
    _stopDateTime = netTime.getDateTimeString();

    Log.info("PumpController - Stopped");
}

void PumpController::setSpeed(PumpSpeed speed)
{
    _speed = speed;
    Log.info("PumpController - Speed set to : %s" CR, pumpSpeedStr(_speed).c_str());
}

PumpSpeed PumpController::getSpeed()
{
    return _speed;
}

void PumpController::setRunDuration(int duration)
{
    _runDuration = duration;
    Log.info("PumpController - Run duration set to : %s" CR, String(duration).c_str());
}

int PumpController::getRunDuration()
{
    return _runDuration;
}

void PumpController::setSchedules(std::vector<String> schedules)
{
    _schedules = schedules;
    Log.info("PumpController - Schedules added");
    _printSchedules();
}

void PumpController::setScheduleAtIndex(String schedule, int index)
{
    String msg = "PumpController - Updating schedule " + schedule + " at index " + index;
    Log.info(msg.c_str());

    if ((_schedules.size() - 1) >= index && index >= 0)
    {
        _schedules[index] = schedule;
        Log.info("PumpController - Schedules updated");
        _printSchedules();
    }
    else
    {
        msg = "PumpController - Index out of bounds: " + index;
        Log.error(msg.c_str());
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
            break;
        }
    }
    return result;
}

String PumpController::getStartDateTime()
{
    return _startDateTime;
}

String PumpController::getStopDateTime()
{
    return _stopDateTime;
}

void PumpController::_printSchedules()
{
    Log.infoln("");
    for (String sc : _schedules)
    {
        Log.info("Schedule :: %s" CR, sc.c_str());
    }
}