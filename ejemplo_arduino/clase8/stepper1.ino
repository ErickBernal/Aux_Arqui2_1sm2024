#include <LiquidCrystal.h>

LiquidCrystal lcd(6, 7, 8, 9, 10, 11);

#define M1 4
#define M2 3
#define Control 5
#define Pot A0
#define Encoder 2

int vel;
volatile unsigned int ripple,
    TRipple = 0;
unsigned long tempo,
    THEWORLD = 1000;
float RPM;

void HAMON()
{
    ripple++;
}

void setup()
{
    Serial.begin(9600);
    pinMode(M1, OUTPUT);
    pinMode(M2, OUTPUT);
    pinMode(Control, OUTPUT);
    pinMode(Encoder, INPUT);
    pinMode(Pot, INPUT);

    lcd.begin(16, 2);
    lcd.print("Velocidade:");
    lcd.setCursor(13, 1);
    lcd.print("RPM");

    attachInterrupt(digitalPinToInterrupt(2), HAMON, RISING);
    tempo = 0;
}

void loop()
{
    vel = map(analogRead(Pot), 0, 1023, 0, 255);

    analogWrite(Control, vel);
    digitalWrite(M1, 1);
    digitalWrite(M2, 0);
    delay(20);

    if (millis() - tempo > THEWORLD)
    {
        detachInterrupt(0);

        lcd.setCursor(0, 1);
        lcd.print(ripple);
        Serial.println(ripple);

        TRipple = TRipple + ripple;
        ripple = 0;
        tempo = millis();
        attachInterrupt(0, HAMON, RISING);

        lcd.setCursor(0, 1);
        ripple = 0;
        delay(200);

        RPM = ripple * 6.25;
        lcd.print(RPM);
    }
}
