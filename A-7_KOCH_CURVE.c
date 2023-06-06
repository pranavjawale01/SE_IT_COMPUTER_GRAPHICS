# include<stdio.h>
#include<GL/glut.h>
#include <math.h>

int it, px1, px2, py2, py1;

int Round(float a)
{
    return (int)(a+0.5);
}

void ddaline(int xa, int ya, int xb, int yb)
{
	int dx, dy, steps;
	
	dx = xb - xa;
	dy = yb - ya;
	
	if(abs(dx) > abs(dy))
		steps = abs(dx);
	else
		steps = abs(dy);
		
	float xinc, yinc;
	xinc = dx/(float)(steps);
	yinc = dy/(float)(steps);
	
	float x=xa;
	float y=ya;
	
	glVertex2d(Round(x), Round(y));
	
	for(int i=0; i<steps; i++)
	{
		x = x + xinc;
		y = y + yinc;
		glVertex2d(Round(x), Round(y));
	}
}


void koch(int xa, int ya, int xb, int yb, int itr)
{
    int x2 = (2*xa+xb)/3;
    int y2 = (2*ya+yb)/3;
    int x3 = (xa+2*xb)/3;
    int y3 = (ya+2*yb)/3;
    float ang = 1.0472;             //60 degrees

    int x = x2 + (x3-x2)*cos(ang) + (y3-y2)*sin(ang);
    int y = y2 - (x3-x2)*sin(ang) + (y3-y2)*cos(ang);

    if(itr>0)
    {
        koch(xa, ya, x2, y2, itr-1);
        koch(x2, y2, x, y, itr-1);
        koch(x, y, x3, y3, itr-1);
        koch(x3, y3, xb, yb, itr-1);
    }
    else
    {
        ddaline(xa, ya, x2, y2);
        ddaline(x2, y2, x, y);
        ddaline(x, y, x3, y3);
        ddaline(x3, y3, xb, yb);
    }
}

void draw()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_POINTS);
    koch(px1, py1, px2, py2, it);
	glEnd();
	glFlush();
}


int main(int argc, char **argb)
{
    printf("Enter Starting point \nX1 : ");
    scanf("%d", &px1);
    printf("Y1 : ");
    scanf("%d", &py1);
    printf("X2 : ");
    scanf("%d", &px2);
    printf("Y2 : ");
    scanf("%d", &py2);
    printf("Enter number of iterations : ");
    scanf("%d", &it);


	glutInit(&argc, argb);
	// It is used to initilize glut library	
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB); 
	// sets the initial display mode.	
	glutInitWindowSize(644,480);	
	glutInitWindowPosition(0,0);	
	glutCreateWindow("KOCH CURVE");	
	glClearColor(1.0, 1.0, 1.0, 0.0);
	// red, green, blue, and alpha 
	// set clear color to white
	glColor3f(0.0, 0.0, 0.0);
	// set feel color to black	
	gluOrtho2D(0, 640, 0, 480);
	glutDisplayFunc(draw);	
	glutMainLoop();
	//keep displaying until program is closed.	
}