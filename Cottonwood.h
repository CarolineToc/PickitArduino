// Cottonwood.h

#ifndef _COTTONWOOD_h
#define _COTTONWOOD_h

#define NO_ERROR 0x00
#define NO_ANSWER_FROM_TAG 0xFF

#define ID_ANTENNA_POWER 0x18
#define ID_ANTENNA_POWER_RESPONSE 0x19
#define ID_WRITE_REGISTER 0x1A
#define ID_WRITE_REGISTER_RESPONSE 0x1B
#define ID_READ_REGISTER 0x1C
#define ID_READ_REGISTER_RESPONSE 0x1D
#define ID_SET_FREQUENCY 0x41
#define ID_SET_FREQUENCY_RESPONSE 0x42
#define ID_SET_GEN2 0x59
#define ID_SET_GEN2_RESPONSE 0x5A
#define ID_INVENTORY 0x31
#define ID_INVENTORY_RESPONSE 0x32
#define ID_INVENTORY_RSSI 0x31
#define ID_INVENTORY_RSSI_RESPONSE 0x32


#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

void Receive_data (byte* buffer, int length); // fulfill the buffer with the received information from rfid reader
void Send_data (byte* buffer, int length); // send data in buffer to rfid reader

void Change_antenna_power (byte cmd); // cmd 0x00(OFF) or 0xFF(ON)
void Write_register (byte Address, byte Data);
void Read_register (byte Address, byte* Data); // store read data in Data
void Set_frequency (long int freq);
void Set_RSSI_threshold(byte value); // generally 0xD8 for -40dBm
//void Set_GEN2() p15

//TODO :  find a way to get the answer
void Start_inventory(void); 
void Get_all_tags (void);




#endif

