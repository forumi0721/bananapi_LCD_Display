#ifndef	TRUE
#  define	TRUE	(1==1)
#  define	FALSE	(1==2)
#endif

void scrollMessage (int lcdHandle, int line, int width, char* message)
{
  char buf [32] ;
  static int position = 0 ;
  static int timer = 0 ;

  if (millis () < timer)
    return ;

  timer = millis () + 200 ;

  strncpy (buf, &message [position], width) ;
  buf [width] = 0 ;
  lcdPosition (lcdHandle, 0, line) ;
  lcdPuts     (lcdHandle, buf) ;

  if (++position == (strlen (message) - width))
    position = 0 ;
}


static void pingPong (int lcdHandle, int cols)
{
  static int position = 0 ;
  static int dir      = 0 ;

  if (dir == 0)		// Setup
  {
    dir = 1 ;
    lcdPosition (lcdHandle, 0, 3) ;
    lcdPutchar  (lcdHandle, '*') ;
    return ;
  }

  lcdPosition (lcdHandle, position, 3) ;
  lcdPutchar (lcdHandle, ' ') ;
  position += dir ;

  if (position == cols)
  {
    dir = -1 ;
    --position ;
  }
  
  if (position < 0)
  {
    dir = 1 ;
    ++position ;
  }

  lcdPosition (lcdHandle, position, 3) ;
  lcdPutchar  (lcdHandle, '#') ;
}

static void waitForEnter (void)
{
  printf ("Press ENTER to continue: ") ;
  (void)fgetc (stdin) ;
}

