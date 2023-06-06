#include<stdio.h>
#include<GL/glut.h>
#include<unistd.h>

int v,lv=0,rv=0,bv=0,tv=0;
int input[2][20],left[2][20],right[2][20],bottom[2][20],top[2][20];
int xmin,ymin,xmax,ymax;

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
    xd  = xa;
    yd  = ya;
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

    printf("\nEnter No. of vertices ");
    scanf("%d",&v);
    for(int i=0;i<v;i++)
    {
        printf("\nEnter X[0][%d] ",i);
        scanf("%d",&input[0][i]);
        printf("\nEnter Y[1][%d] ",i);
        scanf("%d",&input[1][i]);
    }
}

void leftClip(int xa, int ya, int xb, int yb)
{
    int x,y;
    float m = (yb-ya)/(float)(xb-xa);
    if(xa<xmin && xb>xmin)
    {
        x = xmin;
        y = ya + (x-xa)*m;
        left[0][lv]=x;
        left[1][lv]=y;
        lv++;

        left[0][lv]=xb;
        left[1][lv]=yb;
        lv++;
    }
    if(xa>xmin && xb>xmin)
    {
        left[0][lv]=xb;
        left[1][lv]=yb;
        lv++;
    }
    if(xa>xmin && xb<xmin)
    {
        x = xmin;
        y = ya + (x-xa)*m;
        left[0][lv]=x;
        left[1][lv]=y;
        lv++;
    }
}

void rightClip(int xa, int ya, int xb, int yb)
{
    int x,y;
    float m = (yb-ya)/(float)(xb-xa);
    if(xa>xmax && xb<xmax)
    {
        x = xmax;
        y = ya + (x-xa)*m;
        right[0][rv]=x;
        right[1][rv]=y;
        rv++;

        right[0][rv]=xb;
        right[1][rv]=yb;
        rv++;
    }
    if(xa<xmax && xb<xmax)
    {
        right[0][rv]=xb;
        right[1][rv]=yb;
        rv++;
    }
    if(xa<xmax && xb>xmax)
    {
        x = xmax;
        y = ya + (x-xa)*m;
        right[0][rv]=x;
        right[1][rv]=y;
        rv++;
    }
}

void bottomClip(int xa, int ya, int xb, int yb)
{
    int x,y;
    float m = (yb-ya)/(float)(xb-xa);
    if(ya<ymin && yb>ymin)
    {
        y = ymin;
        x = xa + (y-ya)/m;
        bottom[0][bv]=x;
        bottom[1][bv]=y;
        bv++;

        bottom[0][bv]=xb;
        bottom[1][bv]=yb;
        bv++;
    }
    if(ya>ymin && yb>ymin)
    {
        bottom[0][bv]=xb;
        bottom[1][bv]=yb;
        bv++;
    }
    if(ya>ymin && yb<ymin)
    {
        y = ymin;
        x = xa + (y-ya)/m;
        bottom[0][bv]=x;
        bottom[1][bv]=y;
        bv++;
    }
}

void topClip(int xa, int ya, int xb, int yb)
{
    int x,y;
    float m = (yb-ya)/(float)(xb-xa);
    if(ya>ymax && yb<ymax)
    {
        y = ymax;
        x  = xa + (y-ya)/m;
        top[0][tv]=x;
        top[1][tv]=y;
        tv++;

        top[0][tv]=xb;
        top[1][tv]=yb;
        tv++;
    }
    if(ya<ymax && yb<ymax)
    {
        top[0][tv]=xb;
        top[1][tv]=yb;
        tv++;
    }
    if(ya<ymax && yb>ymax)
    {
        y = ymax;
        x  = xa + (y-ya)/m;
        top[0][tv]=x;
        top[1][tv]=y;
        tv++;
    }
}

void polygonClipping()
{
    int l;
    for(l=0;l<v-1;l++)
    {
        leftClip(input[0][l],input[1][l],input[0][l+1],input[1][l+1]);
    }
    leftClip(input[0][l],input[1][l],input[0][0],input[1][0]);

    int r;
    for(r=0;r<lv-1;r++)
    {
        rightClip(left[0][r],left[1][r],left[0][r+1],left[1][r+1]);
    }
    rightClip(left[0][r],left[1][r],left[0][0],left[1][0]);

    int b;
    for(b=0;b<rv-1;b++)
    {
        bottomClip(right[0][b],right[1][b],right[0][b+1],right[1][b+1]);
    }
    bottomClip(right[0][b],right[1][b],right[0][0],right[1][0]);

    int t;
    for(t=0;t<bv-1;t++)
    {
        topClip(bottom[0][t],bottom[1][t],bottom[0][t+1],bottom[1][t+1]);
    }
    topClip(bottom[0][t],bottom[1][t],bottom[0][0],bottom[1][0]);
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

    glColor3f(1,0,0);
    int a;
    for(a=0;a<v-1;a++)
    {
        dda(input[0][a],input[1][a],input[0][a+1],input[1][a+1]);
    }
    dda(input[0][a],input[1][a],input[0][0],input[1][0]);

    glEnd();
    glFlush();
}

void mouse(int button, int state, int x, int y)
{
    y=480-y;
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glPointSize(1.0);
        glBegin(GL_POINTS);
        glColor3f(1,1,1);
        dda(xmin,ymin,xmax,ymin);
        dda(xmax,ymin,xmax,ymax);
        dda(xmax,ymax,xmin,ymax);
        dda(xmin,ymax,xmin,ymin);

        glColor3f(0,0,1);
        int z;
        for(z=0;z<tv-1;z++)
        {
            dda(top[0][z],top[1][z],top[0][z+1],top[1][z+1]);
        }
        dda(top[0][z],top[1][z],top[0][0],top[1][0]);
        glEnd();
        glFlush();
    }
}

int main(int argc, char ** argv)
{
    getData();
    polygonClipping();

    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640,480);
    glutInitWindowPosition(0,0);
    glutCreateWindow("POLYGON CLIPPING");
    gluOrtho2D(0,640,0,480);
    glClearColor(0,0,0,0);
    glColor3f(1,1,1);
    glutDisplayFunc(draw);
    glutMouseFunc(mouse);
    glutMainLoop();

    return 0;
}