#include <logger.h>

#ifndef CONFIGURATION_H
#define CONFIGURATION_H

namespace Configuration {

    const LogType LOG_LEVEL = LogType::TRACE;

    const int INPUT_FAN_PIN = 15;
    const int OUTPUT_FAN_PIN = 13;
    const int TEMPERATURE_PIN = 12;
    
    const int MIN_FAN_SPEED_PERCENT = 10;
    const int MIN_TEMPERATURE_INPUT = 25;
    const int MIN_TEMPERATURE_OUTPUT = 22;

    const int MAX_TEMPERATURE = 38;

}

#endif