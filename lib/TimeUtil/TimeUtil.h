/**
 * @author T Motsoeneng
 * @link https://github.com/themegat
 */

#include <Arduino.h>

#ifndef TimeUtil_h
#define TimeUtil_h

class TimeUtil
{
public:
    /**
     * Gets the time difference between two time strings
     * @param currentTime
     * @param compareTime
     * @returns long
     * @example "12:00:00", "13:00:00" -> 3600
     */
    static long getTimeDifference(String currentTime, String compareTime);

    /**
     * Converts the time string to timestamp
     * @param time
     * @returns long
     * @example "12:00:00" -> 43200
     */
    static long toTimeStamp(String time);

    /**
     * Extracts the seconds from the timestamp
     * @param timeStamp
     * @returns int
     * @example 43200 -> 0
     */
    static int extractSeconds(long timeStamp);

    /**
     * Extracts the minutes from the timestamp
     * @param timeStamp
     * @returns int
     * @example 43200 -> 30
     */
    static int extractMinutes(long timeStamp);

    /**
     * Extracts the hours from the timestamp
     * @param timeStamp
     * @returns int
     * @example 43200 -> 12
     */
    static int extractHours(long timeStamp);

    /**
     * Converts the timestamp to time string
     * @param timeStamp
     * @returns String
     * @example 43200 -> "12:00:00"
    */
    static String toTimeString(long timeStamp);

    // static inline int `SECOND_IN_HOUR = 3600`
    static inline int SECOND_IN_HOUR = 3600;

    // static inline int `SECONDS = 60`
    static inline int SECONDS = 60;

    // static inline int `HOURS_IN_DAY = 24`
    static inline int HOURS_IN_DAY = 24;

    // static inline long `MICRO_SECONDS = 1000000`
    static inline long MICROSECONDS = 1000000;

    // static inline int `MILLISECONDS = 1000`
    static inline int MILLISECONDS = 1000;
};

#endif