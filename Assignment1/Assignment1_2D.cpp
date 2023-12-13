#define FREEGLUT_STATIC
#include <math.h>
#include <GL/freeglut.h>
#define MAX_CHAR 128
typedef struct { GLfloat x, y; } point;// define a 2D point
point p1 = { 0,70 };//Reated to firewark1
point p2 = { 100,70 };//Reated to firewark1
point p3 = { 0,0 };//Reated to firewark1
point p4 = { 0,0 };//Change the color of word during the daytime
point p5 = { 100, 80 };//Reated to firewark2
point p6 = { 100, 100 };//Reated to firewark2
point p7 = { 100, 100 };//Reated to firewark2
point p8 = { 0, 0 }; //cloud
point p9 = { 0, 0 }; //Let the left-handed fireworks fly
point p10 = { 100, 100 }; //Let the left-handed fireworks fly£» change the scale
point p11 = { 0, 0 }; //Let the right-handed fireworks fly
point p12 = { 0, 70 };//Reated to firewark2
point p13 = { 100, 70 };//Reated to firewark2
point p14 = { 0, 0 };//Reated to firewark2
point p15 = { 1, 0 };//Lighting ball of the tree
point p16 = { 0, 0 };//Lighting ball of the tree
point p17 = { 0, 0 };//cloud
point p18 = { 100, 100 }; //Let the right-handed fireworks fly£» change the scale
point p19 = { 0, 0 };//Star
GLint dark = 0;
GLint fly = 0;
GLfloat finishx = 300; // declare position of vertical axis
//Task 2
GLfloat step = 0.01;
GLfloat step3 = 0.2;// declare incremental step
GLfloat step4 = 0.003;
GLfloat step5 = 0.75;// Color
GLfloat step6 = 1;// StarFly
GLfloat step7 = 1;// Cloud
GLfloat step8 = 1.55;//Let the left-handed fireworks fly
GLfloat step9 = 0.5;//Let the right-handed fireworks fly
int step1 = 0.01;
int time_interval = 8; //declare refresh interval in ms

void keyboard_input(unsigned char key, int x, int y) { // keyboard interaction
	if (key == 'q' || key == 'Q')
		exit(0);
	else if (key == 'd' || key == 'D') // Change to the dark mode
		dark = 1;
	else if (key == 'b' || key == 'B') // hange to the daytime mode
		dark = 0;
	else if (key == 's' || key == 'S') //  Stops the snowman from continuously releasing fireworks (Note: fireworks that are still in the sky will not disappear when the button is pressed)
		fly = 1;
	else if (key == 'F' || key == 'f') // Let the snowman start releasing fireworks continuously
		fly = 0;
}

void when_in_mainloop()
{ // idle callback function
	glutPostRedisplay(); // force OpenGL to redraw the current window
}

void OnTimer(int value)
{
	if (p9.x >= 485) {
		p1.x += step;
		p2.x -= step3;
		p2.y += 4 * step3;
	}
	p8.x += step7;
	p8.y += step7;
	p17.x += step7;
	p17.y += step7;
	if (fly % 2 == 1 & p9.x == 0) {
		p9.x = 0;
	}
	else {
		p9.x += step8;
	}
	
	if (fly % 2 == 1 & p11.x == 0) {
		p11.x = 0;
	}
	else {
		p11.x += step9;
	}

	p16.x += 1;
	if (p16.x < 100) {
		p15.x = 1;
		p15.y = 0;
	}
	else {
		p15.x = 0;
		p15.y = 1;
	}

	if (p16.x > 200) {
		p16.x = 0;
	}

	if (p1.x >= 2) {
		p1.x = 0;
		p1.y = 70;
		p2.x = 100;
		p2.y = 70;
		p3.x = 0;
	}
	

	if (p1.x > 0.9) {
		p3.x += step;
		p1.y += 3 * step3;

	}
	
	if (p11.x > 153) {
		p12.x += step;
		p5.x += step6;
		p6.x -= 0.3;
		p13.x -= step3;

	}
	
	if (p12.x >= 2) {
		p12.x = 0;
		p13.x = 100;
		p5.x = 100;
		p7.x = 100;
		p6.x = 100;
		p7.y = 100;
		p14.x = 0;
	}
	
	if (p12.x > 0.9) {
		p14.x += step;
		p7.x -= step3;
		p7.y -= 0.3;
	}

	if (p11.x > 253) {
		p11.x = 0;
		p12.x = 0;
		p13.x = 100;
		p5.x = 100;
		p6.x = 100;
		p7.x = 100;
		p7.y = 100;
		p14.x = 0;
		p18.x = 100;
		p18.y = 100;
	}
	

	if (p8.x > 200) {
		p8.x = -1200;
	}

	if (p8.y > 500) {
		p8.y = -900;
	}

	if (p17.x > 900) {
		p17.x = -500;
	}

	if (p17.y > 1200) {
		p17.y = -200;
	}

	if (p9.x > 785) {
		p9.x = 0;
		p10.x = 100;
		p10.y = 100;
		p1.x = 0;
		p1.y = 70;
		p2.x = 100;
		p2.y = 70;
		p3.x = 0;
	}

	if (p9.x <= 251 & p9.x > 0)  {
		p10.x += 0.6;
		p10.y += 0.2;
	}

	if (p11.x < 110 & p11.x > 0) {
		p18.x += 0.6;
		p18.y += 0.2;
	}

	p19.x += 1;
	if(p19.x > 200){
		p19.x = 0;
	}

	p19.y += 1;
	if (p19.y > 400) {
		p19.y = 0;
	}

	if (p4.x < 100 & p4.y == 0) {
		p4.x += step5;
		if (p4.x >= 100) {
			p4.y = 1;
		}
	}
	else {
		p4.x -= step5;
		if (p4.x <= 0) {
			p4.y = 0;
		}
	}


	

	
	glutTimerFunc(time_interval, OnTimer, 1);
}

//Basic element of firewark1
void Water() {
	int i;
	float x, y;
	glColor3f(1, 0, 0);
	glPushMatrix();
	glScalef(40, 30, 0);
	glBegin(GL_POLYGON); 
	for (i = 0; i < 361; i = i + 5)
	{
		x = (3 * (1 + cos(i * (6.284 / 360.0))) * (2 + cos(i * (6.284 / 360.0)))) / (5 + 4 * cos(i * (6.284 / 360.0))) * (p2.x / 100) + p1.x;
		y = (3 * (1 + cos(i * (6.284 / 360.0))) * sin(i * (6.284 / 360.0))) / (5 + 4 * cos(i * (6.284 / 360.0))) * (p2.x / 100);

		glVertex2f(x, y);
	}
	glEnd();
	glPopMatrix();
}

//Basic element of firewark1
void Water1() {
	int i;
	float x, y;
	glColor3f(1, 1, 0);
	glPushMatrix();
	glScalef(36, 24, 0);
	glBegin(GL_POLYGON);
	if (p1.x > 0.9) {
		for (i = 0; i < 361; i = i + 5)
		{

			x = (3 * (1 + cos(i * (6.284 / 360.0))) * (2 + cos(i * (6.284 / 360.0)))) / (5 + 4 * cos(i * (6.284 / 360.0))) * (p2.x / 100) + p3.x * 4 / 4;
			y = (3 * (1 + cos(i * (6.284 / 360.0))) * sin(i * (6.284 / 360.0))) / (5 + 4 * cos(i * (6.284 / 360.0))) * (p2.x / 100);

			glVertex2f(x, y);

		}
	}
	glEnd();
	glPopMatrix();
}

//Suzhou center
void EastDoor1() {
	int i;
	int k;
	float x, y;
	glScalef(3.3, 3.3, 0);
	glPushMatrix();
	glColor3f(0.20, 0.20, 1);
	glBegin(GL_POLYGON);
	glVertex2f(-45, 0);
	glVertex2f(-44, 116);
	glVertex2f(-42.5, 134);
	glVertex2f(-6, 134);
	glVertex2f(-8, 130);
	glVertex2f(0, 130);
	glVertex2f(0, 0);
	glEnd();
	glColor3f(0.20, 0.20, 1);
	glBegin(GL_POLYGON);
	glVertex2f(7.5, 130);
	glVertex2f(6, 134);
	glVertex2f(7.5, 134);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex2f(7.5, 134);
	glVertex2f(42.5, 134);
	glVertex2f(44, 116);
	glVertex2f(45, 0);
	glVertex2f(8, 0);
	glEnd();
	glPopMatrix();


	if (dark % 2 == 1) {
		//Lights
		glPushMatrix();
		glColor3f(1, 1, 0);
		glBegin(GL_POLYGON); 
		for (i = 0; i < 91; i = i + 5)
		{
			x = 20 * cos(i * (6.284 / 360.0)) + 0.5;
			y = 140 * sin(i * (6.284 / 360.0));
			if (x >= 8) {
				glVertex2f(x, y);
			}
		}
		glVertex2f(8, 130);
		glVertex2f(-8, 130);
		for (i = 90; i < 181; i = i + 5)
		{
			x = 20 * cos(i * (6.284 / 360.0)) - 0.5;
			y = 140 * sin(i * (6.284 / 360.0));
			if (x <= -8) {
				glVertex2f(x, y);
			}
		}
		glEnd();
		glPopMatrix();
	}
	

	glPushMatrix();
	glColor3f(0, 0, 0.55);
	glBegin(GL_POLYGON);
	for (i = 0; i < 91; i = i + 5)
	{
		x = 20 * cos(i * (6.284 / 360.0));
		y = 140 * sin(i * (6.284 / 360.0));
		if (x >= 8) {
			glVertex2f(x, y);
		}
	}
	glVertex2f(8, 130);
	glVertex2f(-8, 130);
	for (i = 90; i < 181; i = i + 5)
	{
		x = 20 * cos(i * (6.284 / 360.0));
		y = 140 * sin(i * (6.284 / 360.0));
		if (x <= -8) {
			glVertex2f(x, y);
		}
	}
	glEnd();
	glPopMatrix();

	if (dark % 2 == 1) {
		//Lights
		glPushMatrix();
		glColor3f(0.9, 0.9, 0);
		glLineWidth(1.25f);
		glBegin(GL_LINES); 
		for (float m = 2.3; m <= 130; m = m + 2.328)
		{
			float xsin;
			xsin = asin(m / 140);
			x = 20 * cos(xsin);
			glVertex2f(-x, m);
			glVertex2f(x, m);
		}

		glEnd();
		glColor3f(1, 1, 0);
		glPopMatrix();

	}
	

	glPushMatrix();
	if (dark % 2 == 0) {
		glColor3f(0, 0, 0.55);
	}
	else {
		glColor3f(0.9, 0.9, 0);
	}
	glLineWidth(1.5f);
	glBegin(GL_LINES); 
	for (float m = 2.3; m <= 134; m = m + 5.328)
	{
		float xsin;
		xsin = asin(m / 140);
		x = 20 * cos(xsin);
		if (m <= 116) {
			glVertex2f(43.5, m);
		}
		else {
			glVertex2f(42, m);
		}
		glVertex2f(x + 0.5, m);

	}

	glEnd();

	glBegin(GL_LINES);
	for (float m = 2.3; m <= 134; m = m + 5.328)
	{
		float xsin;
		xsin = asin(m / 140);
		x = 20 * cos(xsin);
		if (m <= 116) {
			glVertex2f(-43.5, m);
		}
		else {
			glVertex2f(-42, m);
		}
		glVertex2f(-x - 0.5, m);

	}

	glEnd();

	if (dark % 2 == 1) {
		glColor3f(1, 1, 0);
		//Lights
		glLineWidth(1.3f);
		glColor3f(0.9, 0.9, 0);
		glBegin(GL_LINES);
		glVertex2f(-45, 0);
		glVertex2f(-44, 116);
		glVertex2f(-44, 116);
		glVertex2f(-42.5, 134);
		glVertex2f(-42.5, 134);
		glVertex2f(-6, 134);
		glVertex2f(-8, 130);
		glVertex2f(8, 130);
		glVertex2f(42.5, 134);
		glVertex2f(6, 134);
		glVertex2f(44, 116);
		glVertex2f(42.5, 134);
		glVertex2f(45, 0);
		glVertex2f(44, 116);
		glEnd();
	}
	glPopMatrix();

	if (dark % 2 == 1) {
		//Lights
	glPushMatrix();
	glColor3f(1, 1, 0);
	glBegin(GL_POLYGON); 
	for (k = 0; k < 181; k = k + 5)
	{
		if (k < 90) {
			x = 16 * cos(k * (6.284 / 360.0)) + 0.5;
			y = 100 * sin(k * (6.284 / 360.0));
		}
		else if (k > 90) {
			x = 16 * cos(k * (6.284 / 360.0)) - 0.5;
			y = 100 * sin(k * (6.284 / 360.0));
		}
		else {
			x = 16 * cos(k * (6.284 / 360.0)) ;
			y = 100 * sin(k * (6.284 / 360.0)) + 0.5;
		}

		glVertex2f(x, y);
            
	}
	glEnd();
	glPopMatrix();
	}
	

	glPushMatrix();
	if (dark % 2 == 0) {
		glColor3ub(13, 206, 235);
	}
	else {
		glColor3f(0, 0, 0);
	}
	glBegin(GL_POLYGON); 
	for (k = 0; k < 181; k = k + 5)
	{
		x = 16 * cos(k * (6.284 / 360.0));
		y = 100 * sin(k * (6.284 / 360.0));

		glVertex2f(x, y);
	}
	glEnd();
	glPopMatrix();
	glPushMatrix();
	glColor3f(0, 0, 0);
	glBegin(GL_LINES);
	glVertex2f(-41, 134);
	glVertex2f(-41, 146);
	glEnd();
	glBegin(GL_LINES);
	glVertex2f(41, 134);
	glVertex2f(41, 146);
	glEnd();
	glPopMatrix();

	

	glPushMatrix();
	if (dark % 2 == 0) {
		glColor3f(1, 1, 1);
	}
	else {
		glColor3f(0.9, 0.9, 0.9);
	}
	
	glBegin(GL_POLYGON); 
	for (k = 0; k < 90; k = k + 1)
	{
		
		x = 16 * cos(k * (6.284 / 360.0));
		y = 100 * sin(k * (6.284 / 360.0));

		if (y <= 3) {
			glVertex2f(x, y);
		}
	}

	glVertex2f(0, 3.1);
	glVertex2f(16, 3.15);

	for (k = 90; k < 181; k = k + 1)
	{

		x = 16 * cos(k * (6.284 / 360.0));
		y = 100 * sin(k * (6.284 / 360.0));

		if (y <= 2.8) {
			glVertex2f(x, y);
		}
	}
	glEnd();
	glPopMatrix();

}

//Basic element of firewark1; center point
void Cricle() {
	int i;
	float x, y;
	glScalef(0.1 * (p2.y / 100), 0.1 * (p2.y / 100), 0);
	glColor3f(1, 0, 0);
	glBegin(GL_POLYGON); 
	for (i = 0; i < 361; i = i + 5)
	{
		x = 100.0 * cos(i * (6.284 / 360.0));
		y = 100.0 * sin(i * (6.284 / 360.0));

		glVertex2f(x, y);
	}
	glEnd();
}
//Basic element of firewark1; center point
void Cricle1() {
	int i;
	float x, y;
	glScalef(0.1 * (p1.y / 100), 0.1 * (p1.y / 100), 0);
	glColor3f(1, 1, 0);
	glBegin(GL_POLYGON);
	for (i = 0; i < 361; i = i + 5)
	{
		x = 100.0 * cos(i * (6.284 / 360.0));
		y = 100.0 * sin(i * (6.284 / 360.0));

		glVertex2f(x, y);
	}
	glEnd();
}

//Basic element of firewark2
void Star() {
	int i;
	int k = 0;
	float x, y;

	glPushMatrix();
	glScalef(0.75, 1, 0);
	glColor3f(1, 0, 0);
	glBegin(GL_POLYGON);
	for (i = 90; i > 0; i = i - 5)
	{
		float j = 0;
		glVertex2f(0, p5.x * sin(90 * (6.284 / 360.0)) * (p13.x / 100) + 80 * p12.x);
		x = (float)i * (p6.x / 100);
		y = p5.x * sin(i * (6.284 / 360.0)) * (p13.x / 100) + 80 * p12.x;
		j = i - 5;
		float xNext = j * (p6.x / 100);
		float yNext = p5.x * sin(j * (6.284 / 360.0)) * (p13.x / 100) + 80 * p12.x;
		glVertex2f(x, y);
		glVertex2f(xNext, yNext);
	}

	for (i = 90; i > 0; i = i - 5)
	{
		float j = 0;
		glVertex2f(0, p5.x * sin(90 * (6.284 / 360.0)) * (p13.x / 100) + 80 * p12.x);
		x = (float)i * (p6.x / 100);
		y = ((p5.x + p5.y) - p5.y * sin(i * (6.284 / 360.0))) * (p13.x / 100) + 80 * p12.x;
		j = i - 5;
		float xNext = j * (p6.x / 100);
		float yNext = ((p5.x + p5.y) - p5.y * sin(j * (6.284 / 360.0))) * (p13.x / 100) + 80 * p12.x;
		glVertex2f(x, y);
		glVertex2f(xNext, yNext);
	}

	for (i = 90; i > 0; i = i - 5)
	{
		float j = 0;
		glVertex2f(0, p5.x * sin(90 * (6.284 / 360.0)) * (p13.x / 100) + 80 * p12.x);
		x = -(float)i * (p6.x / 100);
		y = ((p5.x + p5.y) - p5.y * sin(i * (6.284 / 360.0))) * (p13.x / 100) + 80 * p12.x;
		j = i - 5;
		float xNext = -j * (p6.x / 100);
		float yNext = ((p5.x + p5.y) - p5.y * sin(j * (6.284 / 360.0))) * (p13.x / 100) + 80 * p12.x;
		glVertex2f(x, y);
		glVertex2f(xNext, yNext);
	}

	for (i = 90; i > 0; i = i - 5)
	{
		float j = 0;
		glVertex2f(0, p5.x * sin(90 * (6.284 / 360.0)) * (p13.x / 100) + 80 * p12.x);
		x = -(float)i * (p6.x / 100);
		y = p5.x * sin(i * (6.284 / 360.0)) * (p13.x / 100) + 80 * p12.x;
		j = i - 5;
		float xNext = -j * (p6.x / 100);
		float yNext = p5.x * sin(j * (6.284 / 360.0)) * (p13.x / 100) + 80 * p12.x;
		glVertex2f(x, y);
		glVertex2f(xNext, yNext);
	}

	glEnd();
	glPopMatrix();
}
//Basic element of firewark2
void Star1() {
	int i;
	int k = 0;
	float x, y;

	glPushMatrix();
	glScalef(0.75, 0.75, 0);
	glScalef(0.75, 1, 0);
	glColor3f(1, 1, 0);
	glBegin(GL_POLYGON);
	if (p12.x > 0.9) {
		for (i = 90; i > 0; i = i - 5)
		{
			float j = 0;
			glVertex2f(0, p5.x * sin(90 * (6.284 / 360.0)) * (p7.x / 100) + 80 * p14.x);
			x = (float)i * (p7.y / 100);
			y = p5.x * sin(i * (6.284 / 360.0)) * (p7.x / 100) + 80 * p14.x;
			j = i - 5;
			float xNext = j * (p7.y / 100);
			float yNext = p5.x * sin(j * (6.284 / 360.0)) * (p7.x / 100) + 80 * p14.x;
			glVertex2f(x, y);
			glVertex2f(xNext, yNext);
		}

		for (i = 90; i > 0; i = i - 5)
		{
			float j = 0;
			glVertex2f(0, p5.x * sin(90 * (6.284 / 360.0)) * (p7.x / 100) + 80 * p14.x);
			x = (float)i * (p7.y / 100);
			y = ((p5.x + p5.y) - p5.y * sin(i * (6.284 / 360.0))) * (p7.x / 100) + 80 * p14.x;
			j = i - 5;
			float xNext = j * (p7.y / 100);
			float yNext = ((p5.x + p5.y) - p5.y * sin(j * (6.284 / 360.0))) * (p7.x / 100) + 80 * p14.x;
			glVertex2f(x, y);
			glVertex2f(xNext, yNext);
		}

		for (i = 90; i > 0; i = i - 5)
		{
			float j = 0;
			glVertex2f(0, p5.x * sin(90 * (6.284 / 360.0)) * (p7.x / 100) + 80 * p14.x);
			x = -(float)i * (p7.y / 100);
			y = ((p5.x + p5.y) - p5.y * sin(i * (6.284 / 360.0))) * (p7.x / 100) + 80 * p14.x;
			j = i - 5;
			float xNext = -j * (p7.y / 100);
			float yNext = ((p5.x + p5.y) - p5.y * sin(j * (6.284 / 360.0))) * (p7.x / 100) + 80 * p14.x;
			glVertex2f(x, y);
			glVertex2f(xNext, yNext);
		}

		for (i = 90; i > 0; i = i - 5)
		{
			float j = 0;
			glVertex2f(0, p5.x * sin(90 * (6.284 / 360.0)) * (p7.x / 100) + 80 * p14.x);
			x = -(float)i * (p7.y / 100);
			y = p5.x * sin(i * (6.284 / 360.0)) * (p7.x / 100) + 80 * p14.x;
			j = i - 5;
			float xNext = -j * (p7.y / 100);
			float yNext = p5.x * sin(j * (6.284 / 360.0)) * (p7.x / 100) + 80 * p14.x;
			glVertex2f(x, y);
			glVertex2f(xNext, yNext);
		}
	}

	glEnd();
	glPopMatrix();
}


void tree() {
	int i;
	int k = 0;
	float x, y;
	glPushMatrix();
	glColor3f(0, 0.75, 0);
	glScalef(0.4, 0.4, 0);
	glBegin(GL_POLYGON);
	
	for (i = 90; i > 0; i = i - 5)
	{
		float j = 0;
		glVertex2f(0, 90);
		x = (float)i;
		y = 180 - 90 * sin(i * (6.284 / 360.0));
		j = i - 5;
		float xNext = j;
		float yNext = 180 - 90 * sin(j * (6.284 / 360.0));
		glVertex2f(x, y);
		glVertex2f(xNext, yNext);
	}

	for (i = 90; i > 0; i = i - 5)
	{
		float j = 0;
		glVertex2f(0, 90);
		x = -(float)i;
		y = 180 - 90 * sin(i * (6.284 / 360.0));
		j = i - 5;
		float xNext = -j;
		float yNext = 180 - 90 * sin(j * (6.284 / 360.0));
		glVertex2f(x, y);
		glVertex2f(xNext, yNext);
	}
	glEnd();

	glTranslatef(85, 90, 0);
	glScalef(0.1, 0.1, 0);
	glColor3f(1, p15.y, 0);
	glBegin(GL_POLYGON);
	for (i = 0; i < 361; i = i + 5)
	{
		x = 100.0 * cos(i * (6.284 / 360.0));
		y = 100.0 * sin(i * (6.284 / 360.0));

		glVertex2f(x, y);
	}
	glEnd();

	glScalef(10, 10, 0);
	glTranslatef(-85, -90, 0);
	glTranslatef(-85, 90, 0);
	glScalef(0.1, 0.1, 0);
	glColor3f(1, p15.y, 0);
	glBegin(GL_POLYGON); 
	for (i = 0; i < 361; i = i + 5)
	{
		x = 100.0 * cos(i * (6.284 / 360.0));
		y = 100.0 * sin(i * (6.284 / 360.0));

		glVertex2f(x, y);
	}
	glEnd();


	glPopMatrix();

}


void tree1() {
	int i;
	int k = 0;
	float x, y;
	glPushMatrix();
	glColor3f(0, 0.75, 0);
	glScalef(0.5, 0.4, 0);
	glBegin(GL_POLYGON);

	for (i = 90; i > 0; i = i - 5)
	{
		float j = 0;
		glVertex2f(0, 90);
		x = (float)i;
		y = 180 - 90 * sin(i * (6.284 / 360.0));
		j = i - 5;
		float xNext = j;
		float yNext = 180 - 90 * sin(j * (6.284 / 360.0));
		glVertex2f(x, y);
		glVertex2f(xNext, yNext);
	}

	glEnd();
	glPopMatrix();

}

void tree2() {
	int i;
	int k = 0;
	float x, y;
	glPushMatrix();
	glColor3f(0, 0.6, 0);
	glScalef(0.35, 0.6, 0);
	glBegin(GL_POLYGON);

	for (i = 90; i > 0; i = i - 5)
	{
		float j = 0;
		glVertex2f(0, 90);
		x = (float)i;
		y = 180 - 90 * sin(i * (6.284 / 360.0));
		j = i - 5;
		float xNext = j;
		float yNext = 180 - 90 * sin(j * (6.284 / 360.0));
		glVertex2f(x, y);
		glVertex2f(xNext, yNext);
	}

	glColor3f(0, 0.65, 0);
	for (i = 90; i > 0; i = i - 5)
	{
		float j = 0;
		glVertex2f(0, 90);
		x = -(float)i;
		y = 180 - 90 * sin(i * (6.284 / 360.0));
		j = i - 5;
		float xNext = -j;
		float yNext = 180 - 90 * sin(j * (6.284 / 360.0));
		glVertex2f(x, y);
		glVertex2f(xNext, yNext);
	}
	glEnd();
	glPopMatrix();

}

void tree3() {
	int i;
	int k = 0;
	float x, y;
	glPushMatrix();
	glScalef(0.35, 0.2, 0);
	glBegin(GL_POLYGON);

	for (i = 90; i > 0; i = i - 5)
	{
		float j = 0;
		glVertex2f(0, 90);
		x = (float)i;
		y = 180 - 90 * sin(i * (6.284 / 360.0));
		j = i - 5;
		float xNext = j;
		float yNext = 180 - 90 * sin(j * (6.284 / 360.0));
		glVertex2f(x, y);
		glVertex2f(xNext, yNext);
	}

	for (i = 90; i > 0; i = i - 5)
	{
		float j = 0;
		glVertex2f(0, 90);
		x = -(float)i;
		y = 180 - 90 * sin(i * (6.284 / 360.0));
		j = i - 5;
		float xNext = -j;
		float yNext = 180 - 90 * sin(j * (6.284 / 360.0));
		glVertex2f(x, y);
		glVertex2f(xNext, yNext);
	}
	glEnd();
	glPopMatrix();
}

void tree_Bottom() {
	int i;
	int k = 0;
	float x, y;
	float x1, y1;
	glPushMatrix();
	glScalef(0.35, 0.2, 0);
	glBegin(GL_POLYGON);

	for (i = 20; i > 0; i = i - 5)
	{
		float j = 0;
		glVertex2f(0, 145);
		x = (float)i;
		y = 180 - 90 * sin(i * (6.284 / 360.0));
		j = i - 5;
		float xNext = j;
		float yNext = 180 - 90 * sin(j * (6.284 / 360.0));
		glVertex2f(x, y);
		glVertex2f(xNext, yNext);
	}

	for (i = 20; i > 0; i = i - 5)
	{
		float j = 0;
		glVertex2f(0, 145);
		x = -(float)i;
		y = 180 - 90 * sin(i * (6.284 / 360.0));
		j = i - 5;
		float xNext = -j;
		float yNext = 180 - 90 * sin(j * (6.284 / 360.0));
		glVertex2f(x, y);
		glVertex2f(xNext, yNext);
	}
	glEnd();
	x1 = (float)20;
	y1 = 180 - 90 * sin(20 * (6.284 / 360.0));
	glBegin(GL_POLYGON);
	glVertex2f(x1, -10);
	glVertex2f(x1, y1);
	glVertex2f(0, 145);
	glVertex2f(-x1, y1);
	glVertex2f(-x1, -10);
	glEnd();
	glPopMatrix();

}

void cicle_Tree() {
	int i;
	float x, y;
	glScalef(0.05, 0.05, 0);
	glBegin(GL_POLYGON);
	for (i = 0; i < 361; i = i + 5)
	{
		x = 100.0 * cos(i * (6.284 / 360.0));
		y = 100.0 * sin(i * (6.284 / 360.0));

		glVertex2f(x, y);
	}
	glEnd();
}

void FiveStar() {
	float R = 100, r = 40;
	float a, b, c, d;
	a = 200.0f;
	b = 300.0f;
	c = a;
	d = b - 100;
	d = b - 100;
	if (p15.x == 1) {
		glColor3f(0.9, 0.9, 0.0f);
	}
	else {
		glColor3f(0.8, 0.8, 0.0f);
	}
	
	glBegin(GL_TRIANGLES);
	glVertex2f(0, 0);
	glVertex2f(0, 100);
	glVertex2f(c - 0.59 * r - 200, d + 0.81 * r - 200);
	glEnd();

	if (p15.x == 1) {
		glColor3f(0.8, 0.8, 0.0f);

	}
	else {
		glColor3f(0.9, 0.9, 0.0f);
	}
	
	glBegin(GL_TRIANGLES);
	glVertex2f(0, 0);
	glVertex2f(0, 100);
	glVertex2f(-(c - 0.59 * r - 200), d + 0.81 * r - 200);
	glEnd();

}


void final_Tree() {
	glPushMatrix();
	glTranslatef(660, 100, 0);
	tree();
	glPopMatrix();


	glPushMatrix();
	glTranslatef(665, 70, 0);
	tree1();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(655, 70, 0);
	glScalef(-1, 1, 0);
	tree1();
	glPopMatrix();

	glPushMatrix();
	glColor3f(0, 0.75, 0);
	glTranslatef(660, 100, 0);
	glScalef(0.5, 0.4, 0);
	glBegin(GL_POLYGON);
	glVertex2f(10, 15);
	glVertex2f(-9, 15);
	glVertex2f(-9, 90);
	glVertex2f(10, 90);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(670, 40, 0);
	glScalef(1.25, 1, 0);
	tree1();
	glPopMatrix();

	glPushMatrix();
	glColor3f(0, 0.75, 0);
	glTranslatef(660, 70, 0);
	glScalef(0.5, 0.4, 0);
	glBegin(GL_POLYGON);
	glVertex2f(21, 15);
	glVertex2f(-20, 15);
	glVertex2f(-20, 90);
	glVertex2f(21, 90);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(650, 40, 0);
	glScalef(-1, 1, 0);
	glScalef(1.25, 1, 0);
	tree1();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(660, 70, 0);
	tree2();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(660, 106, 0);
	glColor3f(0, 0.75, 0);
	tree3();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(660, 37, 0);
	glScalef(1.5, 1, 0);
	tree2();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(660, 73, 0);
	glScalef(1.5, 1, 0);
	glColor3f(0, 0.75, 0);
	tree3();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(660, 4, 0);
	glScalef(2, 1, 0);
	tree2();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(660, 38, 0);
	glScalef(2, 1, 0);
	if (dark % 2 == 0) {
		glColor3ub(13, 206, 235);
	}
	else {
		glColor3f(0, 0, 0);
	}
	tree3();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(660, 40, 0);
	glScalef(2, 1, 0);
	glColor3ub(128, 64, 0);
	tree_Bottom();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(660, 174, 0);
	glScalef(0.15, 0.15, 0);
	for (int i = 0; i < 5; i++) {
		FiveStar();
		glRotatef(72, 0.0f, 0.0f, 1.0f);

	}
	glPopMatrix();

	glPushMatrix();
	glTranslatef(665, 70, 0);
	glTranslatef(41, 36, 0);
	glColor3f(1, p15.y, 0);
	cicle_Tree();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(665, 70, 0);
	glTranslatef(-48, 36, 0);
	glColor3f(1, p15.y, 0);
	cicle_Tree();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(650, 40, 0);
	glTranslatef(66, 36, 0);
	glColor3f(1, p15.y, 0);
	cicle_Tree();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(650, 40, 0);
	glTranslatef(-48, 36, 0);
	glColor3f(1, p15.y, 0);
	cicle_Tree();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(660, 70, 0);
	glTranslatef(32, 54, 0);
	glColor3f(1, p15.x, 0);
	cicle_Tree();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(660, 70, 0);
	glTranslatef(-30, 54, 0);
	glColor3f(1, p15.x, 0);
	cicle_Tree();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(660, 37, 0);
	glTranslatef(39, 54, 0);
	glColor3f(1, p15.x, 0);
	cicle_Tree();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(660, 37, 0);
	glTranslatef(-39, 54, 0);
	glColor3f(1, p15.x, 0);
	cicle_Tree();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(660, 4, 0);
	glTranslatef(54, 54, 0);
	glColor3f(1, p15.x, 0);
	cicle_Tree();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(660, 4, 0);
	glTranslatef(-54, 54, 0);
	glColor3f(1, p15.x, 0);
	cicle_Tree();
	glPopMatrix();

}


void cloud() {
	glPushMatrix();
	glScalef(20, 8, 0);
	if (dark % 2 == 0) {
		glColor3f(1, 1, 1);
	}
	else {
		glColor3ub(148, 159, 189);
	}
	cicle_Tree();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(10, 20, 0);
	glScalef(9, 7, 0);
	if (dark % 2 == 0) {
		glColor3f(1, 1, 1);
	}
	else {
		glColor3ub(148, 159, 189);
	}
	cicle_Tree();
	glPopMatrix();
}

void cloud1() {
	glPushMatrix();
	glScalef(20, 8, 0);
	if (dark % 2 == 0) {
		glColor3f(1, 1, 1);
	}
	else {
		glColor3ub(148, 159, 189);
	}
	cicle_Tree();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-25, 17, 0);
	glScalef(9, 7, 0);
	if (dark % 2 == 0) {
		glColor3f(1, 1, 1);
	}
	else {
		glColor3ub(148, 159, 189);
	}
	cicle_Tree();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(17, -10, 0);
	glScalef(9, 7, 0);
	if (dark % 2 == 0) {
		glColor3f(1, 1, 1);
	}
	else {
		glColor3ub(148, 159, 189);
	}
	cicle_Tree();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(32, 20, 0);
	glScalef(9, 5, 0);
	if (dark % 2 == 0) {
		glColor3f(1, 1, 1);
	}
	else {
		glColor3ub(148, 159, 189);
	}
	cicle_Tree();
	glPopMatrix();
}

void cicle_Smile() {
	int i;
	float x, y;
	glScalef(0.05, 0.05, 0);
	glBegin(GL_POLYGON); 
	for (i = 0; i < 361; i = i + 5)
	{
		x = 100.0 * cos(i * (6.284 / 360.0));
		y = 100.0 * sin(i * (6.284 / 360.0));

		glVertex2f(x, y);
	}
	glEnd();


	glPushMatrix();
	glTranslatef(30, 30, 0);
	glColor3f(0, 0, 0);
	glBegin(GL_POLYGON); 
	for (i = 0; i < 361; i = i + 5)
	{
		x = 10.0 * cos(i * (6.284 / 360.0));
		y = 10.0 * sin(i * (6.284 / 360.0));

		glVertex2f(x, y);
	}
	glEnd();
	glPopMatrix();


	glPushMatrix();
	glTranslatef(0, -60, 0);
	glScalef(1, 1.5, 0);
	glColor3f(1, 0, 0);
	glBegin(GL_POLYGON);
	for (i = 90; i > 0; i = i - 5)
	{
		float j = 0;
		glVertex2f(0, 90);
		x = (float)i;
		y = 180 - 90 * sin(i * (6.284 / 360.0));
		j = i - 5;
		float xNext = j;
		float yNext = 180 - 90 * sin(j * (6.284 / 360.0));
		glVertex2f(x, y);
		glVertex2f(xNext, yNext);
	}

	for (i = 90; i > 0; i = i - 5)
	{
		float j = 0;
		glVertex2f(0, 90);
		x = -(float)i;
		y = 180 - 90 * sin(i * (6.284 / 360.0));
		j = i - 5;
		float xNext = -j;
		float yNext = 180 - 90 * sin(j * (6.284 / 360.0));
		glVertex2f(x, y);
		glVertex2f(xNext, yNext);
	}
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 210, 0);
	glColor3f(1, 1, 1);
	glBegin(GL_POLYGON); 
	for (i = 0; i < 361; i = i + 5)
	{
		x = 15.0 * cos(i * (6.284 / 360.0));
		y = 15.0 * sin(i * (6.284 / 360.0));

		glVertex2f(x, y);
	}
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(85, 75, 0);
	glColor3f(0.97, 0.97, 0.97);
	for (int k = 0; k < 8; k++) {
		glBegin(GL_POLYGON); 
		for (i = 0; i < 361; i = i + 5)
		{
			x = 15.0 * cos(i * (6.284 / 360.0));
			y = 15.0 * sin(i * (6.284 / 360.0));

			glVertex2f(x, y);
		}
		glEnd();
		glTranslatef(-25, 0, 0);
	}
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-30, 30, 0);
	glColor3f(0, 0, 0);
	glBegin(GL_POLYGON); 
	for (i = 0; i < 361; i = i + 5)
	{
		x = 10.0 * cos(i * (6.284 / 360.0));
		y = 10.0 * sin(i * (6.284 / 360.0));

		glVertex2f(x, y);
	}
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glColor3f(1, 0.4, 0);
	glBegin(GL_POLYGON); 
	for (i = 0; i < 361; i = i + 5)
	{
		x = 10.0 * cos(i * (6.284 / 360.0));
		y = 10.0 * sin(i * (6.284 / 360.0));

		glVertex2f(x, y);
	}
	glEnd();
	glPopMatrix();

	glColor3f(0, 0, 0);

	glPushMatrix();
	glTranslatef(0, -10, 0);
	glScalef(1, 0.7, 0);
	glBegin(GL_POLYGON);
	for (i = 180; i < 361; i = i + 5)
	{

		x = 50.0 * cos(i * (6.284 / 360.0));
		y = 50.0 * sin(i * (6.284 / 360.0));

		glVertex2f(x, y);

	}
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(1, 1, 1);
	for (i = 180; i < 361; i = i + 5)
	{

		x = 47.0 * cos(i * (6.284 / 360.0));
		y = 47.0 * sin(i * (6.284 / 360.0));

		glVertex2f(x, y);

	}
	glEnd();
	glPopMatrix();


}

void cicle_Fly() {
	int i;
	float x, y;
	glPushMatrix();
	glColor3f(1, 0.2, 0);
	glBegin(GL_POLYGON); 
	for (i = 0; i < 361; i = i + 5)
	{
		x = 6.0 * cos(i * (6.284 / 360.0));
		y = 6.0 * sin(i * (6.284 / 360.0));

		glVertex2f(x, y);
	}
	glEnd();
	glPopMatrix();
}
void snowMan() {
	glPushMatrix();
	glScalef(11, 11, 0);
	glTranslatef(0, 12, 0);
	glColor3f(1, 1, 1);
	cicle_Smile();
	glPopMatrix();


	glPushMatrix();
	glScalef(20, 20, 0);
	glColor3f(1, 1, 1);
	cicle_Tree();
	glPopMatrix();

	//hand
	glPushMatrix();
	glTranslatef(20, 0, 0);
	if (dark % 2 == 0) {
		glColor3f(0, 0, 0);
	}
	else {
		glColor3f(1, 0.5, 0);
	}

	glBegin(GL_POLYGON); 

	glVertex2f(47, 53);
	
	glVertex2f(53, 47);

	glVertex2f(126, 124);
	glVertex2f(124, 126);

	glEnd();

	glColor3f(1, 1, 0);
	glBegin(GL_POLYGON); 
	//The fireworks stick in the snowman's hand
	glVertex2f(144, 161);
	glVertex2f(146, 159);
	glVertex2f(116, 107);
	glVertex2f(114, 109);
	glEnd();

	glPopMatrix();

	//hand
	glPushMatrix();
	glTranslatef(-20, 0, 0);
	glScalef(-1, 1, 0);
	if (dark % 2 == 0) {
		glColor3f(0, 0, 0);
	}
	else {
		glColor3f(1, 0.5, 0);
	}

	glBegin(GL_POLYGON); 

	glVertex2f(47, 53);
	glVertex2f(53, 47);

	glVertex2f(126, 124);
	glVertex2f(124, 126);

	glEnd();

	glColor3f(1, 1, 0);
	glBegin(GL_POLYGON); 
	//The fireworks stick in the snowman's hand
	glVertex2f(144, 161);
	glVertex2f(146, 159);
	glVertex2f(116, 107);
	glVertex2f(114, 109);
	glEnd();
	glPopMatrix();

}

//The fireworks in the snowman's hand
void Water_Forfly() {
	int i;
	float x, y;
	glColor3f(1, 0.2, 0);
	glPushMatrix();
	glScalef(10, 10, 0);
	glBegin(GL_POLYGON); 
	for (i = 0; i < 361; i = i + 5)
	{
		x = (3 * (1 + cos(i * (6.284 / 360.0))) * (2 + cos(i * (6.284 / 360.0)))) / (5 + 4 * cos(i * (6.284 / 360.0))) * (p10.x/ 100);
		y = (3 * (1 + cos(i * (6.284 / 360.0))) * sin(i * (6.284 / 360.0))) / (5 + 4 * cos(i * (6.284 / 360.0))) * (p10.y/ 100);

		glVertex2f(x, y);
	}
	glEnd();
	glPopMatrix();
}
//The fireworks in the snowman's hand
void Water_Forfly1() {
	int i;
	float x, y;
	glColor3f(1, 0.2, 0);
	glPushMatrix();
	glScalef(10, 10, 0);
	glBegin(GL_POLYGON); 
	for (i = 0; i < 361; i = i + 5)
	{
		x = (3 * (1 + cos(i * (6.284 / 360.0))) * (2 + cos(i * (6.284 / 360.0)))) / (5 + 4 * cos(i * (6.284 / 360.0))) * (p18.x / 100);
		y = (3 * (1 + cos(i * (6.284 / 360.0))) * sin(i * (6.284 / 360.0))) / (5 + 4 * cos(i * (6.284 / 360.0))) * (p18.y / 100);

		glVertex2f(x, y);
	}
	glEnd();
	glPopMatrix();
}

//Suzhou tower
void beisita() {
	int i;
	int k = 0;
	float x, y;

	float point;



	glPushMatrix();
	point = -0.5 * 90 * sin(60 * (6.284 / 360.0));
	glColor3f(0.2, 0.2, 0.2);
	glBegin(GL_POLYGON); 
	glVertex2f(0, 0);
	glVertex2f(0, 45);
	glVertex2f(72, 45);
	glVertex2f(72, 0);
	glEnd();

	glBegin(GL_POLYGON); 
	glVertex2f(-36, 0);
	glVertex2f(-48, point);
	glVertex2f(120, point);
	glVertex2f(108, 0);
	glEnd();
	glPopMatrix();

	if (dark % 2 == 1) {
		//Mid-area Lights
		glPushMatrix();
		point = -0.5 * 90 * sin(60 * (6.284 / 360.0));
		glTranslatef(18, (45 + point) / 2, 0);
		glScalef(0.2, 1, 0);
		glColor3f(1, 1, 0);
		glBegin(GL_POLYGON); 
		for (i = 90; i > -90; i = i - 5)
		{
			float j = 0;
			glVertex2f(90 - 6, -(45 - point) / 2);
			x = (float)i;
			y = ((45 - point) / 2) * sin(i * (6.284 / 360.0));
			j = i - 5;
			float xNext = j;
			float yNext = ((45 - point) / 2) * sin(j * (6.284 / 360.0));
			glVertex2f(x - 6, y);
			glVertex2f(xNext - 6, yNext);
		}
		glEnd();
		glPopMatrix();

		glPushMatrix();
		point = -0.5 * 90 * sin(60 * (6.284 / 360.0));
		glTranslatef(54, (45 + point) / 2, 0);
		glScalef(-0.2, 1, 0);
		glColor3f(1, 1, 0);
		glBegin(GL_POLYGON);
		for (i = 90; i > -90; i = i - 5)
		{
			float j = 0;
			glVertex2f(90 - 6, -(45 - point) / 2);
			x = (float)i;
			y = ((45 - point) / 2) * sin(i * (6.284 / 360.0));
			j = i - 5;
			float xNext = j;
			float yNext = ((45 - point) / 2) * sin(j * (6.284 / 360.0));
			glVertex2f(x - 6, y);
			glVertex2f(xNext - 6, yNext);
		}
		glEnd();
		glPopMatrix();
	}
	


	//Mid-area
	glPushMatrix();
	point = -0.5 * 90 * sin(60 * (6.284 / 360.0));
	glTranslatef(18, (45 + point) / 2, 0);
	glScalef(0.2, 1, 0);
	glColor3f(0, 0, 0);
	glBegin(GL_POLYGON);
	for (i = 90; i > -90; i = i - 5)
	{
		float j = 0;
		glVertex2f(90, -(45 - point) / 2);
		x = (float)i;
		y = ((45 - point) / 2) * sin(i * (6.284 / 360.0));
		j = i - 5;
		float xNext = j;
		float yNext = ((45 - point) / 2) * sin(j * (6.284 / 360.0));
		glVertex2f(x, y);
		glVertex2f(xNext, yNext);
	}
	glEnd();
	glPopMatrix();

	glPushMatrix();
	point = -0.5 * 90 * sin(60 * (6.284 / 360.0));
	glTranslatef(54, (45 + point) / 2, 0);
	glScalef(-0.2, 1, 0);
	glColor3f(0, 0, 0);
	glBegin(GL_POLYGON);
	for (i = 90; i > -90; i = i - 5)
	{
		float j = 0;
		glVertex2f(90, -(45 - point) / 2);
		x = (float)i;
		y = ((45 - point) / 2) * sin(i * (6.284 / 360.0));
		j = i - 5;
		float xNext = j;
		float yNext = ((45 - point) / 2) * sin(j * (6.284 / 360.0));
		glVertex2f(x, y);
		glVertex2f(xNext, yNext);
	}
	glEnd();
	glPopMatrix();

	glPushMatrix();
	point = -0.5 * 90 * sin(60 * (6.284 / 360.0));
	glTranslatef(36, point, 0);
	glColor3f(0.2, 0.2, 0.2);
	glBegin(GL_POLYGON);
    glVertex2f(84, 0);
	glVertex2f(60, -11.5);
	glVertex2f(36, 0);
	glEnd();

	glColor3f(0, 0, 0);
	glBegin(GL_POLYGON); 
	glVertex2f(36, 0);
	glVertex2f(0, -11.5);
	glVertex2f(-36, 0);
	glEnd();

	glColor3f(0.2, 0.2, 0.2);
	glBegin(GL_POLYGON);
	glVertex2f(-36, 0);
	glVertex2f(-60, -11.5);
	glVertex2f(-84, 0);
	glEnd();

	glPopMatrix();


	if (dark % 2 == 1) {
		//Lights
		glPushMatrix();
		glTranslatef(1.5, 0, 0);
		glColor3f(1, 1, 0);
		glScalef(0.4, 0.5, 0);
		glBegin(GL_POLYGON);
		for (i = 90; i > 0; i = i - 5)
		{
			float j = 0;
			glVertex2f(0, 90);
			x = (float)i;
			y = 90 * sin(i * (6.284 / 360.0));
			j = i - 5;
			float xNext = j;
			float yNext = 90 * sin(j * (6.284 / 360.0));
			glVertex2f(x, y);
			glVertex2f(xNext, yNext);
		}
		glEnd();
		glPopMatrix();

		glPushMatrix();
		glTranslatef(1.5, 0, 0);
		glColor3f(1, 1, 0);
		glScalef(0.4, 0.5, 0);
		glScalef(-1, -1, 0);
		glBegin(GL_POLYGON);
		for (i = 120; i > 0; i = i - 5)
		{
			float j = 0;
			glVertex2f(90, 0);
			x = (float)i;
			y = 90 * sin(i * (6.284 / 360.0));
			j = i - 5;
			float xNext = j;
			float yNext = 90 * sin(j * (6.284 / 360.0));
			glVertex2f(x, y);
			glVertex2f(xNext, yNext);
		}
		glEnd();
		glPopMatrix();

		glPushMatrix();
		glTranslatef(70, 0, 0);
		glColor3f(1, 1, 0);
		glScalef(-1, 1, 0);
		glScalef(0.4, 0.5, 0);
		glBegin(GL_POLYGON);
		for (i = 90; i > 0; i = i - 5)
		{
			float j = 0;
			glVertex2f(0, 90);
			x = (float)i;
			y = 90 * sin(i * (6.284 / 360.0));
			j = i - 5;
			float xNext = j;
			float yNext = 90 * sin(j * (6.284 / 360.0));
			glVertex2f(x, y);
			glVertex2f(xNext, yNext);
		}
		glEnd();
		glPopMatrix();


		glPushMatrix();
		glTranslatef(70, 0, 0);
		glColor3f(1, 1, 0);
		glScalef(0.4, 0.5, 0);
		glScalef(-1, -1, 0);
		glScalef(-1, 1, 0);
		glBegin(GL_POLYGON);
		for (i = 120; i > 0; i = i - 5)
		{
			float j = 0;
			glVertex2f(90, 0);
			x = (float)i;
			y = 90 * sin(i * (6.284 / 360.0));
			j = i - 5;
			float xNext = j;
			float yNext = 90 * sin(j * (6.284 / 360.0));
			glVertex2f(x, y);
			glVertex2f(xNext, yNext);
		}
		glEnd();
		glPopMatrix();
		//Lights
	}
	

	glPushMatrix();
	glTranslatef(0, 0, 0);
	if (dark % 2 == 0) {
		glColor3ub(13, 206, 235);
	}
	else {
		glColor3f(0, 0, 0);
	}
	glScalef(0.4, 0.5, 0);
	glBegin(GL_POLYGON);
	for (i = 90; i > 0; i = i - 5)
	{
		float j = 0;
		glVertex2f(0, 90);
		x = (float)i;
		y = 90 * sin(i * (6.284 / 360.0));
		j = i - 5;
		float xNext = j;
		float yNext = 90 * sin(j * (6.284 / 360.0));
		glVertex2f(x, y);
		glVertex2f(xNext, yNext);
	}
	glEnd();
	glPopMatrix();


	glPushMatrix();
	glTranslatef(0, 0, 0);
	if (dark % 2 == 0) {
		glColor3ub(13, 206, 235);
	}
	else {
		glColor3f(0, 0, 0);
	}
	glScalef(0.4, 0.5, 0);
	glScalef(-1, -1, 0);
	glBegin(GL_POLYGON);
	for (i = 120; i > 0; i = i - 5)
	{
		float j = 0;
		glVertex2f(90, 0);
		x = (float)i;
		y = 90 * sin(i * (6.284 / 360.0));
		j = i - 5;
		float xNext = j;
		float yNext = 90 * sin(j * (6.284 / 360.0));
		glVertex2f(x, y);
		glVertex2f(xNext, yNext);
	}
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(72, 0, 0);
	if (dark % 2 == 0) {
		glColor3ub(13, 206, 235);
	}
	else {
		glColor3f(0, 0, 0);
	}
	glScalef(-1, 1, 0);
	glScalef(0.4, 0.5, 0);
	glBegin(GL_POLYGON);
	for (i = 90; i > 0; i = i - 5)
	{
		float j = 0;
		glVertex2f(0, 90);
		x = (float)i;
		y = 90 * sin(i * (6.284 / 360.0));
		j = i - 5;
		float xNext = j;
		float yNext = 90 * sin(j * (6.284 / 360.0));
		glVertex2f(x, y);
		glVertex2f(xNext, yNext);
	}
	glEnd();
	glPopMatrix();


	glPushMatrix();
	glTranslatef(72, 0, 0);
	if (dark % 2 == 0) {
		glColor3ub(13, 206, 235);
	}
	else {
		glColor3f(0, 0, 0);
	}
	glScalef(0.4, 0.5, 0);
	glScalef(-1, -1, 0);
	glScalef(-1, 1, 0);
	glBegin(GL_POLYGON);
	for (i = 120; i > 0; i = i - 5)
	{
		float j = 0;
		glVertex2f(90, 0);
		x = (float)i;
		y = 90 * sin(i * (6.284 / 360.0));
		j = i - 5;
		float xNext = j;
		float yNext = 90 * sin(j * (6.284 / 360.0));
		glVertex2f(x, y);
		glVertex2f(xNext, yNext);
	}
	glEnd();
	glPopMatrix();



	glPushMatrix();
	point = -0.5 * 90 * sin(60 * (6.284 / 360.0));
	glTranslatef(36, point, 0);
	glColor3f(1, 1, 1);
	glBegin(GL_POLYGON); 
	glVertex2f(62, -60);
	glVertex2f(60, -11.5);
	glVertex2f(36, 0);
	glVertex2f(0, -11.5);
	glVertex2f(0, -60);
	glEnd();

	glBegin(GL_POLYGON); 
	glVertex2f(-62, -60);
	glVertex2f(-60, -11.5);
	glVertex2f(-36, 0);
	glVertex2f(0, -11.5);
	glVertex2f(0, -60);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	point = -0.5 * 90 * sin(60 * (6.284 / 360.0));
	glTranslatef(36, point, 0);
	
	glColor3ub(186, 51, 55);
	glBegin(GL_POLYGON); 
	glVertex2f(62, -55);
	glVertex2f(60, -11.5);
	glVertex2f(36, 0);
	glVertex2f(37, -56);
	glEnd();

	glColor3ub(166, 51, 55);
	glBegin(GL_POLYGON); 
	glVertex2f(-36, 0);
	glVertex2f(-37, -56);
	glVertex2f(0, -57);
	glVertex2f(0, -11.5);
	glEnd();

	glColor3ub(166, 51, 55);
	glBegin(GL_POLYGON); 
	glVertex2f(36, 0);
	glVertex2f(37, -56);
	glVertex2f(0, -57);
	glVertex2f(0, -11.5);
	glEnd();


	glColor3ub(186, 51, 55);
	glBegin(GL_POLYGON); 
	glVertex2f(-62, -55);
	glVertex2f(-60, -11.5);
	glVertex2f(-36, 0);
	glVertex2f(-37, -56);
	glEnd();

	if (dark % 2 == 0) {
		glColor3f(1, 1, 1);
	}
	else {
		glColor3f(1, 0.8, 0);
	}
	glBegin(GL_POLYGON); 
	glVertex2f(57.5, -45);
	glVertex2f(57, -21);
	glVertex2f(46, -19);
	glVertex2f(46, -46);
	glEnd();

	if (dark % 2 == 0) {
		glColor3f(1, 1, 1);
	}
	else {
		glColor3f(1, 0.8, 0);
	}
	glBegin(GL_POLYGON);
	glVertex2f(-57.5, -45);
	glVertex2f(-57, -21);
	glVertex2f(-46, -19);
	glVertex2f(-46, -46);
	glEnd();

	if (dark % 2 == 0) {
		glColor3f(1, 1, 1);
	}
	else {
		glColor3f(1, 0.8, 0);
	}
	glBegin(GL_POLYGON); 
	glVertex2f(-22, -46);
	glVertex2f(-21, -19);
	glVertex2f(21, -19);
	glVertex2f(22, -46);
	glEnd();

	glPopMatrix();



	if (dark % 2 == 1) {
		//Spire Lights
		glPushMatrix();
		glTranslatef(36, 48, 0);
		glScalef(1, 1, 0);
		glColor3f(1, 1, 0);
		glBegin(GL_POLYGON); 
		for (i = 0; i < 361; i = i + 5)
		{
			x = 7 * cos(i * (6.284 / 360.0));
			y = 7 * sin(i * (6.284 / 360.0));

			glVertex2f(x, y);

		}
		glEnd();
		glPopMatrix();

		//Spire Lights
		glPushMatrix();
		glTranslatef(36, 72, 0);
		glScalef(1.3, 1, 0);
		glColor3f(1, 1, 0);
		glBegin(GL_POLYGON); 
		for (i = 0; i < 361; i = i + 5)
		{
			x = 4.0 * cos(i * (6.284 / 360.0));
			y = 18.0 * sin(i * (6.284 / 360.0));

			glVertex2f(x, y);

		}
		glEnd();
		glPopMatrix();
		////
	}
	



	//Spire
	glPushMatrix();
	glTranslatef(36, 48, 0);
	glScalef(1, 1, 0);
	glColor3f(0.1, 0.1, 0.1);
	glBegin(GL_POLYGON); 
	for (i = 0; i < 361; i = i + 5)
	{
		x = 6.0 * cos(i * (6.284 / 360.0));
		y = 6.0 * sin(i * (6.284 / 360.0));

		glVertex2f(x, y);

	}
	glEnd();
	glPopMatrix();

	//Spire
	glPushMatrix();
	glTranslatef(36, 71, 0);
	glScalef(1, 1, 0);
	glColor3f(0, 0, 0);
	glBegin(GL_POLYGON); 
	for (i = 0; i < 361; i = i + 5)
	{
		x = 4.0 * cos(i * (6.284 / 360.0));
		y = 18.0 * sin(i * (6.284 / 360.0));

		glVertex2f(x, y);

	}
	glEnd();
	glPopMatrix();


	if (dark % 2 == 1) {
		//First floor Lights
		glPushMatrix();
		glColor3f(1, 1, 0);
		point = -0.5 * 90 * sin(60 * (6.284 / 360.0));

		glTranslatef(-24, point - 1, 0);
		glScalef(1, 0.5, 0);
		glBegin(GL_POLYGON); 
		for (i = 180; i < 361; i = i + 5)
		{
			float j = 0;
			glVertex2f(-0, -23);
			j = (float)i;
			x = 24.0 * cos(i * (6.284 / 360.0));
			y = 24.0 * sin(i * (6.284 / 360.0));
			j = i + 5;
			float xNext = 24.0 * cos(j * (6.284 / 360.0));;
			float yNext = 24 * sin(j * (6.284 / 360.0));
			glVertex2f(x, y);
			glVertex2f(xNext, yNext);

		}
		glEnd();
		glPopMatrix();

		glPushMatrix();
		glColor3f(1, 1, 0);
		point = -0.5 * 90 * sin(60 * (6.284 / 360.0));

		glTranslatef(36, point - 1, 0);
		glScalef(1.5, 0.5, 0);
		glBegin(GL_POLYGON); 
		for (i = 180; i < 361; i = i + 5)
		{
			float j = 0;
			glVertex2f(-0, -23);
			j = (float)i;
			x = 24.0 * cos(i * (6.284 / 360.0));
			y = 24.0 * sin(i * (6.284 / 360.0));
			j = i + 5;
			float xNext = 24.0 * cos(j * (6.284 / 360.0));;
			float yNext = 24 * sin(j * (6.284 / 360.0));
			glVertex2f(x, y);
			glVertex2f(xNext, yNext);

		}
		glEnd();
		glPopMatrix();

		glPushMatrix();
		glColor3f(1, 1, 0);
		point = -0.5 * 90 * sin(60 * (6.284 / 360.0));

		glTranslatef(96, point - 1, 0);
		glScalef(1, 0.5, 0);
		glBegin(GL_POLYGON); 
		for (i = 180; i < 361; i = i + 5)
		{
			float j = 0;
			glVertex2f(-0, -23);
			j = (float)i;
			x = 24.0 * cos(i * (6.284 / 360.0));
			y = 24.0 * sin(i * (6.284 / 360.0));
			j = i + 5;
			float xNext = 24.0 * cos(j * (6.284 / 360.0));;
			float yNext = 24 * sin(j * (6.284 / 360.0));
			glVertex2f(x, y);
			glVertex2f(xNext, yNext);

		}
		glEnd();
		glPopMatrix();
		////
	}
	



	//First floor
	glPushMatrix();
	glColor3f(0.2, 0.2, 0.2);
	point = -0.5 * 90 * sin(60 * (6.284 / 360.0));
	
	glTranslatef(-24, point, 0);
	glScalef(1, 0.5, 0);
	glBegin(GL_POLYGON);
	for (i = 180; i < 361; i = i + 5)
	{
		float j = 0;
		glVertex2f(-0, -23);
		j = (float)i;
		x = 24.0 * cos(i * (6.284 / 360.0));
		y = 24.0 * sin(i * (6.284 / 360.0));
		j = i + 5;
		float xNext = 24.0 * cos(j * (6.284 / 360.0));;
		float yNext = 24 * sin(j * (6.284 / 360.0));
		glVertex2f(x, y);
		glVertex2f(xNext, yNext);
			
	}
	glEnd();
    glPopMatrix();

	glPushMatrix();
	glColor3f(0, 0, 0);
	point = -0.5 * 90 * sin(60 * (6.284 / 360.0));

	glTranslatef(36, point, 0);
	glScalef(1.5, 0.5, 0);
	glBegin(GL_POLYGON);
	for (i = 180; i < 361; i = i + 5)
	{
		float j = 0;
		glVertex2f(-0, -23);
		j = (float)i;
		x = 24.0 * cos(i * (6.284 / 360.0));
		y = 24.0 * sin(i * (6.284 / 360.0));
		j = i + 5;
		float xNext = 24.0 * cos(j * (6.284 / 360.0));;
		float yNext = 24 * sin(j * (6.284 / 360.0));
		glVertex2f(x, y);
		glVertex2f(xNext, yNext);

	}
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.2, 0.2, 0.2);
	point = -0.5 * 90 * sin(60 * (6.284 / 360.0));

	glTranslatef(96, point, 0);
	glScalef(1, 0.5, 0);
	glBegin(GL_POLYGON); 
	for (i = 180; i < 361; i = i + 5)
	{
		float j = 0;
		glVertex2f(-0, -23);
		j = (float)i;
		x = 24.0 * cos(i * (6.284 / 360.0));
		y = 24.0 * sin(i * (6.284 / 360.0));
		j = i + 5;
		float xNext = 24.0 * cos(j * (6.284 / 360.0));;
		float yNext = 24 * sin(j * (6.284 / 360.0));
		glVertex2f(x, y);
		glVertex2f(xNext, yNext);

	}
	glEnd();
	glPopMatrix();


//
	glPushMatrix();
	glTranslatef(36, point, 0);
	glColor3f(1, 1, 1);
	glBegin(GL_POLYGON); 
	glVertex2f(62, -60);
	glVertex2f(64, -120);
	glVertex2f(-64, -120);
	glVertex2f(-62, -60);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(36, point, 0);
	glColor3ub(186, 51, 55);
	glBegin(GL_POLYGON); 
	glVertex2f(62, -60);
	glVertex2f(64, -115);
	glVertex2f(0, -117);
	glVertex2f(-64, -115);
	glVertex2f(-62, -60);
	glEnd();

	glColor3ub(166, 51, 55);
	glBegin(GL_POLYGON); 
	glVertex2f(37, -60);
	glVertex2f(38, -116);
	glVertex2f(0, -117);
	glVertex2f(-38, -116);
	glVertex2f(-37, -60);
	glEnd();

	if (dark % 2 == 0) {
		glColor3f(1, 1, 1);
	}
	else {
		glColor3f(1, 0.8, 0);
	}
	glBegin(GL_POLYGON); 
	glVertex2f(58.5, -105);
	glVertex2f(58, -81);
	glVertex2f(46, -79);
	glVertex2f(46, -106);
	glEnd();

	if (dark % 2 == 0) {
		glColor3f(1, 1, 1);
	}
	else {
		glColor3f(1, 0.8, 0);
	}
	glBegin(GL_POLYGON); 
	glVertex2f(-58.5, -105);
	glVertex2f(-58, -81);
	glVertex2f(-46, -79);
	glVertex2f(-46, -106);
	glEnd();

	if (dark % 2 == 0) {
		glColor3f(1, 1, 1);
	}
	else {
		glColor3f(1, 0.8, 0);
	}
	glBegin(GL_POLYGON); 
	glVertex2f(-23, -106);
	glVertex2f(-22, -79);
	glVertex2f(22, -79);
	glVertex2f(23, -106);
	glEnd();

	glPopMatrix();



	if (dark % 2 == 1) {
		//Secons Lights
		glPushMatrix();
		glColor3f(1, 1, 0);
		point = -0.5 * 90 * sin(60 * (6.284 / 360.0));
		glTranslatef(-25, point - 60 - 1, 0);
		glScalef(1, 0.3, 0);
		glBegin(GL_POLYGON); 
		for (i = 180; i < 360; i = i + 5)
		{
			float j = 0;
			glVertex2f(0, 0);
			j = (float)i;
			x = 25.0 * cos(i * (6.284 / 360.0));
			y = 25.0 * sin(i * (6.284 / 360.0));
			j = i + 5;
			float xNext = 25.0 * cos(j * (6.284 / 360.0));;
			float yNext = 25 * sin(j * (6.284 / 360.0));
			glVertex2f(x, y);
			glVertex2f(xNext, yNext);

		}
		glEnd();
		glPopMatrix();

		glPushMatrix();
		glColor3f(1, 1, 0);
		point = -0.5 * 90 * sin(60 * (6.284 / 360.0));

		glTranslatef(37, point - 60 - 1, 0);
		glScalef(1.5, 0.5, 0);
		glBegin(GL_POLYGON); 
		for (i = 180; i < 360; i = i + 5)
		{
			float j = 0;
			glVertex2f(0, 0);
			j = (float)i;
			x = 24.66 * cos(i * (6.284 / 360.0));
			y = 24.66 * sin(i * (6.284 / 360.0));
			j = i + 5;
			float xNext = 24.66 * cos(j * (6.284 / 360.0));;
			float yNext = 24.66 * sin(j * (6.284 / 360.0));
			glVertex2f(x, y);
			glVertex2f(xNext, yNext);

		}
		glEnd();
		glPopMatrix();

		glPushMatrix();
		glColor3f(1, 1, 1);
		point = -0.5 * 90 * sin(60 * (6.284 / 360.0));

		glTranslatef(99, point - 60 - 1, 0);
		glScalef(1, 0.3, 0);
		glBegin(GL_POLYGON); 
		for (i = 180; i < 360; i = i + 5)
		{
			float j = 0;
			glVertex2f(0, 0);
			j = (float)i;
			x = 25.0 * cos(i * (6.284 / 360.0));
			y = 25.0 * sin(i * (6.284 / 360.0));
			j = i + 5;
			float xNext = 25.0 * cos(j * (6.284 / 360.0));;
			float yNext = 25 * sin(j * (6.284 / 360.0));
			glVertex2f(x, y);
			glVertex2f(xNext, yNext);

		}
		glEnd();
		glPopMatrix();
		////
	}
	


	glPushMatrix();
	glColor3f(0.2, 0.2, 0.2);
	point = -0.5 * 90 * sin(60 * (6.284 / 360.0));
	glTranslatef(-25, point - 60, 0);
	glScalef(1, 0.3, 0);
	glBegin(GL_POLYGON); 
	for (i = 180; i < 360; i = i + 5)
	{
		float j = 0;
		glVertex2f(0, 0);
		j = (float)i;
		x = 25.0 * cos(i * (6.284 / 360.0));
		y = 25.0 * sin(i * (6.284 / 360.0));
		j = i + 5;
		float xNext = 25.0 * cos(j * (6.284 / 360.0));;
		float yNext = 25 * sin(j * (6.284 / 360.0));
		glVertex2f(x, y);
		glVertex2f(xNext, yNext);

	}
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glColor3f(0, 0, 0);
	point = -0.5 * 90 * sin(60 * (6.284 / 360.0));

	glTranslatef(37, point - 60, 0);
	glScalef(1.5, 0.5, 0);
	glBegin(GL_POLYGON); 
	for (i = 180; i < 360; i = i + 5)
	{
		float j = 0;
		glVertex2f(0, 0);
		j = (float)i;
		x = 24.66 * cos(i * (6.284 / 360.0));
		y = 24.66 * sin(i * (6.284 / 360.0));
		j = i + 5;
		float xNext = 24.66 * cos(j * (6.284 / 360.0));;
		float yNext = 24.66 * sin(j * (6.284 / 360.0));
		glVertex2f(x, y);
		glVertex2f(xNext, yNext);

	}
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.2, 0.2, 0.2);
	point = -0.5 * 90 * sin(60 * (6.284 / 360.0));

	glTranslatef(99, point - 60, 0);
	glScalef(1, 0.3, 0);
	glBegin(GL_POLYGON); 
	for (i = 180; i < 360; i = i + 5)
	{
		float j = 0;
		glVertex2f(0, 0);
		j = (float)i;
		x = 25.0 * cos(i * (6.284 / 360.0));
		y = 25.0 * sin(i * (6.284 / 360.0));
		j = i + 5;
		float xNext = 25.0 * cos(j * (6.284 / 360.0));;
		float yNext = 25 * sin(j * (6.284 / 360.0));
		glVertex2f(x, y);
		glVertex2f(xNext, yNext);

	}
	glEnd();
	glPopMatrix();

	glPushMatrix();
	if (dark % 2 == 0) {
		glColor3ub(13, 206, 235);
	}
	else {
		glColor3f(0, 0, 0);
	}
	point = -0.5 * 90 * sin(60 * (6.284 / 360.0));

	glTranslatef(-37.5, point - 60, 0);
	glScalef(1, 0.25, 0);
	glBegin(GL_POLYGON); 
	for (i = 180; i < 381; i = i + 5)
	{
		float j = 0;
		glVertex2f(0, 0);
		j = (float)i;
		x = 12.5 * cos(i * (6.284 / 360.0));
		y = 12.5 * sin(i * (6.284 / 360.0));
		j = i + 5;
		float xNext = 12.5 * cos(j * (6.284 / 360.0));;
		float yNext = 12.5 * sin(j * (6.284 / 360.0));
		glVertex2f(x, y);
		glVertex2f(xNext, yNext);

	}
	glEnd();
	glPopMatrix();

	glPushMatrix();
	if (dark % 2 == 0) {
		glColor3ub(13, 206, 235);
	}
	else {
		glColor3f(0, 0, 0);
	}
	point = -0.5 * 90 * sin(60 * (6.284 / 360.0));

	glTranslatef(111.5, point - 60, 0);
	glScalef(1, 0.25, 0);
	glBegin(GL_POLYGON); 
	for (i = 180; i < 381; i = i + 5)
	{
		float j = 0;
		glVertex2f(0, 0);
		j = (float)i;
		x = 12.5 * cos(i * (6.284 / 360.0));
		y = 12.5 * sin(i * (6.284 / 360.0));
		j = i + 5;
		float xNext = 12.5 * cos(j * (6.284 / 360.0));;
		float yNext = 12.5 * sin(j * (6.284 / 360.0));
		glVertex2f(x, y);
		glVertex2f(xNext, yNext);

	}
	glEnd();
	glPopMatrix();

//Third floor
	glPushMatrix();
	glTranslatef(36, point, 0);
	glColor3f(1, 1, 1);
	glBegin(GL_POLYGON); 
	glVertex2f(64, -120);
	glVertex2f(66, -180);
	glVertex2f(-66, -180);
	glVertex2f(-64, -120);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(36, point, 0);
	glColor3ub(186, 51, 55);
	glBegin(GL_POLYGON); 
	glVertex2f(64, -120);
	glVertex2f(66, -175);
	glVertex2f(0, -177);
	glVertex2f(-66, -175);
	glVertex2f(-64, -120);
	glEnd();

	glColor3ub(166, 51, 55);
	glBegin(GL_POLYGON); 
	glVertex2f(38, -120);
	glVertex2f(39, -176);
	glVertex2f(0, -177);
	glVertex2f(-39, -176);
	glVertex2f(-38, -120);
	glEnd();

	if (dark % 2 == 0) {
		glColor3f(1, 1, 1);
	}
	else {
		glColor3f(1, 0.8, 0);
	}
	glBegin(GL_POLYGON); 
	glVertex2f(59.5, -165);
	glVertex2f(59, -141);
	glVertex2f(46, -139);
	glVertex2f(46, -166);
	glEnd();

	if (dark % 2 == 0) {
		glColor3f(1, 1, 1);
	}
	else {
		glColor3f(1, 0.8, 0);
	}
	glBegin(GL_POLYGON); 
	glVertex2f(-59.5, -165);
	glVertex2f(-59, -141);
	glVertex2f(-46, -139);
	glVertex2f(-46, -166);
	glEnd();

	if (dark % 2 == 0) {
		glColor3f(1, 1, 1);
	}
	else {
		glColor3f(1, 0.8, 0);
	}
	glBegin(GL_POLYGON); 
	glVertex2f(-24, -166);
	glVertex2f(-23, -139);
	glVertex2f(23, -139);
	glVertex2f(24, -166);
	glEnd();
	glPopMatrix();


	if (dark % 2 == 1) {
		//Third floor Lights
		glPushMatrix();
		glColor3f(1, 1, 0);
		point = -0.5 * 90 * sin(60 * (6.284 / 360.0));
		glTranslatef(-26, point - 120 - 1, 0);
		glScalef(1, 0.3, 0);
		glBegin(GL_POLYGON);
		for (i = 180; i < 360; i = i + 5)
		{
			float j = 0;
			glVertex2f(0, 0);
			j = (float)i;
			x = 26.0 * cos(i * (6.284 / 360.0));
			y = 26.0 * sin(i * (6.284 / 360.0));
			j = i + 5;
			float xNext = 26.0 * cos(j * (6.284 / 360.0));;
			float yNext = 26 * sin(j * (6.284 / 360.0));
			glVertex2f(x, y);
			glVertex2f(xNext, yNext);

		}
		glEnd();
		glPopMatrix();

		glPushMatrix();
		glColor3f(1, 1, 0);
		point = -0.5 * 90 * sin(60 * (6.284 / 360.0));

		glTranslatef(38, point - 120 - 1, 0);
		glScalef(1.5, 0.5, 0);
		glBegin(GL_POLYGON); 
		for (i = 180; i < 360; i = i + 5)
		{
			float j = 0;
			glVertex2f(0, 0);
			j = (float)i;
			x = 25.33 * cos(i * (6.284 / 360.0));
			y = 25.33 * sin(i * (6.284 / 360.0));
			j = i + 5;
			float xNext = 25.33 * cos(j * (6.284 / 360.0));;
			float yNext = 25.33 * sin(j * (6.284 / 360.0));
			glVertex2f(x, y);
			glVertex2f(xNext, yNext);

		}
		glEnd();
		glPopMatrix();

		glPushMatrix();
		glColor3f(1, 1, 0);
		point = -0.5 * 90 * sin(60 * (6.284 / 360.0));

		glTranslatef(102, point - 120 - 1, 0);
		glScalef(1, 0.3, 0);
		glBegin(GL_POLYGON); 
		for (i = 180; i < 360; i = i + 5)
		{
			float j = 0;
			glVertex2f(0, 0);
			j = (float)i;
			x = 26.0 * cos(i * (6.284 / 360.0));
			y = 26.0 * sin(i * (6.284 / 360.0));
			j = i + 5;
			float xNext = 26.0 * cos(j * (6.284 / 360.0));;
			float yNext = 26 * sin(j * (6.284 / 360.0));
			glVertex2f(x, y);
			glVertex2f(xNext, yNext);

		}
		glEnd();
		glPopMatrix();
		////
	}
	


	glPushMatrix();
	glColor3f(0.2, 0.2, 0.2);
	point = -0.5 * 90 * sin(60 * (6.284 / 360.0));
	glTranslatef(-26, point - 120, 0);
	glScalef(1, 0.3, 0);
	glBegin(GL_POLYGON); 
	for (i = 180; i < 360; i = i + 5)
	{
		float j = 0;
		glVertex2f(0, 0);
		j = (float)i;
		x = 26.0 * cos(i * (6.284 / 360.0));
		y = 26.0 * sin(i * (6.284 / 360.0));
		j = i + 5;
		float xNext = 26.0 * cos(j * (6.284 / 360.0));;
		float yNext = 26 * sin(j * (6.284 / 360.0));
		glVertex2f(x, y);
		glVertex2f(xNext, yNext);

	}
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glColor3f(0, 0, 0);
	point = -0.5 * 90 * sin(60 * (6.284 / 360.0));

	glTranslatef(38, point - 120, 0);
	glScalef(1.5, 0.5, 0);
	glBegin(GL_POLYGON);
	for (i = 180; i < 360; i = i + 5)
	{
		float j = 0;
		glVertex2f(0, 0);
		j = (float)i;
		x = 25.33 * cos(i * (6.284 / 360.0));
		y = 25.33 * sin(i * (6.284 / 360.0));
		j = i + 5;
		float xNext = 25.33 * cos(j * (6.284 / 360.0));;
		float yNext = 25.33 * sin(j * (6.284 / 360.0));
		glVertex2f(x, y);
		glVertex2f(xNext, yNext);

	}
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.2, 0.2, 0.2);
	point = -0.5 * 90 * sin(60 * (6.284 / 360.0));

	glTranslatef(102, point - 120, 0);
	glScalef(1, 0.3, 0);
	glBegin(GL_POLYGON);
	for (i = 180; i < 360; i = i + 5)
	{
		float j = 0;
		glVertex2f(0, 0);
		j = (float)i;
		x = 26.0 * cos(i * (6.284 / 360.0));
		y = 26.0 * sin(i * (6.284 / 360.0));
		j = i + 5;
		float xNext = 26.0 * cos(j * (6.284 / 360.0));;
		float yNext = 26 * sin(j * (6.284 / 360.0));
		glVertex2f(x, y);
		glVertex2f(xNext, yNext);

	}
	glEnd();
	glPopMatrix();

	glPushMatrix();
	if (dark % 2 == 0) {
		glColor3ub(13, 206, 235);
	}
	else {
		glColor3f(0, 0, 0);
	}
	point = -0.5 * 90 * sin(60 * (6.284 / 360.0));

	glTranslatef(-39, point - 120, 0);
	glScalef(1, 0.25, 0);
	glBegin(GL_POLYGON);
	for (i = 180; i < 381; i = i + 5)
	{
		float j = 0;
		glVertex2f(0, 0);
		j = (float)i;
		x = 13 * cos(i * (6.284 / 360.0));
		y = 13 * sin(i * (6.284 / 360.0));
		j = i + 5;
		float xNext = 13 * cos(j * (6.284 / 360.0));;
		float yNext = 13 * sin(j * (6.284 / 360.0));
		glVertex2f(x, y);
		glVertex2f(xNext, yNext);

	}
	glEnd();
	glPopMatrix();

	glPushMatrix();
	if (dark % 2 == 0) {
		glColor3ub(13, 206, 235);
	}
	else {
		glColor3f(0, 0, 0);
	}
	point = -0.5 * 90 * sin(60 * (6.284 / 360.0));

	glTranslatef(115, point - 120, 0);
	glScalef(1, 0.25, 0);
	glBegin(GL_POLYGON); 
	for (i = 180; i < 381; i = i + 5)
	{
		float j = 0;
		glVertex2f(0, 0);
		j = (float)i;
		x = 13 * cos(i * (6.284 / 360.0));
		y = 13 * sin(i * (6.284 / 360.0));
		j = i + 5;
		float xNext = 13 * cos(j * (6.284 / 360.0));;
		float yNext = 13 * sin(j * (6.284 / 360.0));
		glVertex2f(x, y);
		glVertex2f(xNext, yNext);

	}
	glEnd();
	glPopMatrix();


//Last floor
	glPushMatrix();
	glTranslatef(36, point, 0);
	glColor3f(0, 0, 0);
	glBegin(GL_POLYGON); 
	glVertex2f(66, -180);
	glVertex2f(76, -210);
	glVertex2f(-76, -210);
	glVertex2f(-66, -180);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(36, point, 0);
	glColor3f(1, 1, 1);
	glBegin(GL_POLYGON); 
	glVertex2f(76, -210);
	glVertex2f(76, -270);
	glVertex2f(-76, -270);
	glVertex2f(-76, -210);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(36, point, 0);
	glColor3ub(186, 51, 55);
	glBegin(GL_POLYGON); 
	glVertex2f(76, -210);
	glVertex2f(76, -265);
	glVertex2f(0, -267);
	glVertex2f(-76, -265);
	glVertex2f(-76, -210);
	glEnd();

	glColor3ub(166, 51, 55);
	glBegin(GL_POLYGON); 
	glVertex2f(46, -210);
	glVertex2f(47, -266);
	glVertex2f(0, -267);
	glVertex2f(-47, -266);
	glVertex2f(-46, -210);
	glEnd();

	glPopMatrix();


	if (dark % 2 == 1) {
		//Last floor Lights
		glPushMatrix();
		glColor3f(1, 1, 0);
		point = -0.5 * 90 * sin(60 * (6.284 / 360.0));
		glTranslatef(-61.623 + 1, point - 180 - 1, 0);
		glScalef(1, 1, 0);
		glBegin(GL_POLYGON); 
		for (i = 180; i < 360; i = i + 5)
		{
			float j = 0;
			glVertex2f(0, 0);
			j = (float)i;
			x = 37.623 * cos(i * (6.284 / 360.0));
			y = 37.623 * sin(i * (6.284 / 360.0));
			j = i + 5;
			float xNext = 37.623 * cos(j * (6.284 / 360.0));;
			float yNext = 37.623 * sin(j * (6.284 / 360.0));
			glVertex2f(x, y);
			glVertex2f(xNext, yNext);

		}
		glEnd();
		glPopMatrix();

		glPushMatrix();
		glColor3f(1, 1, 0);
		point = -0.5 * 90 * sin(60 * (6.284 / 360.0));

		glTranslatef(36, point - 210 - 1, 0);
		glScalef(1, 0.2, 0);
		glBegin(GL_POLYGON); 
		for (i = 180; i < 361; i = i + 5)
		{
			float j = 0;
			glVertex2f(0, 0);
			j = (float)i;
			x = 76 * cos(i * (6.284 / 360.0));
			y = 76 * sin(i * (6.284 / 360.0));
			j = i + 5;
			float xNext = 76 * cos(j * (6.284 / 360.0));;
			float yNext = 76 * sin(j * (6.284 / 360.0));
			glVertex2f(x, y);
			glVertex2f(xNext, yNext);

		}
		glEnd();
		glPopMatrix();

		glPushMatrix();
		glColor3f(1, 1, 0);
		point = -0.5 * 90 * sin(60 * (6.284 / 360.0));
		glTranslatef(133.623 - 1, point - 180 - 1, 0);
		glScalef(1, 1, 0);
		glBegin(GL_POLYGON); 
		for (i = 180; i < 360; i = i + 5)
		{
			float j = 0;
			glVertex2f(0, 0);
			j = (float)i;
			x = 37.623 * cos(i * (6.284 / 360.0));
			y = 37.623 * sin(i * (6.284 / 360.0));
			j = i + 5;
			float xNext = 37.623 * cos(j * (6.284 / 360.0));;
			float yNext = 37.623 * sin(j * (6.284 / 360.0));
			glVertex2f(x, y);
			glVertex2f(xNext, yNext);

		}
		glEnd();
		glPopMatrix();
		////
	}


	glPushMatrix();
	glColor3f(0.2, 0.2, 0.2);
	point = -0.5 * 90 * sin(60 * (6.284 / 360.0));
	glTranslatef(-61.623, point - 180, 0);
	glScalef(1, 1, 0);
	glBegin(GL_POLYGON); 
	for (i = 180; i < 360; i = i + 5)
	{
		float j = 0;
		glVertex2f(0, 0);
		j = (float)i;
		x = 37.623 * cos(i * (6.284 / 360.0));
		y = 37.623* sin(i * (6.284 / 360.0));
		j = i + 5;
		float xNext = 37.623 * cos(j * (6.284 / 360.0));;
		float yNext = 37.623 * sin(j * (6.284 / 360.0));
		glVertex2f(x, y);
		glVertex2f(xNext, yNext);

	}
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glColor3f(0, 0, 0);
	point = -0.5 * 90 * sin(60 * (6.284 / 360.0));

	glTranslatef(36, point - 210, 0);
	glScalef(1, 0.2, 0);
	glBegin(GL_POLYGON);
	for (i = 180; i < 361; i = i + 5)
	{
		float j = 0;
		glVertex2f(0, 0);
		j = (float)i;
		x = 76 * cos(i * (6.284 / 360.0));
		y = 76 * sin(i * (6.284 / 360.0));
		j = i + 5;
		float xNext = 76 * cos(j * (6.284 / 360.0));;
		float yNext = 76 * sin(j * (6.284 / 360.0));
		glVertex2f(x, y);
		glVertex2f(xNext, yNext);

	}
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.2, 0.2, 0.2);
	point = -0.5 * 90 * sin(60 * (6.284 / 360.0));
	glTranslatef(133.623, point - 180, 0);
	glScalef(1, 1, 0);
	glBegin(GL_POLYGON); 
	for (i = 180; i < 360; i = i + 5)
	{
		float j = 0;
		glVertex2f(0, 0);
		j = (float)i;
		x = 37.623 * cos(i * (6.284 / 360.0));
		y = 37.623 * sin(i * (6.284 / 360.0));
		j = i + 5;
		float xNext = 37.623 * cos(j * (6.284 / 360.0));;
		float yNext = 37.623 * sin(j * (6.284 / 360.0));
		glVertex2f(x, y);
		glVertex2f(xNext, yNext);

	}
	glEnd();
	glPopMatrix();

	glPushMatrix();
	if (dark % 2 == 0) {
		glColor3ub(13, 206, 235);
	}
	else {
		glColor3f(0, 0, 0);
	}
	point = -0.5 * 90 * sin(60 * (6.284 / 360.0));
	glTranslatef(-68.623, point - 180, 0);
	glScalef(1, 0.5, 0);
	glBegin(GL_POLYGON); 
	for (i = 180; i < 361; i = i + 5)
	{
		float j = 0;
		glVertex2f(0, 0);
		j = (float)i;
		x = 37.623 * cos(i * (6.284 / 360.0));
		y = 37.623 * sin(i * (6.284 / 360.0));
		j = i + 5;
		float xNext = 37.623 * cos(j * (6.284 / 360.0));;
		float yNext = 37.623 * sin(j * (6.284 / 360.0));
		glVertex2f(x, y);
		glVertex2f(xNext, yNext);

	}
	glEnd();
	glPopMatrix();

	glPushMatrix();
	if (dark % 2 == 0) {
		glColor3ub(13, 206, 235);
	}
	else {
		glColor3f(0, 0, 0);
	}
	point = -0.5 * 90 * sin(60 * (6.284 / 360.0));
	glTranslatef(139.623, point - 180, 0);
	glScalef(1, 0.5, 0);
	glBegin(GL_POLYGON); 
	for (i = 180; i < 361; i = i + 5)
	{
		float j = 0;
		glVertex2f(0, 0);
		j = (float)i;
		x = 37.623 * cos(i * (6.284 / 360.0));
		y = 37.623 * sin(i * (6.284 / 360.0));
		j = i + 5;
		float xNext = 37.623 * cos(j * (6.284 / 360.0));;
		float yNext = 37.623 * sin(j * (6.284 / 360.0));
		glVertex2f(x, y);
		glVertex2f(xNext, yNext);

	}
	glEnd();
	glPopMatrix();

}

//Snowy Background
void background() {

	int i;
	float x, y;
	glTranslatef(300, 25, 0);
	if (dark % 2 == 0) {
		glColor3f(1, 1, 1);
	}
	else {
		glColor3f(0.9, 0.9, 0.9);
	}
	glScalef(1, 1, 0);
	glBegin(GL_POLYGON); 
	for (i = 0; i < 361; i = i + 5)
	{
		x = 300.0 * cos(i * (6.284 / 360.0));
		y = 10.0 * sin(i * (6.284 / 360.0));

		glVertex2f(x, y);
	}
	glEnd();

}

//Star Basic Element
void DarkModeElement() {
	int i;
	int k = 0;
	float x, y;
	glPushMatrix();
	glScalef(0.15, 0.15, 0);
	glBegin(GL_POLYGON);
	for (i = 90; i > 0; i = i - 5)
	{
		float j = 0;
		glVertex2f(0, 90);
		x = (float)i;
		y = 90 * sin(i * (6.284 / 360.0));
		j = i - 5;
		float xNext = j;
		float yNext = 90 * sin(j * (6.284 / 360.0));
		glVertex2f(x, y);
		glVertex2f(xNext, yNext);
	}

	for (i = 90; i > 0; i = i - 5)
	{
		float j = 0;
		glVertex2f(0, 90);
		x = (float)i;
		y = 180 - 90 * sin(i * (6.284 / 360.0));
		j = i - 5;
		float xNext = j;
		float yNext = 180 - 90 * sin(j * (6.284 / 360.0));
		glVertex2f(x, y);
		glVertex2f(xNext, yNext);
	}

	for (i = 90; i > 0; i = i - 5)
	{
		float j = 0;
		glVertex2f(0, 90);
		x = -(float)i;
		y = 180 - 90 * sin(i * (6.284 / 360.0));
		j = i - 5;
		float xNext = -j;
		float yNext = 180 - 90 * sin(j * (6.284 / 360.0));
		glVertex2f(x, y);
		glVertex2f(xNext, yNext);
	}

	for (i = 90; i > 0; i = i - 5)
	{
		float j = 0;
		glVertex2f(0, 90);
		x = -(float)i;
		y = 90 * sin(i * (6.284 / 360.0));
		j = i - 5;
		float xNext = -j;
		float yNext = 90 * sin(j * (6.284 / 360.0));
		glVertex2f(x, y);
		glVertex2f(xNext, yNext);
	}

	glEnd();
	glPopMatrix();
}

//Star in the dark
void dark_mode() {

	
		glPushMatrix();
		glTranslatef(575, 750, 0);
		if (p19.x > 100) {
			glColor3f(1, 1, 0);
		}
		else {
			glColor3f(1, 1, 1);
		}
	
		DarkModeElement();
		glPopMatrix();

	

	
		glPushMatrix();
		glTranslatef(1035, 730, 0);
		if (p19.x > 100) {
			glColor3f(1, 1, 0);
		}
		else {
			glColor3f(1, 1, 1);
		}

		DarkModeElement();
		glPopMatrix();

		glPushMatrix();
		glTranslatef(115, 730, 0);
		if (p19.x > 100) {
			glColor3f(1, 1, 0);
		}
		else {
			glColor3f(1, 1, 1);
		}

		DarkModeElement();
		glPopMatrix();

	
	
		glPushMatrix();
		glTranslatef(700, 500, 0);
		if (p19.x <= 100) {
			glColor3f(1, 1, 0);
		}
		else{
			glColor3f(1, 1, 1);
		}
		
		DarkModeElement();
		glPopMatrix();

		glPushMatrix();
		glTranslatef(450, 500, 0);
		if (p19.x <= 100) {
			glColor3f(1, 1, 0);
		}
		else {
			glColor3f(1, 1, 1);
		}
		DarkModeElement();
		glPopMatrix();

	
	

	
		glPushMatrix();
		glTranslatef(830, 700, 0);
		if (p19.x > 100) {
			glColor3f(1, 1, 0);
		}
		else {
			glColor3f(1, 1, 1);
		}
		DarkModeElement();
		glPopMatrix();
	
	
	
		glPushMatrix();
		glTranslatef(320, 700, 0);
		if (p19.x > 100) {
			glColor3f(1, 1, 0);
		}
		else {
			glColor3f(1, 1, 1);
		}
		DarkModeElement();
		glPopMatrix();
	
	

	
		glPushMatrix();
		glTranslatef(235, 565, 0);
		if (p19.x <= 100) {
			glColor3f(1, 1, 0);
		}
		else {
			glColor3f(1, 1, 1);
		}
		DarkModeElement();
		glPopMatrix();

		glPushMatrix();
		glTranslatef(935, 565, 0);
		if (p19.x <= 100) {
			glColor3f(1, 1, 0);
		}
		else {
			glColor3f(1, 1, 1);
		}
		DarkModeElement();
		glPopMatrix();
	


		glPushMatrix();
		glTranslatef(325, 465, 0);
		if (p19.x > 100) {
			glColor3f(1, 1, 0);
		}
		else {
			glColor3f(1, 1, 1);
		}

		DarkModeElement();
		glPopMatrix();

		glPushMatrix();
		glTranslatef(845, 465, 0);
		if (p19.x > 100) {
			glColor3f(1, 1, 0);
		}
		else {
			glColor3f(1, 1, 1);
		}

		DarkModeElement();
		glPopMatrix();
	
	

	


		glPushMatrix();
		glTranslatef(65, 540, 0);
		if (p19.x <= 100) {
			glColor3f(1, 1, 0);
		}
		else {
			glColor3f(1, 1, 1);
		}
		DarkModeElement();
		glPopMatrix();


		glPushMatrix();
		glTranslatef(1105, 540, 0);
		if (p19.x <= 100) {
			glColor3f(1, 1, 0);
		}
		else {
			glColor3f(1, 1, 1);
		}
		DarkModeElement();
		glPopMatrix();
	
	
}
void drawString(const char* str) {
	static int isFirstCall = 1;
	static GLuint lists;
	if (isFirstCall) {
		isFirstCall = 0;
		lists = glGenLists(MAX_CHAR);
		wglUseFontBitmaps(wglGetCurrentDC(), 0, MAX_CHAR, lists);
	}
	for (; *str != '\0'; ++str) {
		glCallList(lists + *str);
	}
}
void selectFont(int size, int charset, const char* face) {
	HFONT hFont = CreateFontA(size, 0, 0, 0, FW_MEDIUM, 0, 0, 0, charset, OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, face);
	HFONT hOldFont = (HFONT)SelectObject(wglGetCurrentDC(), hFont);
	DeleteObject(hOldFont);
}

void display(void)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 1200, 0, 800);
	glClearColor(0, 0, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1, 1, 1);
	glBegin(GL_LINES);
	glVertex2f(finishx, 50);
	glVertex2f(finishx, 350);
	glEnd();
	if (dark % 2 == 0) {
		glColor3ub(13, 206, 235);
		glBegin(GL_POLYGON);
		glVertex2f(0, 0);
		glVertex2f(0, 800);
		glVertex2f(1200, 800);
		glVertex2f(1200, 0);
		glEnd();

		glPushMatrix();
		glBegin(GL_POLYGON);
		glColor3ub(13, 186, 255);
		glVertex2f(0, 800);
		glColor3ub(13, 206, 235);
	    glVertex2f(0, 400);
	    glVertex2f(1200, 400);
		glColor3ub(255, 211, 147);
		glVertex2f(1200, 800);
		glEnd();
		glPopMatrix();

	}
	else {
		glColor3f(0, 0, 0);
		glBegin(GL_POLYGON);
		glVertex2f(0, 0);
		glVertex2f(0, 800);
		glVertex2f(1200, 800);
		glVertex2f(1200, 0);
		glEnd();
	}
	
	if (dark % 2 == 1) {
		glPushMatrix();
		dark_mode();
		glPopMatrix();
	}

	//firewark2
	if (p11.x > 153) {
		glPushMatrix();
		glTranslatef(1000, 580, 0);
		glScalef(0.4, 0.4, 0);
		for (int i = 0; i < 6; i++) {
			glRotatef(60, 0.0f, 0.0f, 1.0f);
			Star();
		}
		for (int i = 0; i < 1; i++) {
			glRotatef(30, 0.0f, 0.0f, 1.0f);
			Star1();
		}
		for (int i = 0; i < 6; i++) {
			glRotatef(60, 0.0f, 0.0f, 1.0f);
			Star1();
		}
		glPopMatrix();
	}
	


	glPushMatrix();
	glTranslatef(400, 500, 0);
	glTranslatef(p17.x, 0, 0);
	cloud1();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(749.75, 62, 0);
	glScalef(0.55, 0.55, 0);
	snowMan();
	glPopMatrix();

	glPushMatrix();
	background();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(1100, 450, 0);
	glTranslatef(p8.x, 0, 0);
	cloud();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(170, 25, 0);
	EastDoor1();
	glPopMatrix();


	glPushMatrix();
	glTranslatef(1000, 330, 0);
	beisita();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(100, 300, 0);
	glTranslatef(p17.y, 0, 0);
	cloud();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(250, -3, 0);
	glScalef(1, 1, 0);
	final_Tree();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(800, 300, 0);
	glTranslatef(p8.y, 0, 0);
	cloud1();
	glPopMatrix();



	glPushMatrix();
	glTranslatef(500, -10, 0);
	glScalef(1, 1, 0);
	final_Tree();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-290, -10, 0);
	glScalef(1, 1, 0);
	final_Tree();
	glPopMatrix();

	glPushMatrix();
	glScalef(1, 1.2, 0);
	glTranslatef(610, -6, 0);
	background();
	glPopMatrix();


	//Firewark1
	if (p9.x >= 485) {
		glPushMatrix();

		glTranslatef(150, 605, 0);
		if (p1.x >= 0.0 & p1.x < 0.9) {
			Cricle();
		}
		if (p1.x >= 0.9 & p1.x < 2.0) {
			Cricle1();
		}
		glPopMatrix();

		glPushMatrix();
		glTranslatef(150, 600, 0);
		for (int i = 0; i < 6; i++) {
			glRotatef(60, 0.0f, 0.0f, 1.0f);
			Water();
		}

		for (int i = 0; i < 1; i++) {
			glRotatef(30, 0.0f, 0.0f, 1.0f);
			Water1();
		}
		for (int i = 0; i < 6; i++) {
			glRotatef(60, 0.0f, 0.0f, 1.0f);
			Water1();
		}
		glPopMatrix();
	}
	

	if (dark % 2 == 0) {
		glColor3f(1, 1, 1);
	}
	else {
		glColor3f(0.9, 0.9, 0.9);
	}
	glBegin(GL_POLYGON);
	glVertex2f(0, 0);
	glVertex2f(0, 25);
	glVertex2f(1200, 23);
	glVertex2f(1200, 0);
	glEnd();

	if (p11.x < 148) {
		glPushMatrix();
		glTranslatef(840.5, 150, 0);
		glTranslatef(p11.x, p11.x  *  430 / 159.5, 0);
		glRotatef(60, 0.0f, 0.0f, 1.0f);
		Water_Forfly1();
		glPopMatrix();
	}

	if (p9.x < 480) {
		glPushMatrix();
		glTranslatef(660, 150, 0);
		glTranslatef(-p9.x, p9.x * 45 / 51, 0);
		glRotatef(128, 0.0f, 0.0f, 1.0f);
		Water_Forfly();
		glPopMatrix();
	}

	

	//Draw 2D text
	if (dark % 2 == 0) {
		glColor3f(0, 0, 0);
	}
	else {
		glColor3f(1, 1, 0);
	}
	selectFont(80, ANSI_CHARSET, "Segoe UI");
	glRasterPos2f(351, 600);
	drawString("Happy New Year!");

	if (dark % 2 == 0) {
		glColor3f(0, 0, 0);
	}
	else {
		glColor3f(1, 1, 0);
	}
	selectFont(80, ANSI_CHARSET, "Segoe UI");
	glRasterPos2f(349, 600);
	drawString("Happy New Year!");

	if (dark % 2 == 0) {
		glColor3f(0, 0, 0);
	}
	else {
		glColor3f(1, 1, 0);
	}
	selectFont(80, ANSI_CHARSET, "Segoe UI");
	glRasterPos2f(350, 601);
	drawString("Happy New Year!");

	if (dark % 2 == 0) {
		glColor3f(0, 0, 0);
	}
	else {
		glColor3f(1, 1, 0);
	}
	selectFont(80, ANSI_CHARSET, "Segoe UI");
	glRasterPos2f(350, 599);
	drawString("Happy New Year!");

	if (dark % 2 == 0) {
		glColor3ub(255, 233 - 1* p4.x, 145);
	}
	else {
		glColor3f(0, 0, 0);
	}
	selectFont(80, ANSI_CHARSET, "Segoe UI");
	glRasterPos2f(350, 600);
	drawString("Happy New Year!");



	glutSwapBuffers();

}




int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(1200, 800);
	glutCreateWindow("Greeting Card");
	glutDisplayFunc(display);

	glutKeyboardFunc(keyboard_input);
	
	glutIdleFunc(when_in_mainloop);
	glutTimerFunc(time_interval, OnTimer, 1);
	glutMainLoop();
}