#include "MessageReceivedTag.h"
#include "DRV_Cottonwood.h"
#include <SoftwareSerial.h>
#include <SPI.h>
#include <Ethernet.h>
#include "Cottonwood.h"



byte Data_to_send[] = {0x18,0x03,0xFF};
	byte * Data_received;
	byte * tag ;
	//Data_received = new byte ;

//byte Data_received[] ={};


	


RFID_Reader UHF_Cottonwood = RFID_Reader(2,3);
MessageReceivedTag Msg ;


char c ;
int Nb_sent = 0;
int Nb_tag = 0;
boolean First_scan = true ;
int decalage = 0;


void setup() {
  Serial.begin(250000);
  Serial.println("Serial initialized");
}

void loop() {
	
	if (Serial.available()){
		byte aux = Serial.read();
		if (aux == 'a') {
			Serial.println("Preparing to send data...");			
			UHF_Cottonwood.Start_inventory(START_INV);
			Serial.println("Data has been sent");
			delay (1000);
			UHF_Cottonwood.Receive_data_inventory(Msg.Data_received);
			if (Msg.Analyse_buffer(Msg.Data_received)) {
				Serial.println("Data bien recue");
				Msg.Display_buffer_inventory(Msg.Data_received);
				for (int index = 0; index < Msg.Get_nb_tags(); index++) {
					tag=Msg.Find_tag(index);
					Msg.Display_buffer_tag(tag);
					Serial.println(Msg.buffer_to_string(tag,LENGTH_TAG));	
				}
			}		

		}
		else if (aux =='b') {
			Serial.println("Preparing to send data...");			
			UHF_Cottonwood.Start_inventory(START_INV);
			Serial.println("Data has been sent");
			delay (1000);
			UHF_Cottonwood.Display_incoming();		
		}

	}

}


