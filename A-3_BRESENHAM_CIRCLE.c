#include<stdio.h>
#include<GL/glut.h>
#include<math.h>

int xc,yc,xd,yd,r;

int Round(float x)
{
    return (int)(x+0.5);
}

void ddaline(int xa, int ya, int xb, int yb)
{
    int dx,dy,steps;
    dx=xb-xa;
    dy=yb-ya;
    if(abs(dx)>abs(dy))
    {
        steps=abs(dx);
    }
    else
    {
        steps=abs(dy);
    }
    float xinc, yinc, xd, yd;
    xinc = dx/(float)(steps);
    yinc = dy/(float)(steps);
    xd = xa;
    yd = ya;
    glBegin(GL_POINTS);
    glVertex2d(Round(xd),Round(yd));
    for(int i=0;i<steps;i++)
    {
        xd += xinc;
        yd += yinc;
        glVertex2d(Round(xd),Round(yd));
    }
    glEnd();
    glFlush();
}

void circle(int xc, int yc, int r)
{
    int x,y,d;
    x=0;
    y=r;
    d = 3-2*r;
    do
    {
        glVertex2d(xc+x,yc+y);
        glVertex2d(xc+y,yc+x);
        glVertex2d(xc-x,yc-y);
        glVertex2d(xc-y,yc-x);
        glVertex2d(xc-x,yc+y);
        glVertex2d(xc-y,yc+x);
        glVertex2d(xc+x,yc-y);
        glVertex2d(xc+y,yc-x);
        if(d<0)
        {
            x += 1;
            d += 4*x + 6;
        }
        else
        {
            x += 1;
            y -= 1;
            d += 4*x-4*y + 10;
        }
    }while(y>=x);    
}

void draw()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1,1,1);
    glPointSize(1.0);
    glBegin(GL_POINTS);
    ddaline(320,0,320,480);
    ddaline(0,240,640,240);
    int i=0;
    while(i<640)
    {
        ddaline(i,235,i,245);
        ddaline(315,i,325,i);
        i+=20;
    }
    glEnd();
    glFlush();
}

void mouse(int button, int state, int x, int y)
{
    y = 480-y;
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        xc = x;
        yc = y;
    }
    if(button == GLUT_LEFT_BUTTON && state == GLUT_UP)
    {
        xd = x;
        yd = y;
        r = sqrt((xd-xc)*(xd-xc) + (yd-yc)*(yd-yc));
        glColor3f(1,0,1);
        glBegin(GL_POINTS);
        circle(    xc,    yc,r);
        circle(640-xc,    yc,r);
        circle(    xc,480-yc,r);
        circle(640-xc,480-yc,r);
        glEnd();
        glFlush();
    }
}

int main(int argc , char ** argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640,480);
    glutInitWindowPosition(0,0);
    glutCreateWindow("BRESENHAM CIRCLE");
    glClearColor(0,0,0,0);
    glColor3f(1,1,1);
    gluOrtho2D(0,640,0,480);
    glutDisplayFunc(draw);
    glutMouseFunc(mouse);
    glutMainLoop();

    return 0;
}