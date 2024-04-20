/*
 * Author:  Tomislav Zorčec
 */

#include <Arduino.h>
#include <configurations.h>
#include <DallasTemperature.h>
#include <logger.h>
#include <arduino-timer.h>

OneWire oneWire;
DallasTemperature sensor;

Timer<1> sensorReadTimer;

void initializeTemperatureSensor(int pin) {
    pinMode(pin, INPUT);
    oneWire.begin(pin);
    sensor.setOneWire(&oneWire);
    sensor.begin();
    DeviceAddress sensorAddress;
    sensor.getAddress(sensorAddress, 0);
}

float getTemperature() {
    sensor.requestTemperatures();
    return sensor.getTempCByIndex(0);
}

void setFanSpeedPercent(int fanPin, int percent) {
    int value = (percent / 100.0) * 255;
    analogWrite(fanPin, value);
}

int getFanSpeedPercent(int current, int min, int max, int minPower) {
    if (current < min) {
       return 0;
    } else if (current >= max) {
        return 100;
    } else {
        float stepPerTemp = 100 / (max /*40*/ - min /*25*/);
        int power = (current - min) * stepPerTemp;
       return power < 100 ? power + minPower : 100;
    }
}

// int getFanSpeedRpm() {
//   int highTime = pulseIn(SIGNAL_PIN, HIGH);
//   int lowTime = pulseIn(SIGNAL_PIN, LOW);
//   int period = highTime + lowTime;
//   if (period == 0) {
//     return 0;
//   }
//   float freq = 1000000.0 / (float)period;
//   return (freq * 60.0) / 2.0; // two cycles per revolution
// }

bool onSensorRead(void *) {
    float temperature = getTemperature();
    int inputPercentage = getFanSpeedPercent(temperature, Configuration::MIN_TEMPERATURE_INPUT, Configuration::MAX_TEMPERATURE, Configuration::MIN_FAN_SPEED_PERCENT);
    int outputPercentage = getFanSpeedPercent(temperature, Configuration::MIN_TEMPERATURE_OUTPUT, Configuration::MAX_TEMPERATURE, Configuration::MIN_FAN_SPEED_PERCENT);
    Logger::info("Temperature: " + String(temperature) + "°C");
    Logger::info("Power in: " + String(inputPercentage) + "\% out:" + String(outputPercentage) + "\%");

    analogWrite(Configuration::INPUT_FAN_PIN, inputPercentage);
    analogWrite(Configuration::OUTPUT_FAN_PIN, outputPercentage);

    return true;
}
    
void setup() {

    delay(500);
    Logger::initialize();
    Logger::log("FanControler v0.1");
    
    analogWriteFreq(25000);
    analogWriteRange(100);

    pinMode(Configuration::INPUT_FAN_PIN, OUTPUT);
    pinMode(Configuration::OUTPUT_FAN_PIN, OUTPUT);

    analogWrite(Configuration::INPUT_FAN_PIN, 0);
    analogWrite(Configuration::OUTPUT_FAN_PIN, 0);
    
    initializeTemperatureSensor(Configuration::TEMPERATURE_PIN);
    sensorReadTimer.every(5000, onSensorRead);
   
}

void loop() {
    sensorReadTimer.tick();
}
