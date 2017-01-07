// 
// 
// 

#include "MessageReceivedTag.h"

MessageReceivedTag::MessageReceivedTag(){}

void MessageReceivedTag::Display_buffer_inventory (byte *buffer){
	Serial.println("Start display");
	for (int index = 0;index < buffer[1]*buffer[2]; index++) {
		Serial.print(buffer[index],HEX);
		Serial.print(",");
	}
	Serial.println("End of reading");
}

void MessageReceivedTag::Display_buffer_tag (byte *buffer){
	Serial.println("Le tag est ");
	for (int index = 0;index < LENGTH_TAG ; index++) {
		Serial.print(buffer[index],HEX);
		Serial.print(",");
	}
	Serial.println("End of reading");
}

byte * MessageReceivedTag::Find_tag (int num){
	Serial.println("Find a tag");
	byte *tag ;
	tag = new byte [LENGTH_TAG];
	int index_buffer;
	int index_tag ;
	for (index_buffer = num*LENGTH_FRAME_INVENTORY+OFFSET_TAG, index_tag = 0; index_tag < LENGTH_TAG; index_tag++, index_buffer++ ){
		tag[index_tag]=Data_received[index_buffer];
	}
	Serial.println("End of finding a tag");
	return tag;
}

String MessageReceivedTag::buffer_to_string (byte *buffer, int length) {
	String result ;
	for (int index = 0; index<length; index++){
		result +=  buffer[index];
		result += ' ';
	}
	return result;
}

int MessageReceivedTag::Get_nb_tags(void){
	return nb_tags;
}

int MessageReceivedTag::Analyse_buffer(byte *buffer){
	if (buffer[1] == ID_INVENTORY_RSSI_RESPONSE){
		return 0; // Answer is not as expected
	}
	else{
		nb_tags = Data_received[2];
		return 1;
	}
}

