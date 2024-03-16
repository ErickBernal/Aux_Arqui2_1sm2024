/*
    pueto Arduino uno
        sudo chmod a+rw /dev/ttyUSB0
    puerto Arduino mega
        sudo chmod a+rw /dev/ttyACM0
*/

#define trigger 2
#define echo 3
#define led 12
int pinButton = 8;
int buttonVal;
int dl = 500;

void setup()
{
    Serial.begin(9600);
    pinMode(trigger, OUTPUT);
    pinMode(echo, INPUT);
    pinMode(led, OUTPUT);
    // boton
    pinMode(pinButton, INPUT_PULLUP);
}

void loop()
{
    long duracion, distancia;
    digitalWrite(trigger, LOW);
    delayMicroseconds(2);
    digitalWrite(trigger, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigger, LOW);
    duracion = pulseIn(echo, HIGH);
    distancia = duracion / 2 / 29.1;
    interrupcion_boton(digitalRead(pinButton), distancia);
}

// interrupcion virtalizada.
void interrupcion_boton(int buttonVal_, long distancia)
{
    if (buttonVal_ == 0)
    {
        Serial.print("Data: ");
        Serial.println(String(distancia) + " cm");
        delay(dl);
    }
}
