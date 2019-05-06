#include <stdlib.h>
#include <stdio.h>
#include <curses.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <math.h>
void fire(int city)
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
  MEVENT event;
  int targets[5]; 
  targets[0] = 11;
  targets[1] = 23;
  targets[2] = 35;
  targets[3] = 47;
  targets[4] = 59;
  targets[5] = 71;
  getmaxyx(stdscr, maxrow, maxcol);
  
  for (int k = 0; k<maxrow-2; k++)
   {
    getyx(stdscr, row, col);
    

    mvprintw(k-2, targets[city], " ");
    mvprintw(k-1, targets[city], "V");
    
    usleep(170000);
    refresh();
    if (k==maxrow-3)
    {
      getyx(stdscr, row, col);
      mvprintw(row, col-1, "O");
      for (int m = 0; m<3; m++)
      {

        mvprintw(row-m, (col-1), "*");
        mvprintw(row+m, (col-1), "*");
        mvprintw(row-m, (col-1)-m, "*");
        mvprintw(row, (col-1)-m, "*");
        mvprintw(row+m, (col-1)-m, "*");
        mvprintw(row+m, (col-1)+m, "*");
        mvprintw(row, (col-1)+m, "*");
        mvprintw(row-m, (col-1)+m, "*");
        
        usleep(170000);
        refresh();
      }

      
    }

    

    
   
    

    

    
    
    while (1)
    {
        
        c = getch();
        timeout(0);
        
        
        if (c == KEY_MOUSE)
        {
          
            if (getmouse(&event) == OK)
            {
              if (event.bstate & BUTTON1_CLICKED)
              {
                //printw("%d, %d, ", event.x, event.y);
                //printw("test");
                x = event.x;
                y = event.y;
                //mx = x -41;
                //my = y-17;
                basex = 41;
                basey = 17;
                //printw("%d, %d ", gx, gy);
                mvprintw(17, 41, "O");
                
                c1 = 0;
                c2 = 2;
                //printw("%d, %d", mx, my);
                decx = x;
                decy = y; 
                disty = 17 - decy;
                distx = 41 - decx;
                //printw("decx = %f decy = %f", decx, decy);
                //printw("%d, %f, %d, %f", basex, decx, basey, decy);
                for (int q = 0; q <5; q ++)
                {
                  
                  if (decy <= 17)
                  {
                    mvprintw((int)basey, (int)basex, " ");  
                    
                    
                    //printw("disty = %d distx = %d", disty, distx);
                    //printw("basex = %d, basey = %d", basex, basey);
                    //basex = basex + (0.2 * decx);
                    basey = basey - (0.2 * (double)disty);
                    basex = basex - (0.2 * (double)distx);
                    round(basex);
                    round(basey);  
                    mvprintw((int)basey, (int)basex, "O"); 
                    
                    usleep(89000); 
                    refresh();   
                    //printw("q = %d", q);
                    //printw("disty = %d distx = %d", disty, distx);
                    
                      
                    //printw("basex = %d, basey = %d", basex,  basey);
                  }
                
                  
                }
                mvprintw((int)basey, (int)basex, " ");
                
                for (int r = 0; r<5; r++)
                {

                  mvprintw(basey-r, (basex), "*");
                  mvprintw(basey+r, (basex), "*");
                  mvprintw(basey-r, (basex)-r, "*");
                  mvprintw(basey, (basex)-r, "*");
                  mvprintw(basey+r, (basex)-r, "*");
                  mvprintw(basey+r, (basex)+r, "*");
                  mvprintw(basey, (basex)+r, "*");
                  mvprintw(basey-r, (basex)+r, "*");
                  usleep(170000);
                  refresh();
                  mvprintw(basey-r, (basex), " ");
                  mvprintw(basey+r, (basex), " ");
                  mvprintw(basey-r, (basex)-r, " ");
                  mvprintw(basey, (basex)-r, " ");
                  mvprintw(basey+r, (basex)-r, " ");
                  mvprintw(basey+r, (basex)+r, " ");
                  mvprintw(basey, (basex)+r, " ");
                  mvprintw(basey-r, (basex)+r, " ");
                  
                  
                }
                
                /*
                
                
                for (int p=0; p<y; p++)
                {
                  a1 = basex-41;
                  a2 = basey-17;
                  b1 = mx;
                  b2 = -(my);
                  //printw("b1 %d, b2 = %d", b1, b2);
                  grad = (((double)b2 - (double)a2) / ((double)b1 - (double)a1));
                  //printw("grad1 = %f", grad);
                  if (grad >0.5 && grad <1)
                  {
                    grad = 1;
                  }
                  if (grad >1.5 && grad<2)
                  {
                    grad = 2;
                  }
                  if (grad >2.5 && grad<3)
                  {
                    grad = 3;
                  }
                  if (grad <-0.5 && grad >-1)
                  {
                    grad = -1;
                  }
                  if (grad <-1.5 && grad>-2)
                  {
                    grad = -2;
                  }
                  if (grad <-2.5 && grad>-3)
                  {
                    grad = -3;
                  }
                  //printw("grad2 = %f", grad);
                  yint = b2 - (grad * b1);
                  //printw("yint = %f", yint);
                  //printw("grad= %d", grad);
                  setx = (a1-(int)yint) / grad;
                  
                  //printw("setx = %d", setx);
                  sety = (grad * a2) + yint;
                  //printw("sety = %d", sety);
                  //printw("setx = %d, sety = %d", setx, sety);
                  mvprintw(sety+17, setx+41, "O");
                  basey = sety;
                  basex = setx;
                  usleep(170000);
                }
                */

                /*
                while(1)
                {
                  if (my < 17 || my > -25)
                  {
                    
                    if (mx > (c1-41) && -(my) < mx)
                    {
                      basex = basex +3;
                      basey = basey -1;
                      c1 = basex;
                      c2 = basey;
                      mvprintw(basey, basex, "O");
                      usleep(220000);
                      //printw("far right, %d, %d", basex+2, basey-1);
                      
                    }
                    else if (mx > (c1-41) && -(my) > mx)
                    {
                      //mvprintw(basey-3, basex+1, "O");
                      basex = basex +1;
                      basey = basey -3;
                      c1 = basex;
                      c2 = basey;
                      mvprintw(basey, basex, "O");
                      usleep(220000);
                      //printw("Right");
                    }
                    else if (mx < (c1-41) && mx > my)
                    {
                      //mvprintw(basey-3, basex-1, "O");
                      basex = basex -1;
                      basey = basey -3;
                      c1 = basex;
                      c2 = basey;
                      mvprintw(basey, basex, "O");
                      usleep(220000);
                      //printw("Left");
                    }
                    else if (mx < (c1-41) && mx < -(my))
                    {
                      //mvprintw(basey-1, basex-3, "O");
                      basex = basex -3;
                      basey = basey -1;
                      c1 = basex;
                      c2 = basey;
                      mvprintw(basey, basex, "O");
                      usleep(220000);
                      //printw("Far Left");
                    }
                    else
                    {
                      printw("error");
                      break;
                    }
                    
                    refresh();
                  }
                  //break;
                }

                */
                //printw("out fo while loop");
                //41, 17
                //printw("mouse has been clicked");
                  
              }     
            }
            
        }
      break;
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
          mvprintw(r-2, i-1, "^");
          mvprintw(r-3, i-1, "^");
          mvprintw(r-4, i-1, "^");
          mvprintw(r-5, i-1, "^");
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

    for (int j = 0; j < 5; j ++)
    {
      mapz(j);
      refresh();
    }
   
   while(1)
   {
    rnd = rand() % 6;
    if (alive)
    {
      fire(rnd);
      usleep(12000);
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


