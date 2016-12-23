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
byte * RFID_Reader::Receive_data (void) {
	byte * buffer;
	int index = 0;
	byte aux ;
	byte aux2;
		while(SerialRFID.available()){
			if (index == 0) {
				aux = SerialRFID.read();
			}
			else if (index == 1) {
				buffer = new byte [aux2=SerialRFID.read()]; //frame length
				buffer[0]=aux;
				buffer[1]=aux2; 
			}
			else {
				Serial.println(buffer[index]=SerialRFID.read(),HEX);				
			}
			index++;
		}
	Serial.println("End of reception");
	return buffer;
		
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
void RFID_Reader::Start_inventory(void){
	byte Data_to_send[] = {0x31,0x03,0x01};
	this->Send_data(Data_to_send,3);
	
}
