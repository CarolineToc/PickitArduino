
#include "MessageReceivedTag.h"
#include "DRV_Cottonwood.h"
#include <SoftwareSerial.h>
#include "JsonMessage.h"
#include "EthernetRPI.h"
#include "Cottonwood.h"
#include "MemoryFree.h"

#include <aJSON.h>
#include <SPI.h>
#include <Ethernet.h>



RFID_Reader UHF_Cottonwood = RFID_Reader(2,3);



char c ;
int Nb_sent = 0;
int Nb_tag = 0;
String MyStringTag;
String jsonmsg;


//String json_String ;
EthernetRaspPi MyEthernet = EthernetRaspPi();
	byte * tag = new byte [LENGTH_TAG];

// button management
int buttonPin = 5 ;

void setup() {

	pinMode(buttonPin, INPUT);
	Serial.begin(250000);
	Serial.println("Serial initialized");
	MyEthernet.setupEthernet();

}

void loop() {
	//Serial.println(digitalRead(buttonPin));
	
	if (digitalRead(buttonPin)==HIGH){
			
			Serial.println("Preparing to send data...");			
			UHF_Cottonwood.Start_inventory(START_INV);
			Serial.println("Data has been sent");
			delay (1000);
			
			MessageReceivedTag Msg; //= new MessageReceivedTag;
			
			UHF_Cottonwood.Receive_data_inventory(Msg.Data_received);
			if (Msg.Analyse_buffer(Msg.Data_received)) {
				Serial.println(F("Data bien recue"));
				Msg.Display_buffer_inventory(Msg.Data_received);
				if (Msg.Get_nb_tags() != 0){
					jsonmsg = "";	
					for (int index = 0; index < Msg.Get_nb_tags(); index++) {
						Msg.Find_tag(index, tag); //Pas d'alloc memoire
						Msg.Display_buffer_tag(tag); // tag bon jusqu'ici
						jsonmsg += Msg.buffer_to_string(tag,LENGTH_TAG);
						if (index != (Msg.Get_nb_tags()-1)) { // pas la fin du json
							jsonmsg += ",";
						}												
					}
					Serial.println(jsonmsg);
					MyEthernet.Send_data_to_rpi(jsonmsg);
				}
				else
					MyEthernet.Send_data_to_rpi("[0]");
			}

		}
}

