// host name and port
//"localhost" => string hostname;
"raspberrypi.local" => string hostname;
6449 => int port;

// send object
OscOut xmit;
// aim the transmitter
xmit.dest( hostname, port );

xmit.start("/devices/light/1/rgb").add(50);
xmit.send();
<<< "Sent 1" >>>;
1::second => now;
xmit.start("/devices/light/1/rgb").add(150).add(120.1);
xmit.send();
<<< "Sent 2" >>>;
