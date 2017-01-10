// 
// 
// 

#include "MessageReceivedTag.h"

MessageReceivedTag::MessageReceivedTag(){}
	
MessageReceivedTag::~MessageReceivedTag(){
delete Data_received;
Serial.println("MessageReceivedTag destructor end");
}

void MessageReceivedTag::Display_buffer_inventory (byte *buffer){
	Serial.println(F("Start display"));
	for (int index = 0;index < buffer[1]*buffer[2]; index++) {
		Serial.print(buffer[index],HEX);
		Serial.print(F(","));
	}
	Serial.println(F("End of reading"));
}

void MessageReceivedTag::Display_buffer_tag (byte *buffer){
	Serial.println(F("Le tag est "));
	for (int index = 0;index < LENGTH_TAG ; index++) {
		Serial.print(buffer[index],HEX);
		Serial.print(",");
	}
	Serial.println(F("End of reading"));
}

void MessageReceivedTag::Find_tag (int num, byte *& tag){
	Serial.println(F("Find a tag"));
	//byte *tag ;
	//tag = new byte [LENGTH_TAG];
	int index_buffer;
	int index_tag ;
	for (index_buffer = num*LENGTH_FRAME_INVENTORY+OFFSET_TAG, index_tag = 0; index_tag < LENGTH_TAG; index_tag++, index_buffer++ ){
		tag[index_tag]=Data_received[index_buffer];
	}
	Serial.println(F("End of finding a tag"));
}

String MessageReceivedTag::buffer_to_string (byte *buffer, int length) {
	String result ;
	for (int index = 0; index<length; index++){
		result +=  buffer[index];
		if (index!=(length-1)){
		result += ' ';
		}
	}
	return result;
}

int MessageReceivedTag::Get_nb_tags(void){
	return nb_tags;
}

int MessageReceivedTag::Analyse_buffer(byte *buffer){
	if (buffer[0] != ID_INVENTORY_RSSI_RESPONSE){
		return 0; // Answer is not as expected
	}
	else{
		nb_tags = Data_received[2];
		return 1;
	}
}

