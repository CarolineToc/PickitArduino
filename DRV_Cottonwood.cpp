// 
// 
// 

#include "DRV_Cottonwood.h"
#include "MemoryFree.h"

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
	
	SerialRFID.begin(9600);
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
void RFID_Reader::Receive_data_inventory (byte *& buffer) {
	int index = 0;
	byte aux[3];
	int length ;
	
		while(SerialRFID.available()){
			if (index == 0) {
				aux[0] = SerialRFID.read();
			}
			else if (index == 1) {
				aux[1]=SerialRFID.read();
			}
			else if (index == 2) {
				Serial.println(aux[1]);
				aux[2]=SerialRFID.read();
				length = aux[1]*aux[2];
				Serial.println(freeMemory());
				buffer = new byte [length]; //frame length
				Serial.println(freeMemory());
				buffer[0]=aux[0];
				buffer[1]=aux[1];
				buffer[2]=aux[2];			
			}
			else {
				buffer[index]=SerialRFID.read();			
			}
			index++;
		}
	Serial.println(F("End of reception"));
	
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
		SerialRFID.write(buffer[index]);
		index++;
	}
	
}
/*
 * Set_antenna_power
 *
 * Turn on or off the antenna
 * 
 *
 * @param (type) about this param
 * @return (type)
 */
void RFID_Reader::Set_antenna_power (byte cmd){
	byte Data_to_send[] = {0x18,0x03,cmd};
	this->Send_data(Data_to_send,3);
}

/*
 * Set_frequency
 *
 * Set frequency to 867.5MHz
 * 
 *
 * @param (type) about this param
 * @return (type)
 */
void RFID_Reader::Set_frequency (void){
	// 41 08 08 AC 3C 0D D8 01
	// 0x41,0x08,0x04, 0xA4, 0x35, 0x0D, 0xD8, 0x01
	// 41 08 04 54 3A 0D D8 01
	byte Data_to_send[] = {0x41,0x08,0x04, 0x54, 0x3A, 0x0D, 0xD8, 0x01};
	this->Send_data(Data_to_send,8);
}

/*
 * Start_inventory
 *
 * 
 * 
 *
 * @param (type) about this param
 * @return (type)
 */
void RFID_Reader::Start_inventory(byte cmd){
	byte Data_to_send[] = {ID_INVENTORY_RSSI,0x03,cmd};
	this->Send_data(Data_to_send,3);
	
}

/*
 * Display_incoming
 *
 * Display icoming data from the Serial  
 * with a simple while loop
 *
 * @param (type) about this param
 * @return (type)
 */
void RFID_Reader::Display_incoming(){
	while (SerialRFID.available()) {
		Serial.print(SerialRFID.read(),HEX);
		Serial.print(",");
	}
}
