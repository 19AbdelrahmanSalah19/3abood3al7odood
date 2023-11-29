#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include "TextureBuilder.h"
#include "Model_3DS.h"
#include "GLTexture.h"
#include <glut.h>
#include <irrKlang.h>
using namespace irrklang;

#pragma comment(lib, "irrKlang.lib") 
#define GLUT_KEY_ESCAPE 27

ISoundEngine* SoundEngine = createIrrKlangDevice();


#define DEG2RAD(a) (a * 0.0174532925)
#define GLUT_KEY_ESCAPE 27
#define PI 3.141592653589793238462643383279502884


float angleX = 0.0; // Initialize rotation angle around the x-axis
int passX = 600;

int WIDTH = 2280;
int HEIGHT = 1720;
bool FView = true;
bool SView = false;
bool TView = false;
bool shoot = false;
int shootTime = 50;
float bulletZ = 0.0;
float cbulletx = 0.0;
float cbullety = 0.0;
float cbulletz = 0.0;
bool shootP = false;
int shootTimeP = 100;
float bulletZP = 0.0;
float cbulletxP = 0.0;
float cbulletyP = 0.0;
float cbulletzP = 0.0;
float cWarriorX = 8.0;
float cWarriorY = 0.0;
float cWarriorZ = 22.0;
float cGunX = 10.0;
float cGunY = 4.0;
float cGunZ = 20.0;
float cRockX[6] = { -5.0,11.0,40.0,22.0,-15.0,-8.0 };
float cRockY[6] = { 0.0,0.0,0.0,0.0,0.0,0.0 };
float cRockZ[6] = { 0.0,-10,-21,-14,-5,-26 };
float cZombieX[6] = { 14.0,5.0,-6.0,28.0,-20.0,18.0};
float cZombieY[6] = { 4.0,4.0,4.0,4.0,4.0,4.0 };
float cZombieZ[6] = { 0.0,-5.0,-30.0,-25.0,-4,-17.0};
float cZombieRotateY[6] = { 0.0,0.0,0.0,0.0,0.0,0.0 };
bool collide[6];
bool collideP[6];
bool shot = false;
bool shotP = false;
float shotAngle = 0.0;
bool zombiefirstShot[6];
bool zombieDied[6];
bool frontView = true;
bool rightView = false;
bool leftView = false;
bool backView = false;
float rotateGun = 0.0;
bool oneZombiePerShot = false;
bool oneZombiePerShotP = false;
bool fV, rV, lV, bV;
bool bullet = true;
bool bulletP = false;
float rotatePlayer = 0.0;
bool firstPersonShooter = true;
bool thirdPersonShooter = false;
bool player = false;
float ex = 9.0;
float ey = 4.5;
float ez = 22.0;
int GameScore = 0;
bool damageSoundOnlyOnce[6];
bool shootSound;
bool alamy;
float cosThet = 0.0;
float sinThet = 0.0;
bool rockCollided;
bool ZombieCollidesRock;
bool bulletCollidesRock;
bool bulletCollidesRockP;
int lives = 8;
bool health[8] = { true,true,true,true,true,true,true,true };
float healthX[8] = { 20,50,80,110,140,170,200,230 };
//float healthX[8] = { -120,-90,-60,-30,0,30,60,90 };
float healthY[8] = { 0,0,0,0,0,0,0,0 };
bool awayFromX[6];
bool awayFromY = false;
bool timerFromDecX[6];
bool timerFromIncX[6];
bool timerFromDecZ[6];
bool timerFromIncZ[6];
int whichRock[6];
float zombiePunchRotateAngle[6]{ 0.0,0.0,0.0,0.0,0.0,0.0 };
float warriorColor[6];
int timerPunch[6] = { 2,2,2,2,2,2 };

GLuint tex;
GLuint tex3;
GLuint tex2;


char title[] = "3D Model Loader Sample";

// 3D Projection Options
GLdouble fovy = 45.0;
GLdouble aspectRatio = (GLdouble)WIDTH / (GLdouble)HEIGHT;
GLdouble zNear = 0.1;
GLdouble zFar = 100;
int rotateSkull = 0;
int rotatefireBall = 0;

//float ex = 0.0;



//class Vector
//{
//public:
//	GLdouble x, y, z;
//	Vector() {}
//	Vector(GLdouble _x, GLdouble _y, GLdouble _z) : x(_x), y(_y), z(_z) {}
//	//================================================================================================//
//	// Operator Overloading; In C++ you can override the behavior of operators for you class objects. //
//	// Here we are overloading the += operator to add a given value to all vector coordinates.        //
//	//================================================================================================//
//	void operator +=(float value)
//	{
//		x += value;
//		y += value;
//		z += value;
//	}
//};

class Vector3f {
public:
	float x, y, z;

	//float eyex = 6.0f, eyey = 1.0f, eyeZ = 3.0f, centerx = 0.0f, centery = 0.5f, centerz = 3.0f, upx = 0.0f, upy = 0.5f, upz = 0.0f;

	Vector3f(float _x = 0.0f, float _y = 0.0f, float _z = 0.0f) {
		x = _x;
		y = _y;
		z = _z;
	}

	Vector3f operator+(Vector3f& v) {
		return Vector3f(x + v.x, y + v.y, z + v.z);
	}

	Vector3f operator-(Vector3f& v) {
		return Vector3f(x - v.x, y - v.y, z - v.z);
	}

	Vector3f operator*(float n) {
		return Vector3f(x * n, y * n, z * n);
	}

	Vector3f operator/(float n) {
		return Vector3f(x / n, y / n, z / n);
	}

	Vector3f unit() {
		return *this / sqrt(x * x + y * y + z * z);
	}

	Vector3f cross(Vector3f v) {
		return Vector3f(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
	}
};

//Vector Eye(20, 5, 20);
//Vector At(0, 0, 0);
//Vector Up(0, 1, 0);

class Camera {
public:
	Vector3f eye, center, up;
	//10,4,9
	

	Camera(float eyeX = ex, float eyeY = ey, float eyeZ = ez, float centerX = 9.0f, float centerY = 4.5f, float centerZ = 10.0f, float upX = 0.0f, float upY = 4.5f, float upZ = 0.0f) {
		eye = Vector3f(eyeX, eyeY, eyeZ);
		center = Vector3f(centerX, centerY, centerZ);
		up = Vector3f(upX, upY, upZ);
	}

	void moveX(float d) {
		Vector3f right = up.cross(center - eye).unit();
		eye = eye + right * d;
		center = center + right * d;
		/*if (eye.x > 8 || eye.x < 0 || eye.y > 8 || eye.y < 0 || eye.z > 8 || eye.z < 0) {
			eye = eye - right * d;
		}
		else
			center = center + right * d;*/
	}
	/*void frontView() {
		eye = Vector3f(8.0, 1.0, 4.0);
		center = Vector3f(0.0, 0.5, 4.0);
		up = Vector3f(0.0, 0.5, 0.0);
		TView = false;
		SView = false;
		FView = true;
	}

	void sideView() {
		eye = Vector3f(4.0, 1.0, 7.8);
		center = Vector3f(4.0, 0.5, 0.0);
		up = Vector3f(0.0, 0.5, 0.0);
		TView = false;
		SView = true;
		FView = false;
	}
	void topView() {
		eye = Vector3f(4.0, 7.8, 4.0);
		center = Vector3f(4.0, 0.0, 4.0);
		up = Vector3f(0.0, 0.0, -1.0);
		TView = true;
		SView = false;
		FView = false;
	}*/

	void moveY(float d) {
		eye = eye + up.unit() * d;
		center = center + up.unit() * d;
		/*if (eye.x > 8 || eye.x < 0 || eye.y > 8 || eye.y < 0 || eye.z > 8 || eye.z < 0) {
			eye = eye - up.unit() * d;
		}
		else
			center = center + up.unit() * d;*/
	}

	void moveZ(float d) {
		Vector3f view = (center - eye).unit();
		eye = eye + view * d;
		center = center + view * d;
		/*if (eye.x > 8 || eye.x < 0 || eye.y > 8 || eye.y < 0 || eye.z > 8 || eye.z < 0) {
			eye = eye - view * d;
		}
		else
			center = center + view * d;*/
	}

	void rotateX(float a) {
		Vector3f view = (center - eye).unit();
		Vector3f right = up.cross(view).unit();
		view = view * cos(DEG2RAD(a)) + up * sin(DEG2RAD(a));
		up = view.cross(right);
		center = eye + view;
	}


	void rotateY(float a) {
		
		Vector3f view = (center - eye).unit();
		Vector3f right = up.cross(view).unit();
		view = view * cos(DEG2RAD(a)) + right * sin(DEG2RAD(a));
		right = view.cross(up);
		/*eye.x = cGunX - 1;
		eye.y = cGunY + 0.5;
		eye.z = cGunZ - 2;*/	
		if (firstPersonShooter) {
			if (frontView) {
				eye.x = cGunX - 1;
				eye.y = cGunY + 0.5;
				eye.z = cGunZ + 2;
				cWarriorX = cGunX - 2;
				cWarriorZ = cGunZ + 2;
			}
			else if (backView) {
				eye.x = cGunX + 1;
				eye.y = cGunY + 0.5;
				eye.z = cGunZ - 2;
				cWarriorX = cGunX + 2;
				cWarriorZ = cGunZ - 2;
			}
			else if (rightView) {
				eye.x = cGunX - 2;
				eye.y = cGunY + 0.5;
				eye.z = cGunZ - 1;
				cWarriorX = cGunX - 2;
				cWarriorZ = cGunZ - 2;
			}
			else if (leftView) {
				eye.x = cGunX + 2;
				eye.y = cGunY + 0.5;
				eye.z = cGunZ + 1;
				cWarriorX = cGunX + 2;
				cWarriorZ = cGunZ + 2;
			}
		}
		if (thirdPersonShooter) {
			if (frontView) {
				eye.x = cGunX - 1;
				eye.y = cGunY + 0.5;
				eye.z = cGunZ + 7;
				cWarriorX = cGunX - 2;
				cWarriorZ = cGunZ + 2;
			}
			else if (backView) {
				eye.x = cGunX + 1;
				eye.y = cGunY + 0.5;
				eye.z = cGunZ - 7;
				cWarriorX = cGunX + 2;
				cWarriorZ = cGunZ - 2;
			}
			else if (rightView) {
				eye.x = cGunX - 7;
				eye.y = cGunY + 0.5;
				eye.z = cGunZ - 1;
				cWarriorX = cGunX - 2;
				cWarriorZ = cGunZ - 2;
			}
			else if (leftView) {
				eye.x = cGunX + 7;
				eye.y = cGunY + 0.5;
				eye.z = cGunZ + 1;
				cWarriorX = cGunX + 2;
				cWarriorZ = cGunZ + 2;
			}
		}
		center = eye + view;
		printf("  eX: %f , eY: %f , eZ: %f, fview: %d, rView: %d, lView %d, bView: %d", eye.x, eye.y, eye.z, frontView, rightView, leftView, backView);
	}

	void look() {
		gluLookAt(
			eye.x, eye.y, eye.z,
			center.x, center.y, center.z,
			up.x, up.y, up.z
		);
	}
};

Camera camera;

int cameraZoom = 0;

// Model Variables
Model_3DS model_home;
Model_3DS model_player;
Model_3DS model_Gun;
Model_3DS model_zombie;
Model_3DS model_rock;
//Model_3DS model_fruit;
Model_3DS model_target;






// Textures
GLTexture tex_ground;
GLTexture tex_wall;
GLTexture tex_rock;


//=======================================================================
// Lighting Configuration Function
//=======================================================================
void InitLightSource()
{
	// Enable Lighting for this OpenGL Program
	glEnable(GL_LIGHTING);

	// Enable Light Source number 0
	// OpengL has 8 light sources
	glEnable(GL_LIGHT0);

	// Define Light source 0 ambient light
	GLfloat ambient[] = { 0.1f, 0.1f, 0.1, 1.0f };
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);

	// Define Light source 0 diffuse light
	GLfloat diffuse[] = { 0.5f, 0.5f, 0.5f, 1.0f };
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);

	// Define Light source 0 Specular light
	GLfloat specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);

	// Finally, define light source 0 position in World Space
	GLfloat light_position[] = { 0.0f, 10.0f, 0.0f, 1.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
}

//=======================================================================
// Material Configuration Function
//======================================================================
void InitMaterial()
{
	// Enable Material Tracking
	glEnable(GL_COLOR_MATERIAL);

	// Sich will be assigneet Material Properties whd by glColor
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

	// Set Material's Specular Color
	// Will be applied to all objects
	GLfloat specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);

	// Set Material's Shine value (0->128)
	GLfloat shininess[] = { 96.0f };
	glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
}

//=======================================================================
// OpengGL Configuration Function
//=======================================================================
void myInit(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);

	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();

	gluPerspective(fovy, aspectRatio, zNear, zFar);
	//*******************************************************************************************//
	// fovy:			Angle between the bottom and top of the projectors, in degrees.			 //
	// aspectRatio:		Ratio of width to height of the clipping plane.							 //
	// zNear and zFar:	Specify the front and back clipping planes distances from camera.		 //
	//*******************************************************************************************//

	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();

	//gluLookAt(Eye.x, Eye.y, Eye.z, At.x, At.y, At.z, Up.x, Up.y, Up.z);
	//*******************************************************************************************//
	// EYE (ex, ey, ez): defines the location of the camera.									 //
	// AT (ax, ay, az):	 denotes the direction where the camera is aiming at.					 //
	// UP (ux, uy, uz):  denotes the upward orientation of the camera.							 //
	//*******************************************************************************************//

	InitLightSource();

	InitMaterial();

	glEnable(GL_DEPTH_TEST);

	glEnable(GL_NORMALIZE);
}

void setupCamera() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(120, 640 / 480, 0.001, 120);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	camera.look();
}


//=======================================================================
// Render Ground Function
//=======================================================================
void RenderGround()
{
	glDisable(GL_LIGHTING);	// Disable lighting 

	glColor3f(0.6, 0.6, 0.6);	// Dim the ground texture a bit

	glEnable(GL_TEXTURE_2D);	// Enable 2D texturing

	glBindTexture(GL_TEXTURE_2D, tex_ground.texture[0]);	// Bind the ground texture

	glPushMatrix();
	glBegin(GL_QUADS);
	glNormal3f(0, 1, 0);	// Set quad normal direction.
	glTexCoord2f(0, 0);		// Set tex coordinates ( Using (0,0) -> (5,5) with texture wrapping set to GL_REPEAT to simulate the ground repeated grass texture).
	glVertex3f(-100, 0, -100);
	glTexCoord2f(5, 0);
	glVertex3f(100, 0, -100);
	glTexCoord2f(5, 5);
	glVertex3f(100, 0, 100);
	glTexCoord2f(0, 5);
	glVertex3f(-100, 0, 100);
	glEnd();
	glPopMatrix();

	glEnable(GL_LIGHTING);	// Enable lighting again for other entites coming throung the pipeline.

	glColor3f(1, 1, 1);	// Set material back to white instead of grey used for the ground texture.
}

void RenderWall()
{
	glDisable(GL_LIGHTING);	// Disable lighting 

	glColor3f(0.6, 0.6, 0.6);	// Dim the ground texture a bit

	glEnable(GL_TEXTURE_2D);	// Enable 2D texturing

	glBindTexture(GL_TEXTURE_2D, tex_wall.texture[0]);	// Bind the ground texture

	glPushMatrix();
	glBegin(GL_QUADS);
	glNormal3f(0, 1, 0);	// Set quad normal direction.
	glTexCoord2f(0, 0);		// Set tex coordinates ( Using (0,0) -> (5,5) with texture wrapping set to GL_REPEAT to simulate the ground repeated grass texture).
	glVertex3f(-34, 0, -40);
	glTexCoord2f(5, 0);
	glVertex3f(-34, 9, -40);
	glTexCoord2f(5, 5);
	glVertex3f(-34, 9, 30);
	glTexCoord2f(0, 5);
	glVertex3f(-34, 0, 30);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glBegin(GL_QUADS);
	glNormal3f(0, 1, 0);	// Set quad normal direction.
	glTexCoord2f(0, 0);		// Set tex coordinates ( Using (0,0) -> (5,5) with texture wrapping set to GL_REPEAT to simulate the ground repeated grass texture).
	glVertex3f(50, 0, -40);
	glTexCoord2f(5, 0);
	glVertex3f(50, 9, -40);
	glTexCoord2f(5, 5);
	glVertex3f(50, 9, 30);
	glTexCoord2f(0, 5);
	glVertex3f(50, 0, 30);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glBegin(GL_QUADS);
	glNormal3f(0, 1, 0);	// Set quad normal direction.
	glTexCoord2f(0, 0);		// Set tex coordinates ( Using (0,0) -> (5,5) with texture wrapping set to GL_REPEAT to simulate the ground repeated grass texture).
	glVertex3f(-34, 0, -40);
	glTexCoord2f(5, 0);
	glVertex3f(-34, 9, -40);
	glTexCoord2f(5, 5);
	glVertex3f(50, 9, -40);
	glTexCoord2f(0, 5);
	glVertex3f(50, 0, -40);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glBegin(GL_QUADS);
	glNormal3f(0, 1, 0);	// Set quad normal direction.
	glTexCoord2f(0, 0);		// Set tex coordinates ( Using (0,0) -> (5,5) with texture wrapping set to GL_REPEAT to simulate the ground repeated grass texture).
	glVertex3f(-34, 0, 30);
	glTexCoord2f(5, 0);
	glVertex3f(-34, 9, 30);
	glTexCoord2f(5, 5);
	glVertex3f(50, 9,30);
	glTexCoord2f(0, 5);
	glVertex3f(50, 0, 30);
	glEnd();
	glPopMatrix();

	glEnable(GL_LIGHTING);	// Enable lighting again for other entites coming throung the pipeline.

	glColor3f(1, 1, 1);	// Set material back to white instead of grey used for the ground texture.
}

//void RenderRock()
//{
//	glDisable(GL_LIGHTING);	// Disable lighting 
//
//	glColor3f(0.6, 0.6, 0.6);	// Dim the ground texture a bit
//
//	glEnable(GL_TEXTURE_2D);	// Enable 2D texturing
//
//	glBindTexture(GL_TEXTURE_2D, tex_rock.texture[0]);	
//
//	glPushMatrix();
//	glTranslatef(4, 1, 0);
//	glRotatef(90, 1, 0, 0);
//	glScalef(3, 3, 3);
//	model_rock.Draw();
//	glPopMatrix();
//
//	glEnable(GL_LIGHTING);	// Enable lighting again for other entites coming throung the pipeline.
//
//	glColor3f(1, 1, 1);	// Set material back to white instead of grey used for the ground texture.
//}

//=======================================================================
// Display Function
//=======================================================================

void drawGun() {

	
	if (bulletP) {
		/*glPushMatrix();
		glColor3d(0, 0, 1);
		glTranslatef(-2, 0.5, bulletZP + 1);
		glutSolidSphere(0.5, 20, 20);
		glPopMatrix();*/

		glPushMatrix();
		GLUquadricObj* qobj;
		qobj = gluNewQuadric();
		//glRotated(rotatefireBall, 0, 1, 0);
		glTranslatef(-2, 0.5, bulletZP + 1);
		glBindTexture(GL_TEXTURE_2D, tex3);
		gluQuadricTexture(qobj, true);
		gluQuadricNormals(qobj, GL_SMOOTH);
		gluSphere(qobj, 0.5, 100, 100);
		glPopMatrix();
	}

	if (player) {
		glPushMatrix();
		for (int i = 0;i < 6;i++) {
			if (warriorColor[i] == 1.0) {
				glColor3f(warriorColor[i], 0.0, 0.0);
				break;
			}
		}
		glTranslatef(-2, -4, 2);
		glRotatef(90, 1, 0, 0);
		glScalef(0.065, 0.065, 0.065);
		glRotated(180, 0, 0, 1);
		model_player.Draw();
		glPopMatrix();
	}

	glPushMatrix();
	//glTranslatef(10, 4, 10);
	glRotatef(shotAngle, 1, 0, 0);
	glRotatef(-90, 0, 1, 0);
	glScalef(0.2, 0.2, 0.2);
	model_Gun.Draw();
	glPopMatrix();

	if (bullet) {
		glPushMatrix();
		glColor3d(0, 0, 0);
		glTranslatef(0, 0.5, bulletZ - 1);
		glutSolidSphere(0.1, 20, 20);
		glPopMatrix();
	}

	

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glPushMatrix();
	glColor4f(1.0f, 0.0f, 0.0f, 0.5f);
	glTranslatef(0, 0.5, -161);
	gluCylinder(gluNewQuadric(), 0.05, 0.05, 160, 20, 20);
	glPopMatrix();
	glDisable(GL_BLEND);

}

void drawZombie(int i) {

	glColor3d(0.5, 0.5, 0.5);
	glPushMatrix();
	glTranslated(0, 0.15, 0);
	if (collide[i])
		glColor3d(1, 0, 0);
	glRotatef(90, 1, 0, 0);
	glScalef(0.09, 0.09, 0.09);
	model_zombie.Draw();
	glPopMatrix();

	if (!zombiefirstShot[i]) {
		glPushMatrix();
		glTranslated(0, 2.8, 0);
		glColor3d(0, 1, 0); // Green color for the cube
		glutSolidCube(0.3); // Draw a small cube
		glPopMatrix();
	}
	
	glPushMatrix();
	glTranslated(-0.15, 2.8, 0);
	glColor3d(0, 1, 0); // Green color for the cube
	glutSolidCube(0.3); // Draw a small cube
	glPopMatrix();
	

	glPushMatrix();
	glColor3d(0, 0, 1);
	glTranslated(0, -3.75, 0);
	glRotated(90,1,0,0);
	GLUquadric* quadric = gluNewQuadric();
	gluCylinder(quadric, 1, 1, 0.2, 20, 20);

	// Draw the top disk to cap the cylinder
	//glTranslated(0, 0, -0.2);
	gluDisk(quadric, 0.0, 1, 20, 20);

	// Move to the bottom of the cylinder and draw the bottom disk
	//glTranslated(0, 0, -0.2);
	gluDisk(quadric, 0.0, 1, 20, 20);
	glColor3d(0.5, 0.5, 0.5);
	glPopMatrix();
}

void drawHealth() {
	for (int j = 0;j < lives;j++) {
		if (health[j]) {
			glPushMatrix();
			glColor3f(1, 0, 0);
			glBegin(GL_POLYGON);
			int sides = 8000;
			double radius = 5.0;
			double pi = 3.14159265358979323846;
			for (double i = 0; i < sides; i++) {
				double angle = pi * (i / sides);
				double x = healthX[j] + radius * cos(angle);
				double y = healthY[j] + radius * sin(angle);
				glVertex3d(x, y, 0);
			}
			glEnd();
			glBegin(GL_POLYGON);
			int s = 8000;
			double r = 5.0;
			for (double i = 0; i < sides; i++) {
				double a = pi * (i / sides);
				double x = healthX[j] - 10 + radius * cos(a);
				double y = healthY[j] + radius * sin(a);
				glVertex3d(x, y, 0);
			}
			glEnd();
			glBegin(GL_POLYGON);
			int side = 10000;
			double rad = 10.0;
			for (double i = side / 2; i < side; i++) {
				double a = 2 * pi * (i / side);
				double x = healthX[j] - 5 + rad * cos(a);
				double y = healthY[j] + rad * sin(a);
				glVertex3d(x, y, 0);
			}
			glEnd();
			glPopMatrix();
		}
	}

}

void myDisplay(void)
{
	setupCamera();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



	GLfloat lightIntensity[] = { 0.7, 0.7, 0.7, 1.0f };
	GLfloat lightPosition[] = { 0.0f, 100.0f, 0.0f, 0.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
	glLightfv(GL_LIGHT0, GL_AMBIENT, lightIntensity);

	// Draw Ground
	RenderGround();

	RenderWall();





	GLUquadricObj* qobj;
	qobj = gluNewQuadric();
	//sky box
	glPushMatrix();
	glTranslated(0, 0, 0);
	glRotated(90, 1, 0, 1);
	glBindTexture(GL_TEXTURE_2D, tex);
	gluQuadricTexture(qobj, true);
	gluQuadricNormals(qobj, GL_SMOOTH);
	gluSphere(qobj, 97.5, 1000, 1000);
	glPopMatrix();

	/*glPushMatrix();
	glTranslated(-9, 2, 4);
	glRotated(rotatefireBall, 0, 1, 0);
	glBindTexture(GL_TEXTURE_2D, tex3);
	gluQuadricTexture(qobj, true);
	gluQuadricNormals(qobj, GL_SMOOTH);
	gluSphere(qobj, 2, 100, 100);
	glPopMatrix();*/


	
	//Rock
	for (int i = 0;i < 6;i++) {
		glPushMatrix();
		glTranslated(cRockX[i], cRockY[i], cRockZ[i]);
		//glRotated(45, 1, 0, 0);  // Rotate by 45 degrees to create a diamond shape
		glRotated(-90, 1, 0, 0);  // Rotate by 45 degrees to create a diamond shape
		//glTranslated(0, -2.5, -2.5);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, tex2);

		gluQuadricTexture(qobj, true);
		gluQuadricNormals(qobj, GL_SMOOTH);

		// Create a "cube" using gluCylinder
		gluCylinder(qobj, 3, 3, 5, 20, 20);  // The base radius should be equal to the desired side length

		glDisable(GL_TEXTURE_2D);
		glPopMatrix();
	}


	/*glPushMatrix();
	glTranslatef(15, 4, 0);
	glRotatef(90, 1, 0, 0);
	glScalef(0.1, 0.1, 0.1);
	model_target.Draw();
	glPopMatrix();*/

	/*glPushMatrix();
	glTranslatef(4, 1, 0);
	glRotatef(90, 1, 0, 0);
	glScalef(0.1, 0.1, 0.1);
	model_rock.Draw();
	glPopMatrix();*/
	for (int i = 0;i < 6; i++) {
		if (!zombieDied[i]) {
			glPushMatrix();
			/*if (collide[i])
				glColor3d(1, 0, 0);*/
			/*glTranslatef(10, 4, 0);
			glRotatef(90, 1, 0, 0);
			glScalef(0.09, 0.09, 0.09);*/
			//model_zombie.Draw(i);
			glTranslatef(cZombieX[i], cZombieY[i], cZombieZ[i]);
			glRotated(zombiePunchRotateAngle[i], 1, 0, 0);
			drawZombie(i);
			glPopMatrix();
		}
	}

	glPushMatrix();
	glColor3f(0.0, 0.0, 0.0);
	glTranslatef(cGunX, cGunY, cGunZ);
	glRotatef(rotateGun, 0, 1, 0);
	if(firstPersonShooter)
		glTranslated(1, 3.5, 0);
	else
		glTranslated(1, 3.5, 5);
	glRasterPos2i(0, 0);
		if (GameScore == 120) {
			if (!alamy) {
				SoundEngine->play2D("audio/perfect.mp3", false);
				alamy = true;
			}
			std::string score = "SCORE : " + std::to_string(GameScore) + " PERFECT!";
			for (char c : score) {
				glutBitmapCharacter(GLUT_BITMAP_9_BY_15, c);
			}
		}
		else
		{
			std::string score = "SCORE : " + std::to_string(GameScore);
			for (char c : score) {
				glutBitmapCharacter(GLUT_BITMAP_9_BY_15, c);
			}
		}
	
	glPopMatrix();



	/*glPushMatrix();
	glTranslatef(4, 1, 0);
	glRotatef(90, 1, 0, 0);
	glScalef(1, 1, 1);
	model_fruit.Draw();
	glPopMatrix();*/

	glPushMatrix();
	glColor3d(0.5, 0.5, 0.5);
	glTranslatef(20, 4.5, -33);
	glRotatef(rotateSkull, 0, 1, 0);
	glScaled(0.3, 0.3, 0.3);
	model_home.Draw();
	glPopMatrix();



	glPushMatrix();
	glTranslatef(cGunX, cGunY, cGunZ);
	glRotatef(rotateGun-angleX , 0, 1, 0);
	drawGun();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(cGunX, cGunY, cGunZ);
	glRotatef(rotateGun, 0, 1, 0);
	if (firstPersonShooter)
		glTranslated(-38, 35, -20);
	else
		glTranslated(-38, 35, -15);
	glScaled(0.125, 0.125, 1);
	drawHealth();
	glPopMatrix();


	glutSwapBuffers();
}

//=======================================================================
// Keyboard Function
//=======================================================================
void myKeyboard(unsigned char button, int x, int y)
{
	float d = 0.5;
	switch (button)
	{
	case 't':
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		break;
	case 'r':
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		break;
	case 'k':
	shootP = true;
	bulletP = true;
	break;
	case 'w':
		//printf("fview: %d, rView: %d, lView %d, bView: %d", frontView, rightView, leftView, backView);
		if (frontView) {
			if (!(cWarriorZ - 2 < -40)) {
				cGunZ -= 0.5;
				cWarriorZ -= 0.5;
				for (int i = 0;i < 6;i++) {
					if (cWarriorX >= cRockX[i] - 3 && cWarriorX <= cRockX[i] + 3 && cWarriorZ >= cRockZ[i] - 3 && cWarriorZ <= cRockZ[i] + 3) {
						cGunZ += 0.5;
						cWarriorZ += 0.5;
						rockCollided = true;
						break;
					}
				}
				if (!rockCollided) {
					camera.moveZ(d);
				}
				else
					rockCollided = false;
			}
			
			//printf("cgunx: %f, cgunz: %f   __  cWarx: %f, cWarz: %f   __", cGunX, cGunZ, cWarriorX, cWarriorZ);
		}
		else if (backView) {
			if (!(cWarriorZ + 2 > 30)) {
				cGunZ += 0.5;
				cWarriorZ += 0.5;
				for (int i = 0;i < 6;i++) {
					if (cWarriorX >= cRockX[i] - 3 && cWarriorX <= cRockX[i] + 3 && cWarriorZ >= cRockZ[i] - 3 && cWarriorZ <= cRockZ[i] + 3) {
						cGunZ -= 0.5;
						cWarriorZ -= 0.5;
						rockCollided = true;
						break;
					}
				}
				if (!rockCollided) {
					camera.moveZ(d);
				}
				else
					rockCollided = false;
			}
		}
		else if (rightView) {
			if (!(cWarriorX + 2 > 50)) {
				cGunX += 0.5;
				cWarriorX += 0.5;
				for (int i = 0;i < 6;i++) {
					if (cWarriorX >= cRockX[i] - 3 && cWarriorX <= cRockX[i] + 3 && cWarriorZ >= cRockZ[i] - 3 && cWarriorZ <= cRockZ[i] + 3) {
						cGunX -= 0.5;
						cWarriorX -= 0.5;
						rockCollided = true;
						break;
					}
				}
				if (!rockCollided) {
					camera.moveZ(d);
				}
				else
					rockCollided = false;
			}
			//printf("cgunx: %f, cgunz: %f   __  cWarx: %f, cWarz: %f   __", cGunX, cGunZ, cWarriorX, cWarriorZ);
		}
		else if (leftView) {
			if (!(cWarriorX - 2 < -34)) {
				cGunX -= 0.5;
				cWarriorX -= 0.5;
				for (int i = 0;i < 6;i++) {
					if (cWarriorX >= cRockX[i] - 3 && cWarriorX <= cRockX[i] + 3 && cWarriorZ >= cRockZ[i] - 3 && cWarriorZ <= cRockZ[i] + 3) {
						cGunX += 0.5;
						cWarriorX += 0.5;
						rockCollided = true;
						break;
					}
				}
				if (!rockCollided)
					camera.moveZ(d);
				else
					rockCollided = false;
			}
		}
		break;
	case 's':
		//printf("fview: %d, rView: %d, lView %d, bView: %d", frontView, rightView, leftView, backView);
		if (frontView) {
			if (!(cWarriorZ + 2 > 30)) {
				cGunZ += 0.5;
				cWarriorZ += 0.5;
				for (int i = 0;i < 6;i++) {
					if (cWarriorX >= cRockX[i] - 3 && cWarriorX <= cRockX[i] + 3 && cWarriorZ >= cRockZ[i] - 3 && cWarriorZ <= cRockZ[i] + 3) {
						cGunZ -= 0.5;
						cWarriorZ -= 0.5;
						rockCollided = true;
						break;
					}
				}
				if (!rockCollided)
					camera.moveZ(-d);
				else
					rockCollided = false;
			}
		}
		else if (backView) {
			if (!(cWarriorZ - 2 < -40)) {
				cGunZ -= 0.5;
				cWarriorZ -= 0.5;
				for (int i = 0;i < 6;i++) {
					if (cWarriorX >= cRockX[i] - 3 && cWarriorX <= cRockX[i] + 3 && cWarriorZ >= cRockZ[i] - 3 && cWarriorZ <= cRockZ[i] + 3) {
						cGunZ += 0.5;
						cWarriorZ += 0.5;
						rockCollided = true;
						break;
					}
				}
				if (!rockCollided)
					camera.moveZ(-d);
				else
					rockCollided = false;
			}
		}
		else if (rightView) {
			if (!(cWarriorX - 2 < -34)) {
				cGunX -= 0.5;
				cWarriorX -= 0.5;
				for (int i = 0;i < 6;i++) {
					if (cWarriorX >= cRockX[i] - 3 && cWarriorX <= cRockX[i] + 3 && cWarriorZ >= cRockZ[i] - 3 && cWarriorZ <= cRockZ[i] + 3) {
						cGunX += 0.5;
						cWarriorX += 0.5;
						rockCollided = true;
						break;
					}
				}
				if (!rockCollided)
					camera.moveZ(-d);
				else
					rockCollided = false;
			}

		}
		else if (leftView) {
			cGunX += 0.5;
			cWarriorX += 0.5;
			if (!(cWarriorX + 2 > 50)) {
				for (int i = 0;i < 6;i++) {
					if (cWarriorX >= cRockX[i] - 3 && cWarriorX <= cRockX[i] + 3 && cWarriorZ >= cRockZ[i] - 3 && cWarriorZ <= cRockZ[i] + 3) {
						cGunX -= 0.5;
						cWarriorX -= 0.5;
						rockCollided = true;
						break;
					}
				}
				if (!rockCollided)
					camera.moveZ(-d);
				else
					rockCollided = false;
			}
		}
		break;
	case 'a':
		//printf("fview: %d, rView: %d, lView %d, bView: %d", frontView, rightView, leftView, backView);
		if (frontView) {
			if (!(cWarriorX - 2 < -34)) {
				cGunX -= 0.5;
				cWarriorX -= 0.5;
				for (int i = 0;i < 6;i++) {
					if (cWarriorX >= cRockX[i] - 3 && cWarriorX <= cRockX[i] + 3 && cWarriorZ >= cRockZ[i] - 3 && cWarriorZ <= cRockZ[i] + 3) {
						cGunX += 0.5;
						cWarriorX += 0.5;
						rockCollided = true;
						break;
					}
				}
				if (!rockCollided)
					camera.moveX(d);
				else
					rockCollided = false;
			}
		}
		else if (backView) {
			if (!(cWarriorX + 2 > 50)) {
				cGunX += 0.5;
				cWarriorX += 0.5;
				for (int i = 0;i < 6;i++) {
					if (cWarriorX >= cRockX[i] - 3 && cWarriorX <= cRockX[i] + 3 && cWarriorZ >= cRockZ[i] - 3 && cWarriorZ <= cRockZ[i] + 3) {
						cGunX -= 0.5;
						cWarriorX -= 0.5;
						rockCollided = true;
						break;
					}
				}
				if (!rockCollided)
					camera.moveX(d);
				else
					rockCollided = false;
			}
		}
		else if (rightView) {
			if (!(cWarriorZ - 2 < -40)) {
				cGunZ -= 0.5;
				cWarriorZ -= 0.5;
				for (int i = 0;i < 6;i++) {
					if (cWarriorX >= cRockX[i] - 3 && cWarriorX <= cRockX[i] + 3 && cWarriorZ >= cRockZ[i] - 3 && cWarriorZ <= cRockZ[i] + 3) {
						cGunZ += 0.5;
						cWarriorZ += 0.5;
						rockCollided = true;
						break;
					}
				}
				if (!rockCollided)
					camera.moveX(d);
				else
					rockCollided = false;
			}

		}
		else if (leftView) {
			if (!(cWarriorZ + 2 > 30)) {
				cGunZ += 0.5;
				cWarriorZ += 0.5;
				for (int i = 0;i < 6;i++) {
					if (cWarriorX >= cRockX[i] - 3 && cWarriorX <= cRockX[i] + 3 && cWarriorZ >= cRockZ[i] - 3 && cWarriorZ <= cRockZ[i] + 3) {
						cGunZ -= 0.5;
						cWarriorZ -= 0.5;
						rockCollided = true;
						break;
					}
				}
				if (!rockCollided)
					camera.moveX(d);
				else
					rockCollided = false;
			}
		}
		break;
	case 'd':
		//printf("fview: %d, rView: %d, lView %d, bView: %d", frontView, rightView, leftView, backView);
		if (frontView) {
			if (!(cWarriorX + 2 > 50)) {
				cGunX += 0.5;
				cWarriorX += 0.5;
				for (int i = 0;i < 6;i++) {
					if (cWarriorX >= cRockX[i] - 3 && cWarriorX <= cRockX[i] + 3 && cWarriorZ >= cRockZ[i] - 3 && cWarriorZ <= cRockZ[i] + 3) {
						cGunX -= 0.5;
						cWarriorX -= 0.5;
						rockCollided = true;
						break;
					}
				}
				if (!rockCollided)
					camera.moveX(-d);
				else
					rockCollided = false;
			}
		}
		else if (backView) {
			if (!(cWarriorX - 2 < -34)) {
				cGunX -= 0.5;
				cWarriorX -= 0.5;
				for (int i = 0;i < 6;i++) {
					if (cWarriorX >= cRockX[i] - 3 && cWarriorX <= cRockX[i] + 3 && cWarriorZ >= cRockZ[i] - 3 && cWarriorZ <= cRockZ[i] + 3) {
						cGunX += 0.5;
						cWarriorX += 0.5;
						rockCollided = true;
						break;
					}
				}
				if (!rockCollided)
					camera.moveX(-d);
				else
					rockCollided = false;
			}
		}
		else if (rightView) {
			if (!(cWarriorZ + 2 > 30)) {
				cGunZ += 0.5;
				cWarriorZ += 0.5;
				for (int i = 0;i < 6;i++) {
					if (cWarriorX >= cRockX[i] - 3 && cWarriorX <= cRockX[i] + 3 && cWarriorZ >= cRockZ[i] - 3 && cWarriorZ <= cRockZ[i] + 3) {
						cGunZ -= 0.5;
						cWarriorZ -= 0.5;
						rockCollided = true;
						break;
					}
				}
				if (!rockCollided)
					camera.moveX(-d);
				else
					rockCollided = false;
			}
		}
		else if (leftView) {
			if (!(cWarriorZ - 2 < -40)) {
				cGunZ -= 0.5;
				cWarriorZ -= 0.5;
				for (int i = 0;i < 6;i++) {
					if (cWarriorX >= cRockX[i] - 3 && cWarriorX <= cRockX[i] + 3 && cWarriorZ >= cRockZ[i] - 3 && cWarriorZ <= cRockZ[i] + 3) {
						cGunZ += 0.5;
						cWarriorZ += 0.5;
						rockCollided = true;
						break;
					}
				}
				if (!rockCollided)
					camera.moveX(-d);
				else
					rockCollided = false;
			}
		}
		break;

	case 'q':
		camera.moveY(d);
		break;
	case 'e':
		camera.moveY(-d);
		break;
	case 'c':
		if (firstPersonShooter) {
			camera.moveZ(-5);
			firstPersonShooter = false;
			thirdPersonShooter = true;
			player = true;;			
		}
		else if (thirdPersonShooter) {
			camera.moveZ(5);
			firstPersonShooter = true;
			thirdPersonShooter = false;
			player = false;
		}
		break;
	/*case 'n':
		camera.sideView();
		break;
	case 'm':
		camera.topView();
		break;*/
	/*case 'k':
		printf("Hello");
		shoot = true;
		break;*/
	case 27:
		exit(0);
		break;
	default:
		break;
	}

	glutPostRedisplay();
}

void passM(int x, int y)//passive motion function takes 2 parameters the x and y positions of the mouse
//it allows the user to make use of the mouse motion without clicking on the mouse buttons
{
	float sensitivity = 0.1; // Adjust sensitivity as needed

	// Calculate the change in mouse position
	int deltaX = x - passX;


	// Update the rotation angle
	angleX = (angleX + (deltaX * sensitivity))/* - 0.80007*/;
	//printf(" angle: %f" ,  angleX );
	

	// Ensure the angle stays within bounds (optional)
	/*if (angleX > 360.0) {
		angleX -= 360.0;
	}
	else if (angleX < 0.0) {
		angleX += 360.0;
	}*/

	// Update the stored mouse position
	passX = x;

	// Request a redraw to reflect the changes
	glutPostRedisplay();
}

void Special(int key, int x, int y) {
	//float a = 2.0;

	switch (key) {
	/*case GLUT_KEY_UP:
		fV = true;
		rV = false;
		lV = false;
		bV = false;
	if (rightView) {
			camera.rotateY(90); 
			rotateGun += 90;
		}
		else if (backView) {
			camera.rotateY(180); 
			rotateGun += 180;
		}
		else if (leftView) {
			camera.rotateY(-90);
			rotateGun -= 90;
		}
		frontView = true;
		leftView = false;
		rightView = false;
		backView = false;
		break;*/
	case GLUT_KEY_DOWN:
		printf("cgunx: %f, cgunz: %f   __  cWarx: %f, cWarz: %f   __", cGunX, cGunZ, cWarriorX, cWarriorZ);
		if (frontView) {
			frontView = false;
			backView = true;
		}
		else if (backView) {
			frontView = true;
			backView = false;
		}
		else if (rightView) {
			leftView = true;
			rightView = false;
		}
		else if (leftView) {
			rightView = true;
			leftView = false;
		}
		//if (backView) {
		//	camera.rotateY(-90); // rotate to your right
		//	rotateGun -= 90;
		//}
		//else if (frontView) {
		//	camera.rotateY(180);
		//	rotateGun += 180;
		//}
		//else if (leftView) {
		//	camera.rotateY(90); // rotate to your left
		//	rotateGun += 90;
		//}
		//frontView = false;
		//leftView = false;
		//rightView = false;
		//backView = true;
		camera.rotateY(180);
		rotateGun += 180;
		if (cWarriorZ > 30 || cWarriorZ < -40 || cWarriorX > 50 || cWarriorX < -34) {
			if (frontView) {
				frontView = false;
				backView = true;
			}
			else if (backView) {
				frontView = true;
				backView = false;
			}
			else if (rightView) {
				leftView = true;
				rightView = false;
			}
			else if (leftView) {
				rightView = true;
				leftView = false;
			}
			camera.rotateY(180);
			rotateGun += 180;
		}
		/*cosThet = cos((rotateGun) * PI / 180.0);
		sinThet = sin((rotateGun) * PI / 180.0);
		cWarriorX = cWarriorX * cosThet + cWarriorZ * sinThet;
		cWarriorX = -cWarriorX * sinThet + cWarriorZ * cosThet;*/
		break;
	case GLUT_KEY_LEFT:
		printf("cgunx: %f, cgunz: %f   __  cWarx: %f, cWarz: %f   __", cGunX, cGunZ, cWarriorX, cWarriorZ);
		if (frontView) {
			frontView = false;
			leftView = true;
		}
		else if (backView) {
			backView = false;
			rightView = true;
		}
		else if (rightView) {
			frontView = true;
			rightView = false;
		}
		else if (leftView) {
			backView = true;
			leftView = false;
		}
		camera.rotateY(90); // rotate to your left
		rotateGun += 90;
		if (cWarriorZ > 30 || cWarriorZ < -40 || cWarriorX > 50 || cWarriorX < -34) {
			if (frontView) {
				frontView = false;
				rightView = true;
			}
			else if (backView) {
				leftView = true;
				backView = false;
			}
			else if (rightView) {
				backView = true;
				rightView = false;
			}
			else if (leftView) {
				frontView = true;
				leftView = false;
			}
			camera.rotateY(-90); // rotate to your right
			rotateGun -= 90;
		}
		/*cosThet = cos((rotateGun) * PI / 180.0);
		sinThet = sin((rotateGun) * PI / 180.0);
		cWarriorX = cWarriorX * cosThet + cWarriorZ * sinThet;
		cWarriorX = -cWarriorX * sinThet + cWarriorZ * cosThet;*/
		break;
	case GLUT_KEY_RIGHT:
		printf("cgunx: %f, cgunz: %f   __  cWarx: %f, cWarz: %f   __", cGunX, cGunZ, cWarriorX, cWarriorZ);
		if (frontView) {
			frontView = false;
			rightView = true;
		}
		else if (backView) {
			leftView = true;
			backView = false;
		}
		else if (rightView) {
			backView = true;
			rightView = false;
		}
		else if (leftView) {
			frontView = true;
			leftView = false;
		}
		camera.rotateY(-90); // rotate to your right
		rotateGun -= 90;
		if (cWarriorZ > 30 || cWarriorZ < -40 || cWarriorX > 50 || cWarriorX < -34) {
			if (frontView) {
				frontView = false;
				leftView = true;
			}
			else if (backView) {
				backView = false;
				rightView = true;
			}
			else if (rightView) {
				frontView = true;
				rightView = false;
			}
			else if (leftView) {
				backView = true;
				leftView = false;
			}
			camera.rotateY(90); // rotate to your left
			rotateGun += 90;
		}
	    /*cosThet = cos((rotateGun) * PI / 180.0);
		sinThet = sin((rotateGun) * PI / 180.0);
		cWarriorX = cWarriorX * cosThet + cWarriorZ * sinThet;
		cWarriorX = -cWarriorX * sinThet + cWarriorZ * cosThet;*/
		break;
	}

	glutPostRedisplay();
}

//=======================================================================
// Motion Function
//=======================================================================
void myMotion(int x, int y)
{
	//y = HEIGHT - y;

	//if (cameraZoom - y > 0)
	//{
	//	Eye.x += -0.1;
	//	Eye.z += -0.1;
	//}
	//else
	//{
	//	Eye.x += 0.1;
	//	Eye.z += 0.1;
	//}

	//cameraZoom = y;

	//glLoadIdentity();	//Clear Model_View Matrix

	//gluLookAt(Eye.x, Eye.y, Eye.z, At.x, At.y, At.z, Up.x, Up.y, Up.z);	//Setup Camera with modified paramters

	//GLfloat light_position[] = { 0.0f, 10.0f, 0.0f, 1.0f };
	//glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	//glutPostRedisplay();	//Re-draw scene 
}

//=======================================================================
// Mouse Function
//=======================================================================
void myMouse(int button, int state, int x, int y)
{
	/*y = HEIGHT - y;

	if (state == GLUT_DOWN)
	{
		cameraZoom = y;
	}*/
	if (button == GLUT_LEFT_BUTTON) {
		shoot = true;
	}
}

//=======================================================================
// Reshape Function
//=======================================================================
void myReshape(int w, int h)
{
	if (h == 0) {
		h = 1;
	}

	WIDTH = w;
	HEIGHT = h;

	// set the drawable region of the window
	glViewport(0, 0, w, h);

	// set up the projection matrix 
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(fovy, (GLdouble)WIDTH / (GLdouble)HEIGHT, zNear, zFar);

	// go back to modelview matrix so we can move the objects about
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//gluLookAt(Eye.x, Eye.y, Eye.z, At.x, At.y, At.z, Up.x, Up.y, Up.z);
}

//=======================================================================
// Assets Loading Function
//=======================================================================
void LoadAssets()
{
	// Loading Model files
	model_home.Load("Models/home2/skull.3ds");
	model_player.Load("Models/player/player.3DS");
	model_zombie.Load("Models/zombie/zombie.3DS");
	model_Gun.Load("Models/Gun/Gun.3ds");
	//model_fruit.Load("Models/fruit/fruit.3ds");
	//model_rock.Load("Models/rock/rock.3DS");
	//model_rock.Load("Models/home/target.3ds");



	// Loading texture files
	tex_ground.Load("Textures/ground.bmp");
	tex_wall.Load("Textures/wall2.bmp");
	//tex_rock.Load("Textures/rock.bmp");
	loadBMP(&tex, "Textures/blu-sky-3.bmp", true);
	loadBMP(&tex3, "Textures/fireBall.bmp", true);
	loadBMP(&tex2, "Textures/rock.bmp", true);


}



void shootTimer(int val) {

	if (shoot && shootTime > 0) {
		if (!shootSound) {
			SoundEngine->play2D("audio/gunShot.mp3", false);
			shootSound = true;
		}
		cbulletx = 0.0;
		cbullety = 0.0;
		cbulletz = 0.0;
		bulletZ -= 1;
		shootTime -= 1;
		//cbulletz -= 1;
		if (shootTime == 49)
			shot = true;

		float cosTheta = cos((rotateGun-angleX) * PI / 180.0);
		float sinTheta = sin((rotateGun-angleX) * PI / 180.0);

		cbulletx = /*cbulletx * cos(-angleX) + cbulletz * sin(-angleX) + */((bulletZ-1) * sinTheta) + cGunX;
		cbullety = cbullety + 0.5 + cGunY;
		cbulletz = /*-cbulletx * sin(-angleX) + cbulletz * cos(-angleX) +*/ ((bulletZ-1) * cosTheta) + cGunZ;
		//printf("  cX: %f , cY: %f , cZ: %f, bullet: %f, angle: %f, cGunZ %f", cbulletx, cbullety, cbulletz, bulletZ, -angleX, cGunZ);
		for (int i = 0;i < 6;i++) {
			if (cbulletx >= cRockX[i] - 3 && cbulletx <= cRockX[i] + 3 && cbulletz >= cRockZ[i] - 3 && cbulletz <= cRockZ[i] + 3) {
				bulletCollidesRock = true;
				bullet = false;
			}
		}
		if (!bulletCollidesRock) {
			for (int i = 0;i < 6;i++) {
				if (cbulletx > cZombieX[i] - 0.8 && cbulletx < cZombieX[i] + 1 && cbullety>0 && cbullety < 8 && cbulletz >= cZombieZ[i] - 2 && cbulletz <= cZombieZ[i] + 2 && !oneZombiePerShot) {
					if (!zombiefirstShot[i]) {
						collide[i] = true;
						zombiefirstShot[i] = true;
						oneZombiePerShot = true;
						bullet = false;
					}
					else if (zombiefirstShot[i] && !zombieDied[i] && !collide[i] && !oneZombiePerShot) {
						collide[i] = true;
						zombieDied[i] = true;
						oneZombiePerShot = true;
						bullet = false;
						GameScore += 20;
					}
				}
				else
					collide[i] = false;
			}
		}
	}
	else {
		shootSound = false;
		shoot = false;
		shootTime = 50;
		bulletZ = 0;
		cbulletz = cGunZ;
		oneZombiePerShot = false;
		bullet = true;
		bulletCollidesRock = false;
	}

	if (shootP && shootTimeP > 0) {
		/*if (!shootSound) {
			SoundEngine->play2D("audio/gunShot.mp3", false);
			shootSound = true;
		}*/
		cbulletxP = 0.0;
		cbulletyP = 0.0;
		cbulletzP = 0.0;
		bulletZP -= 2;
		shootTimeP -= 1;
		//cbulletz -= 1;
		if (shootTimeP == 99)
			shotP = true;

		float cosTheta = cos((rotateGun - angleX) * PI / 180.0);
		float sinTheta = sin((rotateGun - angleX) * PI / 180.0);

		cbulletxP = /*cbulletx * cos(-angleX) + cbulletz * sin(-angleX) + */(-2*cosTheta)+((bulletZP + 1) * sinTheta) + cGunX;
		cbulletyP = cbulletyP + 0.5 + cGunY;
		cbulletzP = /*-cbulletx * sin(-angleX) + cbulletz * cos(-angleX) +*/ (2*sinTheta)+((bulletZP + 1) * cosTheta) + cGunZ;
		//printf("  cX: %f , cY: %f , cZ: %f, bullet: %f, angle: %f, cGunZ %f", cbulletx, cbullety, cbulletz, bulletZ, -angleX, cGunZ);
		for (int i = 0;i < 6;i++) {
			if (cbulletxP >= cRockX[i] - 3 && cbulletxP <= cRockX[i] + 3 && cbulletzP >= cRockZ[i] - 3 && cbulletzP <= cRockZ[i] + 3) {
				bulletCollidesRockP = true;
				bulletP = false;
			}
		}
		if (!bulletCollidesRockP) {
			for (int i = 0;i < 6;i++) {
				if (cbulletxP > cZombieX[i] - 0.8 && cbulletxP < cZombieX[i] + 1 && cbulletyP>0 && cbulletyP < 8 && cbulletzP >= cZombieZ[i] - 2 && cbulletzP <= cZombieZ[i] + 2) {
					if (!zombieDied[i] && !collideP[i] && !oneZombiePerShotP) {
						collideP[i] = true;
						zombieDied[i] = true;
						oneZombiePerShotP = true;
						bulletP = false;
						GameScore += 20;
					}
				}
				else
					collideP[i] = false;
			}
		}
	}
	else {
		//shootSound = false;
		shootP = false;
		shootTimeP = 100;
		bulletZP = 0;
		cbulletzP = cWarriorZ;
		oneZombiePerShotP = false;
		bulletP = false;
		bulletCollidesRockP = false;
	}
	//glTranslatef(10, 4, 0);
	

	/*if (firstPersonShooter) {
		if (frontView) {
			ex = cGunX - 1;
			ey = cGunY + 0.5;
			ez = cGunZ + 2;
		}
		else if (backView) {
			ex = cGunX + 1;
			ey = cGunY + 0.5;
			ez = cGunZ - 2;
		}
		else if (rightView) {
			ex = cGunX - 2;
			ey = cGunY + 0.5;
			ez = cGunZ - 1;
		}
		else if (leftView) {
			ex = cGunX + 2;
			ey = cGunY + 0.5;
			ez = cGunZ + 1;
		}
	}

	else if (thirdPersonShooter) {
		if (frontView) {
			ex = cGunX - 1;
			ey = cGunY + 0.5;
			ez = cGunZ + 4;
		}
		else if (backView) {
			ex = cGunX + 1;
			ey = cGunY + 0.5;
			ez = cGunZ - 4;
		}
		else if (rightView) {
			ex = cGunX - 4;
			ey = cGunY + 0.5;
			ez = cGunZ - 1;
		}
		else if (leftView) {
			ex = cGunX + 4;
			ey = cGunY + 0.5;
			ez = cGunZ + 1;
		}
	}*/


	glutPostRedisplay();
	glutTimerFunc(1, shootTimer, 0);
}

void shootRotation(int val) {
	rotateSkull += 10;
	rotatefireBall += 10;

	if (shot) {
		shotAngle = 45;
		shot = false;
	}
	else if (shotP) {
		shotP = false;
	}
	else
		shotAngle = 0;
	glutPostRedisplay();
	glutTimerFunc(60, shootRotation, 0);
}

void zombieGetCloser(int val) {
	for (int i = 0;i < 6;i++) {
		if (cZombieX[i] > cWarriorX - 0.5 && cZombieX[i]< cWarriorX + 0.5 && cZombieZ[i]>cWarriorZ - 0.5 && cZombieZ[i] < cWarriorZ + 0.5) {
			if (!zombieDied[i]) {
				damageSoundOnlyOnce[i] = true;
				if (timerPunch[i] > 0) {
					zombiePunchRotateAngle[i] = 45;
					timerPunch[i]--;
					warriorColor[i] = 1.0;
				}
				else {
					warriorColor[i] = 0.0;
					zombiePunchRotateAngle[i] = 0.0;
					timerPunch[i] = 2;
				}
			}
		}
		else {
			damageSoundOnlyOnce[i] = false;
			warriorColor[i] = 0.0;
			zombiePunchRotateAngle[i] = 0.0;
			timerPunch[i] = 2;
			if (timerFromDecX[i]) {
				int r = whichRock[i];
				if (cZombieZ[i] <= cRockZ[r] + 3) {
					cZombieZ[i] += 0.2;
				}
				else if (cZombieX[i] >= cRockX[r] - 3) {
					cZombieX[i] -= 0.2;
				}
				else {
					timerFromDecX[i] = false;
				}
			}
			else if (timerFromIncX[i]) {
				int r = whichRock[i];
				if (cZombieZ[i] <= cRockZ[r] + 3) {
					cZombieZ[i] += 0.2;
				}
				else if (cZombieX[i] <= cRockX[r] + 3) {
					cZombieX[i] += 0.2;
				}
				else {
					timerFromIncX[i] = false;
				}
			}
			else if (timerFromDecZ[i]) {
				int r = whichRock[i];
				if (cZombieX[i] <= cRockX[r] + 3) {
					cZombieX[i] += 0.2;
				}
				else if (cZombieZ[i] >= cRockZ[r] - 3) {
					cZombieZ[i] -= 0.2;
				}
				else {
					timerFromDecZ[i] = false;
				}
			}
			else if (timerFromIncZ[i]) {
				int r = whichRock[i];
				if (cZombieX[i] <= cRockX[r] + 3) {
					cZombieX[i] += 0.2;
				}
				else if (cZombieZ[i] <= cRockZ[r] + 3) {
					cZombieZ[i] += 0.2;
				}
				else {
					timerFromIncZ[i] = false;
				}
			}
			else {
				if (!zombieDied[i]) {
					if (cZombieX[i] > cWarriorX && !(fabs(cZombieX[i] - cWarriorX) <= 0.2)) {
						for (int j = i + 1;j < 7;j++) {
							if (j < 6) {
								if (!zombieDied[j]) {
									if (!((fabs(cZombieX[i] - 0.2 - cZombieX[j]) <= 0.5) && (fabs(cZombieZ[i] - cZombieZ[j]) <= 0.5))) {
										cZombieX[i] -= 0.2;
										for (int k = 0;k < 6;k++) {
											if (cZombieX[i] >= cRockX[k] - 3 && cZombieX[i] <= cRockX[k] + 3 && cZombieZ[i] >= cRockZ[k] - 3 && cZombieZ[i] <= cRockZ[k] + 3) {
												cZombieX[i] += 0.2;
												timerFromDecX[i] = true;
												whichRock[i] = k;
												break;
											}

										}
									}
								}
							}
							else {
								cZombieX[i] -= 0.2;
								for (int k = 0;k < 6;k++) {
									if (cZombieX[i] >= cRockX[k] - 3 && cZombieX[i] <= cRockX[k] + 3 && cZombieZ[i] >= cRockZ[k] - 3 && cZombieZ[i] <= cRockZ[k] + 3) {
										cZombieX[i] += 0.2;
										timerFromDecX[i] = true;
										whichRock[i] = k;
										break;
									}

								}
							}
						}

					}
					else if (cZombieX[i] <= cWarriorX && !(fabs(cZombieX[i] - cWarriorX) <= 0.2)) {
						for (int j = i + 1;j < 7;j++) {
							if (j < 6) {
								if (!zombieDied[j]) {
									if (!((fabs(cZombieX[i] + 0.2 - cZombieX[j]) <= 0.5) && (fabs(cZombieZ[i] - cZombieZ[j]) <= 0.5))) {
										cZombieX[i] += 0.2;
										for (int k = 0;k < 6;k++) {
											if (cZombieX[i] >= cRockX[k] - 3 && cZombieX[i] <= cRockX[k] + 3 && cZombieZ[i] >= cRockZ[k] - 3 && cZombieZ[i] <= cRockZ[k] + 3) {
												cZombieX[i] -= 0.2;
												timerFromIncX[i] = true;
												whichRock[i] = k;
												break;
											}

										}
									}
								}
							}
							else {
								cZombieX[i] += 0.2;
								for (int k = 0;k < 6;k++) {
									if (cZombieX[i] >= cRockX[k] - 3 && cZombieX[i] <= cRockX[k] + 3 && cZombieZ[i] >= cRockZ[k] - 3 && cZombieZ[i] <= cRockZ[k] + 3) {
										cZombieX[i] -= 0.2;
										timerFromIncX[i] = true;
										whichRock[i] = k;
									}

								}
							}
						}
					}
					if (cZombieZ[i] > cWarriorZ && !(fabs(cZombieZ[i] - cWarriorZ) <= 0.2)) {
						for (int j = i + 1;j < 7;j++) {
							if (j < 6) {
								if (!zombieDied[j]) {
									if (!((fabs(cZombieZ[i] - 0.2 - cZombieZ[j]) <= 0.5) && (fabs(cZombieX[i] - cZombieX[j]) <= 0.5))) {
										cZombieZ[i] -= 0.2;
										for (int k = 0;k < 6;k++) {
											if (cZombieX[i] >= cRockX[k] - 3 && cZombieX[i] <= cRockX[k] + 3 && cZombieZ[i] >= cRockZ[k] - 3 && cZombieZ[i] <= cRockZ[k] + 3) {
												cZombieZ[i] += 0.2;
												timerFromDecZ[i] = true;
												whichRock[i] = k;
												break;
											}
										}
									}
								}
							}
							else {
								cZombieZ[i] -= 0.2;
								for (int k = 0;k < 6;k++) {
									if (cZombieX[i] >= cRockX[k] - 3 && cZombieX[i] <= cRockX[k] + 3 && cZombieZ[i] >= cRockZ[k] - 3 && cZombieZ[i] <= cRockZ[k] + 3) {
										cZombieZ[i] += 0.2;
										timerFromDecZ[i] = true;
										whichRock[i] = k;
										break;
									}
								}
							}
						}
					}
					else if (cZombieZ[i] <= cWarriorZ && !(fabs(cZombieZ[i] - cWarriorZ) <= 0.2)) {
						for (int j = i + 1;j < 7;j++) {
							if (j < 6) {
								if (!zombieDied[j]) {
									if (!((fabs(cZombieZ[i] + 0.2 - cZombieZ[j]) <= 0.5) && (fabs(cZombieX[i] - cZombieX[j]) <= 0.5))) {
										cZombieZ[i] += 0.2;
										for (int k = 0;k < 6;k++) {
											if (cZombieX[i] >= cRockX[k] - 3 && cZombieX[i] <= cRockX[k] + 3 && cZombieZ[i] >= cRockZ[k] - 3 && cZombieZ[i] <= cRockZ[k] + 3) {
												cZombieZ[i] -= 0.2;
												timerFromIncZ[i] = true;
												whichRock[i] = k;
												break;
											}
										}
									}
								}
							}
							else {
								cZombieZ[i] += 0.2;
								for (int k = 0;k < 6;k++) {
									if (cZombieX[i] >= cRockX[k] - 3 && cZombieX[i] <= cRockX[k] + 3 && cZombieZ[i] >= cRockZ[k] - 3 && cZombieZ[i] <= cRockZ[k] + 3) {
										cZombieZ[i] -= 0.2;
										timerFromIncZ[i] = true;
										whichRock[i] = k;
										break;
									}
								}
							}
						}
					}
				}
			}
		}
	}
	/*for (int i = 0;i < 6;i++) {
		for (int j = i + 1;j < 6;j++) {
			if ((fabs(cZombieX[i] - cZombieX[j]) <= 0.2) && (fabs(cZombieX[i] - cZombieX[j]))
		}
	}*/

	glutPostRedisplay();
	glutTimerFunc(350, zombieGetCloser, 0);
}

void sound(int val) {
	int i = 0;
	while(i<6) {
		if (damageSoundOnlyOnce[i] == true) {
			SoundEngine->play2D("audio/damaged.mp3", false);
			break;
		}
		i++;
	}

	while (i < 6) {
		if (damageSoundOnlyOnce[i] == true) {
			lives--;
		}
		i++;
	}

	//glutPostRedisplay();
	glutTimerFunc(2000, sound, 0);
}



//=======================================================================
// Main Function
//=======================================================================
void main(int argc, char** argv)
{
	SoundEngine->play2D("audio/Game_theme.mp3", true);

	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	glutInitWindowSize(WIDTH, HEIGHT);

	glutInitWindowPosition(0, 0);

	glutCreateWindow(title);

	glutDisplayFunc(myDisplay);

	glutKeyboardFunc(myKeyboard);


	glutMotionFunc(myMotion);

	glutPassiveMotionFunc(passM);

	glutMouseFunc(myMouse);

	glutSpecialFunc(Special);

	glutReshapeFunc(myReshape);

	myInit();

	glutTimerFunc(0, shootTimer, 0);
	glutTimerFunc(0, shootRotation, 0);
	glutTimerFunc(0, zombieGetCloser, 0);
	glutTimerFunc(0, sound, 0);


	LoadAssets();
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);

	glShadeModel(GL_SMOOTH);

	glutMainLoop();
}