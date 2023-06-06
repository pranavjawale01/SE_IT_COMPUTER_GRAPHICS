#include<stdio.h>
#include<GL/glut.h>
#include<math.h>
#define PI 3.14

int ch,v;
float input[3][20],translation[3][3],scaling[3][3],rotation[3][3],reflection[3][3],shearing[3][3],output[3][20];

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
    printf("\n1.Translation \n2.Scaling \n3.Rotation \n4.Reflection \n5.Shearing \n> > > ");
    scanf("%d",&ch);
    printf("\nEnter the No. of vertices ");
    scanf("%d",&v);
    for(int i=0;i<v;i++)
    {
        printf("\nEnter The Co-ordinate x[0][%d] ",i);
        scanf("%f",&input[0][i]);
        printf("\nEnter The Co-ordinate y[1][%d] ",i);
        scanf("%f",&input[1][i]);
        input[2][i]=1;
    }
}

void translationFunc()
{
    float tx,ty;
    printf("\nEnter Tx ");
    scanf("%f",&tx);
    printf("\nEnter Ty ");
    scanf("%f",&ty);
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
        {
            if(i==j)
            {
                translation[i][j]=1;
            }
            else
            {
                translation[i][j]=0;
            }
        }
    }
    translation[0][2]=tx;
    translation[1][2]=ty;
}

void scalingFunc()
{
    float sx,sy;
    printf("\nEnter the value of Sx ");
    scanf("%f",&sx);
    printf("\nEnter the value of Sy ");
    scanf("%f",&sy);
    float xf,yf;
    printf("\nEnter Fixed Point Xf ");
    scanf("%f",&xf);
    printf("\nEnter Fixed Point Yf ");
    scanf("%f",&yf);
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
        {
            if(i==j)
                scaling[i][j]=1;
            else
                scaling[i][j]=0;
        }
    }
    scaling[0][0]=sx;
    scaling[1][1]=sy;
    scaling[0][2]=xf*(1-sx);
    scaling[1][2]=yf*(1-sy);
}

void rotationFunc()
{
    float deg, rad, xr, yr;
    printf("\nEnter Angle in Degress ");
    scanf("%f",&deg);
    rad = (PI*deg)/180;
    printf("\nEnter Co-ordinates for pivot Point(x) ");
    scanf("%f",&xr);
    printf("\nEnter Co-ordinates for pivot Point(y) ");
    scanf("%f",&yr);

    rotation[0][0]=cos(rad);
   	rotation[0][1]=(-sin(rad));
   	rotation[0][2]=xr*(1-cos(rad))+yr*(sin(rad));
   	rotation[1][0]=sin(rad);
   	rotation[1][1]= cos(rad);
   	rotation[1][2]=yr*(1-cos(rad))-xr*(sin(rad));
   	rotation[2][0]=0;
   	rotation[2][1]=0;
   	rotation[2][2]=1; 
}

void reflectionFunc()
{
    int ref;
	printf("Enter reflection along which line :\n1.Along x-axis\n2.Along y-axis\n3.Along an axis that is perpendicular to x-y plane and passing through origin\n4.Along x=y\n5.Along x=-y \n");
	scanf("%d",&ref);
	for (int i=0;i<3;i++)
	{
		for (int j=0;j<3;j++)
		{
			reflection[i][j]=0;
		}
	}	
	if (ref==1)
	{	
		reflection[0][0]=1;
		reflection[1][1]=-1;
		reflection[2][2]=1;
	}
	else if (ref==2)
	{	
		reflection[0][0]=-1;
		reflection[1][1]=1;
		reflection[2][2]=1;
	}
	else if(ref==3)
	{
		reflection[0][0]=-1;
		reflection[1][1]=-1;
		reflection[2][2]=1;
	}
	else if(ref==4)
	{
		reflection[0][1]=1;
		reflection[1][0]=1;
		reflection[2][2]=1;
	}
	else if(ref==5)
	{
		reflection[0][1]=-1;
		reflection[1][0]=-1;
		reflection[2][2]=1;
	}
}

void shearingFunc()
{
    int ch1;
	float shx,shy;
	for (int i=0;i<3;i++)
	{
		for (int j=0;j<3;j++)
		{
            shearing[i][j]=0;
			if(i==j)
			{
				shearing[i][j]=1;
			}
		}
	}
	
	printf("Enter which shearing:\n1.X-direction\n2.Y-direction \n ");
	scanf("%d",&ch1);
	
	if(ch1==1)
	{
		printf("Enter shearing force in x-direction: ");
		scanf("%f",&shx);
		shearing[0][1]=shx;
        int yref=-1;
		shearing[0][2]=shx*yref;
	}
	if(ch1==2)
	{
		printf("Enter shearing force in y-direction: ");
		scanf("%f",&shy);
		shearing[1][0]=shy;
        int xref=-1;
		shearing[1][2]=shy*xref;
	}
}

void multiplyFunc(float opr[3][3], float in[3][20], float out[3][20]) 
{
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<v;j++)
        {
            out[i][j]=0;
            for(int k=0;k<3;k++)
            {
                out[i][j] += opr[i][k]*in[k][j];
            }
        }
    }
}

void draw()
{
    if(ch==1)
    {
        translationFunc();
        multiplyFunc(translation,input,output);
    }
    else if(ch==2)
    {
        scalingFunc();
        multiplyFunc(scaling,input,output);
    }
    else if(ch==3)
    {
        rotationFunc();
        multiplyFunc(rotation,input,output);
    }
    else if(ch==4)
    {
        reflectionFunc();
        multiplyFunc(reflection,input,output);
    }
    else if(ch==5)
    {
        shearingFunc();
        multiplyFunc(shearing,input,output);
    }

    glClear(GL_COLOR_BUFFER_BIT);
    glPointSize(1.0);
    glBegin(GL_POINTS);

    glColor3f(1,1,1);
    dda(320,0,320,480);
    dda(0,240,640,240);
    int i=0;
    while(i<640)
    {
        dda(315,i,325,i);
        dda(i,235,i,245);
        i+=20;
    }

    glColor3f(1,0,0);
    for (i=0;i<v-1;i++)
	{
		dda(320+(input[0][i]),240+(input[1][i]),320+(input[0][i+1]),240+(input[1][i+1]));
	}
	dda(320+(input[0][i]),240+(input[1][i]),320+(input[0][0]),240+(input[1][0]));

    glColor3f(0,0,1);
    for (i=0;i<v-1;i++)
	{
		dda(320+(output[0][i]),240+(output[1][i]),320+(output[0][i+1]),240+(output[1][i+1]));
	}
	dda(320+(output[0][i]),240+(output[1][i]),320+(output[0][0]),240+(output[1][0]));

    glEnd();
    glFlush();
}

int main(int argc, char ** argv)
{
    Input();

    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640,480);
    glutInitWindowPosition(0,0);
    glutCreateWindow("2D-Transformation");
    glClearColor(0,0,0,0);
    glColor3f(1,1,1);
    gluOrtho2D(0,640,0,480);
    glutDisplayFunc(draw);
    glutMainLoop();

    return 0;
}