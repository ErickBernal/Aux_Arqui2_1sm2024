// MQTT
const mqtt = require('mqtt')

/* PROTOCOLO MQTT - TCP Port: 1883 */
// const host = 'broker.emqx.io'
// const port = '1883'
// //const clientId = `mqtt_${Math.random().toString(16).slice(3)}`
// const clientId = 'mqttx_04be0b77_1'

// const connectUrl = `mqtt://${host}:${port}`


/* PROTOCOLO WS - WebSocket Port: 8083 */
const protocol = 'ws'
const host = 'broker.emqx.io'
const port = '8083'
const path = '/mqtt'
//const clientId = 'mqttx_04be0b77_2'
const clientId = `mqtt_${Math.random().toString(16).slice(3)}`

const connectUrl = `${protocol}://${host}:${port}${path}`


const client = mqtt.connect(connectUrl, {
    clientId,
    clean: true,
    connectTimeout: 4000,
    username: '',
    password: '',
    reconnectPeriod: 4000,
})

const TOPIC_MOTOR = 'topic/ventilador_G100'
const TOPIC_TEMPERATURA = "topic/temperatura_G100"


const suscribirse = () => {
    client.subscribe([TOPIC_MOTOR], () => {
        console.log(`Suscrito al topic '${TOPIC_MOTOR}'`)
    })
}

const publicar = (payload) => {
    client.publish(TOPIC_TEMPERATURA, payload, { qos: 0, retain: false }, (error) => {
        if (error) {
            console.error(error)
        }
    })
}

const mostrarMensaje = (topic, payload) =>{
    console.log('Mensaje Recibido:', topic, payload.toString())
}

module.exports = {
    client,
    suscribirse,
    publicar,
    mostrarMensaje
}