#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include <unistd.h>
#include <string.h>
#include <time.h>

#include <wiringPi.h>
#include <lcd.h>

#include "lcd_util.c"
#include "lcd_font_3line_round.c"

#ifndef	TRUE
#  define	TRUE	(1==1)
#  define	FALSE	(1==2)
#endif

// LCD Sepc
#define LCD_ROWS 4
#define LCD_COLS 20
#define LCD_BITS 4
#define LCD_RS 6
#define LCD_STRB 5
#define LCD_D0 4
#define LCD_D1 0
#define LCD_D2 2
#define LCD_D3 3
#define LCD_D4 0
#define LCD_D5 0
#define LCD_D6 0
#define LCD_D7 0


// Global lcd handle:
static int lcdHandle ;

// Display mode
volatile int displayMode ;


void displayClock()
{
	struct tm *t ;
	time_t tim ;
	int prevDate[] = { -1, -1, -1 };
	int prevTime[] = { -1, -1, -1, -1, -1 };
	int displayColon = 0;
	char buf [32] ;

	int milliseconds = 100;
	struct timespec ts;
	ts.tv_sec = milliseconds / 1000;
	ts.tv_nsec = (milliseconds % 1000) * 1000000;

	lcdClear       (lcdHandle) ;

	for (;;)
	{
		if (displayMode != 0)
		{
			break;
		}
		tim = time (NULL) ;
		t = localtime (&tim) ;

		//Hour
		if (prevTime[0] != t->tm_hour / 10)
		{
			prevTime[0] = t->tm_hour / 10;
			lcdPutBigNumber(1, 0, prevTime[0]);
		}
		if (prevTime[1] != t->tm_hour % 10)
		{
			prevTime[1] = t->tm_hour % 10;
			lcdPutBigNumber(5, 0, prevTime[1]);
		}

		//Minute
		if (prevTime[2] != t->tm_min / 10)
		{
			prevTime[2] = t->tm_min / 10;
			lcdPutBigNumber(11, 0, prevTime[2]);
		}
		if (prevTime[3] != t->tm_min % 10)
		{
			prevTime[3] = t->tm_min % 10;
			lcdPutBigNumber(15, 0, prevTime[3]);
		}

		//Second
		if (prevTime[4] != t->tm_sec)
		{
			prevTime[4] = t->tm_sec;
			if (displayColon == 1)
			{
				displayColon = 0;
				lcdPutBigSpecialChar(9, 0, ':');
			}
			else
			{
				displayColon = 1;
				lcdPutBigSpecialChar(9, 0, ' ');
			}
		}

		//Date
		if ( prevDate[0] != t->tm_year + 1900 || prevDate[1] != t->tm_mon + 1 || prevDate[2] != t->tm_mday)
		{
			prevDate[0] = t->tm_year + 1900;
			prevDate[1] = t->tm_mon + 1;
			prevDate[2] = t->tm_mday;
			sprintf (buf, "%04d/%02d/%02d", prevDate[0], prevDate[1], prevDate[2]);

			lcdPosition (lcdHandle, 5, 3) ;
			lcdPuts     (lcdHandle, buf) ;
		}

		//Sleep
		nanosleep(&ts, NULL);
	}
}

int main (int argc, char *argv[])
{
	printf ("=====================\n") ;
	printf ("Banana Pi LCD Display\n") ;
	printf ("=====================\n") ;

	wiringPiSetup () ;

	lcdHandle = lcdInit (LCD_ROWS, LCD_COLS, LCD_BITS, LCD_RS, LCD_STRB, LCD_D0, LCD_D1, LCD_D2, LCD_D3, LCD_D4, LCD_D5, LCD_D6, LCD_D7) ;

	if (lcdHandle < 0)
	{
		fprintf (stderr, "%s: lcdInit failed\n", argv [0]) ;
		return -1 ;
	}

	init_font(lcdHandle);

	//lcd_test();

	displayMode = 0;
	for (;;)
	{
		if (displayMode == 0)
		{
			displayClock();
		}
	}

	return 0 ;
}
