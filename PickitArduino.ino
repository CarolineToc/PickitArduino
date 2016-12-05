#include "EthernetRaspPI.h"
#include "Cottonwood.h"
#include <aJSON.h>
#include <SPI.h>
#include <Ethernet.h>


char c ;
int Nb_sent = 0;
aJsonObject *root, *fmt;
String json_String ;
EthernetRaspPi MyEthernet = EthernetRaspPi();

void setup() {
  
  root = aJson.createObject();

  //set up Ethernet:
  Serial.begin(9600);
  MyEthernet.setupEthernet();
  	aJson.addItemToObject(root, "name", aJson.createItem("Pepito"));
  	aJson.addStringToObject(root, "Surname", "De lu");
  	aJson.addNumberToObject(root, "RFID", 185);
  	aJson.addNumberToObject(root, "nb_sent", 12);
	  
	  	json_String=aJson.print(root);	
  	
}

void loop() {
	// Building Json file

	// converting to string

	if (Serial.available()) {
		if (Serial.read()=='a') {
			Serial.println(json_String);
			MyEthernet.Send_data_to_rpi(json_String);
			Serial.println(Nb_sent++);
		}
	}
}


