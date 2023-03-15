// A Pi-Spigot Algorithm for NABU PC
// Based on the paper "A Spigot Algorithm for the Digits of Pi"
// by Stanley Rabinowitz and Stan Wagons (Pi Stans?)
// C-code by Mike Ziniti for Pi-day 2023 (3/14/2023)
// v0.2 - Slightly modified from YouTube version, also added comments.
// Feel free to use and re-use this code as you see fit, although I'd like credit if you explicitly use the alorithm
// implementation I came up with. I haven't written anything in C in almost 30 years, so please forgive anything that
// I have done "wrong" here. My goal was just to get the program running, with almost no thought to efficiency in
// terms of size or speed. 

// This code is required to get the program in the right place for NABU to execute
static void orgit() __naked {
  __asm
  org     0x140D
    nop
    nop
    nop

    __endasm;
}

void main2();
void pi_spigot();

void main() {
  main2();
}

// The following arrays are for drawing the pictures at the beginning and the end of the program.
// In multi-colour mode, the screen is 64 columns by 48 rows. Each pixel can be one of 16 colors.
// Because 16x16 = 256, each byte of screen memory contains the color info for a pair of cells.
// The order is as follows in (column, row) or (x, y) format: {(0,0)&(1,0)} and then down to
// {(0,7)&(1,7)}. After these 8 bytes, the data moves back up to the top and over two, and proceeds
// to {(2,0)&(3,0)} through {(2,7)&(3,7)}. This is repeated for all 64 columns, at which point we would
// have 32x8 = 256 bytes. Then this repeated for the 5 other groups of 8 rows. So, that explains how
// the data in these arrays is organized. (8 pairs of pixels down)x(32 pairs across)x(Repeat 6 times)
//  = 1536, the size of the array. Each row contains 256 bytes (i.e., numbers between 0 and 255).
// However, I'm not actually storing any color info in these arrays. There are only 4 distinct values:
// 0, 1, 16, and 17. Corresponding to the four possible states for any pair of pixels:
// (off, off) = 0000 0000 = 0 + 0 = 0
// (on, off)  = 0001 0000 = 16 + 0 = 16
// (off, on)  = 0000 0001 = 0 + 1 = 1
// (on, on)   = 0001 0001 = 16 + 1 = 17
// I drew the pictures and arranged the data in the MS Excel file "pi NABU art.xlsx" which should be
// available on GitHub along with this code.

// NABU Pi-Day '23 Logo art
static int nabupic[1536] = {
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,17,0,0,0,0,0,1,17,17,0,0,0,0,1,17,17,17,0,0,0,0,17,17,17,17,0,0,0,0,17,17,17,17,0,0,0,0,17,17,17,17,0,0,0,0,17,17,17,17,0,0,0,0,17,17,17,17,0,0,0,0,17,17,17,17,0,0,0,0,17,17,17,17,0,0,0,0,17,17,17,17,0,0,0,0,17,17,17,17,0,0,0,0,17,17,17,17,0,0,0,0,17,17,17,17,0,0,0,0,17,17,17,17,0,0,0,0,17,17,17,17,0,0,0,0,17,17,17,17,0,0,0,0,17,17,17,17,0,0,0,0,0,17,17,17,0,0,0,0,0,0,0,16,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,17,0,0,0,1,17,17,17,16,0,1,17,17,17,17,0,0,0,17,17,17,17,0,0,0,0,17,17,17,17,0,0,0,0,17,17,17,17,0,0,0,0,17,17,17,17,1,1,1,1,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,16,16,16,16,17,17,17,17,0,0,0,0,17,17,17,17,0,0,0,0,17,17,17,17,0,0,0,0,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,16,16,16,16,17,17,17,17,0,0,0,0,17,17,17,17,0,0,0,0,17,17,17,17,0,0,0,0,17,17,17,17,0,0,0,0,17,17,17,16,0,0,0,0,16,16,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,16,16,16,16,16,16,16,16,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,16,16,16,16,16,16,16,16,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,17,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,16,16,16,16,16,16,16,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,17,17,17,17,17,17,1,1,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,16,16,17,17,17,17,17,17,0,0,0,16,17,17,17,17,0,0,0,0,0,17,17,17,0,0,0,0,1,17,17,17,0,0,1,1,17,17,17,17,17,17,17,17,17,17,17,17,0,16,16,16,16,16,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,17,17,17,1,0,0,0,0,17,17,17,17,0,0,0,0,17,17,16,0,0,0,0,0,16,16,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,17,1,0,0,0,0,0,0,17,17,17,0,0,0,0,0,17,17,17,17,0,0,0,0,17,17,17,17,0,0,0,0,17,17,17,17,0,0,0,0,17,17,17,0,0,0,0,0,17,17,0,0,0,0,0,0,16,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
};

// Pi art
static int pipic[1536] = {
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,17,0,0,0,0,0,0,0,17,0,0,0,0,0,17,0,17,0,0,0,0,0,17,0,17,0,0,0,0,0,17,0,17,0,0,0,0,0,17,0,17,0,0,0,0,0,17,0,17,0,0,0,0,0,17,0,17,0,0,0,0,0,17,0,17,0,0,0,0,0,17,0,17,0,0,0,0,0,17,0,17,0,0,0,0,0,17,0,17,0,0,0,0,0,17,0,17,0,0,0,0,0,17,0,17,0,0,0,0,0,17,0,17,0,0,0,0,0,17,0,17,0,0,0,0,0,17,0,17,0,0,0,0,0,17,0,17,0,0,0,0,0,17,0,17,0,0,0,0,0,17,0,17,0,0,0,0,0,17,0,17,0,0,0,0,0,17,0,17,0,0,0,0,0,16,0,17,0,0,0,0,0,0,0,17,0,0,0,0,0,0,0,16,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,17,17,0,17,0,17,17,0,17,17,0,17,0,17,17,0,17,17,0,17,0,17,17,0,17,17,0,17,0,17,17,0,17,17,0,17,0,17,17,0,17,17,0,17,0,17,17,0,17,17,0,17,0,17,17,0,17,17,0,17,0,17,17,0,17,17,0,17,0,17,17,0,17,17,0,17,0,17,17,0,17,17,0,17,0,17,17,0,17,17,0,17,0,17,17,0,17,17,0,17,0,17,17,0,17,17,0,17,0,17,17,0,17,17,0,17,0,17,17,0,17,17,0,17,0,17,17,0,17,17,0,17,0,17,17,0,17,17,0,17,0,17,17,0,17,17,0,17,0,17,17,0,17,17,0,17,0,17,17,0,17,17,0,17,0,17,17,0,17,17,0,17,0,17,17,0,17,17,0,17,0,17,17,0,17,17,0,17,0,17,17,0,17,17,0,17,0,17,17,0,17,17,0,17,0,17,17,0,17,17,0,0,0,16,16,0,17,17,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,16,16,16,16,16,16,16,17,0,0,0,0,0,0,0,17,1,0,0,0,16,17,17,17,17,17,1,0,0,0,16,17,16,16,16,16,0,0,0,17,0,0,0,0,0,0,0,17,17,17,17,17,17,16,16,17,17,16,16,0,0,0,0,17,0,0,0,1,1,0,0,17,0,0,0,16,16,0,0,17,17,1,1,0,0,0,0,17,17,17,17,17,17,1,1,17,0,0,0,0,0,0,0,17,0,0,1,0,0,1,0,17,0,0,17,0,0,17,0,17,0,0,17,0,0,17,0,17,1,0,0,0,1,0,0,17,17,17,1,17,17,17,1,17,0,0,0,0,0,0,0,17,0,0,0,0,0,0,0,17,17,17,17,17,17,17,0,17,16,16,16,16,16,16,0,17,0,0,0,0,0,0,0,17,1,1,1,1,1,1,1,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,17,17,17,17,17,17,17,17,17,17,16,16,16,16,16,16,16,17,0,1,1,0,1,1,0,17,0,16,16,0,17,17,17,17,17,1,1,17,17,17,17,17,17,0,0,0,0,0,0,17,17,17,16,16,17,17,0,17,17,17,1,1,17,17,16,17,0,0,0,0,0,0,0,17,0,17,17,17,17,0,17,17,1,0,0,0,0,1,17,17,17,17,16,16,16,17,0,17,17,0,1,1,1,0,1,17,17,1,0,0,0,16,0,17,17,17,17,17,17,1,0,17,17,0,0,0,17,0,0,17,17,16,16,0,16,0,0,17,17,1,1,1,1,17,0,17,16,16,17,17,17,17,17,17,1,1,1,17,17,17,16,17,16,0,17,16,0,0,0,17,0,17,16,0,17,0,0,17,1,0,0,17,17,0,0,17,16,16,17,17,16,16,0,17,0,17,16,16,17,0,17,17,0,16,0,0,16,0,17,17,17,1,17,17,1,17,17,17,17,17,17,17,17,17,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,17,0,17,17,0,1,1,0,17,0,17,17,0,17,17,0,17,0,17,17,0,17,17,0,17,0,17,17,0,17,17,0,17,0,17,17,0,17,17,0,17,0,17,17,0,17,17,0,17,0,17,17,0,17,17,0,17,0,17,17,0,17,17,0,17,0,17,17,0,17,17,0,17,0,17,17,0,17,17,0,17,0,17,17,0,17,17,0,17,0,17,17,0,17,17,0,17,0,17,17,0,17,17,0,17,0,17,17,0,17,17,0,17,0,17,17,0,17,17,0,17,0,17,17,0,17,17,0,17,0,17,17,0,17,17,0,17,0,17,17,0,17,17,0,17,0,17,17,0,17,17,0,17,0,17,17,0,17,17,0,17,0,17,17,0,17,17,0,17,0,17,17,0,17,17,0,17,0,17,17,0,17,17,0,17,0,17,17,0,17,17,0,17,0,17,17,0,17,17,0,17,0,17,17,0,17,17,0,17,0,17,17,0,17,17,0,17,0,17,17,0,16,16,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,17,0,1,0,0,0,0,0,17,0,17,0,0,0,0,0,17,0,17,0,1,0,0,0,17,0,17,0,17,0,0,0,17,0,17,0,17,0,0,0,17,0,17,0,17,0,0,0,17,0,17,0,17,0,0,0,17,0,17,0,17,0,0,0,17,0,17,0,17,0,0,0,17,0,17,0,17,0,0,0,17,0,17,0,17,0,0,0,17,0,17,0,17,0,0,0,17,0,17,0,17,0,0,0,17,0,17,0,17,0,0,0,17,0,17,0,17,0,0,0,17,0,17,0,17,0,0,0,17,0,17,0,17,0,0,0,17,0,17,0,17,0,0,0,17,0,17,0,17,0,0,0,17,0,17,0,17,0,0,0,17,0,17,0,17,0,0,0,17,0,17,0,17,0,0,0,17,0,17,0,17,0,0,0,17,0,17,0,16,0,0,0,17,0,17,0,0,0,0,0,17,0,16,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
};

// NABULIB as described on nabu.ca
#include "../NABULIB/NABU-LIB.h"

// This is the main code
void main2() {	
	uint16_t xVal, yVal; // xVal is an index for the art array and also as an offset for the vdp_pattern 
	uint16_t maxCycles = 10000;  // 1250 is around 1 second per picture, which isn't long enough to appreciate them

	// 10 Draw NABU logo
	// 20 GoSub PI_SPIGOT
	// 30 Draw PI
	// 40 GoTo 10
	while (true) {
		vdp_initMultiColorMode();
		yVal = 0;
		while (yVal < maxCycles) {
			xVal = rand()%1535; // A random index from 0 to 1535
			vdp_setWriteAddress(_vdp_pattern_table+xVal); // use xVal to set the address of the next write
			
			// Grab a value from the art array, and use that value to determine what value to write to memory.
			// If either pixel is 0, leave the pixel blank on screen.
			// If either pixel is 1, assign a random color (from 2 to 15). 0 and 1 represent Transparent and 
			// Black, which will just be the background color by default.
			// I'll explain with case 17, in which both pixels need to get a color. First, pick a number from
			// 0 to 13, and add 2; say, 7+2 = 9. Write that in binary as 9 = 8*1 + 4*0 + 2*0 + 1*1 = 1001.
			// <<4 means shift those bits 4 to the left to get 1001 0000. Now, repeat for the right pixel:
			// 11 + 2 = 13 = 8*1 + 4*1 + 2*0 + 1*1 = 1101. Finally, add the results to get:
			//  1001 0000 + 0000 1101 = 1001 1101. Running the command IO_VDPDATA = 1001 1101 will set the 
			// value in VDP memory at the address set above. Because this is being randomly done, and repeated
			// maxCycles times, the result is a sparkly, multi-colored (or multi-coloured, if you're Canadian)
			// mess, but I really like it.
			switch (pipic[xVal]) {
    				case 0:			
					IO_VDPDATA = 0;
      				break;
    				case 1:
     					IO_VDPDATA = (rand()%13)+2;
      				break;
				case 16:
     					IO_VDPDATA = ((rand()%13)+2)<<4 & 240;
      				break;
				case 17:
     					IO_VDPDATA = (((rand()%13)+2)<<4 & 240) + ((rand()%13)+2);
      				break;
			}
			yVal++;
		}

		// Call the Pi-Spigot Algorithm
		pi_spigot();

		// This is just a repeat of the same code from above, except it draws the other picture.
		// Should I write a function to handle this instead? Probably, but I couldn't be bothered
		// to relearn how to send a pointer to an array. See comment above about how much I worried
		// about efficiency.
		vdp_initMultiColorMode();
		yVal = 0;
		while (yVal < maxCycles) {
			xVal = rand()%1535;
			vdp_setWriteAddress(_vdp_pattern_table+xVal);
			switch (nabupic[xVal]) {
    				case 0:			
					IO_VDPDATA = 0;
      				break;
    				case 1:
     					IO_VDPDATA = (rand()%13)+2;
      				break;
				case 16:
     					IO_VDPDATA = ((rand()%13)+2)<<4 & 240;
      				break;
				case 17:
     					IO_VDPDATA = (((rand()%13)+2)<<4 & 240) + ((rand()%13)+2);
      				break;
			}
			yVal++;
		}

	}
	
}

// The Pi-Spigot Algorithm
// The paper by Rabinowitz and Wagon contains a sample program written in Pascal. I couldn't get it to work
// properly in C. I also think there is a bug that prints a leading 0 before moving on to the correct digits.
// Regardless, I instead just wrote the code below from scratch based on the section "Algorithm: pi-spigot"
// on page 5 of the paper. It seems to work just fine.
//
// A note on integer sizes: The paper comments that the Pascal implementation requires 32-bit (longint)
// integers to calculate 1000 digits of pi. Because of the way the algorithm works, some of the values
// calculated below can get relatively large. As long as the number of digits is kept at n = 500 or 
// below, none of the numbers calculated here get larger than 60,000 so 16bit integers suffice for 
// everything. With that being said, if you use a larger value of n, the answers are still correct.
// I have no idea how that could be true, as that should require 32bit integers. Maybe there is some
// automatic conversion going on that I am not aware of. Just to be safe, stick with a relatively small 
// number, preferably a multiple of 33. 
void pi_spigot() {
	// Note: TextMode is two colors only; I'm sticking with classic white text on black background
	vdp_initTextMode(VDP_WHITE, VDP_BLACK);
	
	int16_t i; // used to loop from right to left of a[]; signed int because loop iterates downward and compiler complains if i is unsigned

	// All of the integers in this section are small, so 8bits is sufficient
	uint8_t predig[100]; // keeps track of digits that shouldn't been printed yet. 100 is way too big; only way for the number of held digits to grow is if there are abunch of nines in a row
	uint8_t held_digits = 0; // keeps track of how many digits are currently in predig[]
	uint8_t print_col, print_row; // keeps track of where next digit should go as program goes off and puts text elsewhere
	uint8_t mismatch_count = 33; // for a given row, keeps track of how many incorrect digits have been calculated

	// These can all grow larger, so we need to use 16bits
	//
	// A comment on the number of digits to be calculated:
	// The screen has been set up to look nice with 33 digits per row, so it probably makes sense to pick some multiple
	// of 33 digits. Rows 0-1 and 18-23 are being used for text, so at most you can print 16 rows of 33 digits, or 561.
	// With that being said, digits are initially held and only printed conditional on what the next digit is. So, you'll
	// need to add 1 to the count to try to force that last digit to be printed. Let's try to fill the available screen space
	// by setting n = 16*33 + 1 = 529. Please note, this will be pretty slow :) 
	uint16_t n = 529;
	uint8_t pi_digits_calc[529]; // Must be of size n; only holds digits, so can be 8bit

	// The array a[] that holds the algorith results needs to be of size floor(10*n/3). Store that same value in len
	uint16_t len=1763;
	uint16_t a[1763];

	uint16_t j; // an index from 1 to n, used for each digit calculation

	// These two can be compared to see if there are digits that need to be printed. When digits are ready to be printed to screen,
	// they are pulled out of predig[] and placed into pi_digits_calc[]. The print routine then pulls digits from there. However,
	// at the end of each row, digit printing is paused so that the row can be checked against the actual digits of pi. After that, 
	// thr print routine will immediately print remaining digits, if any.
	uint16_t digits_on_screen = 0;
	uint16_t digits_in_array = 0;

	// These are all used by the algorithm. See below.
	uint16_t q;
	uint16_t carry;
	uint16_t key_val = 0;


	// Set up all the text on the screen. The documentation recommends not using columns 0,1,22, or 23 in case they are cut off
	// by the screen. No such concerns for the top or bottom rows as they aren't cut off.
	vdp_setCursor2(3, 0);
	vdp_print("A Pi-Spigot Algorithm for NABU PC!");
	vdp_newLine();
	vdp_print("----------------------------------------");
	vdp_setCursor2(0, 18);
	vdp_print("----------------------------------------");
	vdp_print("  Correct Digits for Current Row:");
	vdp_setCursor2(2,23);
	vdp_print("Digits Calculated:     (out of ");
	vdp_writeUInt16(n-1);
	vdp_print(")");

	// Set up first digit to be printed at (2,2)
	print_row=2;
	print_col=2;

	//load array a[] with twos
	for (j=0; j<len; j++){ 
		a[j] = 2;
	}
	
	// To start, array is initialized with twos above. Memory will be conserved by over-writing 
	// as we go from right to left. For each digit, we will over-write the entire array, so that
	// by the time we get to the bottom of this step, a[] will be all set for the next digit.
	//
	// Details on this algorithm can be found in the Rabinowitz&Wagon paper. However, keep in 
	// mind that the algorithm as they describe it uses an array indexed starting at 1, rather
	// than the 0 used here.
	for (j = 1; j <= n; j++) {
		// carry starts at 0 for each digit
		carry = 0;

		// for each digit, we need to go through the array from right to left
		// and do the following calculations to determine carry and remainder
		for (i=len-1; i>=0; i--) {
			key_val = 10*a[i] + carry;
			// q = quotient
			q = key_val/(2*i+1);

			// carry for the next (left) array element; note that this is integer
			// and thus results in an integer answer. 
			carry = q*i;

			// now over-write a[i] with the current remainder
			a[i] = key_val-q*(2*i+1);
		}

		
		// Get the next predigit. Reduce a[0] mod 10. The quotient of this modulus is the
		// new predigit. The remainder stays in a[0].
		q = key_val/10;
		a[0] = key_val%10;
		
		// Adjust the predigits.
		// If q is less than 9, release the held predigits (if any) and hold q:
		if (q < 9) {				
			for (i = 0; i < held_digits; i++) {
				pi_digits_calc[digits_in_array] = predig[i];
				digits_in_array++;
			}
			predig[0] = q;
			held_digits = 1;
		}
		
		// If q = 9, add q to the queue of held predigits:
		if (q == 9) {
			predig[held_digits] = 9;
			held_digits++;
		}

		// If q = 10, then do three things:
		// 1) Set the current pre-digit to 0 and hold it.
		// 2) Increase all the other held digits by 1 (9 becomes 0)
		// 3) Release all predigits except for current held one
		if (q == 10) {
			for (i = 0; i < held_digits; i++) {
				pi_digits_calc[digits_in_array] = (predig[i]+1)%10;
				digits_in_array++;
			}
			predig[0] = 0;
			held_digits = 1;
		}

		// print any digits that are in the pi_digits array but haven't been printed yet
		while (digits_on_screen < digits_in_array) {
			
			// If we're currently printing digits and print_col is 2, that means we just finished a row.
			// So, print a new row of actual pi digits in row 20, and clear out the results of checking
			// on row 21.
			if (print_col == 2) {
				mismatch_count = 33;
				vdp_setCursor2(2,20);
				switch (print_row) {
					// Lest anyone think I'm cheating, these are printed on row 20, and are then compared
					// against the digits calculated by the algorithm
					case 2: vdp_print("314159265358979323846264338327950"); break;
					case 3: vdp_print("288419716939937510582097494459230"); break;
					case 4: vdp_print("781640628620899862803482534211706"); break;
					case 5: vdp_print("798214808651328230664709384460955"); break;
					case 6: vdp_print("058223172535940812848111745028410"); break;
					case 7: vdp_print("270193852110555964462294895493038"); break;
					case 8: vdp_print("196442881097566593344612847564823"); break;
					case 9: vdp_print("378678316527120190914564856692346"); break;
					case 10: vdp_print("034861045432664821339360726024914"); break;
					case 11: vdp_print("127372458700660631558817488152092"); break;
					case 12: vdp_print("096282925409171536436789259036001"); break;
					case 13: vdp_print("133053054882046652138414695194151"); break;
					case 14: vdp_print("160943305727036575959195309218611"); break;
					case 15: vdp_print("738193261179310511854807446237996"); break;
					case 16: vdp_print("274956735188575272489122793818301"); break;
					case 17: vdp_print("194912983367336244065664308602139"); break;
					case 18: vdp_print("494639522473719070217986094370277"); break;
					case 19: vdp_print("053921717629317675238467481846766"); break;
					case 20: vdp_print("940513200056812714526356082778577"); break;
					case 21: vdp_print("134275778960917363717872146844090"); break;
					case 22: vdp_print("122495343014654958537105079227968"); break;
					case 23: vdp_print("925892354201995611212902196086403"); break;
					}
					vdp_setCursor2(2,21);
					vdp_print("                                       ");
			}					
			
			// put the cursor in the right place for printing
			vdp_setCursor2(print_col, print_row);
			// write an 8bit integer at the current cursor location
			vdp_writeUInt8(pi_digits_calc[digits_on_screen]);
			// staying in the same column, set the cursor in row 21, where the digit check is made
			vdp_setCursor2(print_col, 21);

			// vdp_getCharAtLocationVRAM(x,y) gets the contents of screen memory at (x,y). Documentation says this is
			// slow, but this is the best way I found to compare these two values. We're checking to see if the 
			// calculated digit that was just printed matches the actual pi digit that was printed above.
			// If so, print an 'o' and decrement the mismatch_count. If not, print an 'x' and don't decrement.
			// For each row, mismatch starts at 33, so if all digits are correct, mismatch_count should be 0
			// when we get to the end of the row.
			if (vdp_getCharAtLocationVRAM(print_col, 20) == vdp_getCharAtLocationVRAM(print_col, print_row)) {					
				vdp_print("o");
				mismatch_count--;					
			}
			else {
				vdp_print("x");
			}
			
			// Note that we have printed a digit to the screen
			digits_on_screen++;
			vdp_setCursor2(21,23);
			vdp_writeUInt16(digits_on_screen);

			// Set the cursor to the correct location, one to the right of where you were before.
			print_col++;
			vdp_setCursor2(print_col, print_row);

			// If we are now in column 35, 2 blank + 33 printed digits, then we have finished a row.
			// If mismatch_count is 0, print " OK". Otherwise, print " XX". Then set print_col to 2 and
			// increment print_row. That will allow the program to set the cursor at the start of the row
			// when it prints the next digit.
			if (print_col == 35) {
				if (mismatch_count == 0) {vdp_print(" OK");}
				else {vdp_print(" XX");}
				print_col = 2;
				print_row++;
			}
		}
	}
	z80_delay_ms(2500);
}

// that's the end, my friend.