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
			UHF_Cottonwood.Receive_data_inventory(Data_received);			
			Display_buffer_inventory(Data_received);
			tag=Find_tag(Data_received,1);
			Display_buffer_tag(tag);
			Serial.println(buffer_to_string(tag,LENGTH_TAG));
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


void Display_buffer_inventory (byte *buffer){
	Serial.println("Start display");
	for (int index = 0;index < buffer[1]*buffer[2]; index++) {
		Serial.print(buffer[index],HEX);
		Serial.print(",");		
	}
	Serial.println("End of reading");
}

void Display_buffer_tag (byte *buffer){
	Serial.println("Le tag est ");
	for (int index = 0;index < LENGTH_TAG ; index++) {
		Serial.print(buffer[index],HEX);
		Serial.print(",");
	}
	Serial.println("End of reading");
}

byte * Find_tag (byte *buffer, int nb){
	Serial.println("Find a tag");
	byte *tag ;
	tag = new byte [LENGTH_TAG];
	int index_buffer;
	int index_tag ;
	for (index_buffer = nb*LENGTH_FRAME_INVENTORY+OFFSET_TAG, index_tag = 0; index_tag < LENGTH_TAG; index_tag++, index_buffer++ ){
		tag[index_tag]=buffer[index_buffer];
	}
	Serial.println("End of finding a tag");
	return tag;
}

String buffer_to_string (byte *buffer, int length) {
	String result ;
	for (int index = 0; index<length; index++){
		result +=  buffer[index];
		result += ' ';
	}
	return result;
}
