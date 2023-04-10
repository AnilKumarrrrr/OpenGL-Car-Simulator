//Anil Kumar
//Mahesh Meena
//Team/Group No: 9

#include<stdio.h>
#include<stdlib.h>
#include<GL/glut.h>
#include<GL/freeglut.h>
#include<math.h>
#include<string.h>
#define ESCAPE 27 //According to the Computer System.
#define ENTER 13







int Xsize = 1366; //Windows X - Size
int Ysize = 768; //Window Y - Size
int window, window2;
float i, theta;


int day = 1, night = 0;




//For Translation
float X_t = 0, Y_t = 0, Z_t = 0;
float T_x = 300, T_y = -75;
float X_s = 1, Y_s = 1, Z_s = 1;
float X_w = 0;


float X_angle = 0, Y_angle = 0, Z_angle = 0;
float angle = 0.0;


float R = 0, G = 0, B = 0; //RGB
float light = 1;

//All Menu

int count = 1, flag = 1;
int view = 0;
int flag1 = 0;
int flag2 = 0;
int aflag = 0;
int wheelflag = 0;


GLUquadricObj* T;

//Simple Transform 
void Transform(float Width, float Height)
{
	glViewport(0, 0, Width, Height);              /* Set the viewport */
	glMatrixMode(GL_PROJECTION);                  /* Select the projection matrix */
	glLoadIdentity();				/* Reset The Projection Matrix */
	gluPerspective(45.0, Width / Height, 0.1, 100.0);  /* Calculate The Aspect Ratio Of The Window */
	glMatrixMode(GL_MODELVIEW);                   /* Switch back to the modelview matrix */
}


/* A general OpenGL initialization function.  Sets all of the initial parameters. */
void InitGL(float Width, float Height)
{

	glClearColor(1.0, 1.0, 1.0, 1.0);
	glLineWidth(2.0);              /* Add line width,   Copy the Line width */
	Transform(Width, Height); /* Perform the transformation */
	//newly added
	T = gluNewQuadric();
	gluQuadricDrawStyle(T, GLU_FILL);

	glEnable(GL_LIGHTING);

	glEnable(GL_LIGHT0);

	// Create light components
	float ambientLight[] = { 0.2f, 0.2f, 0.2f, 1.0f };
	float diffuseLight[] = { 0.8f, 0.8f, 0.8, 1.0f };
	float specularLight[] = { 0.5f, 0.5f, 0.5f, 1.0f };
	float position[] = { 1.5f, 1.0f, 4.0f, 1.0f };

	// Assign created components to GL_LIGHT0
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);
	glLightfv(GL_LIGHT0, GL_POSITION, position);

}


/* The function called when our window is resized  */
void ReSizeGLScene(int Width, int Height)
{
	if (Height == 0)     Height = 1;                   /* Sanity checks */
	if (Width == 0)      Width = 1;
	Transform(Width, Height);                   /* Perform the transformation */
}


//Used For our first display Menu
void init()
{
	glClearColor(0, 0, 0, 0);
	glPointSize(5.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, 900.0, 600.0, 0.0, 50.0, -50.0);
	glutPostRedisplay(); 		// request redisplay
}


//For displaying the String on the first page of Page
void display_string(int x, int y, char* string, int font)
{
	int len, i;
	//glColor3f(0.8, 0.52, 1.0);
	glRasterPos2f(x, y);
	len = (int)strlen(string);
	for (i = 0; i < len; i++) {
		if (font == 1)
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string[i]);
		if (font == 2)
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, string[i]);
		if (font == 3)
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, string[i]);
		if (font == 4)
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, string[i]);
	}

}


//First Page Display 
void display1()
{
	glClearColor(1.0, 1.0, 1.0, 1.0);


	char p[] = "Project: 3D Animated Car";
	display_string(350, 40, p, 1);

	char s[] = "Subject: Computer Graphics Using OpenGL";
	display_string(330, 110, s, 2);

	char c[] = "Subject Code: CS440";
	display_string(400, 150, c, 3);

	char cr[] = "Created By:";
	display_string(400, 200, cr, 3);

	char t[] = "Tahzeer Ashraf";
	display_string(450, 220, t, 2);

	char a[] = "Aarav Jadav";
	display_string(450, 260, a, 2);

	char sa[] = "Satvik Srivastav";
	display_string(450, 300, sa, 2);

	char h[] = "HELP";
	display_string(450, 370, h, 1);

	char mh[] = "PRESS RIGHT BUTTON FOR MENU";
	display_string(450, 400, mh, 3);

	char hk[] = "X-Y-Z KEYS FOR CORRESPONDING ROTATION";
	display_string(450, 410, hk, 3);

	char hk1[] = "A-S-Q CAR CUSTOM SIZE SELECTION";
	display_string(450, 420, hk1, 3);

	char hk2[] = "U-F-M FOR CAMERA VIEW SETTINGS";
	display_string(450, 430, hk2, 3);

	char hk3[] = "USE LEFT ARROW(<-) AND RIGHT ARROW(->) TO MOVE CAR";
	display_string(450, 440, hk3, 3);

	char hk4[] = "ESCAPE TO EXIT";
	display_string(450, 450, hk4, 3);

	char E[] = "Press ENTER to start the Animation.";
	display_string(350, 500, E, 1);


	glutPostRedisplay();
	glutSwapBuffers();

}




//Drawing Panel
void DrawScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	/* Clear The Screen And The Depth Buffer */


	if (view == 0)
	{
		init();
		display1();
	}

	else
	{
		if (count == 1)
			InitGL(Xsize, Ysize);

		if (aflag == 1)
			glClearColor(1, 1, 1, 1);

		else
			glClearColor(0.1, 0.1, 0.1, 0);

		glPushMatrix();
		glLoadIdentity();
		glTranslatef(-1.0, 0.0, -3.5);
		glRotatef(X_angle, 1.0, 0.0, 0.0);
		glRotatef(Y_angle, 0.0, 1.0, 0.0);
		glRotatef(Z_angle, 0.0, 0.0, 1.0);
		glTranslatef(X_t, Y_t, Z_t);
		glScalef(X_s, Y_s, Z_s);
		glEnable(GL_COLOR_MATERIAL);
		glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

		//For FOG
		if (flag2 == 0)
		{
			glDisable(GL_FOG);
		}



		if (flag2 == 1)
		{
			float fogcolour[4] = { 1.0,1.0,1.0,1.0 };

			glFogfv(GL_FOG_COLOR, fogcolour);              /* Define the fog colour */
			glFogf(GL_FOG_DENSITY, 0.1);                   /* How dense */
			glFogi(GL_FOG_MODE, GL_EXP);                   /* exponential decay */
			glFogf(GL_FOG_START, 3.0);                   /* Where wwe start fogging */
			glFogf(GL_FOG_END, 100.0);                       /* end */
			glHint(GL_FOG_HINT, GL_FASTEST);              /* compute per vertex */
			glEnable(GL_FOG);/* ENABLE */
		}




		if (!aflag) {
			glBegin(GL_POINTS);
			glColor3f(1, 1, 1);
			glPointSize(200.0);
			int c = 0;
			float x = 10, y = 10;
			while (c < 20)
			{
				glVertex2f(x, y);
				x += 10;
				y += 10;
				if (y > Ysize) y -= 10;
				if (x > Xsize) x -= 10;
				c++;
			}
			glEnd();
		}



		glColor3f(1.0, .75, 0.0);
		glPointSize(30.0);
		glBegin(GL_POINTS);
		glVertex3f(0.2, 0.3, 0.3);
		glVertex3f(0.2, 0.3, 0.5);
		glEnd();
		glPointSize(200.0);



		glBegin(GL_QUADS);                /* OBJECT MODULE*/

		/* top of cube*/
		//************************FRONT BODY****************************************
		glColor3f(R, G, B);
		glVertex3f(0.2, 0.4, 0.6);
		glVertex3f(0.6, 0.5, 0.6);
		glVertex3f(0.6, 0.5, 0.2);
		glVertex3f(0.2, 0.4, 0.2);

		/* bottom of cube*/
		glVertex3f(0.2, 0.2, 0.6);
		glVertex3f(0.6, 0.2, 0.6);
		glVertex3f(0.6, 0.2, 0.2);
		glVertex3f(0.2, 0.2, 0.2);

		/* front of cube*/
		glVertex3f(0.2, 0.2, 0.6);
		glVertex3f(0.2, 0.4, 0.6);
		glVertex3f(0.2, 0.4, 0.2);
		glVertex3f(0.2, 0.2, 0.2);

		/* back of cube.*/
		glVertex3f(0.6, 0.2, 0.6);
		glVertex3f(0.6, 0.5, 0.6);
		glVertex3f(0.6, 0.5, 0.2);
		glVertex3f(0.6, 0.2, 0.2);

		/* left of cube*/
		glVertex3f(0.2, 0.2, 0.6);
		glVertex3f(0.6, 0.2, 0.6);
		glVertex3f(0.6, 0.5, 0.6);
		glVertex3f(0.2, 0.4, 0.6);

		/* Right of cube */
		glVertex3f(0.2, 0.2, 0.2);
		glVertex3f(0.6, 0.2, 0.2);
		glVertex3f(0.6, 0.5, 0.2);
		glVertex3f(0.2, 0.4, 0.2);
		//****************************************************************************
		glVertex3f(0.7, 0.65, 0.6);
		glVertex3f(0.7, 0.65, 0.2);
		glVertex3f(1.7, 0.65, 0.2);        //top cover
		glVertex3f(1.7, 0.65, 0.6);
		//***************************back guard******************************
		glColor3f(R, G, B);            /* Set The Color To Blue*/
		glVertex3f(1.8, 0.5, 0.6);
		glVertex3f(1.8, 0.5, 0.2);
		glVertex3f(2.1, 0.4, 0.2);
		glVertex3f(2.1, 0.4, 0.6);

		/* bottom of cube*/
		glVertex3f(2.1, 0.2, 0.6);
		glVertex3f(2.1, 0.2, 0.2);
		glVertex3f(1.8, 0.2, 0.6);
		glVertex3f(1.8, 0.2, 0.6);

		/* back of cube.*/
		glVertex3f(2.1, 0.4, 0.6);
		glVertex3f(2.1, 0.4, 0.2);
		glVertex3f(2.1, 0.2, 0.2);
		glVertex3f(2.1, 0.2, 0.6);

		/* left of cube*/
		glVertex3f(1.8, 0.2, 0.2);
		glVertex3f(1.8, 0.5, 0.2);
		glVertex3f(2.1, 0.4, 0.2);
		glVertex3f(2.1, 0.2, 0.2);

		/* Right of cube */
		glVertex3f(1.8, 0.2, 0.6);
		glVertex3f(1.8, 0.5, 0.6);
		glVertex3f(2.1, 0.4, 0.6);
		glVertex3f(2.1, 0.2, 0.6);
		//******************MIDDLE BODY************************************
		glVertex3f(0.6, 0.5, 0.6);
		glVertex3f(0.6, 0.2, 0.6);
		glVertex3f(1.8, 0.2, 0.6);
		glVertex3f(1.8, 0.5, 0.6);

		/* bottom of cube*/
		glVertex3f(0.6, 0.2, 0.6);
		glVertex3f(0.6, 0.2, 0.2);
		glVertex3f(1.8, 0.2, 0.2);
		glVertex3f(1.8, 0.2, 0.6);

		/* back of cube.*/
		glVertex3f(0.6, 0.5, 0.2);
		glVertex3f(0.6, 0.2, 0.2);
		glVertex3f(1.8, 0.2, 0.2);
		glVertex3f(1.8, 0.5, 0.2);
		//*********************ENTER WINDOW**********************************
		glColor3f(0.3, 0.3, 0.3);
		glVertex3f(0.77, 0.63, 0.2);
		glVertex3f(0.75, 0.5, 0.2);        //quad front window
		glVertex3f(1.2, 0.5, 0.2);
		glVertex3f(1.22, 0.63, 0.2);

		glVertex3f(1.27, 0.63, .2);
		glVertex3f(1.25, 0.5, 0.2);        //quad back window
		glVertex3f(1.65, 0.5, 0.2);
		glVertex3f(1.67, 0.63, 0.2);

		glColor3f(R, G, B);
		glVertex3f(0.7, 0.65, 0.2);
		glVertex3f(0.7, 0.5, .2);       //first separation
		glVertex3f(0.75, 0.5, 0.2);
		glVertex3f(0.77, 0.65, 0.2);

		glVertex3f(1.2, 0.65, 0.2);
		glVertex3f(1.2, 0.5, .2);       //second separation
		glVertex3f(1.25, 0.5, 0.2);
		glVertex3f(1.27, 0.65, 0.2);

		glVertex3f(1.65, 0.65, 0.2);
		glVertex3f(1.65, 0.5, .2);     //3d separation
		glVertex3f(1.7, 0.5, 0.2);
		glVertex3f(1.7, 0.65, 0.2);

		glVertex3f(0.75, 0.65, 0.2);
		glVertex3f(0.75, 0.63, 0.2);        //line strip
		glVertex3f(1.7, 0.63, 0.2);
		glVertex3f(1.7, 0.65, 0.2);

		glVertex3f(0.75, 0.65, 0.6);
		glVertex3f(0.75, 0.63, 0.6);        //line strip
		glVertex3f(1.7, 0.63, 0.6);
		glVertex3f(1.7, 0.65, 0.6);

		glColor3f(0.3, 0.3, 0.3);
		glVertex3f(0.77, 0.63, 0.6);
		glVertex3f(0.75, 0.5, 0.6);        //quad front window
		glVertex3f(1.2, 0.5, 0.6);
		glVertex3f(1.22, 0.63, 0.6);

		glVertex3f(1.27, 0.63, .6);
		glVertex3f(1.25, 0.5, 0.6);        //quad back window
		glVertex3f(1.65, 0.5, 0.6);
		glVertex3f(1.67, 0.63, 0.6);

		glColor3f(R, G, B);
		glVertex3f(0.7, 0.65, 0.6);
		glVertex3f(0.7, 0.5, .6);       //first separation
		glVertex3f(0.75, 0.5, 0.6);
		glVertex3f(0.77, 0.65, 0.6);

		glVertex3f(1.2, 0.65, 0.6);
		glVertex3f(1.2, 0.5, .6);       //second separation
		glVertex3f(1.25, 0.5, 0.6);
		glVertex3f(1.27, 0.65, 0.6);

		glVertex3f(1.65, 0.65, 0.6);
		glVertex3f(1.65, 0.5, .6);
		glVertex3f(1.7, 0.5, 0.6);
		glVertex3f(1.7, 0.65, 0.6);
		glEnd();


		//**************************************************************
		glBegin(GL_QUADS);

		/* top of cube*/
		glColor3f(0.3, 0.3, 0.3);
		glVertex3f(0.6, 0.5, 0.6);
		glVertex3f(0.6, 0.5, 0.2);        //quad front window
		glVertex3f(0.7, 0.65, 0.2);
		glVertex3f(0.7, 0.65, 0.6);

		glVertex3f(1.7, 0.65, .6);
		glVertex3f(1.7, 0.65, 0.2);        //quad back window
		glVertex3f(1.8, 0.5, 0.2);
		glVertex3f(1.8, 0.5, 0.6);




		//For Surrounding in Test Mode
		if (flag1)
		{
			glPushMatrix();
			glTranslatef(X_w, 0, 0);
			glColor3f(0, 1, 0);
			glVertex3f(-100, 0.1, -100);
			glVertex3f(-100, 0.1, 0);         //a green surroundings
			glVertex3f(100, 0.1, 0);
			glVertex3f(100, 0.1, -100);

			glColor3f(0.7, 0.7, 0.7);
			glVertex3f(-100, 0.1, 0);
			glVertex3f(-100, 0.1, 0.45);         //a long road
			glVertex3f(100, 0.1, 0.45);
			glVertex3f(100, 0.1, 0);

			glColor3f(1.0, 0.75, 0.0);
			glVertex3f(-100, 0.1, 0.45);       //a median
			glVertex3f(-100, 0.1, 0.55);
			glVertex3f(100, 0.1, 0.55);
			glVertex3f(100, 0.1, 0.45);

			glColor3f(0.7, 0.7, 0.7);
			glVertex3f(-100, 0.1, 0.55);
			glVertex3f(-100, 0.1, 1);         //a long road
			glVertex3f(100, 0.1, 1);
			glVertex3f(100, 0.1, 0.55);

			glColor3f(0, 1, 0);
			glVertex3f(-100, 0.1, 1);
			glVertex3f(-100, 0.1, 100);         //a green surroundings
			glVertex3f(100, 0.1, 100);
			glVertex3f(100, 0.1, 1);
			glPopMatrix();
		}
		glEnd();



		//For Surrounding in Wheel Mode
		if (wheelflag)
		{
			glPushMatrix();
			glTranslatef(-X_w, 0, 0);
			glColor3f(0.5, .2, 0.3);
			glBegin(GL_QUADS);
			for (i = 0; i < 200; i += 0.2)
			{
				glVertex3f(-100 + i, 0, 1);
				glVertex3f(-99.9 + i, 0, 1);
				glVertex3f(-99.9 + i, 0.2, 1);
				glVertex3f(-100 + i, 0.2, 1);
				i += 0.5;
			}
			for (i = 0; i < 200; i += 0.2)
			{
				glVertex3f(-100 + i, 0, 0);
				glVertex3f(-99.9 + i, 0, 0);
				glVertex3f(-99.9 + i, 0.2, 0);
				glVertex3f(-100 + i, 0.2, 0);
				i += 0.5;
			}
			glEnd();
			glPopMatrix();
		}


		//*************************************************************************************************
		glBegin(GL_TRIANGLES);                /* start drawing the cube.*/

		  /* top of cube*/
		glColor3f(0.3, 0.3, 0.3);
		glVertex3f(0.6, 0.5, 0.6);
		glVertex3f(0.7, 0.65, 0.6);       //tri front window
		glVertex3f(0.7, 0.5, 0.6);

		glVertex3f(0.6, 0.5, 0.2);
		glVertex3f(0.7, 0.65, 0.2);       //tri front window
		glVertex3f(0.7, 0.5, 0.2);

		glVertex3f(1.7, 0.65, 0.2);
		glVertex3f(1.8, 0.5, 0.2);       //tri back window
		glVertex3f(1.7, 0.5, 0.2);

		glVertex3f(1.7, 0.65, 0.6);
		glVertex3f(1.8, 0.5, 0.6);       //tri back window
		glVertex3f(1.7, 0.5, 0.6);

		glEnd();
		//************IGNITION SYSTEM**********************************
		glPushMatrix();
		glColor3f(0.7, 0.7, 0.7);
		glTranslatef(1.65, 0.2, 0.3);
		glRotatef(90.0, 0, 1, 0);
		gluCylinder(T, 0.02, 0.03, .5, 10, 10);
		glPopMatrix();
		//********************WHEEL*********************************************

		glColor3f(0.7, 0.7, 0.7);
		glPushMatrix();
		glBegin(GL_LINE_STRIP);
		for (theta = 0; theta < 360; theta = theta + 20)
		{
			glVertex3f(0.6, 0.2, 0.62);
			glVertex3f(0.6 + (0.08 * (cos(((theta + angle) * 3.14) / 180))), 0.2 + (0.08 * (sin(((theta + angle) * 3.14) / 180))), 0.62);
		}
		glEnd();

		glBegin(GL_LINE_STRIP);
		for (theta = 0; theta < 360; theta = theta + 20)
		{
			glVertex3f(0.6, 0.2, 0.18);
			glVertex3f(0.6 + (0.08 * (cos(((theta + angle) * 3.14) / 180))), 0.2 + (0.08 * (sin(((theta + angle) * 3.14) / 180))), 0.18);
		}
		glEnd();

		glBegin(GL_LINE_STRIP);
		for (theta = 0; theta < 360; theta = theta + 20)
		{
			glVertex3f(1.7, 0.2, 0.18);
			glVertex3f(1.7 + (0.08 * (cos(((theta + angle) * 3.14) / 180))), 0.2 + (0.08 * (sin(((theta + angle) * 3.14) / 180))), 0.18);
		}
		glEnd();

		glBegin(GL_LINE_STRIP);
		for (theta = 0; theta < 360; theta = theta + 20)
		{
			glVertex3f(1.7, 0.2, 0.62);
			glVertex3f(1.7 + (0.08 * (cos(((theta + angle) * 3.14) / 180))), 0.2 + (0.08 * (sin(((theta + angle) * 3.14) / 180))), 0.62);
		}
		glEnd();
		glTranslatef(0.6, 0.2, 0.6);
		glColor3f(0, 0, 0);
		glutSolidTorus(0.025, 0.07, 10, 25);

		glTranslatef(0, 0, -0.4);
		glutSolidTorus(0.025, 0.07, 10, 25);

		glTranslatef(1.1, 0, 0);
		glutSolidTorus(0.025, 0.07, 10, 25);

		glTranslatef(0, 0, 0.4);
		glutSolidTorus(0.025, 0.07, 10, 25);
		glPopMatrix();
		//*************************************************************
		glPopMatrix();
		glEnable(GL_DEPTH_TEST);
		glutPostRedisplay();
		glutSwapBuffers();

	}


}




//This Function works when a key is pressed which is not in OpenGL special Keys
void NormalKey(GLubyte key, int x, int y)
{
	switch (key)
	{
	case ESCAPE: printf("Escape Pressed. Exit.\n");
		glutDestroyWindow(window);
		exit(0);
		break;

	case ENTER: view = 1;
		DrawScene();
		break;

	case 'x':
		X_angle += 5.0;
		glutPostRedisplay();
		break;

	case 'X':
		X_angle -= 5.0;
		glutPostRedisplay();
		break;

	case 'y':
		Y_angle += 5.0;
		glutPostRedisplay();
		break;

	case 'Y':
		Y_angle -= 5.0;
		glutPostRedisplay();
		break;

	case 'z':
		Z_angle += 5.0;
		glutPostRedisplay();
		break;

	case 'Z':
		Z_angle -= 5.0;
		glutPostRedisplay();
		break;

	case 'u':                          /* Move up */
		Y_t += 0.2;
		glutPostRedisplay();
		break;

	case 'U':
		Y_t -= 0.2;                      /* Move down */
		glutPostRedisplay();
		break;

	case 'm':
		X_t += 0.2;
		glutPostRedisplay();
		break;

	case 'M':
		X_t -= 0.2;
		glutPostRedisplay();
		break;

	case 'f':                          /* Move forward */
		Z_t += 0.2;
		glutPostRedisplay();
		break;

	case 'F':
		Z_t -= 0.2;                      /* Move away */
		glutPostRedisplay();
		break;

	case 's':Z_s += .2;
		glutPostRedisplay();
		break;

	case 'S':Z_s -= 0.2;
		glutPostRedisplay();
		break;

	case 'a':Y_s += .2;
		glutPostRedisplay();
		break;

	case 'A':Y_s -= 0.2;
		glutPostRedisplay();
		break;

	case 'q':X_s += .2;
		glutPostRedisplay();
		break;

	case 'Q':X_s -= 0.2;
		glutPostRedisplay();
		break;

	default:
		break;


	}
}

//This Function works for the key already known to OpenGL.
void SpecialKeyFunc(int Key, int x, int y)
{
	switch (Key) {
	case GLUT_KEY_RIGHT:
		if (!wheelflag)
			X_t += 0.2;
		if (wheelflag)
		{
			angle += 5;
			X_w += 0.2;
		}
		glutPostRedisplay();
		break;

	case GLUT_KEY_LEFT:
		if (!wheelflag)
			X_t -= 0.2;
		if (wheelflag)
		{
			angle += 5;
			X_w -= 0.2;
		}
		glutPostRedisplay();
		break;
	}
}



//Right Click Menu
void myMenu(int id)
{
	if (id == 1)
	{
		flag1 = 0;
		wheelflag = 0;
		glutPostRedisplay();

	}
	if (id == 2)
	{
		flag1 = 1;
		flag2 = 0;
		wheelflag = 0;
		X_angle += 5.0;
		glutPostRedisplay();
	}
	if (id == 3)
	{
		flag2 = 1;
		wheelflag = 0;
		X_angle += 5.0;
		glutPostRedisplay();
	}
	if (id == 4)
	{
		wheelflag = 1;
		glutPostRedisplay();
	}
	if (id == 5)
	{
		if (day)
		{

			if (light)
			{
				count++;
				glDisable(GL_LIGHTING);
				glDisable(GL_LIGHT0);
				light = 0;
			}
			else
			{
				count--;
				light = 1;
				glEnable(GL_LIGHTING);
				glEnable(GL_LIGHT0);
			}
			glutPostRedisplay();
		}
		else
		{

			if (night == 0 && flag2 == 2)
			{
				flag2 = 0;
				night = 1;
			}
			else
			{
				flag2 = 2;
				night = 0;

				aflag = 0;
				day = 0;

				glClearColor(0.1, 0.1, 0.1, 0);
				float fogcolour[4] = { 0.0,0.0,0.0,1.0 };

				glFogfv(GL_FOG_COLOR, fogcolour);              /* Define the fog colour */
				glFogf(GL_FOG_DENSITY, 0.5);                   /* How dense */
				glFogi(GL_FOG_MODE, GL_EXP);                   /* exponential decay */
						/* end */
				glHint(GL_FOG_HINT, GL_FASTEST);              /* compute per vertex */
				glEnable(GL_FOG);


				glutPostRedisplay();
			}
		}

	}


	if (id == 12)
	{
		aflag = 1;
		day = 1;
		glClearColor(1, 1, 1, 1);
		glDisable(GL_FOG);
		glutPostRedisplay();
	}

	if (id == 13)
	{
		aflag = 0;
		day = 0;
		flag2 = 2;
		glClearColor(0.1, 0.1, 0.1, 0);
		float fogcolour[4] = { 0.0,0.0,0.0,1.0 };

		glFogfv(GL_FOG_COLOR, fogcolour);              /* Define the fog colour */
		glFogf(GL_FOG_DENSITY, 0.5);                   /* How dense */
		glFogi(GL_FOG_MODE, GL_EXP);                   /* exponential decay */
							   /* end */
		glHint(GL_FOG_HINT, GL_FASTEST);              /* compute per vertex */
		glEnable(GL_FOG);

		glutPostRedisplay();
	}
}


//Colour Menu
void colorMenu(int id)
{
	if (id == 6)
	{
		R = G = 0;
		B = 1;
		glutPostRedisplay();

	}
	if (id == 7)
	{
		R = 0.8;
		B = G = 0;
		glutPostRedisplay();
	}
	if (id == 8)
	{
		G = 1;
		R = B = 0;
		glutPostRedisplay();
	}
	if (id == 9)
	{
		R = B = G = 0;
		glutPostRedisplay();
	}
	if (id == 10)
	{
		B = 0;
		R = G = 1;
		glutPostRedisplay();
	}
	if (id == 11)
	{
		B = R = G = .7;
		glutPostRedisplay();
	}
	if (id == 14)
	{
		B = R = G = 1.0;
		glutPostRedisplay();
	}
}


//Window Reshape 
void myreshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w <= h)
		glOrtho(-2.0, 2.0, -2.0 * (float)h / (float)w, 2.0 * (float)h / (float)w, -10.0, 10.0);
	else
		glOrtho(-2.0 * (float)w / (float)h, 2.0 * (float)w / (float)h, -2.0, 2.0, -10.0, 10.0);
	glMatrixMode(GL_MODELVIEW);
	glutPostRedisplay();
}



//Main Calling Function
int main(int argc, char** argv)
{
	printf("Created By:");
	printf("\n           Aarav Jadav\n           Tahzeer Ashraf\n           Satvik Srivastav");
	printf("\nMouse Control:\n");
	printf("              PRESS RIGHT BUTTON FOR MENU");
	printf("\nKeyBoard Control:\n");
	printf("                 X-Y-Z KEYS FOR CORRESPONDING ROTATION\n                 A-S-Q CAR CUSTOM SIZE SELECTION\n                 U-F-M FOR CAMERA VIEW SETTINGS\n                 USE LEFT ARROW(<-) AND RIGHT ARROW(->) TO MOVE CAR\n                 ESCAPE TO EXIT\n                 PRESS ENTER TO START THE ANIMATION.\n");


	/* Initialisation and window creation */

	glutInit(&argc, argv);               /* Initialize GLUT state. */

	glutInitDisplayMode(GLUT_RGBA |      /* RGB and Alpha */
		GLUT_DOUBLE |     /* double buffer */
		GLUT_DEPTH);     /* Z buffer (depth) */

	glutInitWindowSize(Xsize, Ysize);     /* set initial window size. */
	glutInitWindowPosition(0, 0);         /* upper left corner of the screen. */


	glutCreateWindow("3D CAR ANIMATION");
	glutReshapeFunc(myreshape);
	glutDisplayFunc(DrawScene);        /* Function to do all our OpenGL drawing. */
	glutReshapeFunc(ReSizeGLScene);
	glutKeyboardFunc(NormalKey);         /*Normal key is pressed */
	glutSpecialFunc(SpecialKeyFunc);
	InitGL(Xsize, Ysize);
	int submenu = glutCreateMenu(colorMenu);
	glutAddMenuEntry("blue", 6);
	glutAddMenuEntry("red", 7);
	glutAddMenuEntry("green", 8);
	glutAddMenuEntry("black", 9);
	glutAddMenuEntry("yellow", 10);
	glutAddMenuEntry("grey", 11);
	glutAddMenuEntry("white", 14);
	glutCreateMenu(myMenu);
	glutAddMenuEntry("car model mode", 1);
	glutAddMenuEntry("car driving mode", 2);
	glutAddMenuEntry("fog effect", 3);
	glutAddMenuEntry("wheel effect", 4);
	glutAddMenuEntry("toggle light", 5);
	glutAddSubMenu("car colors", submenu);
	glutAddMenuEntry("daymode", 12);
	glutAddMenuEntry("Night mode", 13);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutMainLoop();                      /* Start Event Processing Engine. */
	return 1;
}