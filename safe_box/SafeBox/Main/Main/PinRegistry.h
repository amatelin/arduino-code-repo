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
		static const int BUTTON1 = 1;
		static const int BUTTON2 = 1;
		
		static const int LOCK = 1;
		
		static const int[8] ANODES = {1,2,3,4,5,6,7,8};
		static const int[4] CATHODES = {1,2,3,4};
		
	};



#endif /* PINREGISTRY_H_ */