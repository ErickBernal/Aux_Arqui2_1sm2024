/*
Este programa permite controlar la posicion de un servomotor
a traves de un potenciometro, el arduino lee por el pin analogico
A0 el voltaje que suministra el potenciometro realizando una conversion
analoga digital.

Autor: Ing. Edwin Yesidh Rios Contreras
Mail: eriosc@sena.edu.co,edwinri@hotmail.com
Twitter: @edwinrios

*/

#include <Servo.h>
Servo servo;
int dato,grados=0;
float voltaje=0;


void setup()
{
  // Se define la conexion del pin de control del servomotor
  servo.attach(9);
  // Se lleva el servomotor a 0 grados una vez se encienda el Arduino
  servo.write(0);
  Serial.begin(9600);// 9600 baudios 
}

void loop()
{
  //Lectura del pin analogico A0
  dato=analogRead(0); //en dato se guarda un numero entre 0-1023 equivalente a un voltaje entre 0 y 5v
  //En la variable grados se guarda el resulatdo de llevar la variable dato del rango entre 0 y 1023 al rango 0 y 180
  grados=map(dato,0,1023,0,180);
  //Se lleva el servomotor a la posicion indicada en la variable grados
  servo.write(grados);
  voltaje=map(dato,0,1023,0,5000);
  voltaje=voltaje/1000;
  // Muestra los datos en el Monitor serial
  Serial.print("dato: ");
  Serial.print(dato);
  Serial.print("  V: ");
  Serial.print(voltaje);
  Serial.print("  grados: ");
  Serial.println(grados);
  delay(100);
  
}