// 
// 
// 

#include "DRV_Cottonwood.h"

/*
 * Constructor RFID_Reader
 * Define port of the RFID reader TX and RX
 *  
 * 
 *
 *
 * 
 */
RFID_Reader::RFID_Reader(int RX, int TX) : SerialRFID(RX,TX) 
{
}

/*
 * Receive_data
 *
 * Fulfill a buffer passed in arguments with data received 
 * from the RFID reader
 *
 * @param (type) about this param
 * @return (type)
 */
void RFID_Reader::Receive_data (byte* buffer) {
	int index = 1;
	
	while(SerialRFID.available()){
		buffer[index]=SerialRFID.read();
		Serial.print(buffer[index]);
	}
		
}

/*
 * Send_data
 *
 * Send a serie of data to the reader
 * 
 *
 * @param (type) about this param
 * @return (type)
 */
void RFID_Reader::Send_data(byte* buffer, int length){
int index = 0 ;
	while (index != length) {
		SerialRFID.println(buffer[index]);
		index++;
	}
	
}

