#include "JsonMessage.h"
#include "EthernetRPI.h"
//#include "EthernetRaspPI.h"
#include "Cottonwood.h"
#include <aJSON.h>
#include <SPI.h>
#include <Ethernet.h>


char c ;
int Nb_sent = 0;
//aJsonObject *root, *fmt;
String json_String ;
EthernetRaspPi MyEthernet = EthernetRaspPi();
JsonMessage MyMessage = JsonMessage();

void setup() {


  //set up Ethernet:
	 Serial.begin(9600);
	//MyEthernet.setupEthernet();

	MyMessage.Add_in_json("12 45 78 ");
	MyMessage.Add_in_json("45 56 89 ");
	MyMessage.Build_message();
	json_String=MyMessage.Convert_json_to_string();
	Serial.println(json_String);
  	
}

void loop() {
	// Building Json file

	// converting to string

	if (Serial.available()) {
		if (Serial.read()=='a') {
			Serial.println(json_String);
			//MyEthernet.Send_data_to_rpi(json_String);
			Serial.println(Nb_sent++);
		}
	}
}


