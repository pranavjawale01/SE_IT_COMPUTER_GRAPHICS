#include<stdio.h>
#include<GL/glut.h>
#include<unistd.h>

int xmin,ymin,xmax,ymax;
int outcode1[4],outcode2[4],and[4];
int xi,yi,xj,yj;
int xi1,yi1,xj1,yj1;

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

void getData()
{
    printf("\nEnter X-Min ");
    scanf("%d",&xmin);
    printf("\nEnter Y-Min ");
    scanf("%d",&ymin);
    printf("\nEnter X-Max ");
    scanf("%d",&xmax);
    printf("\nEnter Y-Max ");
    scanf("%d",&ymax);

    printf("\nEnter the value of xi ");
    scanf("%d",&xi);
    printf("\nEnter the value of yi ");
    scanf("%d",&yi);
    printf("\nEnter the value of xj ");
    scanf("%d",&xj);
    printf("\nEnter the value of yj ");
    scanf("%d",&yj);
}

void draw()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glPointSize(1.0);
    glBegin(GL_POINTS);
    glColor3f(1,1,1);
    dda(xmin,ymin,xmax,ymin);
    dda(xmax,ymin,xmax,ymax);
    dda(xmax,ymax,xmin,ymax);
    dda(xmin,ymax,xmin,ymin);
    sleep(1);
    glColor3f(1,0,0);
    dda(xi,yi,xj,yj);

    glEnd();
    glFlush();
}

void lineclip()
{
    for(int i=0;i<4;i++)
    {
        outcode1[i]=0;
        outcode2[i]=0;
    }
    if(yi>ymax)
    {
        outcode1[0]=1;
    }
    if(yi<ymin)
    {
        outcode1[1]=1;
    }
    if(xi>xmax)
    {
        outcode1[2]=1;
    }
    if(xi<xmin)
    {
        outcode1[3]=1;
    }
    if(yj>ymax)
    {
        outcode2[0]=1;
    }
    if(yj<ymin)
    {
        outcode2[1]=1;
    }
    if(xj>xmax)
    {
        outcode2[2]=1;
    }
    if(xj<xmin)
    {
        outcode2[3]=1;
    }
    int flag=0,flag1=0;
    for(int i=0;i<4;i++)
    {
        if(outcode1[i]==0 && outcode2[i]==0)
        {
            continue;
        }
        else
        {
            flag=1;
            break;
        }
    }
    if(flag==0)
    {
        dda(xi,yi,xj,yj);
    }
    else
    {
        for(int i=0;i<4;i++)
        {
            and[i] = outcode1[i] & outcode2[i];
        }
        for(int i=0;i<4;i++)
        {
            if(and[i]==0)
            {
                continue;
            }
            else
            {
                flag1=1;
                break;
            }
        }
        if(flag1==0)
        {
            float m = (yj-yi)/(float)(xj-xi);
            if(outcode1[0]==1)
            {
                yi1 = ymax;
                xi1 = xi + (yi1-yi)/m;
            }
            else if(outcode1[1]==1)
            {
                yi1 = ymin;
                xi1 = xi + (yi1-yi)/m;
            }
            else if(outcode1[2]==1)
            {
                xi1 = xmax;
                yi1 = yi + (xi1-xi)*m;
            }
            else if(outcode1[3]==1)
            {
                xi1 = xmin;
                yi1 = yi + (xi1-xi)*m;
            }
            else
            {
                xi1 = xi;
                yi1 = yi;
            }

            if(outcode2[0]==1)
            {
                yj1 = ymax;
                xj1 = xj + (yj1-yj)/m;
            }
            else if(outcode2[1]==1)
            {
                yj1 = ymin;
                xj1 = xj + (yj1-yj)/m;
            }
            else if(outcode2[2]==1)
            {
                xj1 = xmax;
                yj1 = yj + (xj1-xj)*m;
            }
            else if(outcode2[3]==1)
            {
                xj1 = xmin;
                yj1 = yj + (xj1-xj)*m;
            }
            else
            {
                xj1 = xj;
                yj1 = yj;
            }
            dda(xi1,yi1,xj1,yj1);
        }
    }
}

void mouse(int button, int state, int x, int y)
{
    y = 480-y;
    if(button == GLUT_LEFT_BUTTON && state ==GLUT_DOWN)
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glPointSize(1.0);
        glBegin(GL_POINTS);
        glColor3f(1,1,1);
        dda(xmin,ymin,xmax,ymin);
        dda(xmax,ymin,xmax,ymax);
        dda(xmax,ymax,xmin,ymax);
        dda(xmin,ymax,xmin,ymin);
        sleep(1);
        glColor3f(0,0,1);
        lineclip();
        glEnd();
        glFlush();
    }
}

int main(int argc, char ** argv)
{
    getData();

    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640,480);
    glutInitWindowPosition(0,0);
    glutCreateWindow("LINE CLIPPING");
    gluOrtho2D(0,640,0,480);
    glClearColor(0,0,0,0);
    glColor3f(1,1,1);
    glutDisplayFunc(draw);
    glutMouseFunc(mouse);
    glutMainLoop();

    return 0;
}