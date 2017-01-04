// 
// 
// 

#include "JsonMessage.h"

JsonMessage::JsonMessage(){
	
	json_file = aJson.createObject();
	root = aJson.createArray();
}

void JsonMessage::Add_in_json(char * data) {
	
	aJsonObject* Rfid_json;
	Rfid_json=aJson.createItem(data);
	aJson.addItemToArray(root, Rfid_json);
	
}

void JsonMessage::Build_message(void){
	aJson.addItemToObject(json_file,"RFID",root);		
}

String JsonMessage::Convert_json_to_string (){
	String json_string;
	json_string = aJson.print(json_file);
	return json_string;		
}