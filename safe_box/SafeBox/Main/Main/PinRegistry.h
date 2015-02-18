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
		static const unsigned int BUTTON2 = 18;
		
		static const unsigned int LOCK = 15;
		
		static const unsigned int ANODES[8];
		static const unsigned int CATHODES[4];
		
	};

const unsigned int PinRegistry::ANODES[8] = {1,2,7,4,3,6,8,5};
const unsigned int PinRegistry::CATHODES[4] = {10, 11, 12, 9};



#endif /* PINREGISTRY_H_ */