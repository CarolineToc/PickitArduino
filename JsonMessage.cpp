// 
// 
// 

#include "JsonMessage.h"

JsonMessage::JsonMessage(){
	Serial.println(freeMemory());
	json_file = aJson.createObject();
	Serial.println(freeMemory());
	root = aJson.createArray();
	Serial.println(freeMemory());
	Serial.println("Create JsonMessage");
	
}

JsonMessage::~JsonMessage(){
		Serial.println(freeMemory());
		delete root;	  
		Serial.println(freeMemory());
		delete json_file;
		Serial.println(freeMemory());
	Serial.println("JsonMessage destructor end");
}

String toString(byte *buffer, int length){
	String result ;
	for (int index = 0; index<length; index++){
		result +=  buffer[index];
		result += ' ';
	}
	return result;
}

void JsonMessage::Add_in_json(String data) {
	
	aJsonObject* Rfid_json;
	Rfid_json=aJson.createItem(data.c_str());
	//Serial.println(data);
	aJson.addItemToArray(root, Rfid_json);
}

void JsonMessage::Build_message(void){
	aJson.addItemToObject(json_file,"RFID",root);		
}

String JsonMessage::Convert_json_to_string (){
	return aJson.print(json_file);	
}

