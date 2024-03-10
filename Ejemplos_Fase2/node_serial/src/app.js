const express = require("express");
const morgan = require("morgan");
const cors = require("cors");

// Serial Port - Arduino
const {SerialPort} = require('serialport');
const {DelimiterParser} = require('@serialport/parser-delimiter')

const app = express();
const PORT = process.env.PORT || 3000;

const portSerial = new SerialPort({
    path: 'COM3',
    baudRate: 9600
})

const parserSerial = portSerial.pipe(new DelimiterParser({delimiter: '\n'}))

parserSerial.on('open', function(){
    console.log('Opened Serial Port.');
})

// parserSerial.on('data', function (data) {
//     const datoSensor = data.toString()
//     console.log("datoSensor", datoSensor);
    
// });


// MQTT Conexion
const mqttController = require('../src/mqtt')
const clientMQTT = mqttController.client

clientMQTT.on('connect', mqttController.suscribirse)

clientMQTT.on('message', mqttController.mostrarMensaje)


// Publicar en el broker los datos obtenidos desde Arduino a traves del puerto Serial
parserSerial.on('data', function (data) {
    const datoSensor = data.toString()
    console.log("datoSensor", datoSensor);

    mqttController.publicar(datoSensor)
});

clientMQTT.on('message', (topic, payload) => {
    console.log('Mensaje Recibido:', topic, payload.toString())

    // Escribir en el puerto Serial, para recibirlo en Arduino
    portSerial.write(payload);
})



//Middlewares
app.use(morgan("dev"));
app.use(cors());

//Route Initial API
app.get("/", (req, res) => {
    res.json({ message: "ARQUI2 - Fase 2 - API ARDUINO SERIAL" });
});
  
app.listen(PORT, () => {
    console.log(`API is listening on port ${PORT}`);
});