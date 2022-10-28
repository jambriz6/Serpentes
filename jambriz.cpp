//Jorge Ambriz
//CMPS 3350-SE
//Source file

#include <iostream>
#include <GL/glx.h>
#include <cstring>
#include <stdlib.h>
#include <time.h>
#include <X11/Xlib.h>
#include <X11/keysym.h>
#include "fonts.h"
using namespace std;

struct Jlobal {
    int gamestart;
    int reset;
    int gameover;
    int timerstart;
    int seconds;
    int min;
    int tmp;
    Jlobal(){
        gamestart = time(NULL);
        timerstart = time(NULL);
    }
} j;

//This function will update values from the Global struct in snake.cpp
//to Jlobal in this source file to increase functionality
void get_class_data(int gameover, int timestat, int reset)
{
    //For timer behavior
    j.gameover = gameover;
    j.reset = reset;
    if (timestat == 0 || j.gameover == 1 || reset == 1) {
            j.timerstart = time(NULL);
            j.seconds = 0;
            j.min = 0;
    }
}

int jhello()
{
    cout << "Jorge" << endl;
    return 0;
}

int timer(int xres, int yres)
{
    if (j.seconds >= 60) {
        j.tmp = time(NULL) - j.timerstart; //grab the 59 seconds
        j.timerstart = j.timerstart + j.tmp; //Add them to the start
        j.seconds = 0; //reset the seconds
        j.min++; //Add a minute
    }
    else {
        j.seconds = time(NULL) - j.timerstart; //count upwards
    }
    Rect r;
    int w = 76;
    int h = w/2;
    int xpos = (xres/2)+300;
    int ypos = (yres/2)+160;
    glColor3ub(150, 160, 220); 
    glPushMatrix();
    glTranslatef(xpos, ypos, 0.0f);
    glBegin(GL_QUADS); 
        glVertex2f(-w, -h);
        glVertex2f(-w,  h);
        glVertex2f( w,  h);
        glVertex2f( w, -h);
        glEnd();
    glPopMatrix();
    r.left = xpos;
    r.bot = ypos-8;
    r.center = 50;
    //Display time in the corect 00:00 (min:sec) format
    if (j.min<10 && j.seconds<10) {
        ggprint16(&r, 50, 0xffffffff, "Time: 0%d:0%d",j.min,j.seconds);
    }
    else if (j.min<10 && j.seconds>=10) {
        ggprint16(&r, 50, 0xffffffff, "Time: 0%d:%d",j.min,j.seconds);
    }
    else if (j.min>=10 && j.seconds<10) {
        ggprint16(&r, 50, 0xffffffff, "Time: %d:0%d",j.min,j.seconds);
    }
    else {
        ggprint16(&r, 50, 0xffffffff, "Time: %d:%d",j.min,j.seconds);
    }
    return 0;
}

unsigned int set_credits_state(unsigned int credits) 
{
    credits = credits ^ 1;
    return credits;
}

void show_credits_screen(int xres, int yres, GLuint snakectexture)
{
    glColor3f(1.0f, 1.0f, 1.0f);
	glBindTexture(GL_TEXTURE_2D, snakectexture);
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f); glVertex2i(0,      0);
		glTexCoord2f(0.0f, 1.0f); glVertex2i(0,      yres);
		glTexCoord2f(1.0f, 1.0f); glVertex2i(xres, yres);
		glTexCoord2f(1.0f, 0.0f); glVertex2i(xres, 0);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, 0);

    //Edit names and profile pictures onto credits screen.
    /* older render code
    int xcent = xres / 2;
    int ycent = yres / 2;
    int w = 500;
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_QUADS);
    	glVertex2f(xcent-w, ycent-w);
    	glVertex2f(xcent-w, ycent+w);
    	glVertex2f(xcent+w, ycent+w);
    	glVertex2f(xcent+w, ycent-w);
    glEnd();
    */
}
