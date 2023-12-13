

#define FREEGLUT_STATIC
#include <GL/freeglut.h>
#include <stdlib.h>
#include<math.h>
#include "vector"
using namespace std;

GLfloat ctrlpoints[3][3][3] = {
{{-100.0, 350.0, -95.0}, {0.0, 400.0, -95.0}, {100.0, 350.0, -95.0}},
{{-100.0, 350.0, 130.0}, {0.0, 400.0, 130.0}, {100.0, 355.0, 130.0}},
{{-100.0, 350.0, 355.0}, {0.0, 400.0, 355.0}, {100.0, 350.0, 355.0}},
};

int intWinWidth = 1200; //Default window size
int intWinHeight = 800;
float fltColourVal1 = 0.5; //First colour value
float fltColourVal2 = 0.7; //Second colour value
float fltColourVal3 = 0.4; //Third colour value
float fltFOV = 75; //Field Of View
float distance1 = 3000.0;
float angle1 = 0;
float fltZoom = 1.0; //Zoom amount
float fltX0 = 0.0; //Camera position
float fltY0 = 185.0;
float fltZ0 = -2145;
float fltXRef = 0.0; //Look At reference point
float fltYRef = 185.0;
float fltZRef = 1100;
float fltXUp = 0.0; //Up vector
float fltYUp = 1.0;
float fltZUp = 0.0;
float fltViewingAngle = 0; //Used for rotating camera
float chuanlian_move = 75 * cos(10 * (6.284 / 360.0)); //Used to control cutain 
float angle_chuanlian1 = 10; //Used to control cutain 
float chuanlian_move1 = 75 * cos(10 * (6.284 / 360.0)); //Used to control cutain 
float angle_chuanlian = 10; //Used to control cutain 
float lift_move = 45.0;
float lift_move1 = 45.0;
float animate_choice;
float lift = 5.0; //Used to control lift
float updown_controller = 0.0; //Used to camera position and look at point
GLfloat mat_ambient4[] = { 0.8 * (255.0 / 255), 0.8 * (251.0 / 255), 0.8 * 240.0 / (255), 1.0f };  
GLfloat mat_diffuse4[] = { (255.0 / 255), (255.0 / 255), 255.0 / (255), 1.0f };  
GLfloat mat_specular4[] = { 0.0f, 0.0f, 0.0f, 1.0f };  
GLfloat mat_emission4[] = { 0.0f, 0.0f, 0.0f, 1.0f };   
GLfloat mat_shininess4 = 0.0f;

GLint imagewidth0, imagewidth1;
GLint imageheight0, imageheight1;
GLint pixellength0, pixellength1;
vector<GLubyte*>p; // Similar to GLubyte* for program 3 but for 2 images (so a vector)
GLuint texture[7];
GLfloat angle = 0;

void adjustDisplay(unsigned char key, int x, int y)
{
	//Down Camera and look at point down
	if (key == 'd' || key == 'D')
		if (updown_controller > -100) {
			fltY0 -= 5; //Camera and look at point down
			fltYRef -= 5;
			updown_controller -= 5;
		}
	//Up Camera and look at point down
	if (key == 'u' || key == 'U')
		if (updown_controller < 55) {
			fltY0 += 5; //Camera and look at point down
			fltYRef += 5;
			updown_controller += 5;
		}
	//Pull the curtain
	if (key == 'l' || key == 'L') {
		if (angle_chuanlian < 62.0) {
			angle_chuanlian += 1; 
			chuanlian_move = 75 * cos(angle_chuanlian * (6.284 / 360.0));
		}
		if (angle_chuanlian1 < 84.0) {
			angle_chuanlian1 += 1; 
			chuanlian_move1 = 75 * cos(angle_chuanlian1 * (6.284 / 360.0));
		}
	}
	//Close the curtain
	if (key == 'j' || key == 'J') {
		if (angle_chuanlian > 10.0) {
			angle_chuanlian -= 1;
			chuanlian_move = 75 * cos(angle_chuanlian * (6.284 / 360.0));
		}
		if (angle_chuanlian1 > 10.0) {
			angle_chuanlian1 -= 1; 
			chuanlian_move1 = 75 * cos(angle_chuanlian1 * (6.284 / 360.0));
		}
	}

	//Moving towards the direction of looking
	//IMPORTANT !!! The range that this key allows you to go forward is different between outside the whole building and inside the room
	if (key == 't' || key == 'T') {
		if (fltY0 > 500) {
			if (fltZ0 < 1000.0) {
				if ((fltX0 < -700 && angle1 < 0) || (fltX0 > 800 && angle1 > 0)) {

				}
				else {
					fltX0 += 5 * cos((90 - angle1) * (6.284 / 360.0));
					fltZ0 += 5 * cos(angle1 * (6.284 / 360.0));
				}
			}
		}

		if (fltY0 < 500) {
			if (fltZ0 < -800.0) {
					fltX0 += 5 * cos((90 - angle1) * (6.284 / 360.0));
					fltZ0 += 5 * cos(angle1 * (6.284 / 360.0));
			}
		}
	}
		

	//Backward
	//IMPORTANT !!! The range that this key allows you to go forward is different between outside the whole building and inside the room
	if (key == 'g' || key == 'G') {
		if (fltY0 > 500) {
			if (fltZ0 > -550.0) {
				if ((fltX0 < -700 && angle1 > 0) || (fltX0 > 800 && angle1 < 0)) {

				}
				else {
					fltX0 -= 5 * cos((90 - angle1) * (6.284 / 360.0));
					fltZ0 -= 5 * cos(angle1 * (6.284 / 360.0));
				}
				
			}
		}

		if (fltY0 < 500) {
			if (fltZ0 > -2200.0) {
				fltX0 -= 5 * cos((90 - angle1) * (6.284 / 360.0));
				fltZ0 -= 5 * cos(angle1 * (6.284 / 360.0));
			}
		}
		
	}
	
	//Taking the elevator
	if (key == 'z' || key == 'Z') {
		fltX0 = 0.0; //Camera position
		fltY0 = 185.0;
		fltZ0 = -1600;
		fltXRef = 0.0; //Look At reference point
		fltYRef = 185.0;
		fltZRef = 1100.0;
		fltZoom = 1.0;
		lift_move = 45;
		lift_move1 = 45;
		lift = 5;
		animate_choice = 1;
		angle1 = 0;
	}

	//Turn your head to the right
	//IMPORTANT !!! This key can only be used after you enter the living room ( even in the entrance hall can not be used )
	if (key == 'e' || key == 'E')
		if (angle1 >= -88 && fltZ0 > 401) {
			angle1 -= 1;
			fltXRef = distance1 * cos((90 - angle1) * (6.284 / 360.0)); //Look At reference point
			fltZRef = fltZ0 + distance1 * cos(angle1 * (6.284 / 360.0));

		}

	//Turn your head to the left
	//IMPORTANT !!! This key can only be used after you enter the living room ( even in the entrance hall can not be used )
	if (key == 'q' || key == 'Q' && fltZ0 > 401)
		if (angle1 <= 88) {
			angle1 += 1;
			fltXRef = distance1 * cos((90 - angle1) * (6.284 / 360.0)); //Look At reference point
			fltZRef = fltZ0 + distance1 * cos(angle1 * (6.284 / 360.0));

		}


	glutPostRedisplay();
}

void ReadImage(const char path[256], GLint& imagewidth, GLint& imageheight, GLint& pixellength) {
	GLubyte* pixeldata;
	FILE* pfile;
	fopen_s(&pfile, path, "rb");
	if (pfile == 0) exit(0);
	fseek(pfile, 0x0012, SEEK_SET);
	fread(&imagewidth, sizeof(imagewidth), 1, pfile);
	fread(&imageheight, sizeof(imageheight), 1, pfile);
	pixellength = imagewidth * 3;
	while (pixellength % 4 != 0)pixellength++;
	pixellength *= imageheight;
	pixeldata = (GLubyte*)malloc(pixellength);
	if (pixeldata == 0) exit(0);
	fseek(pfile, 54, SEEK_SET);
	fread(pixeldata, pixellength, 1, pfile);
	p.push_back(pixeldata); // Similar to glDrawPixels for program 3
	fclose(pfile);
}

void myinit(void) {
	//glShadeModel(GL_FLAT);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	//glShadeModel(GL_FLAT);
	glEnable(GL_TEXTURE_2D);
	ReadImage("hongzhuan.bmp", imagewidth0, imageheight0, pixellength0);
	ReadImage("muban.bmp", imagewidth1, imageheight1, pixellength1);
	ReadImage("lihua.bmp", imagewidth1, imageheight1, pixellength1);
	ReadImage("xingkong.bmp", imagewidth1, imageheight1, pixellength1);
	ReadImage("fengjing.bmp", imagewidth1, imageheight1, pixellength1);
	ReadImage("back1.bmp", imagewidth1, imageheight1, pixellength1);
	ReadImage("caodi.bmp", imagewidth1, imageheight1, pixellength1);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // set pixel storage modes (in the memory)
	glGenTextures(7, &texture[0]); // number of texture names to be generated and an array of texture names
	glBindTexture(GL_TEXTURE_2D, texture[0]); // target to which texture is bound and name of a texture
	glTexImage2D(GL_TEXTURE_2D, 0, 3, imagewidth0, imageheight0, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, p[0]);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPLACE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPLACE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glBindTexture(GL_TEXTURE_2D, texture[1]);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, imagewidth1, imageheight1, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, p[1]);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPLACE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPLACE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glBindTexture(GL_TEXTURE_2D, texture[2]); // target to which texture is bound and name of a texture
	glTexImage2D(GL_TEXTURE_2D, 0, 3, imagewidth0, imageheight0, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, p[2]);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPLACE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPLACE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glBindTexture(GL_TEXTURE_2D, texture[3]);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, imagewidth1, imageheight1, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, p[3]);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPLACE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPLACE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glBindTexture(GL_TEXTURE_2D, texture[4]);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, imagewidth1, imageheight1, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, p[4]);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPLACE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPLACE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glBindTexture(GL_TEXTURE_2D, texture[5]);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, imagewidth1, imageheight1, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, p[5]);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPLACE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPLACE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glBindTexture(GL_TEXTURE_2D, texture[6]);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, imagewidth1, imageheight1, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, p[6]);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPLACE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPLACE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);


}


void sunlight(float x, float y, float z) {
	GLfloat sun_light_position[] = { x , y , z , 1.0f }; 
	GLfloat sun_light_ambient[] = { 1.0f, 1.0f, 1.0f, 1.0f };  
	GLfloat sun_light_diffuse[] = { 243.0f / 255, 155.0f/ 255, 66.0f / 255, 1.0f };  
	GLfloat sun_light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f }; 
	glLightfv(GL_LIGHT0, GL_POSITION, sun_light_position);
	glLightfv(GL_LIGHT0, GL_AMBIENT, sun_light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, sun_light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, sun_light_specular);

	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
}

void sunlight1(float x, float y, float z) {
	GLfloat sun_light_position[] = { x , y , z , 1.0f }; 
	GLfloat sun_light_ambient[] = { 1.0f, 1.0f, 1.0f, 1.0f };  
	GLfloat sun_light_diffuse[] = { 103.0f / 255, 5.0f / 255, 6.0f / 255, 1.0f };  
	GLfloat sun_light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f }; 
	glLightfv(GL_LIGHT1, GL_POSITION, sun_light_position);
	glLightfv(GL_LIGHT1, GL_AMBIENT, sun_light_ambient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, sun_light_diffuse);
	glLightfv(GL_LIGHT1, GL_SPECULAR, sun_light_specular);

	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
}

void housefloor(float x, float y, float z) {
	glPushMatrix();
	glTranslatef(0.0, -5.0, 400.0);
	glScalef(10000.0, 10.0, 10000.0);

	glPushMatrix();
	GLfloat mat_ambient[] = {0,  0, 0, 1.0f }; ;  
	GLfloat mat_diffuse[] = { 0, 0, 0, 1.0f };  
	GLfloat mat_specular[] = { 0.0f, 0.0f, 0.0f, 1.0f };   
	GLfloat mat_emission[] = { x / 255,  y / 255,  z / 255, 1.0f };   
	GLfloat mat_shininess = 0.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
	glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess);  
	glutSolidCube(1);
	
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[6]);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0); glVertex3f(-0.5, 0.7, -0.5);
	glTexCoord2f(0.0, 20.0); glVertex3f(-0.5, 0.7, 0.5);
	glTexCoord2f(20.0, 20.0); glVertex3f(0.5, 0.7, 0.5);
	glTexCoord2f(20.0, 0.0); glVertex3f(0.5, 0.7, -0.5);
	glEnd();
	glDisable(GL_TEXTURE_2D);

	GLfloat mat_ambient1[] = { 0, 0, 0, 1.0f };  
	GLfloat mat_diffuse1[] = { 0, 0, 0, 1.0f };  
	GLfloat mat_specular1[] = { 0.0f, 0.0f, 0.0f, 1.0f };   
	GLfloat mat_emission1[] = { 0,  0,  0, 1.0f };
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient1);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse1);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular1);
	glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission1);
	glutWireCube(1.0001);
	glPopMatrix();
	glPopMatrix();
}

void background() {
	glPushMatrix();
	glTranslatef(0.0, -5.0, 2000.0);
	glScalef(8000.0, 8200.0, 10.0);
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[5]);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0); glVertex3f(-0.5, -0.0, -1.1);
	glTexCoord2f(0.0, 1.0); glVertex3f(-0.5, 0.5, -1.1);
	glTexCoord2f(1.0, 1.0); glVertex3f(0.5, 0.5, -1.1);
	glTexCoord2f(1.0, 0.0); glVertex3f(0.5, -0.0, -1.1);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
	glPopMatrix();
}

void kuangkuangMEN(float x, float y, float z) {
	glPushMatrix();
	GLfloat mat_ambient[] = { 0.8 * (x / 255), 0.8 * (y / 255), 0.8 * z / (255), 1.0f };  
	GLfloat mat_diffuse[] = { (x / 255), (y / 255), z / (255), 1.0f }; 
	GLfloat mat_specular[] = { 0.0f, 0.0f, 0.0f, 1.0f };   
	GLfloat mat_emission[] = { 0.0f, 0.0f, 0.0f, 1.0f };   
	GLfloat mat_shininess = 0.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
	glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess);

	//glColor3ub(255, 251, 240);
	glBegin(GL_QUAD_STRIP);
	glVertex3f(-65, 0, -40);    // v1
	glVertex3f(-70, 5, -45);    // v2
	glVertex3f(65, 0, -40);    // v3
	glVertex3f(70, 5, -45);    // v4
	glVertex3f(65, 0, 40);    // v5
	glVertex3f(70, 5, 45);    // v6
	glVertex3f(-65, 0, 40);
	glVertex3f(-70, 5, 45);
	glVertex3f(-65, 0, -40);    // v1
	glVertex3f(-70, 5, -45);
	glEnd();

	glBegin(GL_POLYGON);
	//glColor3ub(255, 51, 240);
	glVertex3f(-65, 0, -40);    // v1 // v2
	glVertex3f(65, 0, -40);    // v3 // v4
	glVertex3f(65, 0, 40);    // v5  // v6
	glVertex3f(-65, 0, 40);
	glEnd();

	glBegin(GL_POLYGON); // v1
	glVertex3f(-70, 5, -45);    // v2 // v3
	glVertex3f(70, 5, -45);    // v4// v5
	glVertex3f(70, 5, 45);    // v6
	glVertex3f(-70, 5, 45);
	glEnd();

	GLfloat mat_ambient1[] = { 0, 0, 0, 1.0f };  //定义材质的环境光颜色
	GLfloat mat_diffuse1[] = { 0, 0, 0, 1.0f };  //定义材质的漫反射光颜色
	GLfloat mat_specular1[] = { 0.0f, 0.0f, 0.0f, 1.0f };   //定义材质的镜面反射光颜色
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient1);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse1);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular1);
	glutWireCube(1.005);

	//glLineWidth(1.45);
	glBegin(GL_LINES);
	glVertex3f(-65, 0, -40);    // v1
	glVertex3f(-70, 5, -45);    // v2
	glVertex3f(65, 0, -40);    // v3
	glVertex3f(70, 5, -45);    // v4
	glVertex3f(65, 0, 40);    // v5
	glVertex3f(70, 5, 45);    // v6
	glVertex3f(-65, 0, 40);
	glVertex3f(-70, 5, 45);
	glEnd();

	glBegin(GL_LINE_STRIP);
	glVertex3f(-64.7, 0, -40);    // v1 // v2
	glVertex3f(64.7, 0, -40);    // v3 // v4
	glVertex3f(64.7, 0, 40);    // v5  // v6
	glVertex3f(-64.7, 0, 40);
	glVertex3f(-64.7, 0, -40);
	glEnd();

	glBegin(GL_LINE_STRIP); // v1
	glVertex3f(-70, 5, -45);    // v2 // v3
	glVertex3f(70, 5, -45);    // v4// v5
	glVertex3f(70, 5, 45);    // v6
	glVertex3f(-70, 5, 45);
	glVertex3f(-70, 5, -45);
	glEnd();


	glPopMatrix();
}

void huakuangMEN(float x, float y, float z) {
	glPushMatrix();
	glPushMatrix();
	glScalef(1.0, 1.0, 1.0);
	kuangkuangMEN(x, y, z);
	glRotatef(90, 0, 0, 1);
	glTranslatef(-65.0, 0.0, 0.0);
	glTranslatef(0.0, 65.0, 0.0);
	kuangkuangMEN(x, y, z);
	glPopMatrix();

	glPushMatrix();
	glScalef(-1.0, -1.0, 1.0);
	glTranslatef(0.0, 130.0, 0.0);
	kuangkuangMEN(x, y, z);
	glRotatef(90, 0, 0, 1);
	glTranslatef(-65.0, 0.0, 0.0);
	glTranslatef(0.0, 65.0, 0.0);
	kuangkuangMEN(x, y, z);
	glPopMatrix();
	glPopMatrix();
}

void cicleroof(float x, float y , float z) {
	glPushMatrix();
	glTranslatef(0.0, 5.0, 0.0);
	GLfloat mat_ambient[] = { 0.8 * (x / 255), 0.8 * (y / 255), 0.8 * z / (255), 1.0f };  
	GLfloat mat_diffuse[] = { (x / 255), (y / 255), z / (255), 1.0f };  
	GLfloat mat_specular[] = { 0.0f, 0.0f, 0.0f, 1.0f };  
	GLfloat mat_emission[] = { 0.0f, 0.0f, 0.0f, 1.0f }; 
	GLfloat mat_shininess = 0.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
	glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess);
	glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 3, 0, 1, 9, 3, &ctrlpoints[0][0][0]);
	glEnable(GL_MAP2_VERTEX_3);
	glMapGrid2f(20, 0.0f, 1.0f, 20, 0.0f, 1.0f);
	glEvalMesh2(GL_FILL, 0, 20, 0, 20); 
	glPopMatrix();

}

void housewall1(float x, float y, float z) {
	glPushMatrix();
	glPushMatrix();

	GLfloat mat_ambient[] = { 0.8 * (x / 255), 0.8 * (y / 255), 0.8 * z / (255), 1.0f };  
	GLfloat mat_diffuse[] = { 1, 1, 1, 1.0f };  
	GLfloat mat_specular[] = { 0.0f, 0.0f, 0.0f, 1.0f };   
	GLfloat mat_emission[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	GLfloat mat_shininess = 0.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
	glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess);

	glutSolidCube(1);
	GLfloat mat_ambient1[] = { 0, 0, 0, 1.0f };  
	GLfloat mat_diffuse1[] = { 0, 0, 0, 1.0f };  
	GLfloat mat_specular1[] = { 0.0f, 0.0f, 0.0f, 1.0f };   
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient1);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse1);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular1);
	glutWireCube(1.005);
	glPopMatrix();
	glPopMatrix();
}

void housewall2(float x, float y, float z, float rate) {
	glPushMatrix();
	glPushMatrix();

	GLfloat mat_ambient[] = { rate * (x / 255), rate * (y / 255), rate * z / (255), 1.0f };  //定义材质的环境光颜色
	//GLfloat mat_diffuse[] = { (x / 255), (y / 255), z / (255), 1.0f };  //定义材质的漫反射光颜色
	GLfloat mat_diffuse[] = { 1, 1, 1, 1.0f };  //RGBA模式的漫反射光，全白光
	GLfloat mat_specular[] = { 0.0f, 0.0f, 0.0f, 1.0f };   //定义材质的镜面反射光颜色
	GLfloat mat_emission[] = { 0.0f, 0.0f, 0.0f, 1.0f };   //定义材质的辐射光颜色，为0
	GLfloat mat_shininess = 0.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
	glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess);

	glutSolidCube(1);
	GLfloat mat_ambient1[] = { 0, 0, 0, 1.0f };  //定义材质的环境光颜色
	GLfloat mat_diffuse1[] = { 0, 0, 0, 1.0f };  //定义材质的漫反射光颜色
	GLfloat mat_specular1[] = { 0.0f, 0.0f, 0.0f, 1.0f };   //定义材质的镜面反射光颜色
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient1);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse1);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular1);
	glutWireCube(1.005);
	glPopMatrix();
	glPopMatrix();
}

void housewall3(float x, float y, float z, float rate, int text, int many, int much) {
	glPushMatrix();
	glPushMatrix();

	

	if (text != 1) {
		GLfloat mat_ambient[] = { rate * (x / 255), rate * (y / 255), rate * z / (255), 1.0f };  //定义材质的环境光颜色
	    //GLfloat mat_diffuse[] = { (x / 255), (y / 255), z / (255), 1.0f };  //定义材质的漫反射光颜色
		GLfloat mat_diffuse[] = { 1, 1, 1, 1.0f };  //RGBA模式的漫反射光，全白光
		GLfloat mat_specular[] = { 0.0f, 0.0f, 0.0f, 1.0f };   //定义材质的镜面反射光颜色
		GLfloat mat_emission[] = { 0.0f, 0.0f, 0.0f, 1.0f };   //定义材质的辐射光颜色，为0
		GLfloat mat_shininess = 0.0f;
		glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
		glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
		glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess);
		glutSolidCube(1);
	}
	if (text == 0) {
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texture[0]);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0, 0.0); glVertex3f(-0.5, -0.5, -0.5);
		glTexCoord2f(0.0, much); glVertex3f(-0.5, 0.5, -0.5);
		glTexCoord2f(many, much); glVertex3f(0.5, 0.5, -0.5);
		glTexCoord2f(many, 0.0); glVertex3f(0.5, -0.5, -0.5);
		glEnd();
		glDisable(GL_TEXTURE_2D);
	}

	if (text == 1) {
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texture[1]);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0, 0.0); glVertex3f(-0.5, 0.501, -0.5);
		glTexCoord2f(0.0, much); glVertex3f(-0.5, 0.501, 0.5);
		glTexCoord2f(many, much); glVertex3f(0.5, 0.501, 0.5);
		glTexCoord2f(many, 0.0); glVertex3f(0.5, 0.501, -0.5);
		glEnd();
		glDisable(GL_TEXTURE_2D);
	}


	if (text != 1) {
		GLfloat mat_ambient1[] = { 0, 0, 0, 1.0f };  //定义材质的环境光颜色
		GLfloat mat_diffuse1[] = { 0, 0, 0, 1.0f };  //定义材质的漫反射光颜色
		GLfloat mat_specular1[] = { 0.0f, 0.0f, 0.0f, 1.0f };   //定义材质的镜面反射光颜色
		glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient1);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse1);
		glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular1);
		glutWireCube(1.001);
	}
	glPopMatrix();
	glPopMatrix();
}

void housewall4(float x, float y, float z) {
	glPushMatrix();
	glPushMatrix();

	GLfloat mat_ambient[] = { 0.8 * (x / 255), 0.8 * (y / 255), 0.8 * z / (255), 1.0f };  //定义材质的环境光颜色
	//GLfloat mat_diffuse[] = { (x / 255), (y / 255), z / (255), 1.0f };  //定义材质的漫反射光颜色
	GLfloat mat_diffuse[] = { 1, 1, 1, 1.0f };  //RGBA模式的漫反射光，全白光
	GLfloat mat_specular[] = { 0.0f, 0.0f, 0.0f, 1.0f };   //定义材质的镜面反射光颜色
	GLfloat mat_emission[] = { 0.0f, 0.0f, 0.0f, 1.0f };   //定义材质的辐射光颜色，为0
	GLfloat mat_shininess = 0.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
	glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess);

	glutSolidCube(1);
	//GLfloat mat_ambient1[] = { 0, 0, 0, 1.0f };  //定义材质的环境光颜色
	//GLfloat mat_diffuse1[] = { 0, 0, 0, 1.0f };  //定义材质的漫反射光颜色
	//GLfloat mat_specular1[] = { 0.0f, 0.0f, 0.0f, 1.0f };   //定义材质的镜面反射光颜色
	//glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient1);
	//glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse1);
	//glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular1);
	//glutWireCube(1.001);
	glPopMatrix();
	glPopMatrix();
}

void cylinder(float x, float y, float z) {
	glPushMatrix();
	glPushMatrix();

	GLfloat mat_ambient[] = { 0.8 * (x / 255), 0.8 * (y / 255), 0.8 * z / (255), 1.0f };  //定义材质的环境光颜色
	GLfloat mat_diffuse[] = { (255 / 255), (255 / 255), 255 / (255), 1.0f };  //定义材质的漫反射光颜色
	GLfloat mat_specular[] = { 0.0f, 0.0f, 0.0f, 1.0f };   //定义材质的镜面反射光颜色
	GLfloat mat_emission[] = { 0.0f, 0.0f, 0.0f, 1.0f };   //定义材质的辐射光颜色，为0
	GLfloat mat_shininess = 0.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
	glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess);
	glutSolidCylinder(1, 1, 30, 1);

	GLfloat mat_ambient1[] = { 0, 0, 0, 1.0f };  //定义材质的环境光颜色
	GLfloat mat_diffuse1[] = { 0, 0, 0, 1.0f };  //定义材质的漫反射光颜色
	GLfloat mat_specular1[] = { 0.0f, 0.0f, 0.0f, 1.0f };   //定义材质的镜面反射光颜色
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient1);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse1);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular1);
	glutWireCylinder(1, 1, 15, 1);
	glPopMatrix();
	glPopMatrix();
}

void coneLight(float x, float y, float z) {
	glPushMatrix();
	glPushMatrix();
	sunlight(0, 0, 0);
	if (fltZ0 < -2200 || fltZ0 > 305) {
		glDisable(GL_LIGHT0);
	}
	GLfloat mat_ambient[] = { 0.8 * (x / 255), 0.8 * (y / 255), 0.8 * z / (255), 1.0f };  //定义材质的环境光颜色
	GLfloat mat_diffuse[] = { (x / 255), (y / 255), z / (255), 1.0f };  //定义材质的漫反射光颜色
	GLfloat mat_specular[] = { 0.0f, 0.0f, 0.0f, 1.0f };   //定义材质的镜面反射光颜色
	GLfloat mat_emission[] = { 0.0f, 0.0f, 0.0f, 1.0f };   //定义材质的辐射光颜色，为0
	GLfloat mat_shininess = 0.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
	glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess);
	glutSolidCone(1, 1, 6, 10);

	GLfloat mat_ambient1[] = { 0, 0, 0, 1.0f };  //定义材质的环境光颜色
	GLfloat mat_diffuse1[] = { 0, 0, 0, 1.0f };  //定义材质的漫反射光颜色
	GLfloat mat_specular1[] = { 0.0f, 0.0f, 0.0f, 1.0f };   //定义材质的镜面反射光颜色
	GLfloat mat_emission1[] = { 1.0f, 1.0f, 1.0f, 1.0f };   //定义材质的辐射光颜色，为0
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient1);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse1);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular1);
	glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission1);
	glutWireCone(1, 1, 6, 1);

	glPopMatrix();
	glPopMatrix();
}

void cicleLight() {
	glPushMatrix();
	glPushMatrix();
	GLfloat mat_ambient[] = { (255.0f / 255), (190.0f / 255), 174.0f / (255), 1.0f };  //定义材质的环境光颜色
	GLfloat mat_diffuse[] = { (255.0 / 255), (255.0 / 255), 255.0 / (255), 1.0f };  //定义材质的漫反射光颜色
	GLfloat mat_specular[] = { 0.0f, 0.0f, 0.0f, 1.0f };   //定义材质的镜面反射光颜色
	GLfloat mat_emission[] = { 0.0f, 0.0f, 0.0f, 1.0f };   //定义材质的辐射光颜色，为0
	GLfloat mat_shininess = 0.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
	glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess);
	glutSolidSphere(1, 30, 30);

	glPopMatrix();
	glPopMatrix();
}

void door1() {
	glPushMatrix();
	glPushMatrix();
	glutSolidCube(1);
	glColor3f(0.0, 0.0, 0.0);
	glutWireCube(1.001);
	glPopMatrix();
	glPopMatrix();
}

void door11(float x, float y, float z, int text) {
	glPushMatrix();
	glPushMatrix();
	GLfloat mat_ambient[] = { 0.8 * (x / 255), 0.8 * (y / 255), 0.8 * z / (255), 1.0f };  //定义材质的环境光颜色
	GLfloat mat_diffuse[] = { 1, 1, 1, 1.0f };  //定义材质的漫反射光颜色
	GLfloat mat_specular[] = { 0.0f, 0.0f, 0.0f, 1.0f };   //定义材质的镜面反射光颜色
	GLfloat mat_emission[] = { 0.0f, 0.0f, 0.0f, 1.0f };   //定义材质的辐射光颜色，为0
	GLfloat mat_shininess = 0.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
	glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess);

	if (text == 3) {
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texture[3]);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0, 0.0); glVertex3f(-0.48, -0.48, 1.1);
		glTexCoord2f(0.0, 1.0); glVertex3f(-0.48, 0.48, 1.1);
		glTexCoord2f(1.0, 1.0); glVertex3f(0.48, 0.48, 1.1);
		glTexCoord2f(1.0, 0.0); glVertex3f(0.48, -0.48, 1.1);
		glEnd();
		glDisable(GL_TEXTURE_2D);
	}

	glutSolidCube(1);

	GLfloat mat_ambient1[] = { 0, 0, 0, 1.0f };  //定义材质的环境光颜色
	GLfloat mat_diffuse1[] = { 0, 0, 0, 1.0f };  //定义材质的漫反射光颜色
	GLfloat mat_specular1[] = { 0.0f, 0.0f, 0.0f, 1.0f };   //定义材质的镜面反射光颜色
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient1);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse1);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular1);
	glutWireCube(1.001);
	glPopMatrix();
	glPopMatrix();
}

void desk1() {

	glPushMatrix();
	glPushMatrix();
	glTranslatef(-76.0, 65.0, 205.0);
	glScalef(30.0, 80.0, 20.0);
	housewall1(229, 202, 160);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, -50.0, 0.0);
	glTranslatef(-76.0, 75.0, 205.0);
	GLfloat mat_ambient[] = { 0.5 * (60 / 255), 0.5 * (60 / 255), 0.5 * (60 / 255), 1.0f };  //定义材质的环境光颜色
	GLfloat mat_diffuse[] = { (60 / 255), (60 / 255), 60 / (255), 1.0f };  //定义材质的漫反射光颜色
	GLfloat mat_specular[] = { 0.0f, 0.0f, 0.0f, 1.0f };   //定义材质的镜面反射光颜色
	GLfloat mat_emission[] = { 0.0f, 0.0f, 0.0f, 1.0f };   //定义材质的辐射光颜色，为0
	GLfloat mat_shininess = 0.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
	glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess);

	glBegin(GL_QUAD_STRIP);
	glVertex3f(-15, -30, 20);    // v1
	glVertex3f(-15, 0, 10);    // v2
	glVertex3f(25, -30, 20);    // v3
	glVertex3f(15, 0, 10);    // v4
	glVertex3f(25, -30, -20);    // v5
	glVertex3f(15, 0, -10);    // v6
	glVertex3f(-15, -30, -20);
	glVertex3f(-15, 0, -10);
	glEnd();

	//glLineWidth(1.45);
	GLfloat mat_ambient1[] = { 0.5 * (0 / 255), 0.5 * (0 / 255), 0.5 * (0 / 255), 1.0f };  //定义材质的环境光颜色
	GLfloat mat_diffuse1[] = { (0 / 255), (0 / 255), (0 / 255), 1.0f };  //定义材质的漫反射光颜色
	GLfloat mat_specular1[] = { 0.0f, 0.0f, 0.0f, 1.0f };   //定义材质的镜面反射光颜色
	GLfloat mat_emission1[] = { 0.0f, 0.0f, 0.0f, 1.0f };   //定义材质的辐射光颜色，为0
	GLfloat mat_shininess1 = 0.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient1);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse1);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular1);
	glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission1);
	glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess1);

	glBegin(GL_LINES);
	glVertex3f(-15, -30, 20);    // v1
	glVertex3f(-15, 0, 10);    // v2
	glVertex3f(25.1, -30, 20);    // v3
	glVertex3f(15.1, 0, 10);    // v4
	glVertex3f(25.1, -30, -20);    // v5
	glVertex3f(15.1, 0, -10);    // v6
	glVertex3f(-15, -30, -20);
	glVertex3f(-15, 0, -10);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, -50.0, -200.0);
	glTranslatef(-76.0, 75.0, 205.0);
	
	GLfloat mat_ambient2[] = { 0.5 * (60 / 255), 0.5 * (60 / 255), 0.5 * (60 / 255), 1.0f };  //定义材质的环境光颜色
	GLfloat mat_diffuse2[] = { (60 / 255), (60 / 255), 60 / (255), 1.0f };  //定义材质的漫反射光颜色
	GLfloat mat_specular2[] = { 0.0f, 0.0f, 0.0f, 1.0f };   //定义材质的镜面反射光颜色
	GLfloat mat_emission2[] = { 0.0f, 0.0f, 0.0f, 1.0f };   //定义材质的辐射光颜色，为0
	GLfloat mat_shininess2 = 0.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient2);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse2);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular2);
	glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission2);
	glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess2);

	glBegin(GL_QUAD_STRIP);
	glVertex3f(-15, -30, 20);    // v1
	glVertex3f(-15, 0, 10);    // v2
	glVertex3f(25, -30, 20);    // v3
	glVertex3f(15, 0, 10);    // v4
	glVertex3f(25, -30, -20);    // v5
	glVertex3f(15, 0, -10);    // v6
	glVertex3f(-15, -30, -20);
	glVertex3f(-15, 0, -10);
	glEnd();

	GLfloat mat_ambient3[] = { 0.5 * (0 / 255), 0.5 * (0 / 255), 0.5 * (0 / 255), 1.0f };  //定义材质的环境光颜色
	GLfloat mat_diffuse3[] = { (0 / 255), (0 / 255), (0 / 255), 1.0f };  //定义材质的漫反射光颜色
	GLfloat mat_specular3[] = { 0.0f, 0.0f, 0.0f, 1.0f };   //定义材质的镜面反射光颜色
	GLfloat mat_emission3[] = { 0.0f, 0.0f, 0.0f, 1.0f };   //定义材质的辐射光颜色，为0
	GLfloat mat_shininess3 = 0.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient3);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse3);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular3);
	glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission3);
	glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess3);

	glBegin(GL_LINES);
	glVertex3f(-15, -30, 20);    // v1
	glVertex3f(-15, 0, 10);    // v2
	glVertex3f(25.1, -30, 20);    // v3
	glVertex3f(15.1, 0, 10);    // v4
	glVertex3f(25.1, -30, -20);    // v5
	glVertex3f(15.1, 0, -10);    // v6
	glVertex3f(-15, -30, -20);
	glVertex3f(-15, 0, -10);
	glEnd();
	glPopMatrix();


	glPushMatrix();
	GLfloat mat_ambient4[] = { 0.5 * (60 / 255), 0.5 * (60 / 255), 0.5 * (60 / 255), 1.0f };  //定义材质的环境光颜色
	GLfloat mat_diffuse4[] = { (60 / 255), (60 / 255), 60 / (255), 1.0f };  //定义材质的漫反射光颜色
	GLfloat mat_specular4[] = { 0.0f, 0.0f, 0.0f, 1.0f };   //定义材质的镜面反射光颜色
	GLfloat mat_emission4[] = { 0.0f, 0.0f, 0.0f, 1.0f };   //定义材质的辐射光颜色，为0
	GLfloat mat_shininess4 = 0.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient4);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse4);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular4);
	glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission4);
	glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess4);
	
	glTranslatef(0.0, 30.0, -100.0);
	glTranslatef(-76.0, 75.0, 205.0);
	glRotatef(-180, 1, 0, 0);
	glScalef(1.0, 0.4, 11);
	//housewall();
	glBegin(GL_QUAD_STRIP);
	glVertex3f(-15, -30, 12);    // v1
	glVertex3f(-15, 0, 10);    // v2
	glVertex3f(25, -30, 12);    // v3
	glVertex3f(15, 0, 10);    // v4
	glVertex3f(25, -30, -12);    // v5
	glVertex3f(15, 0, -10);    // v6
	glVertex3f(-15, -30, -12);
	glVertex3f(-15, 0, -10);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(-15, -30, 12);    // v1
	glVertex3f(25, -30, 12);    // v3
	glVertex3f(25, -30, -12);    // v5
	glVertex3f(-15, -30, -12);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(-15, 0, 10);    // v2
	glVertex3f(15, 0, 10);    // v4
	glVertex3f(15, 0, -10);    // v6
	glVertex3f(-15, 0, -10);
	glEnd();

	//glLineWidth(1.45);
	GLfloat mat_ambient5[] = { 0.5 * (0 / 255), 0.5 * (0 / 255), 0.5 * (0 / 255), 1.0f };  //定义材质的环境光颜色
	GLfloat mat_diffuse5[] = { (0 / 255), (0 / 255), (0 / 255), 1.0f };  //定义材质的漫反射光颜色
	GLfloat mat_specular5[] = { 0.0f, 0.0f, 0.0f, 1.0f };   //定义材质的镜面反射光颜色
	GLfloat mat_emission5[] = { 0.0f, 0.0f, 0.0f, 1.0f };   //定义材质的辐射光颜色，为0
	GLfloat mat_shininess5 = 0.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient5);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse5);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular5);
	glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission5);
	glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess5);

	glBegin(GL_LINES);
	glColor3f(0.0, 0.0, 0.0);
	glVertex3f(-15, -30, 12);    // v1
	glVertex3f(-15, 0, 10);    // v2
	glVertex3f(25.1, -30, 12);    // v3
	glVertex3f(15.1, 0, 10);    // v4
	glVertex3f(25.1, -30, -12);    // v5
	glVertex3f(15.1, 0, -10);    // v6
	glVertex3f(-15, -30, -12);
	glVertex3f(-15, 0, -10);
	glEnd();

	glBegin(GL_LINE_STRIP);
	glVertex3f(-15, -30, 12);    // v1
	glVertex3f(25, -30, 12);    // v3
	glVertex3f(25, -30, -12);    // v5
	glVertex3f(-15, -30, -12);
	glEnd();
	glPopMatrix();


	glPushMatrix();
	glTranslatef(0.0, 0.0, -200.0);
	glTranslatef(-76.0, 65.0, 205.0);
	glScalef(30.0, 80.0, 20.0);
	housewall1(229, 202, 160);
	glPopMatrix();

	glPopMatrix();



}


// elelment to draw the Building and house inside
void tixingelement(float x, float y, float z, float out, float width) {
	glPushMatrix();
	GLfloat mat_ambient[] = { 0.8 * (x / 255), 0.8 * (y / 255), 0.8 * (z / 255), 1.0f };  //定义材质的环境光颜色
	GLfloat mat_diffuse[] = { (255 / 255), (255 / 255), 255 / (255), 1.0f };  //定义材质的漫反射光颜色
	GLfloat mat_specular[] = { 0.0f, 0.0f, 0.0f, 1.0f };   //定义材质的镜面反射光颜色
	GLfloat mat_emission[] = { 0.0f, 0.0f, 0.0f, 1.0f };   //定义材质的辐射光颜色，为0
	GLfloat mat_shininess = 0.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
	glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess);

	/*glTranslatef(0.0, 30.0, -100.0);
	glTranslatef(-76.0, 75.0, 205.0);
	glRotatef(-180, 1, 0, 0);
	glScalef(1.0, 0.4, 11);*/
	//housewall();
	glBegin(GL_QUAD_STRIP);
	glVertex3f(-15, -30, out);    // v1
	glVertex3f(-15, 0, 10);    // v2
	glVertex3f(width, -30, out);    // v3
	glVertex3f(15, 0, 10);    // v4
	glVertex3f(width, -30, -out);    // v5
	glVertex3f(15, 0, -10);    // v6
	glVertex3f(-15, -30, -out);
	glVertex3f(-15, 0, -10);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(-15, -30, out);    // v1
	glVertex3f(width, -30, out);    // v3
	glVertex3f(width, -30, -out);    // v5
	glVertex3f(-15, -30, -out);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(-15, 0, 10);    // v2
	glVertex3f(15, 0, 10);    // v4
	glVertex3f(15, 0, -10);    // v6
	glVertex3f(-15, 0, -10);
	glEnd();

	//glLineWidth(1.45);
	GLfloat mat_ambient5[] = { 0.5 * (0 / 255), 0.5 * (0 / 255), 0.5 * (0 / 255), 1.0f };  //定义材质的环境光颜色
	GLfloat mat_diffuse5[] = { (0 / 255), (0 / 255), (0 / 255), 1.0f };  //定义材质的漫反射光颜色
	GLfloat mat_specular5[] = { 0.0f, 0.0f, 0.0f, 1.0f };   //定义材质的镜面反射光颜色
	GLfloat mat_emission5[] = { 0.0f, 0.0f, 0.0f, 1.0f };   //定义材质的辐射光颜色，为0
	GLfloat mat_shininess5 = 0.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient5);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse5);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular5);
	glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission5);
	glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess5);

	glBegin(GL_LINES);
	glColor3f(0.0, 0.0, 0.0);
	glVertex3f(-15, -30, out);    // v1
	glVertex3f(-15, 0, 10);    // v2
	glVertex3f(width + 0.1, -30, out);    // v3
	glVertex3f(15.1, 0, 10);    // v4
	glVertex3f(width + 0.1, -30, -out);    // v5
	glVertex3f(15.1, 0, -10);    // v6
	glVertex3f(-15, -30, -out);
	glVertex3f(-15, 0, -10);
	glEnd();

	glBegin(GL_LINE_STRIP);
	glVertex3f(-15, -30, out);    // v1
	glVertex3f(width, -30, out);    // v3
	glVertex3f(width, -30, -out);    // v5
	glVertex3f(-15, -30, -out);
	glEnd();

	glBegin(GL_LINE_STRIP);
	glVertex3f(-15, 0, 10);    // v2
	glVertex3f(15, 0, 10);    // v4
	glVertex3f(15, 0, -10);    // v6
	glVertex3f(-15, 0, -10);
	glEnd();

	glPopMatrix();
}

// elelment to draw the Building and house inside
void wailizhuelement(float x, float y, float z, float out, float width, float up_width) {
	glPushMatrix();
	GLfloat mat_ambient[] = { 0.8 * (x / 255), 0.8 * (y / 255), 0.8 * (z / 255), 1.0f };  //定义材质的环境光颜色
	GLfloat mat_diffuse[] = { (255 / 255), (255 / 255), 255 / (255), 1.0f };  //定义材质的漫反射光颜色
	GLfloat mat_specular[] = { 0.0f, 0.0f, 0.0f, 1.0f };   //定义材质的镜面反射光颜色
	GLfloat mat_emission[] = { 0.0f, 0.0f, 0.0f, 1.0f };   //定义材质的辐射光颜色，为0
	GLfloat mat_shininess = 0.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
	glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess);

	/*glTranslatef(0.0, 30.0, -100.0);
	glTranslatef(-76.0, 75.0, 205.0);
	glRotatef(-180, 1, 0, 0);
	glScalef(1.0, 0.4, 11);*/
	//housewall();
	glBegin(GL_QUAD_STRIP);
	glVertex3f(-width, -30, out);    // v1
	glVertex3f(-up_width, 0, 10);    // v2
	glVertex3f(width, -30, out);    // v3
	glVertex3f(up_width, 0, 10);    // v4
	glVertex3f(width, -30, -out);    // v5
	glVertex3f(up_width, 0, -10);    // v6
	glVertex3f(-width, -30, -out);
	glVertex3f(-up_width, 0, -10);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(-width, -30, out);    // v1
	glVertex3f(width, -30, out);    // v3
	glVertex3f(width, -30, -out);    // v5
	glVertex3f(-width, -30, -out);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(-up_width, 0, 10);    // v2
	glVertex3f(up_width, 0, 10);    // v4
	glVertex3f(up_width, 0, -10);    // v6
	glVertex3f(-up_width, 0, -10);
	glEnd();

	//glLineWidth(1.45);
	GLfloat mat_ambient5[] = { 0.5 * (0 / 255), 0.5 * (0 / 255), 0.5 * (0 / 255), 1.0f };  //定义材质的环境光颜色
	GLfloat mat_diffuse5[] = { (0 / 255), (0 / 255), (0 / 255), 1.0f };  //定义材质的漫反射光颜色
	GLfloat mat_specular5[] = { 0.0f, 0.0f, 0.0f, 1.0f };   //定义材质的镜面反射光颜色
	GLfloat mat_emission5[] = { 0.0f, 0.0f, 0.0f, 1.0f };   //定义材质的辐射光颜色，为0
	GLfloat mat_shininess5 = 0.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient5);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse5);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular5);
	glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission5);
	glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess5);

	glBegin(GL_LINES);
	glColor3f(0.0, 0.0, 0.0);
	glVertex3f(-width, -30, out);    // v1
	glVertex3f(-up_width, 0, 10);    // v2
	glVertex3f(width + 0.1, -30, out);    // v3
	glVertex3f(up_width + 0.1, 0, 10);    // v4
	glVertex3f(width + 0.1, -30, -out);    // v5
	glVertex3f(up_width + 0.1, 0, -10);    // v6
	glVertex3f(-width, -30, -out);
	glVertex3f(-up_width, 0, -10);
	glEnd();

	glBegin(GL_LINE_STRIP);
	glVertex3f(-width, -30, out);    // v1
	glVertex3f(width, -30, out);    // v3
	glVertex3f(width, -30, -out);    // v5
	glVertex3f(-width, -30, -out);
	glEnd();

	glBegin(GL_LINE_STRIP);
	glVertex3f(-up_width, 0, 10);    // v2
	glVertex3f(up_width, 0, 10);    // v4
	glVertex3f(up_width, 0, -10);    // v6
	glVertex3f(-up_width, 0, -10);
	glEnd();

	glPopMatrix();
}

void mirror1(float x, float y, float z) {

	glPushMatrix();
	GLfloat mat_ambient[] = { 0.5 * (x / 255), 0.5 * (y / 255), 0.5 * z / (255), 1.0f };  //定义材质的环境光颜色
	GLfloat mat_diffuse[] = { 1, 1, 1, 1.0f };  //定义材质的漫反射光颜色
	GLfloat mat_specular[] = { 0.0f, 0.0f, 0.0f, 1.0f };   //定义材质的镜面反射光颜色
	GLfloat mat_emission[] = { 0.0f, 0.0f, 0.0f, 1.0f };   //定义材质的辐射光颜色，为0
	GLfloat mat_shininess = 0.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
	glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess);
	glutSolidTorus(2.0, 35.0, 10, 30);
	GLfloat mat_ambient1[] = { 0.8 * (169.0 / 255), 0.8 * (159.0 / 255), 0.8 * 133.0 / (255), 1.0f };
	GLfloat mat_diffuse1[] = { 0.6, 0.6, 0.6, 1.0f };  //定义材质的漫反射光颜色
	GLfloat mat_specular1[] = { 1.0f, 1.0f, 1.0f, 1.0f };   //定义材质的镜面反射光颜色
	GLfloat mat_shininess1 = 70.0f;
	glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess1);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient1);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse1);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular1);
	glutSolidCylinder(33.0, 2.0, 30, 30);
	glPopMatrix();
}

// elelment to draw the Paintings
void huakuang11(float x, float y, float z, float angle, int text) {

	glPushMatrix();
	glTranslatef(0.0, -45.0, 0.0);
	glTranslatef(0.0, 200.0, 200.0);
	glScalef(80.0, 80.0, 5.0);
	if (text == 2) {
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texture[2]);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0, 0.0); glVertex3f(-0.5, -0.5, -0.5);
		glTexCoord2f(0.0, 1.0); glVertex3f(-0.5, 0.5, -0.5);
		glTexCoord2f(1.0, 1.0); glVertex3f(0.5, 0.5, -0.5);
		glTexCoord2f(1.0, 0.0); glVertex3f(0.5, -0.5, -0.5);
		glEnd();
		glDisable(GL_TEXTURE_2D);

	}


	if (text == 4) {
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texture[4]);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0, 0.0); glVertex3f(-0.5, -0.5, -0.5);
		glTexCoord2f(0.0, 1.0); glVertex3f(-0.5, 0.5, -0.5);
		glTexCoord2f(1.0, 1.0); glVertex3f(0.5, 0.5, -0.5);
		glTexCoord2f(1.0, 0.0); glVertex3f(0.5, -0.5, -0.5);
		glEnd();
		glDisable(GL_TEXTURE_2D);
	}
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, 200.0, 200.0);
	glScalef(100.0, 10.0, 5.0);
	glRotatef(angle, 0, 1, 0);
	housewall2(x, y, z, 0.6);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-45.0, -45.0, 0.0);
	glTranslatef(0.0, 200.0, 200.0);
	glRotatef(90, 0, 0, 1);
	glScalef(100.0, 10.0, 5.0);
	glRotatef(angle, 0, 1, 0);
	housewall2(x, y, z, 0.6);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, -90.0, 0.0);
	glTranslatef(0.0, 200.0, 200.0);
	glScalef(100.0, 10.0, 5.0);
	glRotatef(angle, 0, 1, 0);
	housewall2(x, y, z, 0.6);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(45.0, -45.0, 0.0);
	glTranslatef(0.0, 200.0, 200.0);
	glRotatef(90, 0, 0, 1);
	glScalef(100.0, 10.0, 5.0);
	glRotatef(angle, 0, 1, 0);
	housewall2(x, y, z, 0.6);
	glPopMatrix();
}

void window1(float x, float y, float z, float angle) {
	glPushMatrix();
	glScalef(100.0, 10.0, 5.0);
	glRotatef(angle, 0, 1, 0);
	housewall1(x, y, z);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-45.0, -45.0, 0.0);
	glRotatef(90, 0, 0, 1);
	glScalef(100.0, 10.0, 5.0);
	glRotatef(angle, 0, 1, 0);
	housewall1(x, y, z);
	glPopMatrix();

	/*glPushMatrix();
	glColor3ub(x, y, z);
	glTranslatef(0.0, -90.0, 0.0);
	glScalef(100.0, 10.0, 5.0);
	glRotatef(angle, 0, 1, 0);
	housewall();
	glPopMatrix();*/

	glPushMatrix();
	glTranslatef(45.0, -45.0, 0.0);
	glRotatef(90, 0, 0, 1);
	glScalef(100.0, 10.0, 5.0);
	glRotatef(angle, 0, 1, 0);
	housewall1(x, y, z);
	glPopMatrix();


	//KUANGJIA
	glPushMatrix();
	//glColor3ub(x, y, z);
	glTranslatef(0.0, 4.0, 0.0);
	glScalef(100.0, 2.0, 6.0);
	glRotatef(angle, 0, 1, 0);
	housewall1(255, 251, 240);
	glPopMatrix();

	glPushMatrix();
	//glColor3ub(x, y, z);
	glTranslatef(-49.0, -45.0, 0.0);
	glRotatef(90, 0, 0, 1);
	glScalef(100.0, 2.0, 6.0);
	glRotatef(angle, 0, 1, 0);
	housewall1(255, 251, 240);
	glPopMatrix();

	glPushMatrix();
	//glColor3ub(x, y, z);
	glTranslatef(0.0, -96.0, 0.0);
	glScalef(100.0, 2.0, 6.0);
	glRotatef(angle, 0, 1, 0);
	housewall1(255, 251, 240);
	glPopMatrix();

	glPushMatrix();
	//glColor3ub(x, y, z);
	glTranslatef(49.0, -45.0, 0.0);
	glRotatef(90, 0, 0, 1);
	glScalef(100.0, 2.0, 6.0);
	glRotatef(angle, 0, 1, 0);
	housewall1(255, 251, 240);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, -45.0, 0.0);
	glScalef(6.0, 100.0, 1.0);
	glRotatef(angle, 0, 1, 0);
	housewall1(255, 251, 240);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-37.0, -45.0, 0.0);
	glScalef(6.0, 100.0, 1.0);
	glRotatef(angle, 0, 1, 0);
	housewall1(255, 251, 240);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(37.0, -45.0, 0.0);
	glScalef(6.0, 100.0, 1.0);
	glRotatef(angle, 0, 1, 0);
	housewall1(255, 251, 240);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-18.5, -45.0, 0.0);
	glScalef(1.0, 100.0, 1.0);
	glRotatef(angle, 0, 1, 0);
	housewall1(255, 251, 240);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(18.5, -45.0, 0.0);
	glScalef(1.0, 100.0, 1.0);
	glRotatef(angle, 0, 1, 0);
	housewall1(255, 251, 240);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, -20.0, 0.0);
	glScalef(100.0, 5.0, 1.0);
	housewall1(255, 251, 240);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, -40.0, 0.0);
	glScalef(100.0, 1.0, 1.0);
	housewall1(255, 251, 240);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, -60.0, 0.0);
	glScalef(100.0, 1.0, 1.0);
	housewall1(255, 251, 240);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, -80.0, 0.0);
	glScalef(100.0, 1.0, 1.0);
	housewall1(255, 251, 240);
	glPopMatrix();
}

void window2(float x, float y, float z, float angle) {
	glPushMatrix();
	glScalef(100.0, 10.0, 5.0);
	glRotatef(angle, 0, 1, 0);
	housewall1(x, y, z);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-45.0, -45.0, 0.0);
	glRotatef(90, 0, 0, 1);
	glScalef(100.0, 10.0, 5.0);
	glRotatef(angle, 0, 1, 0);
	housewall1(x, y, z);
	glPopMatrix();


	glPushMatrix();
	glTranslatef(45.0, -45.0, 0.0);
	glRotatef(90, 0, 0, 1);
	glScalef(100.0, 10.0, 5.0);
	glRotatef(angle, 0, 1, 0);
	housewall1(x, y, z);
	glPopMatrix();


	//KUANGJIA
	glPushMatrix();
	//glColor3ub(x, y, z);
	glTranslatef(0.0, 4.0, 0.0);
	glScalef(100.0, 2.0, 6.0);
	glRotatef(angle, 0, 1, 0);
	housewall1(255, 251, 240);
	glPopMatrix();

	glPushMatrix();
	//glColor3ub(x, y, z);
	glTranslatef(-49.0, -45.0, 0.0);
	glRotatef(90, 0, 0, 1);
	glScalef(100.0, 2.0, 6.0);
	glRotatef(angle, 0, 1, 0);
	housewall1(255, 251, 240);
	glPopMatrix();

	glPushMatrix();
	//glColor3ub(x, y, z);
	glTranslatef(0.0, -96.0, 0.0);
	glScalef(100.0, 2.0, 6.0);
	glRotatef(angle, 0, 1, 0);
	housewall1(255, 251, 240);
	glPopMatrix();

	glPushMatrix();
	//glColor3ub(x, y, z);
	glTranslatef(49.0, -45.0, 0.0);
	glRotatef(90, 0, 0, 1);
	glScalef(100.0, 2.0, 6.0);
	glRotatef(angle, 0, 1, 0);
	housewall1(255, 251, 240);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, -45.0, 0.0);
	glScalef(6.0, 100.0, 1.0);
	glRotatef(angle, 0, 1, 0);
	housewall1(255, 251, 240);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-37.0, -45.0, 0.0);
	glScalef(6.0, 100.0, 1.0);
	glRotatef(angle, 0, 1, 0);
	housewall1(255, 251, 240);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(37.0, -45.0, 0.0);
	glScalef(6.0, 100.0, 1.0);
	glRotatef(angle, 0, 1, 0);
	housewall1(255, 251, 240);
	glPopMatrix();

	

	glPushMatrix();
	glTranslatef(0.0, -30.0, 0.0);
	glScalef(100.0, 5.0, 1.0);
	housewall1(255, 251, 240);
	glPopMatrix();

	
}

void window3(float x, float y, float z, float angle) {
	glPushMatrix();
	glScalef(100.0, 10.0, 5.0);
	glRotatef(angle, 0, 1, 0);
	housewall1(x, y, z);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-45.0, -45.0, 0.0);
	glRotatef(90, 0, 0, 1);
	glScalef(100.0, 10.0, 5.0);
	glRotatef(angle, 0, 1, 0);
	housewall1(x, y, z);
	glPopMatrix();

	

	glPushMatrix();
	glTranslatef(45.0, -45.0, 0.0);
	glRotatef(90, 0, 0, 1);
	glScalef(100.0, 10.0, 5.0);
	glRotatef(angle, 0, 1, 0);
	housewall1(x, y, z);
	glPopMatrix();


	//KUANGJIA
	glPushMatrix();
	//glColor3ub(x, y, z);
	glTranslatef(0.0, 4.0, 0.0);
	glScalef(100.0, 2.0, 6.0);
	glRotatef(angle, 0, 1, 0);
	housewall1(255, 251, 240);
	glPopMatrix();

	glPushMatrix();
	//glColor3ub(x, y, z);
	glTranslatef(-49.0, -45.0, 0.0);
	glRotatef(90, 0, 0, 1);
	glScalef(100.0, 2.0, 6.0);
	glRotatef(angle, 0, 1, 0);
	housewall1(255, 251, 240);
	glPopMatrix();

	glPushMatrix();
	//glColor3ub(x, y, z);
	glTranslatef(0.0, -96.0, 0.0);
	glScalef(100.0, 2.0, 6.0);
	glRotatef(angle, 0, 1, 0);
	housewall1(255, 251, 240);
	glPopMatrix();

	glPushMatrix();
	//glColor3ub(x, y, z);
	glTranslatef(49.0, -45.0, 0.0);
	glRotatef(90, 0, 0, 1);
	glScalef(100.0, 2.0, 6.0);
	glRotatef(angle, 0, 1, 0);
	housewall1(255, 251, 240);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-10.0, -45.0, 0.0);
	glScalef(4.0, 100.0, 4.0);
	glRotatef(angle, 0, 1, 0);
	housewall1(255, 251, 240);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(10.0, -45.0, 0.0);
	glScalef(4.0, 100.0, 4.0);
	glRotatef(angle, 0, 1, 0);
	housewall1(255, 251, 240);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-37.0, -45.0, 0.0);
	glScalef(6.0, 100.0, 1.0);
	glRotatef(angle, 0, 1, 0);
	housewall1(255, 251, 240);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(37.0, -45.0, 0.0);
	glScalef(6.0, 100.0, 1.0);
	glRotatef(angle, 0, 1, 0);
	housewall1(255, 251, 240);
	glPopMatrix();

	

	glPushMatrix();
	glTranslatef(0.0, -25.0, 0.0);
	glScalef(100.0, 4.0, 2.0);
	housewall1(255, 251, 240);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, -45.0, 0.0);
	glScalef(100.0, 4.0, 2.0);
	housewall1(255, 251, 240);
	glPopMatrix();


}

//Entrance hall
void xuanguan1() {
	//Qiang
	glPushMatrix();
	glTranslatef(-100.0, 180.0, 130.0);
	glScalef(10.0, 350.0, 450.0);
	housewall1(255, 251, 240);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(200.0, 0.0, 0.0);
	glTranslatef(-100.0, 180.0, 130.0);
	glScalef(10.0, 350.0, 450.0);
	housewall1(255, 251, 240);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(186.0, 0.0, 0.0);
	glTranslatef(-93, 20.0, 130.0);
	glScalef(3.0, 30.0, 450.0);
	housewall1(255, 251, 240);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-93, 20.0, 130.0);
	glScalef(3.0, 30.0, 450.0);
	housewall1(255, 251, 240);
	glPopMatrix();
	//

	//XUANGUANDIBIAN
	glPushMatrix();
	glTranslatef(-82.75, 20.0, 352.75);
	glScalef(16.5, 30.0, 3.5);
	housewall1(255, 251, 240);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(165.5, 0.0, 0.0);
	glTranslatef(-82.75, 20.0, 352.75);
	glScalef(16.5, 30.0, 3.5);
	housewall1(255, 251, 240);
	glPopMatrix();
	//

	//XUANGUANDOOR
	glPushMatrix();
	glTranslatef(0.0, 275.0, 377.0);
	glScalef(1.0545, 2.0, 1.0 * 5 / 9);
	huakuangMEN(255, 251, 240);
	glPopMatrix();
	//

	glPushMatrix();
	glColor3ub(255, 251, 240);
	desk1();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-90.0, 205.0, 105.0);
	glRotatef(-93, 0, 1, 0);
	mirror1(40, 40, 40);
	glPopMatrix();

	glPushMatrix();
	glRotatef(90, 0, 1, 0);
	glTranslatef(0.0, 50.0, -110.0);
	huakuang11(60, 60, 60, 0, 2);
	glPopMatrix();

	glPushMatrix();
	glRotatef(90, 0, 1, 0);
	glTranslatef(-200.0, 50.0, -107.5);
	huakuang11(60, 60, 60, 0, 4);
	glPopMatrix();

	cicleroof(255, 251, 240);

	glPushMatrix();
	glTranslatef(0.0, 285.0, 130);
	glRotatef(-90, 1, 0, 0);
	glScalef(15, 15.0, 40);
	coneLight(243, 155, 66);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, 315.0, 130);
	glRotatef(-90, 1, 0, 0);
	glScalef(1, 1.0, 60);
	cylinder(255, 245, 225);
	glPopMatrix();


}

//Curtain
void chuanlian_element(int x, float move, float angle) {

	glPushMatrix();
	glTranslatef(2.5, 355.0, 1133.5);
	if (x == 1) {
		glTranslatef(move - 75 * cos(10 * (6.284 / 360.0)), 0, 0);
	}

	if (x == 2) {
		glTranslatef(-move + 75 * cos(10 * (6.284 / 360.0)), 0, 0);
	}

	if (x == 3) {
		glTranslatef((move - 75 * cos(10 * (6.284 / 360.0))) / 2, 0, 0);
	}

	if (x == 4) {
		glTranslatef((-move + 75 * cos(10 * (6.284 / 360.0))) / 2, 0, 0);
	}
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient4);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse4);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular4);
	glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission4);
	glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess4);

	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	glScalef(5, 5.0, 320);
	glutSolidCylinder(1, 1, 30, 1);
	glPopMatrix();

	glPushMatrix();
	if (x == 1 || x == 2 || x == 3 || x == 4) {
		glRotatef(angle, 0, 1, 0);
	}
	else {
		glRotatef(10, 0, 1, 0);
	}
	glTranslatef(-2.5, -160.0, 36.5);
	glScalef(5, 320.0, 75);
	housewall1(255, 251, 240);
	glPopMatrix();

	glPushMatrix();
	if (x == 1 || x == 2 || x == 3 || x == 4) {
		glRotatef(-angle, 0, 1, 0);
	}
	else {
		glRotatef(-10, 0, 1, 0);
	}
	glTranslatef(2.5, -160.0, 36.5);
	glScalef(5, 320.0, 75);
	housewall1(255, 251, 240);
	glPopMatrix();
	glPopMatrix();

}

//Curtain
void chuanlian1() {
	//CHUANGLIAN
	glPushMatrix();
	glPushMatrix();
	glTranslatef(25, 0.0, 0.0);
	chuanlian_element(1, chuanlian_move, angle_chuanlian);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(45, 0.0, 0.0);
	chuanlian_element(0, chuanlian_move, angle_chuanlian);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(65, 0.0, 0.0);
	chuanlian_element(0, chuanlian_move, angle_chuanlian);
	glPopMatrix();

	glPopMatrix();
	//
}

//Curtain
void chuanlian3() {
	//CHUANGLIAN
	glPushMatrix();

	glPushMatrix();
	glTranslatef(0, 0.0, 0.0);
	chuanlian_element(0, chuanlian_move, angle_chuanlian);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(25, 0.0, 0.0);
	chuanlian_element(0, chuanlian_move, angle_chuanlian);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(45, 0.0, 0.0);
	chuanlian_element(0, chuanlian_move, angle_chuanlian);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(65, 0.0, 0.0);
	chuanlian_element(2, chuanlian_move, angle_chuanlian);
	glPopMatrix();

	glPopMatrix();
	//
}

//Curtain
void chuanlian2() {
	//CHUANGLIAN
	glPushMatrix();

	glPushMatrix();
	glTranslatef(25, 0.0, 0.0);
	chuanlian_element(1, chuanlian_move, angle_chuanlian);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(45, 0.0, 0.0);
	chuanlian_element(3, chuanlian_move, angle_chuanlian);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(65, 0.0, 0.0);
	chuanlian_element(4, chuanlian_move, angle_chuanlian);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(85, 0.0, 0.0);
	chuanlian_element(2, chuanlian_move, angle_chuanlian);
	glPopMatrix();


	glPopMatrix();
	//
}

//Curtain
void chuanlian4() {
	//CHUANGLIAN
	glPushMatrix();

	glPushMatrix();
	glTranslatef(0, 0.0, 0.0);
	chuanlian_element(0, chuanlian_move1, angle_chuanlian1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(25, 0.0, 0.0);
	chuanlian_element(0, chuanlian_move1, angle_chuanlian1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(45, 0.0, 0.0);
	chuanlian_element(0, chuanlian_move1, angle_chuanlian1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(65, 0.0, 0.0);
	chuanlian_element(2, chuanlian_move1, angle_chuanlian1);
	glPopMatrix();

	glPopMatrix();
	//
}

//Curtain
void chuanlian5() {
	//CHUANGLIAN
	glPushMatrix();
	glPushMatrix();
	glTranslatef(25, 0.0, 0.0);
	chuanlian_element(1, chuanlian_move1, angle_chuanlian1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(40, 0.0, 0.0);
	chuanlian_element(0, chuanlian_move1, angle_chuanlian1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(60, 0.0, 0.0);
	chuanlian_element(0, chuanlian_move1, angle_chuanlian1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(80, 0.0, 0.0);
	chuanlian_element(0, chuanlian_move1, angle_chuanlian1);
	glPopMatrix();

	glPopMatrix();
	//
}

//Lights in the middle of the house
void taideng() {
	//TAIDENG
	glPushMatrix();
	glTranslatef(85, 75.0, 1018.5);
	glScalef(25, 110.0, 25);
	housewall1(255, 251, 230);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(85, 133.5, 1018.5);
	glScalef(25, 5.0, 25);
	housewall1(200, 148, 101);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(85, 18.5, 1018.5);
	glScalef(25, 5.0, 25);
	housewall1(200, 148, 101);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(85, 287, 1018.5);
	glRotatef(90, 1, 0, 0);
	glScalef(25, 25.0, 120);
	GLfloat mat_ambient4[] = { 0.8 * (255.0 / 255), 0.8 * (251.0 / 255), 0.8 * 240.0 / (255), 1.0f };  //定义材质的环境光颜色
	GLfloat mat_diffuse4[] = { (255.0 / 255), (251.0 / 255), 240.0 / (255), 1.0f };  //定义材质的漫反射光颜色
	GLfloat mat_specular4[] = { 0.0f, 0.0f, 0.0f, 1.0f };   //定义材质的镜面反射光颜色
	GLfloat mat_emission4[] = { 0.0f, 0.0f, 0.0f, 1.0f };   //定义材质的辐射光颜色，为0
	GLfloat mat_shininess4 = 0.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient4);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse4);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular4);
	glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission4);
	glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess4);
	glutSolidCylinder(1, 1, 30, 1);
	GLfloat mat_ambient3[] = { 0, 0, 0, 1.0f };  //定义材质的环境光颜色
	GLfloat mat_diffuse3[] = { 0, 0, 0, 1.0f };  //定义材质的漫反射光颜色
	GLfloat mat_specular3[] = { 0.0f, 0.0f, 0.0f, 1.0f };   //定义材质的镜面反射光颜色
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient3);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse3);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular3);
	glutWireCylinder(1, 1, 20, 1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(85, 187, 1018.5);
	glRotatef(90, 1, 0, 0);
	glScalef(1.0, 1.0, 120);
	GLfloat mat_emission[] = { 0.83 * (200.0 / 255), 0.83 * (148.0 / 255) , 101.0 / (255), 1.0f };  //定义材质的环境光颜色
	glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
	glutSolidCylinder(1, 1, 30, 1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(85, 289.5, 1018.5);
	glRotatef(90, 1, 0, 0);
	glScalef(25, 25.0, 2);
	//glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient5);
	glutSolidCylinder(1, 1, 30, 1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(85, 166.5, 1018.5);
	glRotatef(90, 1, 0, 0);
	glScalef(25, 25.0, 2);
	//glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient5);
	glutSolidCylinder(1, 1, 30, 1);
	glPopMatrix();
	//
}

//Dest in the house
void canyi() {
	//CANYI
	glPushMatrix();
	glTranslatef(-300.0, 18.0, 775.0);
	glScalef(2.0, 2.0, 50);
	cylinder(0, 0, 0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-387.5, 18.0, 770.0);
	glRotatef(90, 0, 1, 0);
	glScalef(2.0, 2.0, 50);
	cylinder(0, 0, 0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-387.5, 18.0, 830.0);
	glRotatef(90, 0, 1, 0);
	glScalef(2.0, 2.0, 50);
	cylinder(0, 0, 0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-300.0, 118.0, 800.0);
	glRotatef(90, 1, 0, 0);
	glScalef(2.0, 2.0, 100);
	cylinder(0, 0, 0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-357.5, 118.0, 770.0);
	glRotatef(90, 1, 0, 0);
	glScalef(2.0, 2.0, 100);
	cylinder(0, 0, 0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-357.5, 118.0, 830.0);
	glRotatef(90, 1, 0, 0);
	glScalef(2.0, 2.0, 100);
	cylinder(0, 0, 0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-360.0, 68.0, 800.0);
	glRotatef(90, 0, 1, 0);
	glScalef(30.0, 8.0, 60);
	cylinder(255, 245, 225);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-305.0, 158.0, 830.0);
	glRotatef(90, 1, 0, 0);
	glScalef(5.0, 5.0, 60);
	cylinder(255, 245, 225);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-305.0, 158.0, 770.0);
	glRotatef(90, 1, 0, 0);
	glScalef(5.0, 5.0, 60);
	cylinder(255, 245, 225);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-305.0, 128.0, 800.0);
	glScalef(10.0, 60.0, 60);
	housewall1(255, 245, 225);
	glPushMatrix();

	GLfloat mat_ambient[] = { 0.8 * (255.0 / 255), 0.8 * (245.0 / 255), 0.8 * 225.0 / (255), 1.0f };  //定义材质的环境光颜色
	GLfloat mat_diffuse[] = { (225.0 / 255), (221.0 / 255), 210.0 / (255), 1.0f };  //定义材质的漫反射光颜色
	GLfloat mat_specular[] = { 0.0f, 0.0f, 0.0f, 1.0f };   //定义材质的镜面反射光颜色
	GLfloat mat_emission[] = { 0.0f, 0.0f, 0.0f, 1.0f };   //定义材质的辐射光颜色，为0
	GLfloat mat_shininess = 0.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
	glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess);

	glBegin(GL_QUAD_STRIP);
	glVertex3f(0, -0.5, 0.5);    // v1
	glVertex3f(0, -0.5, 0.4);    // v2
	glVertex3f(0, 0.5, 0.5);    // v3
	glVertex3f(0, 0.5, 0.4);    // v4
	glVertex3f(-5.5, 0.0, 0.5);    // v5
	glVertex3f(-5.5, 0.0, 0.4);    // v6
	glVertex3f(-5.5, -0.5, 0.5);
	glVertex3f(-5.5, -0.5, 0.4);
	glVertex3f(0, -0.5, 0.5);    // v1
	glVertex3f(0, -0.5, 0.4);    // v2
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(0, -0.5, 0.5);    // v2
	glVertex3f(0, 0.5, 0.5);    // v3
	glVertex3f(-5.5, 0.0, 0.5);    // v5
	glVertex3f(-5.5, -0.5, 0.5);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(0, -0.5, 0.4);    // v2
	glVertex3f(0, 0.5, 0.4);    // v3
	glVertex3f(-5.5, 0.0, 0.4);    // v5
	glVertex3f(-5.5, -0.5, 0.4);
	glEnd();

	glBegin(GL_QUAD_STRIP);
	glVertex3f(0, -0.5, -0.5);    // v1
	glVertex3f(0, -0.5, -0.4);    // v2
	glVertex3f(0, 0.5, -0.5);    // v3
	glVertex3f(0, 0.5, -0.4);    // v4
	glVertex3f(-5.5, 0.0, -0.5);    // v5
	glVertex3f(-5.5, 0.0, -0.4);    // v6
	glVertex3f(-5.5, -0.5, -0.5);
	glVertex3f(-5.5, -0.5, -0.4);
	glVertex3f(0, -0.5, -0.5);    // v1
	glVertex3f(0, -0.5, -0.4);    // v2
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(0, -0.5, -0.5);    // v2
	glVertex3f(0, 0.5, -0.5);    // v3
	glVertex3f(-5.5, 0.0, -0.5);    // v5
	glVertex3f(-5.5, -0.5, -0.5);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(0, -0.5, -0.4);    // v2
	glVertex3f(0, 0.5, -0.4);    // v3
	glVertex3f(-5.5, 0.0, -0.4);    // v5
	glVertex3f(-5.5, -0.5, -0.4);
	glEnd();

	GLfloat mat_ambient1[] = { 0.5 * (0 / 255), 0.5 * (0 / 255), 0.5 * (0 / 255), 1.0f };  //定义材质的环境光颜色
	GLfloat mat_diffuse1[] = { (0 / 255), (0 / 255), (0 / 255), 1.0f };  //定义材质的漫反射光颜色
	GLfloat mat_specular1[] = { 0.0f, 0.0f, 0.0f, 1.0f };   //定义材质的镜面反射光颜色
	GLfloat mat_emission1[] = { 0.0f, 0.0f, 0.0f, 1.0f };   //定义材质的辐射光颜色，为0
	GLfloat mat_shininess1 = 0.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient1);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse1);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular1);
	glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission1);
	glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess1);

	glBegin(GL_LINE_STRIP);
	glVertex3f(0, -0.5, -0.5);    // v2
	glVertex3f(0, 0.5, -0.5);    // v3
	glVertex3f(-5.5, 0.0, -0.5);    // v5
	glVertex3f(-5.5, -0.5, -0.5);
	glVertex3f(0, -0.5, -0.5);    // v2
	glEnd();

	glBegin(GL_LINE_STRIP);
	glVertex3f(0, -0.5, -0.4);    // v2
	glVertex3f(0, 0.5, -0.4);    // v3
	glVertex3f(-5.5, 0.0, -0.4);    // v5
	glVertex3f(-5.5, -0.5, -0.4);
	glVertex3f(0, -0.5, -0.4);    // v2
	glEnd();

	glBegin(GL_LINE_STRIP);
	glVertex3f(0, -0.5, 0.5);    // v2
	glVertex3f(0, 0.5, 0.5);    // v3
	glVertex3f(-5.5, 0.0, 0.5);    // v5
	glVertex3f(-5.5, -0.5, 0.5);
	glVertex3f(0, -0.5, 0.5);    // v2
	glEnd();

	glBegin(GL_LINE_STRIP);
	glVertex3f(0, -0.5, 0.4);    // v2
	glVertex3f(0, 0.5, 0.4);    // v3
	glVertex3f(-5.5, 0.0, 0.4);    // v5
	glVertex3f(-5.5, -0.5, 0.4);
	glVertex3f(0, -0.5, 0.4);    // v2
	glEnd();
	glPopMatrix();
	glPopMatrix();


	//

}

//Ligts in the left of the house
void ditan_deng() {
	//DITAN Deng
	glPushMatrix();
	glTranslatef(400.0, 448.0, 825.0);
	glRotatef(90, 1, 0, 0);
	glScalef(0.7, 0.7, 100);
	cylinder(0, 0, 0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(400.0, 425.0, 825.0);
	glRotatef(90, 1, 0, 0);
	glScalef(6, 6.0, 20);
	cylinder(40, 40, 40);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(400.0, 350.0, 825.0);
	glRotatef(0, 1, 0, 0);
	glScalef(1, 1.0, 60);
	cylinder(0, 0, 0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(400.0, 350.0, 825.0);
	glRotatef(45, 0, 1, 0);
	glScalef(1, 1.0, 60);
	cylinder(0, 0, 0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(400.0, 350.0, 825.0);
	glRotatef(90, 0, 1, 0);
	glScalef(1, 1.0, 60);
	cylinder(0, 0, 0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(400.0, 350.0, 825.0);
	glRotatef(135, 0, 1, 0);
	glScalef(1, 1.0, 60);
	cylinder(0, 0, 0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(400.0, 350.0, 825.0);
	glRotatef(180, 0, 1, 0);
	glScalef(1, 1.0, 60);
	cylinder(0, 0, 0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(400.0, 350.0, 825.0);
	glRotatef(225, 0, 1, 0);
	glScalef(1, 1.0, 60);
	cylinder(0, 0, 0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(400.0, 350.0, 825.0);
	glRotatef(270, 0, 1, 0);
	glScalef(1, 1.0, 60);
	cylinder(0, 0, 0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(400.0, 350.0, 825.0);
	glRotatef(315, 0, 1, 0);
	glScalef(1, 1.0, 60);
	cylinder(0, 0, 0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(400.0, 350.0, 825.0);
	sunlight1(0, 0, 0);
	if (fltZ0 < 400 || fltZ0 > 1355) {
		glDisable(GL_LIGHT1);
	}

	glPushMatrix();
	glTranslatef(0.0, -10, -45);
	//glRotatef(300, 0, 1, 0);
	glScalef(8, 12, 10);
	cicleLight();
	glPopMatrix();

	glPushMatrix();
	glRotatef(45, 0, 1, 0);
	glTranslatef(0.0, -10, -45);
	glScalef(8, 12, 10);
	cicleLight();
	glPopMatrix();

	glPushMatrix();
	glRotatef(90, 0, 1, 0);
	glTranslatef(0.0, -10, -45);
	glScalef(8, 12, 10);
	cicleLight();
	glPopMatrix();

	glPushMatrix();
	glRotatef(135, 0, 1, 0);
	glTranslatef(0.0, -10, -45);
	glScalef(8, 12, 10);
	cicleLight();
	glPopMatrix();

	glPushMatrix();
	glRotatef(180, 0, 1, 0);
	glTranslatef(0.0, -10, -45);
	glScalef(8, 12, 10);
	cicleLight();
	glPopMatrix();

	glPushMatrix();
	glRotatef(225, 0, 1, 0);
	glTranslatef(0.0, -10, -45);
	glScalef(8, 12, 10);
	cicleLight();
	glPopMatrix();

	glPushMatrix();
	glRotatef(270, 0, 1, 0);
	glTranslatef(0.0, -10, -45);
	glScalef(8, 12, 10);
	cicleLight();
	glPopMatrix();

	glPushMatrix();
	glRotatef(315, 0, 1, 0);
	glTranslatef(0.0, -10, -45);
	glScalef(8, 12, 10);
	cicleLight();
	glPopMatrix();
	glPopMatrix();
	//


}

//Used to draw building
void wailizhu(float up, float down, float height) {
	int i;
	float x, z, xnext, znext, xup, zup, xupnext, zupnext;
	glBegin(GL_POLYGON);
	for (i = 0; i < 361; i = i + 5)
	{
		float j = i + 5;
		x = down * cos(i * (6.284 / 360.0));
		z = down * sin(i * (6.284 / 360.0));
		xup = up * cos(i * (6.284 / 360.0));
		zup = up * sin(i * (6.284 / 360.0));

		xnext = down * cos(i * (6.284 / 360.0));
		znext = down * sin(i * (6.284 / 360.0));
		xupnext = up * cos(i * (6.284 / 360.0));
		zupnext = up * sin(i * (6.284 / 360.0));

		glVertex3f(x, 0, z);
		glVertex3f(xnext, 0, znext);
		glVertex3f(xupnext, height, zupnext);
		glVertex3f(xup, height, zup);
	}
	glEnd();
}

//Used to draw building window
void wailiwindow(int x) {
	if(x == 0){
		glPushMatrix();
		glTranslatef(-335.0, 700.0, -168.0);
		glScalef(1.0, 2.5, 1.0);
		window2(225 / (0.8), 209 / (0.8), 193 / (0.8), 0);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(-335.0, 580.0, -165.0);
		glScalef(100.0, 250, 2.0);
		housewall1(0 / (0.8), 0 / (0.8), 0 / (0.8));
		glPopMatrix();
	}

	if (x == 1) {
		glPushMatrix();
		glTranslatef(-335.0, 700.0, -168.0);
		glScalef(1.0, 2.5, 1.0);
		window3(225 / (0.8), 209 / (0.8), 193 / (0.8), 0);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(-335.0, 580.0, -165.0);
		glScalef(100.0, 250, 2.0);
		housewall1(0 / (0.8), 0 / (0.8), 0 / (0.8));
		glPopMatrix();
	}

	if (x == 2) {
		glPushMatrix();
		glTranslatef(-335.0, 700.0, -168.0);
		glScalef(1.0, 2.5, 1.0);
		window3(225 / (0.8), 209 / (0.8), 193 / (0.8), 0);
		glPopMatrix();
	}
	

}

//Used to draw building
void wailizhu() {
	glPushMatrix();
	glTranslatef(0.0, 562.5, -250.0);
	glScalef(1.0, 1.0, 1.0);
	wailizhuelement(225 / (0.8), 209 / (0.8), 193 / (0.8), 20, 20, 11);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, 442.5, -250.0);
	glRotatef(180, 1, 0, 0);
	glScalef(1.0, 3, 1.0);
	wailizhuelement(225 / (0.8), 209 / (0.8), 193 / (0.8), 20, 20, 10);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, 439.5, -255.0);
	glScalef(30.0, 10, 30);
	housewall1(225 / (0.8), 209 / (0.8), 193 / (0.8));
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, 568, -255.0);
	glScalef(30.0, 10, 30);
	housewall1(225 / (0.8), 209 / (0.8), 193 / (0.8));
	glPopMatrix();
}

//Used to draw the house room inside the building
void finalhouse() {

	glPushMatrix();
	background();
	glPopMatrix();

	glPushMatrix();
	housefloor(229, 202, 160);
	glPopMatrix();

	glPushMatrix();//IMPORTANT WHOLE PUSH
	glTranslatef(0.0, 800, 0.0);

	xuanguan1();


	//Coner
	glPushMatrix();
	glTranslatef(-200.0, 0.0, 0.0);
	glTranslatef(1085.0, 205.0, 427.0);
	glScalef(20, 400.0, 100);
	housewall1(225, 221, 210);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-200.0, 0.0, 0.0);
	glTranslatef(36.0, 0.0, 51.0);
	glTranslatef(1080.0, 205.0, 417.0);
	glRotatef(90, 0, 1, 0);
	glScalef(20, 400.0, 70);
	housewall1(225, 221, 210);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-200.0, 0.0, 0.0);
	glTranslatef(1073.5, 20.0, 428.0);
	glScalef(3, 30.0, 100);
	housewall1(255, 251, 240);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-200.0, 0.0, 0.0);
	glTranslatef(35.0, 0.0, 51.0);
	glTranslatef(1079.0, 20.0, 430);
	glRotatef(90, 0, 1, 0);
	glScalef(3, 30.0, 83);
	housewall1(255, 251, 240);
	glPopMatrix();
	//

	//RIGHT AND LEFT WALL
	glPushMatrix();
	glTranslatef(-200.0, 0.0, 0.0);
	glTranslatef(1181.0, 205.0, 668.0);
	glScalef(40, 400.0, 400);
	housewall1(225, 221, 210);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-200.0, 0.0, 0.0);
	glTranslatef(1181.0, 205.0, 1067.0);
	glScalef(40, 400.0, 100);
	housewall1(225, 221, 210);
	glPopMatrix();
	//

	//LEFT WALL
	glPushMatrix();
	glTranslatef(-775.0, 0.0, 0.0);
	glTranslatef(0.0, 205.0, 821.5);
	glScalef(40, 400.0, 847);
	housewall1(225, 221, 210);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-752.5, 0.0, 0.0);
	glTranslatef(0.0, 20.0, 821.5);
	glScalef(5, 30.0, 847);
	housewall1(255, 251, 240);
	glPopMatrix();
	//

	//MIDDLE OUT WALL
	glPushMatrix();
	glTranslatef(-135.0, 0.0, 0.0);
	glTranslatef(0.0, 205.0, 1157.0);
	glScalef(20, 400.0, 100);
	housewall1(225, 221, 210);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-33.0, 0.0, 0.0);
	glTranslatef(0.0, 205.0, 1157.0);
	glScalef(20, 400.0, 100);
	housewall1(225, 221, 210);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-120.0, 0.0, 0.0);
	glTranslatef(36.0, 0.0, 51.0);
	glTranslatef(0.0, 205.0, 1065.0);
	glRotatef(90, 0, 1, 0);
	glScalef(20, 400.0, 120);
	housewall1(225, 221, 210);
	glPopMatrix();
	//

	//Bedroom door
	glPushMatrix();
	glTranslatef(981, 275.0, 942.5);
	glRotatef(90, 0, 1, 0);
	glScalef(1.0545, 2.0, 1.0 * 5 / 9);
	huakuangMEN(255, 251, 240);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(981, 345.0, 942.5);
	glScalef(40, 120, 146);
	housewall1(225, 221, 210);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(981, 145.0, 942.5);
	glScalef(30, 280, 146);
	housewall1(50, 50, 50);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(971, 85.0, 942.5);
	glScalef(30, 100, 80);
	housewall1(255, 251, 240);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(971, 205.0, 942.5);
	glScalef(30, 100, 80);
	housewall1(255, 251, 240);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(901, 135.0, 872.5);
	glScalef(2.5, 5, 5);
	glRotatef(90, 0, 1, 0);
	cylinder(255, 251, 240);
	glPopMatrix();
	//

	//CHUANLIANGAN
	glPushMatrix();
	glTranslatef(-1000.0, 335.0, 1135.5);
	glScalef(2000, 3, 3);
	glRotatef(90, 0, 1, 0);
	cylinder(50, 50, 50);
	glPopMatrix();
	//

	//SHUGUI
	glPushMatrix();
	glTranslatef(-200.0, 0.0, 0.0);
	glTranslatef(1131.0, 135.0, 668.0);
	glScalef(60, 50.0, 200);
	housewall1(40, 40, 40);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-200.0, 0.0, 0.0);
	glTranslatef(1098.0, 130.0, 605.0);
	glScalef(6, 25.0, 53);
	housewall1(60, 60, 60);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-200.0, 0.0, 0.0);
	glTranslatef(1098.0, 130.0, 668.0);
	glScalef(6, 25.0, 53);
	housewall1(60, 60, 60);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-200.0, 0.0, 0.0);
	glTranslatef(1098.0, 130.0, 731.0);
	glScalef(6, 25.0, 53);
	housewall1(60, 60, 60);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-200.0, 0.0, 0.0);
	glTranslatef(1131.0, 35.0, 668.0);
	glScalef(60, 15.0, 200);
	housewall1(40, 40, 40);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-200.0, 0.0, 0.0);
	glTranslatef(1156.0, 92.5, 640.0);
	glScalef(10, 130.0, 10);
	housewall1(40, 40, 40);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-200.0, 0.0, 0.0);
	glTranslatef(1156.0, 79.0, 573.0);
	glScalef(10, 160.0, 10);
	housewall1(40, 40, 40);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-200.0, 0.0, 0.0);
	glTranslatef(1156.0, 92.5, 696.0);
	glScalef(10, 130.0, 10);
	housewall1(40, 40, 40);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-200.0, 0.0, 0.0);
	glTranslatef(1156.0, 79.0, 763.0);
	glScalef(10, 160.0, 10);
	housewall1(40, 40, 40);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-200.0, 0.0, 0.0);
	glTranslatef(1106.0, 92.5, 640.0);
	glScalef(10, 130.0, 10);
	housewall1(40, 40, 40);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-200.0, 0.0, 0.0);
	glTranslatef(1106.0, 79.0, 573.0);
	glScalef(10, 160.0, 10);
	housewall1(40, 40, 40);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-200.0, 0.0, 0.0);
	glTranslatef(1106.0, 92.5, 696.0);
	glScalef(10, 130.0, 10);
	housewall1(40, 40, 40);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-200.0, 0.0, 0.0);
	glTranslatef(1106.0, 79.0, 763.0);
	glScalef(10, 160.0, 10);
	housewall1(40, 40, 40);
	glPopMatrix();
	//


	//Front Floor
	glPushMatrix();
	glTranslatef(-230.0, 205.0, 377.0);
	glScalef(310.0, 400.0, 40.0);
	door11(225, 221, 210, 0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, 345.0, 377.0);
	glScalef(150.0, 120.0, 40.0);
	door11(225, 221, 210, 0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-695.0, 205.0, 377.0);
	glScalef(180.0, 400.0, 40.0);
	door11(225, 221, 210, 0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(950.0, 0.0, 0.0);
	glTranslatef(-475.0, 205.0, 377.0);
	glScalef(800.0, 400.0, 40.0);
	door11(225, 221, 210, 0);
	glPopMatrix();

	//Front LEFT DOOR
	glPushMatrix();
	glTranslatef(-495.0, 275.0, 377.0);
	glScalef(1.545, 2.0, 1.0 * 5 / 9);
	huakuangMEN(255, 251, 240);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-495.0, 145.0, 377.0);
	glScalef(218.5, 280.0, 40);
	housewall1(50, 50, 50);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-495.0, 85.0, 382.0);
	glScalef(146, 120.0, 40);
	housewall1(255, 251, 240);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-495.0, 215.0, 382.0);
	glScalef(146, 80.0, 40);
	housewall1(255, 251, 240);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-495.0, 345.0, 377.0);
	glScalef(218.5, 120.0, 40);
	housewall1(225, 221, 210);
	glPopMatrix();
	//

	//HUABIAN
	glPushMatrix();
	glTranslatef(950.0, 0.0, 0.0);
	glTranslatef(-475.0, 20.0, 398.5);
	glScalef(800.0, 30.0, 3.0);
	door11(255, 251, 240, 0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-230.0, 20.0, 398.5);
	glScalef(310.0, 30.0, 3.0);
	door11(255, 251, 240, 0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-695.0, 20.0, 398.5);
	glScalef(180.0, 30.0, 3.0);
	door11(255, 251, 240, 0);
	glPopMatrix();
	//

	//JINSEHUAKUANG
	glPushMatrix();
	glTranslatef(1300.0, 0.0, 0.0);
	glTranslatef(-675.0, 220.0, 400.5);
	glScalef(250.0, 250.0, 3.0);
	door11(254, 219, 135, 3);
	glPopMatrix();
	//


	//TIMER
	glPushMatrix();
	glTranslatef(200.0, 275.0, 400.5);
	//glRotatef(0, 0, 1, 0);
	glScalef(2.0, 2.0, 1.0);
	mirror1(40, 40, 40);
	glPopMatrix();


	glPushMatrix();
	glTranslatef(722.0, -40.0, 650.0);
	glRotatef(-5, 0, 0, 1);
	glRotatef(90, 0, 1, 0);
	glScalef(1.0, 2.0, 1.0);
	huakuang11(255, 251, 240, 90, 0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(710.0, 90.0, 700.0);
	glRotatef(-10, 0, 0, 1);
	glRotatef(90, 0, 1, 0);
	glScalef(1.0, 1.0, 1.0 );
	huakuang11(255, 251, 240, 90, 0);
	glPopMatrix();

	//BILU
	glPushMatrix();
	glTranslatef(350.0, 137.0, 410.0);
	glScalef(1.0545, 1.0, 1.0 * 2 / 9);
	huakuangMEN(255, 251, 240);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(1025.0, 0.0, 0.0);
	glTranslatef(-675.0, 72.0, 405.5);
	glScalef(140.0, 137.0, 3.0);
	door11(30, 30, 30, 0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(1025.0, 0.0, 0.0);
	glTranslatef(-675.0, 56.0, 408.5);
	glScalef(80.0, 110.0, 3.0);
	door11(0, 0, 0, 0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(1025.0, 0.0, 0.0);
	glTranslatef(-675.0, 6.5, 428.5);
	glScalef(200.0, 5.0, 60.0);
	door11(15, 15, 15, 0);
	glPopMatrix();
	//

	//

	//Back Wall
	glPushMatrix();
	glTranslatef(700.0, 325.0, 1227.0);
	glScalef(1.5, 3.0, 8.0 );
	window1(245, 241, 230, 0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(430.0, 325.0, 1227.0);
	glScalef(1.5, 3.0, 8.0);
	window1(245, 241, 230, 0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(160.0, 325.0, 1227.0);
	glScalef(1.5, 3.0, 8.0);
	window1(245, 241, 230, 0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-480.0, 325.0, 1227.0);
	glScalef(3.0, 3.0, 8.0);
	window1(245, 241, 230, 0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(1350.0, 0.0, 0.0);
	glTranslatef(-475.0, 205.0, 1227.0);
	glScalef(200.0, 400.0, 40.0);
	door11(225, 221, 210, 0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(1050.0, 0.0, 0.0);
	glTranslatef(-485.0, 205.0, 1227.0);
	glScalef(120.0, 400.0, 40.0);
	door11(225, 221, 210, 0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(800.0, 0.0, 0.0);
	glTranslatef(-505.0, 205.0, 1227.0);
	glScalef(120.0, 400.0, 40.0);
	door11(225, 221, 210, 0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(430.0, 0.0, 0.0);
	glTranslatef(-475.0, 205.0, 1227.0);
	glScalef(260.0, 400.0, 40.0);
	door11(225, 221, 210, 0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(222.5, 0.0, 0.0);
	glTranslatef(-475.0, 205.0, 1227.0);
	glScalef(155.0, 400.0, 40.0);
	door11(225, 221, 210, 0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(225.0, 0.0, 0.0);
	glTranslatef(-925.0, 205.0, 1227.0);
	glScalef(145.0, 400.0, 40.0);
	door11(225, 221, 210, 0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-200.0, 0.0, 0.0);
	glTranslatef(1085.0, 205.0, 1159.0);
	glScalef(20, 400.0, 100);
	housewall1(225, 221, 210);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-200.0, 0.0, 0.0);
	glTranslatef(36.0, 0.0, 51.0);
	glTranslatef(1085.0, 205.0, 1067.0);
	glRotatef(90, 0, 1, 0);
	glScalef(20, 400.0, 80);
	housewall1(225, 221, 210);
	glPopMatrix();
	//DIBIAN
	glPushMatrix();
	glTranslatef(562.5, 0.0, 0.0);
	glTranslatef(-475.0, 20.0, 1227.0);
	glScalef(1775.0, 30.0, 50.0);
	door11(255, 251, 240, 0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(955.0, 0.0, 0.0);
	glTranslatef(-475.0, 372.0, 1227.0);
	glScalef(790.0, 64.0, 40.0);
	door11(225, 221, 210, 0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(55.0, 0.0, 0.0);
	glTranslatef(-475.0, 372.0, 1227.0);
	glScalef(750.0, 64.0, 40.0);
	door11(225, 221, 210, 0);
	glPopMatrix();
	//
	//

	//DITAN
	glPushMatrix();
	glTranslatef(400.0, 10.0, 825.0);
	glScalef(700, 10.0, 550);
	housewall1(240, 236, 225);
	glPopMatrix();

	//DITAN DENG
	ditan_deng();
	//DITAN1
	glPushMatrix();
	glTranslatef(-450.0, 10.0, 825.0);
	glScalef(400, 10.0, 550);
	housewall1(240, 236, 225);
	glPopMatrix();

	//Chaji
	glPushMatrix();
	glTranslatef(400.0, 85.0, 775.0);
	glRotatef(90, 1, 0, 0);
	glScalef(70, 70.0, 70);
	GLfloat mat_ambient[] = { 0.8 * (100.0 / 255), 0.8 * (100.0 / 255), 0.8 * 100.0 / (255), 1.0f };  //定义材质的环境光颜色
	GLfloat mat_diffuse[] = { (100.0 / 255), (100.0 / 255), 100.0 / (255), 1.0f };  //定义材质的漫反射光颜色
	GLfloat mat_specular[] = { 0.0f, 0.0f, 0.0f, 1.0f };   //定义材质的镜面反射光颜色
	GLfloat mat_emission[] = { 0.0f, 0.0f, 0.0f, 1.0f };   //定义材质的辐射光颜色，为0
	GLfloat mat_shininess = 0.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
	glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess);

	glutSolidCylinder(1, 1, 30, 1);

	GLfloat mat_ambient1[] = { 0, 0, 0, 1.0f };  //定义材质的环境光颜色
	GLfloat mat_diffuse1[] = { 0, 0, 0, 1.0f };  //定义材质的漫反射光颜色
	GLfloat mat_specular1[] = { 0.0f, 0.0f, 0.0f, 1.0f };   //定义材质的镜面反射光颜色
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient1);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse1);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular1);
	glutWireCylinder(1, 1, 10, 10);
	glPopMatrix();

	//XIAOYUANYI
	glPushMatrix();
	glPushMatrix();
	glTranslatef(220.0, 35.0, 655.0);
	glRotatef(90, 1, 0, 0);
	glScalef(25, 25.0, 20);
	GLfloat mat_ambient2[] = { 0.8 * (0.0 / 255), 0.8 * (0.0 / 255), 0.8 * 0.0 / (255), 1.0f };  //定义材质的环境光颜色
	GLfloat mat_diffuse2[] = { (0.0 / 255), (0.0 / 255), 0.0 / (255), 1.0f };  //定义材质的漫反射光颜色
	GLfloat mat_specular2[] = { 0.0f, 0.0f, 0.0f, 1.0f };   //定义材质的镜面反射光颜色
	GLfloat mat_emission2[] = { 0.0f, 0.0f, 0.0f, 1.0f };   //定义材质的辐射光颜色，为0
	GLfloat mat_shininess2 = 0.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient2);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse2);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular2);
	glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission2);
	glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess2);
	glutSolidCylinder(1, 1, 30, 1);

	GLfloat mat_ambient3[] = { 0, 0, 0, 1.0f };  //定义材质的环境光颜色
	GLfloat mat_diffuse3[] = { 0, 0, 0, 1.0f };  //定义材质的漫反射光颜色
	GLfloat mat_specular3[] = { 0.0f, 0.0f, 0.0f, 1.0f };   //定义材质的镜面反射光颜色
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient3);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse3);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular3);
	glutWireCylinder(1, 1, 10, 10);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(220.0, 105.0, 655.0);
	glRotatef(90, 1, 0, 0);
	glScalef(26, 26.0, 70);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient4);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse4);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular4);
	glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission4);
	glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess4);
	glutSolidCylinder(1, 1, 30, 1);
	glColor3ub(0, 0, 0);
	glutWireCylinder(1, 1, 10, 10);
	glPushMatrix();
	glScalef(1.0, 1.0, 0.15);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient3);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse3);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular3);
	//glColor3ub(255, 251, 240);
	glutSolidSphere(1, 30, 30);
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	//

	//XIAOZHUOZI
	glPushMatrix();
	glTranslatef(625.0, 55.0, 665.0);
	glRotatef(20, 0, 0, 1);
	glScalef(7, 100.0, 7);
	housewall1(222, 184, 135);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(615.0, 55.0, 665.0);
	glRotatef(-20, 0, 0, 1);
	glScalef(7, 100.0, 7);
	housewall1(222, 184, 135);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(620.0, 55.0, 660.0);
	glRotatef(20, 1, 0, 0);
	glScalef(7, 100.0, 7);
	housewall1(222, 184, 135);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(620.0, 55.0, 670.0);
	glRotatef(-20, 1, 0, 0);
	glScalef(7, 100.0, 7);
	housewall1(222, 184, 135);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(620.0, 105.0, 665.0);
	glColor3ub(255, 251, 220);
	glRotatef(90, 1, 0, 0);
	glScalef(30, 30.0, 6);
	glutSolidCylinder(1, 1, 30, 1);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient3);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse3);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular3);
	glutWireCylinder(1, 1, 10, 10);
	glPopMatrix();
	//


	//XIAOYUANYI
	glPushMatrix();
	glPushMatrix();
	glTranslatef(160.0, 35.0, 775.0);
	glRotatef(90, 1, 0, 0);
	glScalef(25, 25.0, 20);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient2);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse2);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular2);
	glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission2);
	glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess2);
	glutSolidCylinder(1, 1, 30, 1);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient3);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse3);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular3);
	glutWireCylinder(1, 1, 10, 10);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(160.0, 105.0, 775.0);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient4);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse4);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular4);
	glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission4);
	glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess4);
	glRotatef(90, 1, 0, 0);
	glScalef(26, 26.0, 70);
	glutSolidCylinder(1, 1, 30, 1);
	glColor3ub(0, 0, 0);
	glutWireCylinder(1, 1, 10, 10);
	glPushMatrix();
	glScalef(1.0, 1.0, 0.15);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient3);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse3);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular3);
	//glColor3ub(255, 251, 240);
	glutSolidSphere(1, 30, 30);
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();

	//



	//SOFA
	glPushMatrix();
	glTranslatef(0.0, 0.0, 0.0);
	glPushMatrix();
	glTranslatef(475.0, 55.0, 975.0);
	glScalef(150, 100.0, 120);
	housewall2(255, 251, 240, 0.8);
	glPopMatrix();


	glPushMatrix();
	glTranslatef(475.0, 108.0, 975.0);
	glScalef(150, 1.0, 120);
	housewall4(255, 251, 240);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(325, 55.0, 975.0);
	glScalef(150, 100.0, 120);
	housewall2(255, 251, 240, 0.8);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(325.0, 108.0, 975.0);
	glScalef(150, 1.0, 120);
	housewall4(255, 251, 240);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(219, 55.0, 956);
	glScalef(100, 100.0, 100);
	glRotatef(45, 0, 1, 0);
	housewall2(255, 251, 240, 0.8);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(219, 108.0, 956);
	glScalef(100, 1.0, 100);
	glRotatef(45, 0, 1, 0);
	housewall4(255, 251, 240);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(581, 55.0, 956.0);
	glScalef(100, 100.0, 100);
	glRotatef(-45, 0, 1, 0);
	housewall2(255, 251, 240, 0.8);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(581, 108.0, 956.0);
	glScalef(100, 1.0, 100);
	glRotatef(-45, 0, 1, 0);
	housewall4(255, 251, 240);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(250.0, 105.0, 975.0);
	glRotatef(90, 1, 0, 0);
	glScalef(60, 60.0, 90);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient4);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse4);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular4);
	glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission4);
	glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess4);
	glutSolidCylinder(1, 1, 30, 1);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient3);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse3);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular3);
	glutWireCylinder(1, 1, 20, 1);
	glPopMatrix();


	glPushMatrix();
	glTranslatef(250.0, 108.0, 975.0);
	glRotatef(90, 1, 0, 0);
	glScalef(60, 60.0, 2);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient4);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse4);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular4);
	glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission4);
	glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess4);
	glutSolidCylinder(1, 1, 30, 1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(550.0, 105.0, 975.0);
	glRotatef(90, 1, 0, 0);
	glScalef(60, 60.0, 90);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient4);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse4);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular4);
	glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission4);
	glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess4);
	glutSolidCylinder(1, 1, 30, 1);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient3);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse3);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular3);
	glutWireCylinder(1, 1, 20, 1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(550.0, 108.0, 975.0);
	glRotatef(90, 1, 0, 0);
	glScalef(60, 60.0, 2);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient4);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse4);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular4);
	glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission4);
	glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess4);
	glutSolidCylinder(1, 1, 30, 1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(182.5, 105.0, 918.5);
	glRotatef(90, 1, 0, 0);
	glScalef(50, 50.0, 90);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient4);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse4);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular4);
	glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission4);
	glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess4);
	glutSolidCylinder(1, 1, 30, 1);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient3);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse3);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular3);
	glutWireCylinder(1, 1, 20, 1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(182.5, 108.0, 918.5);
	glRotatef(90, 1, 0, 0);
	glScalef(50, 50.0, 2);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient4);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse4);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular4);
	glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission4);
	glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess4);
	glutSolidCylinder(1, 1, 30, 1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(618.5, 105.0, 918.5);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient4);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse4);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular4);
	glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission4);
	glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess4);
	glRotatef(90, 1, 0, 0);
	glScalef(50, 50.0, 90);
	glutSolidCylinder(1, 1, 30, 1);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient3);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse3);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular3);
	glutWireCylinder(1, 1, 20, 1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(618.5, 108.0, 918.5);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient4);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse4);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular4);
	glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission4);
	glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess4);
	glRotatef(90, 1, 0, 0);
	glScalef(50, 50.0, 2);
	glutSolidCylinder(1, 1, 30, 1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(358.5, 130.0, 1008.5);
	glScalef(150, 45, 30);
	glRotatef(90, 0, 1, 0);
	cylinder(20, 20, 20);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(268.5, 130.0, 1008.5);
	glScalef(300, 45, 30);
	glRotatef(90, 0, 1, 0);
	cylinder(20, 20, 20);
	glPopMatrix();

	glPopMatrix();
	//

	//TAIDENG
	taideng();

	//CHUANLIAN
	glPushMatrix();
	glTranslatef(-10.0, 0.0, 0.0);
	chuanlian3();

	glTranslatef(251.0, 0.0, 0.0);
	chuanlian2();

	glTranslatef(271.0, 0.0, 0.0);
	chuanlian2();

	glTranslatef(270.0, 0.0, 0.0);
	chuanlian1();

	glTranslatef(-1142.0, 0.0, 0.0);
	chuanlian5();

	glTranslatef(-327.0, 0.0, 0.0);
	chuanlian4();
	glPopMatrix();
	//

	//CANZHUO
	glPushMatrix();
	glTranslatef(-450.0, 130.0, 825.0);
	glPushMatrix();
	glScalef(120, 10.0, 350);
	housewall1(200, 148, 101);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, 5.0, 0.0);
	glScalef(70, 5.0, 350);
	housewall1(255, 251, 240);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-40.0, -80.0, 115.0);
	glRotatef(-20, 1, 0, 0);
	glScalef(10, 160.0, 10);
	housewall1(20, 20, 20);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(40.0, -80.0, 115.0);
	glRotatef(-20, 1, 0, 0);
	glScalef(10, 160.0, 10);
	housewall1(20, 20, 20);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-40.0, -80.0, -115.0);
	glRotatef(20, 1, 0, 0);
	glScalef(-10, 160.0, 10);
	housewall1(20, 20, 20);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(40.0, -80.0, -115.0);
	glRotatef(20, 1, 0, 0);
	glScalef(10, 160.0, 10);
	housewall1(20, 20, 20);
	glPopMatrix();
	glPopMatrix();

	//CANYI
	// 
	glPushMatrix();
	glTranslatef(0.0, 0.0, 20.0);
	canyi();

	glTranslatef(0.0, 0.0, 120.0);
	canyi();

	glTranslatef(0.0, 0.0, -240.0);
	canyi();

	
	glPushMatrix();
	glTranslatef(-920.0, 0.0, 0.0);
	glScalef(-1.0, 1.0, 1.0);
	canyi();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-920.0, 0.0, 120.0);
	glScalef(-1.0, 1.0, 1.0);
	canyi();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-920.0, 0.0, 240.0);
	glScalef(-1.0, 1.0, 1.0);
	canyi();
	glPopMatrix();

	glPopMatrix();
	//LEFT CANGUI
	glPushMatrix();
	glTranslatef(-724.0, 0.0, 93.75);
	glTranslatef(0.0, 85.0, 821.5);
	glScalef(62, 160.0, 62.5);
	housewall1(255, 251, 240);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-724.0, 0.0, 31.25);
	glTranslatef(0.0, 85.0, 821.5);
	glScalef(62, 160.0, 62.5);
	housewall1(255, 251, 240);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-724.0, 0.0, -31.25);
	glTranslatef(0.0, 85.0, 821.5);
	glScalef(62, 160.0, 62.5);
	housewall1(255, 251, 240);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-724.0, 0.0, -93.75);
	glTranslatef(0.0, 85.0, 821.5);
	glScalef(62, 160.0, 62.5);
	housewall1(255, 251, 240);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-726.0, 0.0, 0);
	glTranslatef(0.0, 87.5, 821.5);
	glScalef(58, 165.0, 260);
	housewall1(20, 20, 20);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-750.0, 0.0, 0.0);
	glTranslatef(0.0, 225.0, 861.5);
	glScalef(10, 100.0, 75.0);
	housewall1(200, 148, 101);
	glPushMatrix();
	glTranslatef(2.0, 0.0, 0.0);
	glScalef(1.0, 0.95, 0.90);
	housewall1(225, 221, 210);
	glPopMatrix();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-750.0, 0.0, 0.0);
	glTranslatef(0.0, 225.0, 781.5);
	glScalef(10, 100.0, 75.0);
	housewall1(200, 148, 101);
	glPushMatrix();
	glTranslatef(2.0, 0.0, 0.0);
	glScalef(1.0, 0.95, 0.90);
	housewall1(225, 221, 210);
	glPopMatrix();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-750.0, 0.0, 0.0);
	glTranslatef(0.0, 330.0, 861.5);
	glScalef(10, 100.0, 75.0);
	housewall1(200, 148, 101);
	glPushMatrix();
	glTranslatef(2.0, 0.0, 0.0);
	glScalef(1.0, 0.95, 0.90);
	housewall1(225, 221, 210);
	glPopMatrix();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-750.0, 0.0, 0.0);
	glTranslatef(0.0, 330.0, 781.5);
	glScalef(10, 100.0, 75.0);
	housewall1(200, 148, 101);
	glPushMatrix();
	glTranslatef(2.0, 0.0, 0.0);
	glScalef(1.0, 0.95, 0.90);
	housewall1(225, 221, 210);
	glPopMatrix();
	glPopMatrix();
	//


	glPopMatrix();//IMPORTANT WHOLE POP

	

}

//The whole building
void wailimian() {
	//DIBAN
	glPushMatrix();
	glTranslatef(0.0, 0.0, -115.0);
	glTranslatef(0.0, 800.0, 670);
	glScalef(2140, 10.0, 1360);
	//housewall1(154 / (0.8), 107 / (0.8), 91 / (0.8));
	housewall3(229 / (0.8), 202 / (0.8), 160 / (0.8), 0.8, 1, 21.4, 13.6);
	glPopMatrix();

	//CEILING
	glPushMatrix();
	glTranslatef(-85.0, 383.0, -115.0);
	glTranslatef(0.0, 800.0, 1170);
	glScalef(128, 50.0, 1360);
	housewall1(255 / 0.95, 247 / 0.95, 240 / 0.95);
	glPopMatrix();
	//

	glPushMatrix();
	glTranslatef(0.0, 415.0, -115.0);
	glTranslatef(0.0, 800.0, 670);
	glScalef(2140, 10.0, 1360);
	housewall1(255 / 0.95, 247 / 0.95, 240 / 0.95);
	glPopMatrix();
	// 
	//WALLS
	glPushMatrix();
	glTranslatef(-580.0, 0.0, -115.0);
	glTranslatef(0.0, 805.0, 0);
	glScalef(980, 1600.0, 40);
	//housewall1(154 / (0.8), 107 / (0.8), 91 / (0.8));
	housewall3(225 / (0.8), 213 / (0.8), 193 / (0.8), 0.8, 0, 10, 10);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-880.0, 0.0, -150.0);
	glTranslatef(0.0, 205.0, 0);
	glScalef(1580, 400.0, 20);
	housewall1(225 / (0.8), 209 / (0.8), 193 / (0.8));
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-1050.0, 0.0, -115.0);
	glTranslatef(0.0, 805.0, 700);
	glScalef(40, 1600.0, 1400);
	housewall1(154 / (0.8), 107 / (0.8), 91 / (0.8));
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-710.0, 0.0, -115.0);
	glTranslatef(1290.0, 805.0, 0);
	glScalef(980, 1600.0, 40);
	housewall3(225 / (0.8), 209 / (0.8), 193 / (0.8), 0.8, 0, 10, 10);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-710.0, 0.0, -150.0);
	glTranslatef(1590.0, 205.0, 0);
	glScalef(1580, 400.0, 20);
	housewall1(225 / (0.8), 209 / (0.8), 193 / (0.8));
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-910.0, 0.0, -115.0);
	glTranslatef(1960.0, 805.0, 700);
	glScalef(40, 1600.0, 1400);
	housewall1(154 / (0.8), 107 / (0.8), 91 / (0.8));
	glPopMatrix();
	//

	//TIAOWEN
	//RIGHT
	glPushMatrix();
	glTranslatef(-580.0, 0.0, -115.0);
	glTranslatef(370.0, 805.0, -30);
	glScalef(100, 1600.0, 20);
	housewall1(225 / (0.8), 209 / (0.8), 193 / (0.8));
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-580.0, 0.0, -115.0);
	glTranslatef(100, 805.0, -30);
	glScalef(100, 1600.0, 20);
	housewall1(225 / (0.8), 209 / (0.8), 193 / (0.8));
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-580.0, 0.0, -115.0);
	glTranslatef(-170.0, 805.0, -30);
	glScalef(100, 1600.0, 20);
	housewall1(225 / (0.8), 209 / (0.8), 193 / (0.8));
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-580.0, 0.0, -115.0);
	glTranslatef(-440.0, 805.0, -30);
	glScalef(100, 1600.0, 20);
	housewall1(225 / (0.8), 209 / (0.8), 193 / (0.8));
	glPopMatrix();
	//

	//LEFT
	glPushMatrix();
	glTranslatef(-580.0, 0.0, -115.0);
	glTranslatef(790.0, 805.0, -30);
	glScalef(100, 1600.0, 20);
	housewall1(225 / (0.8), 209 / (0.8), 193 / (0.8));
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-580.0, 0.0, -115.0);
	glTranslatef(1060.0, 805.0, -30);
	glScalef(100, 1600.0, 20);
	housewall1(225 / (0.8), 209 / (0.8), 193 / (0.8));
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-580.0, 0.0, -115.0);
	glTranslatef(1330.0, 805.0, -30);
	glScalef(100, 1600.0, 20);
	housewall1(225 / (0.8), 209 / (0.8), 193 / (0.8));
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-580.0, 0.0, -115.0);
	glTranslatef(1600.0, 805.0, -30);
	glScalef(100, 1600.0, 20);
	housewall1(225 / (0.8), 209 / (0.8), 193 / (0.8));
	glPopMatrix();
	//

	//MENMEI
	glPushMatrix();
	glTranslatef(0.0, 1140.0, -115.0);
	glTranslatef(0.0, 0.0, 0.0);
	glRotatef(90, 0, 1, 0);
	glRotatef(180, 1, 0, 0);
	glScalef(5.0, 4, 107.5);
	tixingelement(225 / (0.8), 209 / (0.8), 193 / (0.8), 10, 25);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, 800.0, -115.0);
	glTranslatef(0.0, 805.0, -40);
	glScalef(2140, 20.0, 50);
	housewall1(209 / (0.8), 199 / (0.8), 173 / (0.8));
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, 445.0, -115.0);
	glTranslatef(0.0, 805.0, -120);
	glScalef(2140, 20.0, 50);
	housewall1(209 / (0.8), 199 / (0.8), 173 / (0.8));
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, 340.0, -115.0);
	glTranslatef(0.0, 805.0, -90);
	glScalef(2140, 20.0, 50);
	housewall1(209 / (0.8), 199 / (0.8), 173 / (0.8));
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, -400.0, -115.0);
	glTranslatef(0.0, 805.0, -90);
	glScalef(3180, 20.0, 160);
	housewall1(209 / (0.8), 199 / (0.8), 173 / (0.8));
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, -380.0, -115.0);
	glTranslatef(0.0, 805.0, -80);
	glScalef(3140, 20.0, 150);
	housewall1(209 / (0.8), 199 / (0.8), 173 / (0.8));
	glPopMatrix();

	//

	//WINDOW
	glPushMatrix();
	glTranslatef(0.0, 0.0, 0.0);
	glPushMatrix();
	glTranslatef(270, 0.0, 0.0);
	for (float i = 0; i < 3; i++) {
		glTranslatef(-270, 0.0, 0.0);
		wailiwindow(0);
	}
	glPopMatrix();

	glPushMatrix();
	glTranslatef(405, 0.0, 0.0);
	for (float i = 0; i < 3; i++) {
		glTranslatef(270, 0.0, 0.0);
		wailiwindow(0);
	}
	glPopMatrix();

	glPushMatrix();
	glTranslatef(270, 400.0, 0.0);
	for (float i = 0; i < 3; i++) {
		glTranslatef(-270, 0.0, 0.0);
		wailiwindow(1);
	}
	glPopMatrix();

	glPushMatrix();
	glTranslatef(405, 400.0, 0.0);
	for (float i = 0; i < 3; i++) {
		glTranslatef(270, 0.0, 0.0);
		wailiwindow(1);
	}
	glPopMatrix();

	glPushMatrix();
	glTranslatef(270, 850.0, 0.0);
	for (float i = 0; i < 3; i++) {
		glTranslatef(-270, 0.0, 0.0);
		wailiwindow(0);
	}
	glPopMatrix();

	glPushMatrix();
	glTranslatef(405, 850.0, 0.0);
	for (float i = 0; i < 3; i++) {
		glTranslatef(270, 0.0, 0.0);
		wailiwindow(0);
	}
	glPopMatrix();

	glPushMatrix();
	glTranslatef(270, -400.0, 0.0);
	for (float i = 0; i < 5; i++) {
		glTranslatef(-270, 0.0, 0.0);
		wailiwindow(1);
	}
	glPopMatrix();

	glPushMatrix();
	glTranslatef(405, -400.0, 0.0);
	for (float i = 0; i < 5; i++) {
		glTranslatef(270, 0.0, 0.0);
		wailiwindow(1);
	}
	glPopMatrix();
	glPopMatrix();
	//

	//WAILIZHU
	glPushMatrix();

	glPushMatrix();
	glTranslatef(0.0, 578, -255.0);
	glScalef(3140.0, 10, 40);
	housewall1(225 / (0.8), 209 / (0.8), 193 / (0.8));
	glPopMatrix();

	wailizhu();
	glPushMatrix();
	for (int j = 0; j < 19; j++) {

		glTranslatef(-80, 0.0, 0.0);
		wailizhu();
	}
	glPopMatrix();

	glPushMatrix();
	for (int j = 0; j < 19; j++) {

		glTranslatef(80, 0.0, 0.0);
		wailizhu();
	}
	glPopMatrix();

	glPopMatrix();
	//

	//DAINTI
	glPushMatrix();
	glTranslatef(-120.0, 0.0, -555.0);
	glTranslatef(0.0, 805.0, -30);
	glScalef(80, 1600.0, 20);
	housewall1(99 / (0.8), 96 / (0.8), 89 / (0.8));
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-157.5, 0.0, -535.0);
	glTranslatef(0.0, 805.0, -30);
	glScalef(10, 1600.0, 40);
	housewall1(99 / (0.8), 96 / (0.8), 89 / (0.8));
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-157.5, 0.0, -185.0);
	glTranslatef(0.0, 805.0, -30);
	glScalef(10, 1600.0, 120);
	housewall1(99 / (0.8), 96 / (0.8), 89 / (0.8));
	glPopMatrix();

	glPushMatrix();
	glTranslatef(120.0, 0.0, -555.0);
	glTranslatef(0.0, 805.0, -30);
	glScalef(80, 1600.0, 20);
	housewall1(99 / (0.8), 96 / (0.8), 89 / (0.8));
	glPopMatrix();

	glPushMatrix();
	glTranslatef(157.5, 0.0, -535.0);
	glTranslatef(0.0, 805.0, -30);
	glScalef(10, 1600.0, 40);
	housewall1(99 / (0.8), 96 / (0.8), 89 / (0.8));
	glPopMatrix();

	glPushMatrix();
	glTranslatef(157.5, 0.0, -185.0);
	glTranslatef(0.0, 805.0, -30);
	glScalef(10, 1600.0, 120);
	housewall1(99 / (0.8), 96 / (0.8), 89 / (0.8));
	glPopMatrix();


	//ZUIGAOJINMENQIANG
	glPushMatrix();
	glTranslatef(-84.0, 0.0, -185.0);
	glTranslatef(0.0, 805.0, -30);
	glScalef(10, 1600.0, 120);
	housewall1(99 / (0.8), 96 / (0.8), 89 / (0.8));
	glPopMatrix();

	glPushMatrix();
	glTranslatef(84.0, 0.0, -185.0);
	glTranslatef(0.0, 805.0, -30);
	glScalef(10, 1600.0, 120);
	housewall1(99 / (0.8), 96 / (0.8), 89 / (0.8));
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, 0.0, -185.0);
	glTranslatef(0.0, 220.0, -21);
	glScalef(180, 1200.0, 120);
	housewall3(225 / (0.8), 209 / (0.8), 193 / (0.8), 0.8, 1, 2.14, 1.36);
	glPopMatrix();
	//

	glPushMatrix();
	glTranslatef(0.0, 175.0, -555.0);
	glTranslatef(0.0, 805.0, -30);
	glScalef(165, 1250.0, 20);
	housewall1(215 / (0.8), 219 / (0.8), 203 / (0.8));
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-lift_move, 0.0, -275.0);
	glTranslatef(0.0, 805.0, -30);
	glScalef(90, 1600.0, 20);
	housewall1(225 / (0.8), 209 / (0.8), 193 / (0.8));
	glPopMatrix();

	glPushMatrix();
	glTranslatef(lift_move, 0.0, -275.0);
	glTranslatef(0.0, 805.0, -30);
	glScalef(90, 1600.0, 20);
	housewall1(225 / (0.8), 209 / (0.8), 193 / (0.8));
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0.0, -255.0);
	glTranslatef(0.0, 245.0, -30);
	glScalef(110, 1200.0, 20);
	housewall4(225 / (0.8), 209 / (0.8), 193 / (0.8));
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0.0, -255.0);
	glTranslatef(0.0, 1295.0, -30);
	glScalef(110, 400.0, 20);
	housewall4(225 / (0.8), 209 / (0.8), 193 / (0.8));
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-100, 0.0, -255.0);
	glTranslatef(0.0, 805.0, -30);
	glScalef(90, 1600.0, 20);
	housewall1(225 / (0.8), 209 / (0.8), 193 / (0.8));
	glPopMatrix();

	glPushMatrix();
	glTranslatef(100, 0.0, -255.0);
	glTranslatef(0.0, 805.0, -30);
	glScalef(90, 1600.0, 20);
	housewall1(225 / (0.8), 209 / (0.8), 193 / (0.8));
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-100, 0.0, -295.0);
	glTranslatef(0.0, 805.0, -30);
	glScalef(90, 1600.0, 20);
	housewall1(99 / (0.8), 96 / (0.8), 89 / (0.8));
	glPopMatrix();

	glPushMatrix();
	glTranslatef(100, 0.0, -295.0);
	glTranslatef(0.0, 805.0, -30);
	glScalef(90, 1600.0, 20);
	housewall1(99 / (0.8), 96 / (0.8), 89 / (0.8));
	glPopMatrix();



	glPushMatrix();
	glTranslatef(-lift_move1, 0.0, -552.0);
	glTranslatef(0.0, 805.0, -30);
	glScalef(90, 1600.0, 20);
	housewall1(225 / (0.8), 209 / (0.8), 193 / (0.8));
	glPopMatrix();

	glPushMatrix();
	glTranslatef(lift_move1, 0.0, -552.0);
	glTranslatef(0.0, 805.0, -30);
	glScalef(90, 1600.0, 20);
	housewall1(225 / (0.8), 209 / (0.8), 193 / (0.8));
	glPopMatrix();


	//DIANTIMENMEI
	glPushMatrix();
	glTranslatef(0.0, 1140.0, -475.0);
	glTranslatef(0.0, 0.0, -155.0);
	glRotatef(90, 0, 1, 0);
	glRotatef(180, 1, 0, 0);
	glScalef(1.0, 4, 15);
	tixingelement(225 / (0.8), 209 / (0.8), 193 / (0.8), 12, 20);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, 800.0, -475.0);
	glTranslatef(0.0, 805.0, -110);
	glScalef(340, 20.0, 20);
	housewall1(209 / (0.8), 199 / (0.8), 173 / (0.8));
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, 445.0, -475.0);
	glTranslatef(0.0, 805.0, -180);
	glScalef(370, 20.0, 20);
	housewall1(209 / (0.8), 199 / (0.8), 173 / (0.8));
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, 340.0, -475.0);
	glTranslatef(0.0, 805.0, -160);
	glScalef(340, 20.0, 20);
	housewall1(209 / (0.8), 199 / (0.8), 173 / (0.8));
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, -445.0, -475.0);
	glTranslatef(0.0, 805.0, -160);
	glScalef(380, 20.0, 20);
	housewall1(209 / (0.8), 199 / (0.8), 173 / (0.8));
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, -425.0, -475.0);
	glTranslatef(0.0, 805.0, -150);
	glScalef(340, 20.0, 10);
	housewall1(209 / (0.8), 199 / (0.8), 173 / (0.8));
	glPopMatrix();
	//DIANTICANG
	glPushMatrix();
	glTranslatef(0.0, lift, -413.0);
	glTranslatef(0.0, 5.0, -30);
	glScalef(270, 10.0, 256);
	housewall1(99 / (0.8), 96 / (0.8), 89 / (0.8));
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, lift + 350, -413.0);
	glTranslatef(0.0, 5.0, -30);
	glScalef(270, 10.0, 256);
	housewall1(119 / (0.8), 116 / (0.8), 109 / (0.8));
	glPopMatrix();

	glPushMatrix();
	glTranslatef(290, -605.0 + lift, 0.0);
	glTranslatef(0, 0.0, -1090.0);
	glScalef(1.0, 1.35, 2.0);
	glRotatef(90, 0, 1, 0);
	wailiwindow(2);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(45, -605.0 + lift, 0.0);
	glTranslatef(0, 0.0, -1090.0);
	glScalef(1.0, 1.35, 2.0);
	glRotatef(90, 0, 1, 0);
	wailiwindow(2);
	glPopMatrix();
	// 
	//
}

void displayObject()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(fltFOV, 1, 0.1, 5000);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(fltX0 * fltZoom, fltY0 * fltZoom, fltZ0 * fltZoom, fltXRef, fltYRef, fltZRef, fltXUp,
		fltYUp, fltZUp);
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.2, 0.2, 0.8, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	finalhouse();
	wailimian();
	glutSwapBuffers();
}
void reshapeWindow(GLint intNewWidth, GLint intNewHeight)
{
	glViewport(0, 0, intNewWidth, intNewHeight);
}

void animate()
{
	if (animate_choice ==  1) {
			if(fltZ0 <= -885) {
				fltZ0 += 2;
		     }

			if (fltZ0 >= -885) {
				if (lift_move1 <= 100) {
					lift_move1 += 0.3;
				}

			}

			if (lift_move1 >= 100) {
				if (fltZ0 <= -570) {
					fltZ0 += 2;
				}

				if (fltZ0 >= -570) {
					if (fltY0 <= 1040) {
						fltY0 += 2;
						fltYRef += 2;
						lift += 2;
					}

					if (fltY0 >= 1040) {
						if (lift_move <= 100) {
							lift_move += 0.5;

							if (lift_move >= 100) {
								animate_choice = 0;
							}
						}

					}
				}
			}

			

	}
	glutPostRedisplay();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(50, 50);
	glutInitWindowSize(intWinWidth, intWinHeight);
	glutCreateWindow("Assignment2 3D Project");
	myinit();
	glutDisplayFunc(displayObject);
	glutReshapeFunc(reshapeWindow);
	glutKeyboardFunc(adjustDisplay);
	glutIdleFunc(animate); 
	glutMainLoop();
}

