# include<stdio.h>
#include<GL/glut.h>
#include<math.h>
int inpts[2][11];
int n;
int Round(float a)
{
	return (int)(a+0.5);
}

float fact(int b)
{
	int fac=1;
	if (b < 0){
	return 0;
	}
    else 
    {
        for (int i = 1; i <= b; ++i) 
        {
            fac *= i;
        }
        return fac;
    }
}
void bezier()
{
    int bx, by;
    bx=0;
    by=0;
	for(float q=0; q<=1; q+=0.00001)
	{
		for(int i=0;i<n;i++)
        {
			
			bx+=(fact(n-1)/(float)(fact(n-1-i)*fact(i)))*(pow(q,i))*(pow(1-q,n-1-i))*(inpts[0][i]);
			by+=(fact(n-1)/(float)(fact(n-1-i)*fact(i)))*(pow(q,i))*(pow(1-q,n-1-i))*(inpts[1][i]);			
		}
		glVertex2d(bx,by);
		bx=0;
		by=0;
	}
}

void draw()
{
	glClear(GL_COLOR_BUFFER_BIT);
    //glPointSize(2);
	glBegin(GL_POINTS);
    glColor3f(1,0.2,0.2);
 
    for(int i=0; i<n; i++)
    {
        glVertex2d(inpts[0][i], inpts[1][i]);
    }
    
    glColor3f(1,1,.04);
    bezier();
	glEnd();
	glFlush();
}


int main(int argc, char **argb)
{
    printf("Enter n point \n");
    scanf("%d",&n);
    for(int i=0; i<n; i++)
    {
        printf("\n%d) X : ", i+1);
        scanf("%d", &inpts[0][i]);
        printf("%d) Y : ", i+1);
        scanf("%d", &inpts[1][i]);
    }

	glutInit(&argc, argb);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB); 	
	glutInitWindowSize(1000,1000);	
	glutInitWindowPosition(0,0);	
	glutCreateWindow("Bezier Curve");
	glClearColor(0,0,0, 0.0);
	glColor3f(1,1,1);
	gluOrtho2D(0, 640, 0, 480);
	glutDisplayFunc(draw);
	glutMainLoop();	
}

/*
# include<stdio.h>
#include<GL/glut.h>
int inpts[2][4];

void bezier()
{
    int bx, by;
    for(float q=0; q<=1; q+=0.001)
    {
        bx = (1-q)*(1-q)*(1-q)*inpts[0][0] + 3*(1-q)*(1-q)*(q)*inpts[0][1] + 3*(1-q)*(q)*(q)*inpts[0][2] + (q)*(q)*(q)*inpts[0][3];
        by = (1-q)*(1-q)*(1-q)*inpts[1][0] + 3*(1-q)*(1-q)*(q)*inpts[1][1] + 3*(1-q)*(q)*(q)*inpts[1][2] + (q)*(q)*(q)*inpts[1][3];
        glVertex2d(bx,by);
    }
}

void draw()
{
	glClear(GL_COLOR_BUFFER_BIT);
    glPointSize(2);
	glBegin(GL_POINTS);
    glColor3f(1,0.2,0.2);
    for(int i=0; i<4; i++)
    {
        glVertex2d(inpts[0][i], inpts[1][i]);
    }
    glColor3f(1,1,.04);
    bezier();
	glEnd();
	glFlush();
}

int main(int argc, char **argb)
{
    printf("Enter 4 point \n");
    for(int i=0; i<4; i++)
    {
        printf("\n%d) X : ", i+1);
        scanf("%d", &inpts[0][i]);
        printf("%d) Y : ", i+1);
        scanf("%d", &inpts[1][i]);
    }

	glutInit(&argc, argb);
	// It is used to initilize glut library
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB); 
	// sets the initial display mode.
	glutInitWindowSize(644,480);
	glutInitWindowPosition(0,0);
	glutCreateWindow("Bezier");
	glClearColor(0,0,0, 0.0);
	// red, green, blue, and alpha 
	// set clear color to white
	glColor3f(1,1,1);
	// set feel color to black
	gluOrtho2D(0, 640, 0, 480);
	glutDisplayFunc(draw);
	glutMainLoop();
	//keep displaying until program is closed.	
}
*/