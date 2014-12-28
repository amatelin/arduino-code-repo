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
		void Display(int * array, int * array);
		
		void show(int);
		void clearDigits();

	private:
		unsigned int anodePinRegistry[8];
		unsigned int cathodePinRegistry[4];
		
		unsigned int anodePinsPatterns[10] = {126, 48, 109, 121, 51, 91, 95, 112, 127, 123};
		unsigned int masks[7] = {1, 2, 4, 8, 16, 32, 64};
		
		void activateDigit(int);
		void showNumber(int);
};
	



#endif /* DISPLAY_H_ */