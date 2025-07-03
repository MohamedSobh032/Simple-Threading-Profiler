const net = require('net');

const client = net.createConnection({ port: 9090 }, () => {
  console.log('Connected to C++ backend');
});

client.on('data', (data) => {
  console.log(data.toString());
});

client.on('end', () => {
  console.log('Disconnected from C++ backend');
});