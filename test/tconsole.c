/*************************************************************************
    > File Name: tconsole.c
    > Author: xgod
    > Mail: xgod@163.com 
    > Created Time: Thu 30 Mar 2017 07:45:45 PM CST
 ************************************************************************/

#include <stdio.h>
/*
 * rotate.c
 */ 
#include    <ncurses.h>

#define     ROW 5
#define     COL 10

void show(char *);

int main(int argc, char* argv[])
{
    char        *sign_1 = "|";
    char        *sign_2 = "/";
    char        *sign_3 = "-";
    char        *sign_4 = "\\"; 
        
    initscr();          /* turn on curses */
    clear();            /* clear screen for drawing */
    while(1) {          /* in a loop */
        show(sign_1);   /* draw sign_1 */
        show(sign_2);   /* draw sign_2 */
        show(sign_3);   /* draw sign_3 */
        show(sign_4);   /* draw sign_4 */
    }
    endwin();           /* reset the tty etc */
}


void show(char *sign)
{
/* 
 *  draw a sign and wait 1 second
 */
    move(ROW, COL);             /* move cursor for drawing */
    addstr(sign);               /* add a string */
    move(1, 0);           /* move cursor */
    refresh();                  /* refresh window */
    sleep(1);                   /* sleep */
}

