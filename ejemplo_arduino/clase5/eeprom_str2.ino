#include <EEPROM.h>
int pinButton_mostrar = 8; // una linea del boton a tierra y la otra punta al pin 8
int pinButton_guardar = 9; // una linea del boton a tierra y la otra punta al pin 9

int buttonVal;
int dl = 500;

struct MyStr
{
    float field1;
    byte field2;
    char name[10];
};
//************************ metodos *******************************************
void guardar()
{
    Serial.begin(9600);

    MyStr str = {
        3.14f,
        65,
        "Working!"};

    EEPROM.put(0, str);
}

//--------- imprimir
// interrupcion
void interrupcion_boton_mostrar_data(int buttonVal_)
{
    if (buttonVal_ == 0)
    {
        MyStr str;
        EEPROM.get(0, str);

        Serial.println("ahora leemos el struct");
        Serial.println(str.field1);
        Serial.println(str.field2);
        Serial.println(str.name);
        Serial.println(sizeof(str));
        Serial.println(buttonVal_);
        Serial.println("--------------------------------------------------------------");

        delay(dl);
    }
}

void interrupcion_boton_guardar_data(int buttonVal_)
{
    if (buttonVal_ == 0)
    {
        guardar();
    }
}
//************************ setup y loop********************************

void setup()
{
    pinMode(pinButton_mostrar, INPUT_PULLUP);
    pinMode(pinButton_guardar, INPUT_PULLUP);

    Serial.begin(9600);
    // guardar();
}
void loop()
{
    // mostramos informacion.
    buttonVal = digitalRead(pinButton_mostrar);
    interrupcion_boton_mostrar_data(buttonVal);

    // guardamos la data
    interrupcion_boton_guardar_data(digitalRead(pinButton_guardar));
}
