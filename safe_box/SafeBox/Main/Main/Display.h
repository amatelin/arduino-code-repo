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
		
		void show(int);
		void clearDigits();

	private:
		unsigned int anodePinRegistry[8];
		unsigned int cathodePinRegistry[4];
		
		unsigned int anodePinsPatterns[10];
		unsigned int masks[7];
		
		void activateDigit(int);
		void showNumber(int);
};
	



#endif /* DISPLAY_H_ */