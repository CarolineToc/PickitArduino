#include "DRV_Cottonwood.h"
#include <SoftwareSerial.h>
#include <SPI.h>
#include <Ethernet.h>
#include "Cottonwood.h"



byte Data_to_send[] = {0x18,0x03,0xFF};
	byte * Data_received;
	//Data_received = new byte ;

//byte Data_received[] ={};


	


RFID_Reader UHF_Cottonwood = RFID_Reader(2,3);


char c ;
int Nb_sent = 0;

void setup() {
  Serial.begin(250000);
  Serial.println("Serial initialized");
}

void loop() {
	
	if ((Serial.available()) & (Serial.read()=='a') ){
		Serial.println("Preparing to send data...");
		
		UHF_Cottonwood.Start_inventory();
		Serial.println("Data has been sent");
		delay (1000);
		Data_received=UHF_Cottonwood.Receive_data();
		Display_buffer(Data_received);

	}

}


void Display_buffer (byte *buffer){
	Serial.println("Start display");
	for (int index = 0;index < buffer[1]; index++) {
		Serial.print(buffer[index],HEX);
		Serial.print(",");		
	}
	Serial.println("End of reading");
}


