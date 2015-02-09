/*
 * Display.h
 *
 * Created: 2014-12-04 9:35:41 PM
 *  Author: amate_000
 */ 


#ifndef DISPLAY_H_
#define DISPLAY_H_

class Display {
	public:
		Display(const unsigned int *,const unsigned int *);
		
		void enablePins();
		void show(int);
		void clearDigits();

	private:
		unsigned int anodePinRegistry[8];
		unsigned int cathodePinRegistry[4];
		
		static const unsigned int* ANODE_PIN_PATTERNS;
		static const unsigned int* MASKS;
		
		void activateDigit(int);
		void showNumber(int);
};
	



#endif /* DISPLAY_H_ */