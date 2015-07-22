// Global lcd handle:
static int lcdHandle ;

/* **********************************************************************************/
/* This section defines the characters to place into the HD44780's GCRAM. It can hold 8
   user-defined caharacters
   */
static unsigned char CustomCharacter0 [8] =
{
	0b00000,
	0b00111,
	0b01111,
	0b11111,
	0b11111,
	0b11111,
	0b11111,
	0b11111,
} ;

static unsigned char CustomCharacter1 [8] =
{
	0b11100,
	0b11110,
	0b11111,
	0b11111,
	0b11111,
	0b11111,
	0b11111,
	0b11111,
} ;

static unsigned char CustomCharacter2 [8] =
{
	0b11111,
	0b11111,
	0b11111,
	0b11111,
	0b11111,
	0b00000,
	0b00000,
	0b00000,
} ;

static unsigned char CustomCharacter3 [8] =
{
	0b00000,
	0b00000,
	0b00000,
	0b11111,
	0b11111,
	0b11111,
	0b11111,
	0b11111,
} ;

static unsigned char CustomCharacter4 [8] =
{
	0b11111,
	0b11111,
	0b11111,
	0b11111,
	0b11111,
	0b11111,
	0b01111,
	0b00111,
} ;

static unsigned char CustomCharacter5 [8] =
{
	0b11111,
	0b11111,
	0b11111,
	0b11111,
	0b11111,
	0b11111,
	0b00000,
	0b00000,
} ;

static unsigned char CustomCharacter6 [8] =
{
	0b00000,
	0b11111,
	0b11111,
	0b11111,
	0b11111,
	0b11111,
	0b00000,
	0b00000,
} ;

static unsigned char CustomCharacter7 [8] =
{
	0b00000,
	0b11100,
	0b11110,
	0b11111,
	0b11111,
	0b11111,
	0b11111,
	0b11111,
} ;


/*
 * init_font:
 *********************************************************************************
 */
int init_font(int lcd)
{
	lcdHandle = lcd;

	if (lcdHandle < 0)
	{
		return -1 ;
	}

	lcdCharDef  (lcdHandle, 0, CustomCharacter0) ;
	lcdCharDef  (lcdHandle, 1, CustomCharacter1) ;
	lcdCharDef  (lcdHandle, 2, CustomCharacter2) ;
	lcdCharDef  (lcdHandle, 3, CustomCharacter3) ;
	lcdCharDef  (lcdHandle, 4, CustomCharacter4) ;
	lcdCharDef  (lcdHandle, 5, CustomCharacter5) ;
	lcdCharDef  (lcdHandle, 6, CustomCharacter6) ;
	lcdCharDef  (lcdHandle, 7, CustomCharacter7) ;

	return 0 ;
}

int lcdPutBigSpecialChar(int col, int row, char charToPrint)
{
	int font[][9] = {
		//' '
		{
			254,
			254,
			254,
		},
		//':'
		{
			3,
			254,
			2,
		},
	};

	int index = -1;

	switch(charToPrint)
	{
		case ' ':
			index = 0;
			break;
		case ':':
			index = 1;
			break;
	}

	if(index >= 0)
	{
		// the number to screen at the position specified.
		lcdPosition(lcdHandle, col, row);  // LINE 1
		lcdPutchar (lcdHandle, font[index][0]);

		lcdPosition(lcdHandle, col, row + 1);   //LINE 2
		lcdPutchar (lcdHandle, font[index][1]);

		lcdPosition(lcdHandle, col, row + 2);   //LINE 3
		lcdPutchar (lcdHandle, font[index][2]);
	}

	return 0;
}

int lcdPutBigNumber(int col, int row, int numberToPrint)
{
	int font[][9] = {
		//0
		{
			255,2,1,
			255,254,255,
			4,3,255,
		},
		//1
		{
			2,1,254,
			254,255,254,
			3,255,3,
		},
		//2
		{
			2,2,1,
			0,6,5,
			4,3,3,
		},
		//3
		{
			2,2,1,
			254,2,1,
			3,3,255,
		},
		//4
		{
			255,254,1,
			5,5,255,
			254,254,255,
		},
		//5
		{
			255,2,2,
			2,2,1,
			3,3,255,
		},
		//6
		{
			255,2,2,
			255,2,7,
			4,3,255,
		},
		//7
		{
			2,2,255,
			254,0,2,
			254,255,254,
		},
		//8
		{
			255,2,1,
			255,2,255,
			4,3,255,
		},
		//9
		{
			255,2,1,
			2,2,255,
			3,3,255,
		},
	};

	// the number to screen at the position specified.
	lcdPosition(lcdHandle, col, row);  // LINE 1
	lcdPutchar (lcdHandle, font[numberToPrint][0]);
	lcdPutchar (lcdHandle, font[numberToPrint][1]);
	lcdPutchar (lcdHandle, font[numberToPrint][2]);

	lcdPosition(lcdHandle, col, row + 1);   //LINE 2
	lcdPutchar (lcdHandle, font[numberToPrint][3]);
	lcdPutchar (lcdHandle, font[numberToPrint][4]);
	lcdPutchar (lcdHandle, font[numberToPrint][5]);

	lcdPosition(lcdHandle, col, row + 2);   //LINE 3
	lcdPutchar (lcdHandle, font[numberToPrint][6]);
	lcdPutchar (lcdHandle, font[numberToPrint][7]);
	lcdPutchar (lcdHandle, font[numberToPrint][8]);

	//int big4_1[] = {255,2,1,	//0
	//                2,1,254,	//1
	//                2,2,1,	//2
	//                2,2,1,	//3
	//                255,254,1,	//4
	//                255,2,2,	//5
	//                255,2,2,	//6
	//                2,2,255,	//7
	//                255,2,1,	//8
	//                255,2,1,	//9
	//                254,3,254,	//10 (:)
	//                254,254,254,	//11 ( )
	//               };
	//int big4_2[] = {255,254,255,	//0
	//                254,255,254,	//1
	//  			  0,6,5,	//2
	//  		 	  254,2,1,	//3
	//  		   	  5,5,255,	//4
	//  		 	  2,2,1,	//5
	//  		 	  255,2,7,	//6
	//  			  254,0,2,	//7
	//  		   	  255,2,255,	//8
	//  		   	  2,2,255,	//9
	//                254,254,254,	//10 (:)
	//                254,254,254,	//11 ( )
	//               };
	//int big4_3[] = {4,3,255,	//0
	//                3,255,3,	//1
	//  			  4,3,3,	//2
	//  			  3,3,255,	//3
	//  			  254,254,255,	//4
	//  			  3,3,255,	//5
	//  			  4,3,255,	//6
	//  			  254,255,254,	//7
	//  			  4,3,255,	//8
	//  			  3,3,255,	//9
	//                254,2,254,	//10 (:)
	//                254,254,254,	//11 ( )
	//               };

	//// the number to screen at the position specified.
	//lcdPosition(lcdHandle, position, rowShift + 0);  // LINE 1
	//lcdPutchar (lcdHandle, big4_1[(numToPrint * 3) + 0 ]);
	//lcdPutchar (lcdHandle, big4_1[(numToPrint * 3) + 1 ]);
	//lcdPutchar (lcdHandle, big4_1[(numToPrint * 3) + 2 ]);
	//
	//lcdPosition(lcdHandle, position, rowShift + 1);   //LINE 2
	//lcdPutchar (lcdHandle, big4_2[(numToPrint * 3) + 0 ]);
	//lcdPutchar (lcdHandle, big4_2[(numToPrint * 3) + 1 ]);
	//lcdPutchar (lcdHandle, big4_2[(numToPrint * 3) + 2 ]);
	//
	//lcdPosition(lcdHandle, position, rowShift + 2);   //LINE 3
	//lcdPutchar (lcdHandle, big4_3[(numToPrint * 3) + 0 ]);
	//lcdPutchar (lcdHandle, big4_3[(numToPrint * 3) + 1 ]);
	//lcdPutchar (lcdHandle, big4_3[(numToPrint * 3) + 2 ]);

	return 0;
}

void lcd_test()
{
	lcdCursor      (lcdHandle, FALSE) ;
	lcdCursorBlink (lcdHandle, FALSE) ;
	lcdClear       (lcdHandle) ;

	lcdPutBigNumber(0, 0, 0);
	lcdPutBigNumber(3, 0, 1);
	lcdPutBigNumber(6, 0, 2);
	lcdPutBigNumber(9, 0, 3);
	lcdPutBigNumber(12, 0, 4);

	waitForEnter () ;

	lcdClear       (lcdHandle) ;

	lcdPutBigNumber(0, 0, 5);
	lcdPutBigNumber(3, 0, 6);
	lcdPutBigNumber(6, 0, 7);
	lcdPutBigNumber(9, 0, 8);
	lcdPutBigNumber(12, 0, 9);

	waitForEnter () ;

	lcdClear       (lcdHandle) ;

	lcdPutBigNumber(0, 0, 0);
	lcdPutBigNumber(4, 0, 1);
	lcdPutBigNumber(8, 0, 2);
	lcdPutBigNumber(12, 0, 3);
	lcdPutBigNumber(16, 0, 4);

	waitForEnter () ;

	lcdClear       (lcdHandle) ;

	lcdPutBigNumber(0, 0, 5);
	lcdPutBigNumber(4, 0, 6);
	lcdPutBigNumber(8, 0, 7);
	lcdPutBigNumber(12, 0, 8);
	lcdPutBigNumber(16, 0, 9);

	waitForEnter () ;

	lcdClear       (lcdHandle) ;

	lcdPutBigSpecialChar(0, 0, ':');

	waitForEnter () ;
}

