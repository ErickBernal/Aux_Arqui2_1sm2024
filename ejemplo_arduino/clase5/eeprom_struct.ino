// https://cursoarduinomega.blogspot.com/2015/10/eeprom.html
//  EEPROM EJE 1
#include <EEPROM.h>

struct MyStr
{
    float field1;
    byte field2;
    char name[10];
};

void guardar()
{
    Serial.begin(9600);

    MyStr str = {
        1.15f,
        24,
        "Guardo!"};

    EEPROM.put(0, str);
}

void setup()
{
    guardar();
}
void loop() {}

// --------------------------------------------------------------------------------------------------------------
// EEPROM EJE 2
