/*
 * Author:  Tomislav Zorčec
 */

#include <Arduino.h>
#include <configurations.h>
#include <logger.h>

bool Logger::isSerialReady = false;

void Logger::initialize() {
    Logger::info("Initializing logger");
    Serial.begin(115200);
    Serial.println();
    isSerialReady = true;
};

void Logger::log(String message) { 
    Logger::log(LogType::INFO, message);
}

void Logger::log(LogType type, String message) {
    if (type >= Configuration::LOG_LEVEL) {
        String fullMessage = "[{TYPE}]\t{MESSAGE}";
        String typeStr = "";
        switch(type) {
            case LogType::TRACE:
                typeStr = "TRACE";
                break;
            case LogType::DEBUG:
                typeStr = "DEBUG";
                break;
            case LogType::INFO:
                typeStr = "INFO";
                break;
            case LogType::WARN:
                typeStr = "WARN";
                break;
            case LogType::ERROR:
                typeStr = "ERROR";
                break;
        }
        fullMessage.replace("{TYPE}", typeStr);
        fullMessage.replace("{MESSAGE}", message);
        if (isSerialReady) {
            Serial.print(fullMessage);
            Serial.println();
        }

    }
};

void Logger::trace(String message) {
    Logger::log(LogType::TRACE, message);
};

void Logger::debug(String message) {
    Logger::log(LogType::DEBUG, message);
};

void Logger::info(String message) {
    Logger::log(LogType::INFO, message);
};

void Logger::warn(String message) {
    Logger::log(LogType::WARN, message);
};

void Logger::error(String message) {
    Logger::log(LogType::ERROR, message);
};