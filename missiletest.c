#include <stdlib.h>
#include <stdio.h>
#include <curses.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <math.h>

void armageddon(int x, int y, int m) //Produces an explosion for the cities
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

bool interception(int attacky, int attackx, int defencex, int defencey) //checks if the defending missile is close to the attacking
{
  for (int i = -6; i < 6; i++)
  {
    for (int j = -6; j < 6; j++)
    {
      if(defencey-4 < attacky && defencex+4 > attackx && defencey+4 > attacky && defencex-4 < attackx)
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
//checks if the missile has reached its target
bool inRange(int usrx, int usry, int missx, int missy)
{
  for (int i = -5; i < 5; i++)
  {
    for (int j = -5; j < 5; j++)
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
void fire() //beginnning of missile firing function
{

  int maxrow, maxcol, row, col, x, y, mx, my, c1, c2;
  mousemask(ALL_MOUSE_EVENTS | REPORT_MOUSE_POSITION, NULL); //tells program to report mouse position when clicked
  keypad(stdscr, true);
  int c;
  double grad, decx, decy, basex, basey;
  double yint;
  int citiesRemaining = 6;
  int a1, a2, b1, b2, g;
  int eq, rgrad;
  double quater;
  int disty, distx;
  int setx;
  int sety;
  int city;
  int score = 0;
  int disappear = 0;
  MEVENT event;
  int targets[5];
  targets[0] = 11;
  targets[1] = 23;
  targets[2] = 35;
  targets[3] = 47;
  targets[4] = 59;
  targets[5] = 71; //y coordiantes of the cities
  bool exp = true;
  bool explode = false;
  bool retaliate = false;
  bool isDestroyed = false;
  bool boom = false;
  getmaxyx(stdscr, maxrow, maxcol); //returns maximum x and y coordinate
  int k = 0, m = 0, q = 0, r = 0;
  while (citiesRemaining>0) //loops provided there are still cities standing
  {
    k = 0;
    m = 0;
    r = 0;
    city = rand() % 6; //randomises the city chosen

    retaliate = false;
    boom = false;
    //mvprintw(6, 0,"reset k");

    //while (k<maxrow-2)
    //{

    while (k < maxrow - 2)//loops until the missile has hit the ground
    {
      
      

      if (explode)
      {

        if (m < 3)
        {
          //printw("cities: %d", city);
          
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
      mvprintw(k - 2, targets[city], " ");// clears previous missile position
      mvprintw(k - 1, targets[city], "V"); //places missile in new position
      c = getch();
      timeout(0);

      if (c == KEY_MOUSE)
      {

        if (getmouse(&event) == OK)
        {
          if (event.bstate & BUTTON1_CLICKED) //checks if mouse has been clicked
          {
            basex = 41;
            basey = 17; //starting coordinates for defending missile
            retaliate = true;
          }
        }
      }
      if (retaliate == true)
      {
        x = event.x; //sets variables to mouse coordinates
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
        distx = 41 - decx; //calculates distance to target
        if ((int)decy <= 17) // provided the mouse position is in a suitable firing range
        {

          

          mvprintw((int)basey, (int)basex, " ");

         
          if (basey > decy)
          {
            basey = basey - (0.2 * (double)disty);
            basex = basex - (0.2 * (double)distx); // moves missile closer to targets

            round(basex);
            round(basey); //rounds number from double to int
            mvprintw((int)basey, (int)basex, "O");
            //printw("basex = %f basey = %f", basex, basey);
            retaliate = true;
            
          }
          else
          {

            if ((inRange) && r < 4)
            {
              
              //mvprintw(8, 0, "suOBNDGJAKBNGp");
              //printw("r = %d", r);
              
                mvprintw(basey - r, (basex), "*");
                mvprintw(basey + r, (basex), "*");
                mvprintw(basey - r, (basex)-r, "*"); //tl
                mvprintw(basey, (basex)-r, "*");
                mvprintw(basey + r, (basex)-r, "*"); //tr
                mvprintw(basey + r, (basex) + r, "*"); //br
                mvprintw(basey, (basex) + r, "*");
                mvprintw(basey - r, (basex) + r, "*"); //bl
                //explosion for the defending missile
                
                refresh();
                usleep(110000);
                
                mvprintw(basey-r, (basex), " ");
                mvprintw(basey+r, (basex), " ");
                mvprintw(basey-r, (basex)-r, " ");
                mvprintw(basey, (basex)-r, " ");
                mvprintw(basey+r, (basex)-r, " ");
                mvprintw(basey+r, (basex)+r, " ");
                mvprintw(basey, (basex)+r, " ");
                mvprintw(basey-r, (basex)+r, " ");
                if (r==3)
                {
                    if (interception(k-2, targets[city], basex, basey)) //Checks if def missile hits attacking
                    {
                      mvprintw(k-1, targets[city], " ");
                      boom = true;
                      score++;
                      mvprintw(7,0, "Score = %d", score); //updates score
                      break; //as missile has been destroyed it cannot hit ground, hence the break
                    }
                }

              
                r++;
                
                
            }
          }
        }

        //mvprintw((int)basey, (int)basex, " ");
      }
      
      k++;
      //r++;
      //printw("k = %d", k);
      disappear = 1;
      refresh();
      usleep(130000);
     
    }
  if (!boom)
  {
    for (int p=0; p<3; p++)
    {
      armageddon(k, targets[city], p); //explodes city if a missile has broken through
      
      
    }
    
    citiesRemaining--;
    mvprintw(8, 0, "cities: %d", citiesRemaining); //keeps track of number of cities
  
    //printw("EXITED");
    explode = true;
  }
    //printw("breaking!");
  }

  mvprintw(9, 41, "Your Score was %d", score);
  refresh();
  usleep(1700000); //end of game
}

void mapz(int level)
{
  int r, c, gap;
  gap = 15;
  getmaxyx(stdscr, r, c);

  r = r - level;
  //layout for the map
  for (int i = 1; i < c + 1; i++)
  {

    if (level == 2)
    {
      if ((i > 9 && i < 15) || (i > 21 && i < 27) || (i > 33 && i < 39) || (i > 45 && i < 51) || (i > 57 && i < 63) || (i > 69 && i < 75))
      {
        mvprintw(r - 1, i - 1, "@"); //2nd row up on map
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
        mvprintw(r - 5, i - 1, "^"); //sets missile base
      }
      else
      {
        mvprintw(r - 1, i - 1, "#"); //sets floor
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
  getmaxyx(stdscr, maxrow, col); //ncurses declaration commands
  //printw("col = %d", col);

  for (int j = 0; j < 5; j++)
  {
    mapz(j);
    refresh();
  } //creates 5 rows to set map

  

    fire();
    

  getch();  //creates a system pause for user interaction, press any key to continue
  endwin(); //frees memory under initscr and closes ncurses library
  return 0;
}
