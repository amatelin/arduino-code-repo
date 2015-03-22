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
		static const unsigned int BUTTON1 = 2;
		static const unsigned int BUTTON2 = 4;
		
		static const unsigned int LOCK = 5;
		
		static const unsigned int CATHODES[8];
		static const unsigned int ANODES[5];
		
	};

const unsigned int PinRegistry::CATHODES[8] = {6, 7, 8, 9, 10, 11, 12, 13};
const unsigned int PinRegistry::ANODES[5] = {14, 15, 16, 17, 18};



#endif /* PINREGISTRY_H_ */