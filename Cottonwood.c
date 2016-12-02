// 
// 
// 

#include "Cottonwood.h"

/*
 * Receive_data
 *
 * Fulfill a buffer passed in arguments with data received 
 * from the RFID reader
 *
 * @param (type) about this param
 * @return (type)
 */
void Receive_data (byte* buffer) {
	int index = 1;
	
	while(SerialRFID.available()){
		buffer[index]=SerialRFID.read();
		Serial.print(buffer[index]);
	}
		
}

