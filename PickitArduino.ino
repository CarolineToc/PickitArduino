#include "DRV_Cottonwood.h"
#include <SoftwareSerial.h>
#include <SPI.h>
#include <Ethernet.h>
#include "Cottonwood.h"



byte Data_to_send[] = {0x18,0x03,0xFF};
byte Data_received[] ={};
	


RFID_Reader UHF_Cottonwood = RFID_Reader(2,3);


char c ;
int Nb_sent = 0;

void setup() {
  Serial.begin(9600);
  Serial.println("Serial initialized");
}

void loop() {
	
	if ((Serial.available()) & (Serial.read()=='a') ){
		Serial.println("Preparing to send data...");
		UHF_Cottonwood.Send_data(Data_to_send, sizeof(Data_to_send)/sizeof(byte));
		Serial.println("Data has been sent");
		delay (1000);
		UHF_Cottonwood.Receive_data(Data_received);
		//Display_buffer(Data_received);

	}

}


void Display_buffer (byte *buffer){

	for (int index =0;index <= sizeof(buffer)/sizeof(byte); index++) {
		Serial.print(buffer[index]);		
	}
	Serial.println();
}


