// client.js
const net = require('net');

const client = net.createConnection({ port: 9090 }, () => {
  console.log('Connected to C++ backend');
});

client.on('data', (data) => {
  console.log('Received from C++:', data.toString());
});

client.on('end', () => {
  console.log('Disconnected from C++ backend');
});