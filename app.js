const { SerialPort } = require('serialport');
const { ReadlineParser } = require('@serialport/parser-readline');
const mqtt = require('mqtt');

const MongoClient = require('mongodb').MongoClient;

const port = new SerialPort({ path: 'COM4', baudRate: 9600 }); // Ellenőrizd a portot
const parser = port.pipe(new ReadlineParser({ delimiter: '\n' }));

const url = "mongodb://localhost:27017/";
const mqttClient = mqtt.connect('mqtt://localhost:1883');

let ledStatus = true; // Kezdeti érték

parser.on('data', data => {
  console.log(data);
});

mqttClient.on('connect', () => {
  console.log('Csatlakozva az MQTT brokerhez');
  mqttClient.subscribe('topic/control');
  mqttClient.subscribe('topic/status');
});

mqttClient.on('message', (topic, message) => {
  if (topic === 'topic/status') {
    ledStatus = message.toString() === 'Y';
    console.log('Új LED státusz:', ledStatus);

  if (ledStatus) {
      port.write('Y');
    } else {
      port.write('N');
    }
  }
});

// Kezelje az esetleges port hibákat
port.on('error', function (err) {
  console.log('Hiba: ', err.message);
});
