// MessageReceivedTag.h

#ifndef _MESSAGERECEIVEDTAG_h
#define _MESSAGERECEIVEDTAG_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
	#include "DRV_Cottonwood.h"
#else
	#include "WProgram.h"
#endif

#define LENGTH_TAG 12
#define LENGTH_FRAME_INVENTORY 22
#define OFFSET_TAG 10

class MessageReceivedTag
{
	private :
		int nb_tags;
		
	public :
		byte * Data_received;
		
		MessageReceivedTag();
		void Display_buffer_inventory (byte *buffer);
		void Display_buffer_tag (byte *buffer);
		byte * Find_tag (int num);
		String buffer_to_string (byte *buffer, int length);
		int Get_nb_tags(void);
		int Analyse_buffer(byte *buffer);
		
		
	
};

#endif

