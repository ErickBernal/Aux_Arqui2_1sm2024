/*
BOTON EN LUGAR ESPECIFICO DE INTERRUPCION.
    conectar
        1 cable a pin 2
        1 cable a GND
        ambos cables a un boton

*/
// ejemplo 1 clase 3 ----------------------------------------------------------------------------------------
const byte ledPin = 13;
const byte interruptPin = 2;
volatile byte state = LOW;

void setup()
{
    pinMode(ledPin, OUTPUT);
    pinMode(interruptPin, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(interruptPin), blink, CHANGE);
}
void loop()
{
    digitalWrite(ledPin, state);
}

void blink()
{ // funcion ISR
    state = !state;
}
//*********************************************************************************************************
/*
BOTON EN CUALQUIER PIN DIGITAL
    conectar
        1 cable a pin 8
        1 cable a GND
        ambos cables a un boton

*/

// ejemplo 2 clase 4 ----------------------------------------------------------------------------------------
int pinButton = 8;
int buttonVal;
int dl = 500;

void setup()
{
    // put your setup code here, to run once:
    pinMode(pinButton, INPUT);
    digitalWrite(pinButton, HIGH);
    Serial.begin(9600);
}

void loop()
{
    // put your main code here, to run repeatedly:
    buttonVal = digitalRead(pinButton);
    Serial.println(buttonVal);
    delay(dl);
}

// ejemplo 3 clase 4 ----------------------------------------------------------------------------------------
int pinButton = 8;
int buttonVal;
int dl = 500;

void setup()
{
    // put your setup code here, to run once:
    pinMode(pinButton, INPUT_PULLUP);
    Serial.begin(9600);
}

void loop()
{
    // put your main code here, to run repeatedly:
    buttonVal = digitalRead(pinButton);
    Serial.println(buttonVal);
    delay(dl);
}

// ejemplo 4 A clase 4 ----------------------------------------------------------------------------------------
int pinButton = 8;
int buttonVal;
int dl = 500;

void setup()
{
    // put your setup code here, to run once:
    pinMode(pinButton, INPUT_PULLUP);
    Serial.begin(9600);
}

void loop()
{
    // put your main code here, to run repeatedly:
    buttonVal = digitalRead(pinButton);

    if (buttonVal == 0)
    {
        Serial.println(buttonVal);
        delay(dl);
    }
}

// ejemplo 4 B clase 4 ----------------------------------------------------------------------------------------
int pinButton = 8;
int buttonVal;
int dl = 500;

void setup()
{
    // put your setup code here, to run once:
    pinMode(pinButton, INPUT_PULLUP);
    Serial.begin(9600);
}

void loop()
{
    // put your main code here, to run repeatedly:
    buttonVal = digitalRead(pinButton);
    interrupcion_boton(buttonVal);
}

// interrupcion virtalizada.
void interrupcion_boton(int buttonVal_)
{
    if (buttonVal_ == 0)
    {
        Serial.println(buttonVal_);
        delay(dl);
    }
}
