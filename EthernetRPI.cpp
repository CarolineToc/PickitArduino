//
//
//

#include "EthernetRPI.h"

EthernetRaspPi::EthernetRaspPi() : gateway(192, 168, 0, 1), subnet(255, 255, 0, 0), ip(192, 168, 0, 10), ipRPi(192,168,0,11)
{
}

void EthernetRaspPi::Send_data_to_rpi (String data){
	if (client.connect(ipRPi, 1880))
	{
		Serial.println("Posting data to Raspberry");
		// POST 192.168.0.11:1880/PickIT

		client.print("POST /pickit");
		client.println(" HTTP/1.1");
		client.print("Host: ");
		client.println(ipRPi);
		client.println("Connection: close");
		client.print("Content-Length: ");
		client.println(data.length());
		client.println("Content-Type: application/x-www-form-urlencoded");
		client.println();
		client.println(data);

	}
	else
	{
		Serial.println(F("Connection failed"));
	}

	// Check for a response from the server, and route it
	// out the serial port.
	while (client.connected())
	{
		if ( client.available() )
		{
			char c = client.read();
			Serial.print(c);
		}
	}
	Serial.println(" Fin de reception ");
	client.stop();
}

void EthernetRaspPi::setupEthernet(){
	Serial.println("Setting up Ethernet...");
	// start the Ethernet connection:
	Serial.println(F("Static ip addressing"));
	Ethernet.begin(mac, ip);
	Serial.print("My IP address: ");
	Serial.println(Ethernet.localIP());
	// give the Ethernet shield a second to initialize:
	delay(1000);
}



