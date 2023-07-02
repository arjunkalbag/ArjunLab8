/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#include "Particle.h"
#line 1 "/Users/student/Desktop/IoT/ArjunLab8/src/ArjunLab8.ino"
#include "env.h"
#include "Wire.h"
#include "blynk.h"
#include "oled-wing-adafruit.h"
#include "SparkFun_VCNL4040_Arduino_Library.h"

void setup();
void loop();
void ResetDisplay();
void ProxResults();
void LightLevel();
#line 7 "/Users/student/Desktop/IoT/ArjunLab8/src/ArjunLab8.ino"
#define GREEN D6
#define YELLOW D5
#define BLUE D4
#define PROX V0
#define LIGHT V1

SYSTEM_THREAD(ENABLED);

OledWingAdafruit display;
VCNL4040 proximitySensor;
uint16_t proxValue;
int lightValue;
bool lvp;
bool dvb;

void setup()
{
    display.setup();
    Serial.begin(9600);
    Wire.begin();
    Blynk.begin(BLYNK_AUTH_TOKEN);

    proximitySensor.begin();
    proximitySensor.powerOnProximity();
    proximitySensor.powerOnAmbient();
    proximitySensor.enableWhiteChannel();

    pinMode(GREEN, OUTPUT);
    pinMode(YELLOW, OUTPUT);
    pinMode(BLUE, OUTPUT);

    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0, 0);
    display.println("Start!");
    display.display();
}

void loop()
{
    Blynk.run();
    display.loop();
    proxValue = proximitySensor.getProximity();
    lightValue = proximitySensor.getAmbient();
    Blynk.virtualWrite(LIGHT, lightValue);
    Blynk.virtualWrite(PROX, proxValue);
    Serial.print(proxValue);
    Serial.println();
    Serial.print(lightValue);
    Serial.println();

    if (proxValue <= 50)
    {
        digitalWrite(GREEN, LOW);
        digitalWrite(YELLOW, LOW);
        digitalWrite(BLUE, HIGH);
    }
    if (proxValue <= 400 && proxValue > 50)
    {
        digitalWrite(GREEN, LOW);
        digitalWrite(YELLOW, HIGH);
        digitalWrite(BLUE, LOW);
    }
    if (proxValue > 400)
    {
        digitalWrite(GREEN, HIGH);
        digitalWrite(YELLOW, LOW);
        digitalWrite(BLUE, LOW);
    }

    if (display.pressedA())
    {
        lvp = false;
    }
    if (display.pressedB())
    {
        lvp = true;
    }

    if (lvp)
    {
        LightLevel();
    }
    else
    {
        ProxResults();
    }

    // if (display.pressedC())
    // {
    //     dvb = !dvb;
    // }

    // if (dvb)
    // {
    //     display.unlock();
    // }
    // else
    // {
    //     display.lock();
    //     Blynk.virtualWrite(LIGHT, lightValue);
    //     Blynk.virtualWrite(PROX, proxValue);
    // }
}

void ResetDisplay()
{
    display.clearDisplay();
    display.setCursor(0, 0);
}

void ProxResults()
{
    ResetDisplay();
    display.println("Proximity");
    display.println("");
    display.println(proxValue);
    display.display();
}

void LightLevel()
{
    ResetDisplay();
    display.println("Light Level");
    display.println("");
    display.print(lightValue);
    display.display();
}
