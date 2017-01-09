// JsonMessage.h

#ifndef _JSONMESSAGE_h
#define _JSONMESSAGE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
	#include <aJSON.h>
#else
	#include "WProgram.h"
#endif

class JsonMessage {
	private :
	aJsonObject* json_file = aJson.createObject();
	aJsonObject* root = aJson.createArray();	
	
	
	public:
	JsonMessage (); // Constructor
	void Add_in_json(char * data);
	String Convert_json_to_string ();
	void JsonMessage::Build_message(void);

};

#endif

