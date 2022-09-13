#include <Arduino.h>
#include "task3.h"
#include "events.h"

String btnState(uint8_t btnState)
{
    if (btnState == HIGH)
    {
        return "OFF";
    }
    else
        return "ON";
}
void task3()
{

    enum class TaskStates
    {
        INIT,
        WAIT_PRESS,
    };
    static TaskStates taskState = TaskStates::INIT;

    constexpr uint8_t PRESS_BTN_PIN = 13;

    static uint8_t ledGren = 25;
    static uint8_t ledBlue = 26;

    static uint32_t lasTime;
    static constexpr uint32_t STATIC_TIME = 500;

    static bool ledStatus = false;

    switch (taskState)
    {
    case TaskStates::INIT:
    {
        pinMode(PRESS_BTN_PIN, INPUT_PULLUP);
        ledStatus = LOW;
        pinMode(ledGren, OUTPUT);
        digitalWrite(ledGren, ledStatus);
        lasTime = 0;
        pinMode(ledBlue, OUTPUT);
        digitalWrite(ledBlue, ledStatus);
        break;
    }
    case TaskStates::WAIT_PRESS:
    {
        uint32_t currentTime = millis();
        if ((currentTime - lasTime) >= STATIC_TIME)
        {
            lasTime = currentTime;
            ledStatus = !ledStatus;
            digitalWrite(ledGren, ledStatus);
        }
        if (Serial.available() > 0)
        {
            String command = Serial.readStringUntil('\n');
            if (command == "outON")
            {
                digitalWrite(ledBlue, HIGH);
            }
            else if (command == "outOFF")
            {
                digitalWrite(ledBlue, LOW);
            }
            else if (command == "read")
            {

                Serial.print("btn: ");
                Serial.print(btnState(digitalRead(PRESS_BTN_PIN)).c_str());
            }
        }
        break;
    }
    default:
    {
        break;
    }
    }
}