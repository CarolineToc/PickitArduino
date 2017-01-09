// EthernetRaspPI.h

#ifndef _ETHERNETRASPPI_h
#define _ETHERNETRASPPI_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
	#include <aJSON.h>
	#include <SPI.h>
	#include <Ethernet.h>
#else
	#include "WProgram.h"
#endif

class EthernetRaspPi {
private :

	uint8_t mac[] ;	// MAC address
	IPAddress gateway; 	// the router's gateway address:
	IPAddress subnet; //subnet mask	
	IPAddress ip; // local ip
	IPAddress ipRPi;
	EthernetClient client;
	
	
public:
	EthernetRaspPi (); // Constructor
	void setupEthernet();	
	void Send_data_to_rpi(String data);
	String Build_json(aJsonObject *root, char * data);

};



#endif

