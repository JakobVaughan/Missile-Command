#include <stdlib.h>
#include <stdio.h>
#include <curses.h>
#include <string.h>
#include <unistd.h>

void fire(int city)
{
  int maxrow, col;
  int targets[5]; 
  targets[0] = 11;
  targets[1] = 23;
  targets[2] = 35;
  targets[3] = 47;
  targets[4] = 59;
  targets[5] = 71;
  getmaxyx(stdscr, maxrow, col);
  for (int k = 0; k<maxrow-2; k++)
   {
        
    mvprintw(k-2, targets[city], " ");
    mvprintw(k-1, targets[city], "V");
    usleep(170000);
    refresh();
    if (k==maxrow-3)
    {
      printw("BANG!");
    }
    }
    
}


void mapz(int level)
{
  int r, c, gap;
  gap = 15;
  getmaxyx(stdscr, r, c);
  
  r = r - level;
  for (int i = 1; i<c + 1; i++)
    {
      
      if (level == 2)
      {
        if ((i > 9 && i < 15) || (i>21 && i<27) || (i>33 && i<39) || (i>45 && i<51) || (i>57 && i<63) || (i>69 && i<75))
        {
          mvprintw(r-1, i-1, "@");
          
        }
      }
      else if (level == 3)
      {
        if ((i > 10 && i < 14) || (i>22 && i<26) || (i>34 && i<38) || (i>46 && i<50) || (i>58 && i<62) || (i>70 && i<74))
        {
          mvprintw(r-1, i-1, "@");
          
        }
      }
      else if (level == 4)
      {
        if ((i > 11 && i < 13) || (i>23 && i<25) || (i>35 && i<37) || (i>47 && i<49) || (i>59 && i<61) || (i>71 && i<73))
        {
          mvprintw(r-1, i-1, "^");
          
        }
      }
      else
      {
        if (i > 41 && i < 43)
        {
          mvprintw(r - 1, i - 1, "^");
        }
        else
        {
          mvprintw(r - 1, i - 1, "#");

        }

      }
      /*
      sprintf(thing, "row=%d ", row);
      mvprintw(maxrow-1, col, "%s", thing);
      sprintf(thing, " col=%d", col);
      mvprintw(maxrow-1, col, "%s", thing);
      */
    }
}


int main()
{
    MEVENT event;
    int startx, starty, width, height;
    int ch;
    int maxrow;
    int grid[80][24];
    bool resize = true;
    int row, col;
    char thing[100];

    initscr();
    clear();
    noecho();
    cbreak();
    mousemask(ALL_MOUSE_EVENTS, NULL);
    getmaxyx(stdscr, maxrow, col);
    printw("col = %d", col);

    for (int j = 0; j < 5; j ++)
    {
      mapz(j);
      refresh();
    }

    fire(2);
    usleep(12000);
    fire(3);
    usleep(12138);
    fire(1);
  

 
    
    while(1)
    {
      ch = wgetch(stdscr);
      if (ch == 113)
      {
        break;
      }
      //printw("£   %d     £", ch);
      switch(ch)
      {
        case 27:
        //printw("entered case statement");

        if(getmouse(&event) == OK)
        {
          //printw("getmouse(&event) is OK");
          if (event.bstate & BUTTON1_PRESSED)
          {
            mvprintw(maxrow-1, 0, "%s", thing);
            getyx(stdscr, col, row);
            //col = 1;
            //row = 1;
            
            sprintf(thing, "row=%d ", row);
            mvprintw(maxrow-1, 0, "%s", thing);
            sprintf(thing, " col=%d", col);
            mvprintw(maxrow-1, 5, "%s", thing);    
            refresh(); 

          }
        
        }
        break;
        
      }
      


    }
   
    

    

    

   // cbreak(); // allows you to use ctrl + z etc
     //used if creating test programs
   /* keypad(stdscr, TRUE);
    start_color(); //shows you intend to use colour
    init_pair(1, COLOR_RED, COLOR_BLUE); //middle = foreground, end = background
    attron(COLOR_PAIR(1)); //sets them in the attributes
    /*
    - A_STANDOUT - makes things standout
    - A_UNDERLINE - makes things underline
    - COLOR_RED - makes text red
    
   mvprintw(12, 40, "Type a character");//sets coordinates and prints to the screen
   attroff(COLOR_PAIR(1)); //turns attribute off
   mvprintw(row-2, 0, "This screen has %d rows and %d columns\n", row, col);
   ch = getch();
   if (ch == KEY_F(1))
   {
       printw("F1 key pressed");
   }
   else
   {
       printw("The pressed key is ");
       attron(A_BOLD);
       printw("%c", ch);
       attroff(A_BOLD);   
   }
   */
//    printw("Hello World! %d\n", thing);
  //  addch('a');
    //move(12,13); //in form (y, x)!!!!!!!!
    //mvprintw(15,20, "Movement");
    //mvaddch(12, 50, '@');
 
    getch(); //creates a system pause for user interaction, press any key to continue
    endwin(); //frees memory under initscr and closes ncurses library
    return 0;
}


