/*════════════
  LaBuhardillaDelLoco
  ════════════ */

#define trigger 2
#define echo 3
#define led 12

void setup()
{
    Serial.begin(9600);
    pinMode(trigger, OUTPUT);
    pinMode(echo, INPUT);
    pinMode(led, OUTPUT);
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
    Serial.println(String(distancia) + " cm");

    if (distancia < 5)
    {
        digitalWrite(led, HIGH);
    }
    else
    {
        digitalWrite(led, LOW);
    }
}
