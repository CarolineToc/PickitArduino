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
				Serial.println(aux[2]);
				length = aux[1]*aux[2];
				Serial.println(length);
				buffer = new byte [length]; //frame length
				buffer[0]=aux[0];
				buffer[1]=aux[1];
				buffer[2]=aux[2];
				Serial.println(length);			
			}
			else {
				Serial.println(buffer[index]=SerialRFID.read(),HEX);				
			}
			index++;
		}
	Serial.println("End of reception");
		
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
		Serial.print(buffer[index],HEX);
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
	byte Data_to_send[] = {0x41,0x08,0x08,0xA0,0x3E,0x0D,0xD8,0x01};
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
