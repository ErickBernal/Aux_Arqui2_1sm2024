const mqtt = require("mqtt");

const { SerialPort, ReadlineParser } = require("serialport");
const port = new SerialPort({
  path: "/dev/ttyUSB0",
  baudRate: 9600,
});

const parser = port.pipe(new ReadlineParser({ delimiter: "\n" }));
// console.log("parser: ", parser, "}}}");

const pub = mqtt.connect("mqtt://localhost:9000");
pub.on("connect", () => {
  parser.on("data", (line) => {
    console.log(line);
  });
});

port.on("open", () => {
  console.log("Conexión serial abierta en /dev/ttyUSB0");
});

port.on("error", (err) => {
  console.error("Error en la conexión serial:", err);
});
