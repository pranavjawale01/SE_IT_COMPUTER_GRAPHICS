#include<stdio.h>
#include<GL/glut.h>

int xp,yp,xq,yq,ch;

int Round(int x);
void ddaline(int xa, int ya, int xb, int yb, int ch);
void mouse(int button, int state, int x, int y);
void Draw();

int main(int argc, char** argv)
{
    printf("\nWhich Type of Line You Want to Draw ");
    printf("\n1.Simple Line \n2.Dotted Line \n3.Dashed Line \n4.Solid Line \n> > > ");
    scanf("%d",&ch);
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640,480);
    glutInitWindowPosition(0,0);
    glutCreateWindow("DDA LINE");
    glClearColor(0.0,0.0,0.0,0);
    glColor3f(1.0,1.0,1.0);
    gluOrtho2D(0,640,0,480);
    glutDisplayFunc(Draw);
    glutMouseFunc(mouse);
    glutMainLoop();

    return 0;
}

void mouse(int button, int state, int x, int y)
{
    y=480-y;
    if(button==GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        xp=x;
        yp=y;
    }
    if(button==GLUT_LEFT_BUTTON && state == GLUT_UP)
    {
        xq=x;
        yq=y;
        glColor3f(0.0,1.0,1.0);
        if(ch==4)
        {
            glPointSize(3.0);
        }   
        else
        {
            glPointSize(1.0);
        }
        glBegin(GL_POINTS);
        ddaline(xp,yp,xq,yq,ch);
        glEnd();
        glFlush();
        
    }
}

void Draw()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POINTS);
    ddaline(320,0,320,640,1);
    ddaline(0,240,640,240,1);
    int i=0;
    while(i<640)
    {
        ddaline(i,235,i,245,1);
        ddaline(315,i,325,i,1);
        i+=20;
    }
    glEnd();
    glFlush();
}

int Round(int x)
{
    return (int)(x+0.5);
}

void ddaline(int xa, int ya, int xb, int yb, int ch)
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
    float xinc,yinc;
    xinc = dx/(float) (steps);
    yinc = dy/(float) (steps);
    float xi,yi;
    xi = xa, yi= ya;
    glBegin(GL_POINTS);
    glVertex2d(Round(xi),Round(yi));
    if(ch==1 || ch==4)
    {
        for(int i=0;i<steps;i++)
        {
            xi += xinc;
            yi += yinc;
            glVertex2d(Round(xi),Round(yi));
        }
    }
    else if(ch==2)
    {
        for(int i=0;i<steps;i++)
        {
            xi += xinc;
            yi += yinc;
            if(i%2==0)
            {
                glVertex2d(Round(xi),Round(yi));
            }
        }
    }
    else if(ch==3)
    {
        for(int i=0;i<2*steps;i++)
        {
            xi += xinc;
            yi += yinc;
            if(i%8==0)
            {
                i+=4;
            }
            else
            {
                glVertex2d(Round(xi),Round(yi));
            }
        }
    }
    glEnd();
    glFlush();    
}