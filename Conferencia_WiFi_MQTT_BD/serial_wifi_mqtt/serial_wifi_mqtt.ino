
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

WiFiClient espClient;
PubSubClient mqttClient(espClient);

String ssid     = "***";
String password = "***";

byte cont_intentos = 0;
byte max_intentos = 50;

char *server = "broker.emqx.io";
int port = 1883;

String resultS = "";

char bufferPublish[10]; // Define un buffer para almacenar el dato convertido

void setup() {
    // Inicia Serial
    Serial.begin(115200);
    Serial.println("\n");

    wifiInit();
    mqttClient.setServer(server, port);
    mqttClient.setCallback(callback);

    //while(!Serial){;}
}

void loop() {
    if (!mqttClient.connected()) {
        reconnect();
    }
    mqttClient.loop();

    // ** Serial conexion Arduino **
    if(Serial.available()){
      //Serial.write(Serial.read());

      int valorArduino = Serial.read();
      Serial.println("valorArduino: ");
      Serial.println(valorArduino);
      
      itoa(valorArduino, bufferPublish, 10); // Convierte el número en una cadena de caracteres

      mqttClient.publish("topic/temperatura_G100", bufferPublish);
      delay(100);
    }

    // ** Prueba **
    /*int numeroAleatorio = random(10, 20); // Genera un número aleatorio entre 10 y 19
    Serial.println(numeroAleatorio);

    itoa(numeroAleatorio, bufferPublish, 10); // Convierte el número en una cadena de caracteres

    mqttClient.publish("topic/temperatura_G100", bufferPublish);
    delay(5000);*/
}


void wifiInit(){
    // Conexión WIFI
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED and cont_intentos < max_intentos) { //Cuenta hasta 50 si no se puede conectar lo cancela
        cont_intentos++;
        delay(500);
        Serial.print(".");
    }

    Serial.println("");

    if (cont_intentos < max_intentos) {  //Si se conectó      
        Serial.println("********************************************");
        Serial.print("Conectado a la red WiFi: ");
        Serial.println(WiFi.SSID());
        Serial.print("IP: ");
        Serial.println(WiFi.localIP());
        Serial.print("macAdress: ");
        Serial.println(WiFi.macAddress());
        Serial.println("*********************************************");
    }
    else { //No se conectó
        Serial.println("------------------------------------");
        Serial.println("Error de conexion");
        Serial.println("------------------------------------");
    }
}



void callback(char* topic, byte* payload, unsigned int length) {
    Serial.print("Mensaje recibido - Topic [");
    Serial.print(topic);
    Serial.print("] ");

    char payload_string[length + 1];
    
    int resultI;

    memcpy(payload_string, payload, length);    // guardar_destino, origen, tamaño
    payload_string[length] = '\0';
    resultI = atoi(payload_string);
    
    Serial.println();
    Serial.print("resultI:");
    Serial.println(resultI);

    // *** Guardar como STRING ***
    /*resultS = "";
    
    for (int i=0;i<length;i++) {
        resultS= resultS + (char)payload[i];
    }
    Serial.println();
    Serial.println(resultS);*/
}


void reconnect() {
    while (!mqttClient.connected()) {
        Serial.print("Intentando conectarse MQTT...");

        if (mqttClient.connect("arduinoClient")) {
            Serial.println("Conectado");

            mqttClient.subscribe("topic/motor_G100");
        
        } else {
            Serial.print("Fallo, rc=");
            Serial.print(mqttClient.state());
            Serial.println(" intentar de nuevo en 5 segundos");
            // Wait 5 seconds before retrying
            delay(5000);
        }
    }
}
