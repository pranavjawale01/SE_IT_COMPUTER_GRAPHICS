#include<stdio.h>
#include<GL/glut.h>

int v, input[2][20], ch;
float boundary[3], background[3], fillcolor[3], linecolor[3];

int Round(float x)
{
    return (int)(x+0.5);
}

void dda(int xa, int ya, int xb, int yb)
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
    float xinc,yinc,xd,yd;
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

void Input()
{
    printf("\n1.Boundary Fill \n2.Flood Fill \n> > > ");
    scanf("%d",&ch);
    printf("\nEnter Number of Vertices ");
    scanf("%d",&v);
    for(int i=0;i<v;i++)
    {
        printf("\nEnter X-Coordinate x[0][%d] ",i);
        scanf("%d",&input[0][i]);
        printf("\nEnter Y-Coordinate y[1][%d] ",i);
        scanf("%d",&input[1][i]);
    }
    printf("\nEnter Fill Color (RGB) ");
    for(int i=0;i<3;i++)
    {
        scanf("%f",&fillcolor[i]);
    }
    if(ch==1)
    {
        printf("\nEnter Boundary Color (RGB) ");
        for(int i=0;i<3;i++)
        {
            scanf("%f",&boundary[i]);
        }
    }
    else if(ch==2)
    {
        printf("\nEnter Background Color (RGB) ");
        for(int i=0;i<3;i++)
        {
            scanf("%f",&background[i]);
        }
    }
}

void Output()
{
    int i;
    for(i=0;i<v-1;i++)
    {
        if(ch==2)
        {
            printf("\nEnter Line Color (RGB) ");
            for(int j=0;j<3;j++)
            {
                scanf("%f",&linecolor[j]);
            }
            glColor3f(linecolor[0],linecolor[1],linecolor[2]);
        }
        dda(input[0][i],input[1][i],input[0][i+1],input[1][i+1]);
    }
    if(ch==2)
    {
        printf("\nEnter Line Color (RGB) ");
        for(int j=0;j<3;j++)
        {
            scanf("%f",&linecolor[j]);
        }
        glColor3f(linecolor[0],linecolor[1],linecolor[2]);
    }
    dda(input[0][i],input[1][i],input[0][0],input[1][0]);
}

void boundaryFill(int x, int y, float* fillcolor, float* boundary)
{
    float current[3];
    glReadPixels(x,y,1.0,1.0,GL_RGB,GL_FLOAT,current);
    if((current[0] != boundary[0] || current[1] != boundary[1] || current[2] != boundary[2]) && (current[0] != fillcolor[0] || current[1] != fillcolor[1] || current[2] != fillcolor[2]))
    {
        glColor3f(fillcolor[0],fillcolor[1],fillcolor[2]);
        glBegin(GL_POINTS);
        glVertex2d(x,y);
        glEnd();
        glFlush();

        boundaryFill(x+2,y  ,fillcolor,boundary);
        boundaryFill(x-2,y  ,fillcolor,boundary);
        boundaryFill(x  ,y+2,fillcolor,boundary);
        boundaryFill(x  ,y-2,fillcolor,boundary);
    }
}

void floodFill(int x, int y, float* fillcolor, float* background)
{
    float current[3];
    glReadPixels(x,y,1.0,1.0,GL_RGB,GL_FLOAT,current);
    if ((current[0] == background[0] && current[1] == background[1] && current[2] == background[2]) && (current[0] != fillcolor[0] || current[1] != fillcolor[1] || current[2] != fillcolor[2]))
    {
        glColor3f(fillcolor[0],fillcolor[1],fillcolor[2]);
		glBegin(GL_POINTS);
		glVertex2d(x,y);
		glEnd();
		glFlush();
		floodFill(x+2, y   , fillcolor, background);
		floodFill(x-2, y   , fillcolor, background);
		floodFill(x  , y+2 , fillcolor, background);
		floodFill(x  , y-2 , fillcolor, background);
    }
}

void draw()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glPointSize(2.0);
    glBegin(GL_POINTS);
    Output();
    glEnd();
    glFlush();
}

void mouse(int button, int state, int x, int y)
{
    y=480-y;
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        if(ch==1)
        {
            boundaryFill(x,y,fillcolor,boundary);
        }
        if(ch==2)
        {
            floodFill(x,y,fillcolor,background);
        }
    }
}

int main(int argc, char ** argv)
{
    Input();

    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640,480);
    glutInitWindowPosition(0,0);
    glutCreateWindow("Polygon Filling");
    glClearColor(0,0,0,0);
    glColor3f(1,1,1);
    gluOrtho2D(0,640,0,480);
    glutDisplayFunc(draw);
    glutMouseFunc(mouse);
    glutMainLoop();

    return 0;
}