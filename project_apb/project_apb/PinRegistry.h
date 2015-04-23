/*
 * PinRegistry.h
 *
 * Created: 12/11/2014 4:05:53 PM
 *  Author: alexis.matelin
 */ 


#ifndef PINREGISTRY_H_
#define PINREGISTRY_H_

class PinRegistry {
	public:
		static const unsigned int BUTTON1 = 19;
		static const unsigned int BUTTON2 = 16;
		
		static const unsigned int LOCK = 3;
		static const unsigned int LED = 4;
		
		static const unsigned int CATHODES[8];
		static const unsigned int ANODES[5];
		
	};

const unsigned int PinRegistry::CATHODES[8] = {12, 10, 5, 1, 0, 11, 6, 9};
const unsigned int PinRegistry::ANODES[5] = {15, 14, 13, 7, 8};



#endif /* PINREGISTRY_H_ */