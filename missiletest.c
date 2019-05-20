#include <stdlib.h>
#include <stdio.h>
#include <curses.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <math.h>

void armageddon(int x, int y, int m)
{

  mvprintw(x, y, " ");
  mvprintw(x - m, (y - 1), "*");
  mvprintw(x + m, (y - 1), "*");
  mvprintw(x - m, (y - 1) - m, "*");
  mvprintw(x, (y - 1) - m, "*");
  mvprintw(x + m, (y - 1) - m, "*");
  mvprintw(x + m, (y - 1) + m, "*");
  mvprintw(x, (y - 1) + m, "*");
  mvprintw(x - m, (y - 1) + m, "*");
}

bool inRange(int usrx, int usry, int missx, int missy)
{
  for (int i = -6; i < 6; i++)
  {
    for (int j = -6; j < 6; j++)
    {
      if ((usrx == missx && usry == missy) || (usrx + i == missx + i || usry + j == missy + j || usrx - i == missx + i || usry - j == missy + j || usrx + i == missx - i || usry + j == missy - j))
      {
        return true;
      }
      else
      {
        return false;
      }
    }
  }
}
void fire()
{

  int maxrow, maxcol, row, col, x, y, mx, my, c1, c2;
  mousemask(ALL_MOUSE_EVENTS | REPORT_MOUSE_POSITION, NULL);
  keypad(stdscr, true);
  int c;
  double grad, decx, decy, basex, basey;
  double yint;
  int a1, a2, b1, b2, g;
  int eq, rgrad;
  double quater;
  int disty, distx;
  int setx;
  int sety;
  int city;
  ;
  MEVENT event;
  int targets[5];
  targets[0] = 11;
  targets[1] = 23;
  targets[2] = 35;
  targets[3] = 47;
  targets[4] = 59;
  targets[5] = 71;
  bool exp = true;
  bool explode = false;
  bool retaliate = false;

  getmaxyx(stdscr, maxrow, maxcol);
  int k = 0, m = 0, q = 0, r = 0;
  while (1)
  {
    k = 0;
    m = 0;
    r = 0;
    city = rand() % 6;

    retaliate = false;
    //mvprintw(6, 0,"reset k");

    //while (k<maxrow-2)
    //{

    while (k < maxrow - 2)
    {

      //usleep(170000);
      //refresh();

      if (explode)
      {

        if (m < 3)
        {
          armageddon(maxrow-k, targets[city], m);
          mvprintw(maxrow-k, targets[city], "");
          getyx(stdscr, row, col);
          //printw("row: %d col = %d", row, col);
          explode = true;
          m++;
          //usleep(170000);
          //refresh();
          //exp=false;
        }
        else
        {
          explode = false;
        }
      }
      mvprintw(k - 2, targets[city], " ");
      mvprintw(k - 1, targets[city], "V");
      c = getch();
      timeout(0);

      if (c == KEY_MOUSE)
      {

        if (getmouse(&event) == OK)
        {
          if (event.bstate & BUTTON1_CLICKED)
          {
            basex = 41;
            basey = 17;
            retaliate = true;
          }
        }
      }
      if (retaliate == true)
      {
        x = event.x;
        y = event.y;
        //mx = x -41;
        //my = y-17;

        //printw("%d, %d ", gx, gy);

        c1 = 0;
        c2 = 2;
        //printw("%d, %d", mx, my);
        decx = x;
        decy = y;
        disty = 17 - decy;
        distx = 41 - decx;
        if ((int)decy <= 17)
        {

          //printw("%d, %d, ", event.x, event.y);
          //printw("test");

          //printw("decx = %f decy = %f", decx, decy);
          //printw("%d, %f, %d, %f", basex, decx, basey, decy);
          mvprintw(0, 3, "decy = %f", decy);

          mvprintw((int)basey, (int)basex, " ");

          //printw("disty = %d distx = %d", disty, distx);
          //printw("basex = %d, basey = %d", basex, basey);
          //basex = basex + (0.2 * decx);
          //printw("basex = %f basey = %f", basex, basey);
          if (basey > decy)
          {
            basey = basey - (0.2 * (double)disty);
            basex = basex - (0.2 * (double)distx);

            round(basex);
            round(basey);
            mvprintw((int)basey, (int)basex, "O");
            //printw("basex = %f basey = %f", basex, basey);
            retaliate = true;
            //usleep(89000);
            //refresh();
            //printw("q = %d", q);
            //printw("disty = %d distx = %d", disty, distx);

            //printw("basex = %d, basey = %d", basex,  basey);
          }
          else
          {

            if ((inRange) && r < 4)
            {

              //mvprintw(8, 0, "suOBNDGJAKBNGp");
              //printw("r = %d", r);
              mvprintw(basey - r, (basex), "*");
              mvprintw(basey + r, (basex), "*");
              mvprintw(basey - r, (basex)-r, "*");
              mvprintw(basey, (basex)-r, "*");
              mvprintw(basey + r, (basex)-r, "*");
              mvprintw(basey + r, (basex) + r, "*");
              mvprintw(basey, (basex) + r, "*");
              mvprintw(basey - r, (basex) + r, "*");

              /*
                                                            mvprintw(basey-r, (basex), " ");
                                                            mvprintw(basey+r, (basex), " ");
                                                            mvprintw(basey-r, (basex)-r, " ");
                                                            mvprintw(basey, (basex)-r, " ");
                                                            mvprintw(basey+r, (basex)-r, " ");
                                                            mvprintw(basey+r, (basex)+r, " ");
                                                            mvprintw(basey, (basex)+r, " ");
                                                            mvprintw(basey-r, (basex)+r, " ");
                                                            */
              r++;
            }
          }
        }

        //mvprintw((int)basey, (int)basex, " ");
      }

      k++;
      //r++;
      //printw("k = %d", k);
      refresh();
      usleep(170000);
    }
    printw("EXITED");
    explode = true;

    //printw("breaking!");
  }
}

void mapz(int level)
{
  int r, c, gap;
  gap = 15;
  getmaxyx(stdscr, r, c);

  r = r - level;
  for (int i = 1; i < c + 1; i++)
  {

    if (level == 2)
    {
      if ((i > 9 && i < 15) || (i > 21 && i < 27) || (i > 33 && i < 39) || (i > 45 && i < 51) || (i > 57 && i < 63) || (i > 69 && i < 75))
      {
        mvprintw(r - 1, i - 1, "@");
      }
    }
    else if (level == 3)
    {
      if ((i > 10 && i < 14) || (i > 22 && i < 26) || (i > 34 && i < 38) || (i > 46 && i < 50) || (i > 58 && i < 62) || (i > 70 && i < 74))
      {
        mvprintw(r - 1, i - 1, "@");
      }
    }
    else if (level == 4)
    {
      if ((i > 11 && i < 13) || (i > 23 && i < 25) || (i > 35 && i < 37) || (i > 47 && i < 49) || (i > 59 && i < 61) || (i > 71 && i < 73))
      {
        mvprintw(r - 1, i - 1, "^");
      }
    }
    else
    {
      if (i > 41 && i < 43)
      {
        mvprintw(r - 1, i - 1, "^");
        mvprintw(r - 2, i - 1, "^");
        mvprintw(r - 3, i - 1, "^");
        mvprintw(r - 4, i - 1, "^");
        mvprintw(r - 5, i - 1, "^");
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
  resizeterm(24, 80);
  MEVENT event;
  int startx, starty, width, height;
  int ch, rnd;
  int maxrow;
  int grid[80][24];
  bool resize = true;
  int row, col;
  char thing[100];
  bool alive = true;
  srand(time(NULL));
  initscr();
  clear();
  noecho();
  cbreak();
  mousemask(ALL_MOUSE_EVENTS, NULL);
  getmaxyx(stdscr, maxrow, col);
  printw("col = %d", col);

  for (int j = 0; j < 5; j++)
  {
    mapz(j);
    refresh();
  }

  while (1)
  {

    fire();
    //usleep(12000);
  }
  //ch = wgetch(stdscr);
  //if (ch == 113)
  //{
  //break;
  //}
  /*
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
        //break;
        
      }
      */

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
  // {
    //   printw("The pressed key is ");
      // attron(A_BOLD);
       //printw("%c", ch);
       //attroff(A_BOLD);   
   //.}
  */
  //    printw("Hello World! %d\n", thing);
  //  addch('a');
  //move(12,13); //in form (y, x)!!!!!!!!
  //mvprintw(15,20, "Movement");
  //mvaddch(12, 50, '@');

  getch();  //creates a system pause for user interaction, press any key to continue
  endwin(); //frees memory under initscr and closes ncurses library
  return 0;
}
