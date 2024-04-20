/*
 * Author:  Tomislav Zorčec
 * URL:     https://github.com/zorcec/sensorio
 */

#ifndef LOGGER_H
#define LOGGER_H

#include <Arduino.h>

enum LogType {
    TRACE = 0,
    DEBUG,
    INFO,
    WARN,
    ERROR
};

class Logger {
    public:
        static void initialize();
        static void log(String);
        static void log(LogType, String);
        static void trace(String);
        static void debug(String);
        static void info(String);
        static void warn(String);
        static void error(String);

    private:
        static bool isSerialReady;
};

#endif