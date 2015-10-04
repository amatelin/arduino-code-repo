#include <Adafruit_NeoPixel.h>
 
#define PIXEL_PIN 2
#define PIXEL_COUNT 512
//#define PIXEL_TYPE NEO_KHZ800

Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIXEL_COUNT, PIXEL_PIN, NEO_GRB + NEO_KHZ800);
 
typedef struct{
    unsigned char red, green, blue;
} color;
 
typedef struct{
    int x, y, z;
} point;
 
//function definitions
color lerpColor(color* a, color* b, int val, int min, int max);
color colorMap(float val, float min, float max);
color getPixel(int x, int y, int z);
void setPixel(int x, int y, int z, color* col);
 
#define SIDE 8
#define BUTTON D2 //press this button to connect to the internet
#define MODE D3

int colorific;
bool fading=false;
int fadeValue=255;
bool onlinePressed=false;
bool lastOnline=true;
 
void setup() {
    strip.begin();
	strip.setBrightness(20);
   
}
//maxBrightness is the brightness limit for each pixel.  All color data will be scaled down
//so that the largest value is maxBrightness
int maxBrightness=50;
 
 
//returns a color from a set of colors fading from blue to green to red and back again
//the color is returned based on where the parameter *val* falls between the parameters
//*min* and *max*.  If *val* is min, the function returns a blue color.  If *val* is halfway
//between *min* and *max*, the function returns a yellow color.  
color colorMap(float val, float min, float max)
{
  float range=1024;
  val=range*(val-min)/(max-min);
  color colors[6];
  colors[0].red=0;
  colors[0].green=0;
  colors[0].blue=maxBrightness;
 
  colors[1].red=0;
  colors[1].green=maxBrightness;
  colors[1].blue=maxBrightness;
 
  colors[2].red=0;
  colors[2].green=maxBrightness;
  colors[2].blue=0;
 
  colors[3].red=maxBrightness;
  colors[3].green=maxBrightness;
  colors[3].blue=0;
 
  colors[4].red=maxBrightness;
  colors[4].green=0;
  colors[4].blue=0;
 
  colors[5].red=maxBrightness;
  colors[5].green=0;
  colors[5].blue=maxBrightness;
 
  if (val<=range/6)
    return(lerpColor(&colors[0], &colors[1], val, 0, range/6));
  else if (val<=2*range/6)
    return(lerpColor(&colors[1], &colors[2], val, range/6, 2*range/6));
  else if (val<=3*range/6)
    return(lerpColor(&colors[2], &colors[3], val, 2*range/6, 3*range/6));
  else if (val<=4*range/6)
    return(lerpColor(&colors[3], &colors[4], val, 3*range/6, 4*range/6));
  else if (val<=5*range/6)
    return(lerpColor(&colors[4], &colors[5], val, 4*range/6, 5*range/6));
  else
    return(lerpColor(&colors[5], &colors[0], val, 5*range/6, range));
}
 
 
//returns a color that's an interpolation between colors a and b.  The color
//is controlled by the position of val relative to min and max -- if val is equal to min,
//the resulting color is identical to color a.  If it's equal to max, the resulting color
//is identical to color b.  If val is (max-min)/2, the resulting color is the average of
//color a and color b
color lerpColor(color* a, color* b, int val, int min, int max)
{
    color lerped;
    lerped.red=a->red+(b->red-a->red)*(val-min)/(max-min);
    lerped.green=a->green+(b->green-a->green)*(val-min)/(max-min);
    lerped.blue=a->blue+(b->blue-a->blue)*(val-min)/(max-min);
    return lerped;
}
 
 
void loop() {
    /*if(!fading)
    {
        randomize();
        fading=true;
        fadeValue=255;
    }
    else
    {
        fadeValue--;
        fade();
        //if we're done fading)
        if(fadeValue==0)
            fading=false;
    }*/
	/*color col;
	col.red=rand()%255;
	col.green=rand()%255;
	col.blue=rand()%255;*/
    sphere(4, 4, 4, 3);   
    strip.show();
	delay(5000);
    /*if(!fading)
        delay(2000);  //wait for a few seconds to show off the pretty colors;*/
 
}
 
void randomize()
{
    color col;
    for(int x=0;x<SIDE;x++)
        for(int y=0;y<SIDE;y++)
            for(int z=0;z<SIDE;z++)
                {
                    col.red=rand()%255;
                    col.green=rand()%255;
                    col.blue=rand()%255;
                    /*
                    col.red=25;
                    col.green=50;
                    col.blue=100;
                    */
                    setPixel(x,y,z,&col);
                }    
}
 
void fade()
{
    color pixelColor;
        for(int x=0;x<SIDE;x++)
            for(int y=0;y<SIDE;y++)
                for(int z=0;z<SIDE;z++)
                    {
                        pixelColor=getPixel(x,y,z);
                        if(pixelColor.red>0)
                            pixelColor.red--;
                        if(pixelColor.green>0)
                            pixelColor.green--;
                        if(pixelColor.blue>0)
                            pixelColor.blue--;
                        setPixel(x,y,z,&pixelColor);    
                    }
}
 
//sets a pixel at position (x,y,z) to the col parameter's color
void setPixel(int x, int y, int z, color* col)
{
    int index = (z*SIDE*SIDE) + (x*SIDE) + y;
    int rando=10;
    if(col->green>rando/2)
        strip.setPixelColor(index,strip.Color(col->red,  rand()%rando - rando/2 + col->green, col->blue));
    else
        strip.setPixelColor(index,strip.Color(col->red,  col->green, col->blue));
}
 
//returns the color value currently displayed at the x,y,z location
color getPixel(int x, int y, int z)
{
    int index = (z*SIDE*SIDE) + (x*SIDE) + y;
    uint32_t col=strip.getPixelColor(index);
    color pixelColor;
    pixelColor.red=(col>>16)&255;
    pixelColor.green=(col>>8)&255;
    pixelColor.blue=col&255;
    return pixelColor;
}

void sphere(int x, int y, int z, int r)
{
	color col;
	col.red=rand()%255;
	col.green=rand()%255;
	col.blue=rand()%255;
	for(int dx = -r; dx <= r; dx++) {
		for(int dy = -r; dy <= r; dy++) {
			for(int dz = -r; dz <= r; dz++) {
				if(sqrt(dx*dx + dy*dy + dz*dz) <= r) {
					setPixel(x + dx, y + dy, z + dz, &col);
				}
			}
		}
	}
}