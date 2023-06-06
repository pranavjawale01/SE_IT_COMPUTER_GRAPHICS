#include<stdio.h>
#include<GL/glut.h>

int xc,yc,flag=0,dxc,dyc=300,r1=0,r2=0,r3=0;

void bresenhamCircle(int r,int xc,int yc)
{
	int x=0;
	int y=r;
	int d=3-2*r;
	glBegin(GL_POINTS);
	do
	{
		glVertex2d(xc+x,yc+y);
		glVertex2d(xc+y,yc+x);
		glVertex2d(xc-x,yc+y);
		glVertex2d(xc-y,yc+x);
		glVertex2d(xc-x,yc-y);
		glVertex2d(xc-y,yc-x);
		glVertex2d(xc+x,yc-y);
		glVertex2d(xc+y,yc-x);
		if(d<0)
		{
			x+=1;
			d+=4*x+6;
		}
		else
		{
			x+=1;
			y-=1;
			d+=4*x-4*y+10;
		}
	}while(x<=y);
}

void timer(int)
{
	glutPostRedisplay();
	glutTimerFunc(100,timer,0);
	dyc-=10;
	if(flag==1 && dyc<yc)
	{
		r1+=10;//After every 100ms r1 is incr by 10 and then draw is called
		if(r1>40)
		{
			r2+=10;//Again Entire circle is shifted by 10(wave)
		}
		if(r2>33)
		{
			r3+=10;
		}
	}
}

void wave(int w, int r)//w-no of circle in wave, r-radii of wave
{
	float c=1.0f; //Color of circle
	float cin=0.3/w; //change in color
	for(int i=w;i>0;i--)
	{
		for(int j=0;j<i;j++)
		{
			glColor3f(0,0,c);//color shade change from faint to dark
			bresenhamCircle(r,xc,yc);
			r+=1;
		}
		c-=cin;
	}
	for(int i=0;i<w;i++)
	{
		for(int j=0;j<i;j++)
		{
			glColor3f(0,0,c);
			bresenhamCircle(r,xc,yc);
			r+=1;
		}
		c+=cin;
	}
	for(int i=w;i>0;i--)
	{
		for(int j=0;j<i;j++)
		{
			glColor3f(0,0,c);
			bresenhamCircle(r,xc,yc);
			r+=1;
		}
		c-=cin;
	}
	for(int i=0;i<w;i++)
	{
		glColor3f(0,0,c);
		bresenhamCircle(r,xc,yc);
		r+=1;
	}
}

void drop()
{
	glBegin(GL_POINTS);
	float dropColor=0.5;
	glColor3f(0,0,0.5);
	if(dyc>yc)
	{
		for(int a=20;a>10;a--)
		{
			bresenhamCircle(a,dxc,dyc);
			glClear(GL_COLOR_BUFFER_BIT);
			glColor3f(0,0,dropColor);
			dropColor+=0.05;
		}
	}
}

void myMouse(int button, int state, int x, int y)
{
	y=300-y,x=x-300;
	glBegin(GL_POINTS);
	if(button==GLUT_LEFT_BUTTON)
	{
		if(state==GLUT_UP)
		{
			xc=x,yc=y;
			r1=0,r2=0,r3=0,flag=1;
			dxc=xc,dyc=300;
		}
	}
}

void Draw()
{
	glutMouseFunc(myMouse);
	glClear(GL_COLOR_BUFFER_BIT);
	drop();
	if(r1>40)
	{
		wave(5,r2);
	}
	if(r2>33)
	{
		wave(4,r3);
	}
	glEnd();
	glFlush();
}

int main(int argc, char** argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(600,600);
	glutInitWindowPosition(-300,-300);
	glutCreateWindow("Water Drop");
	glClearColor(0,0,1,0.2);
	glColor3f(0,0,0.5);
	gluOrtho2D(-300,300,-300,300);
	glutDisplayFunc(Draw);
	glutTimerFunc(0,timer,0);
	glutMainLoop();

	return 0;
}