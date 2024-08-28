#include <GL/glut.h>
#include <iostream>
#include "texturas/RgbImage.h"

using namespace std;



float camaraX = 0;
float camaraY = 32;
float camaraZ = 135;


/*float camaraX = -20;
float camaraY = 15;
float camaraZ = 30;*/



float posLuzX = 0;
//float posLuzY = 70;
float posLuzY = 70;
//sugerencia SUBIR Z a 70
float posLuzZ = 0;

float angulo = 0;

GLuint texture[8];

float centroX = 0;
float centroZ = 0;
//float movimientoCamara = 2.5;
float movimientoCamara = 1.5;
/*****************VARIABLES DE ANIMACION*****************/
float velocidadMovimiento = 0.9;


float anguloPierna1 = 0;
float ladoPierna1 = 2.5;

float anguloPierna2 = 0;
float ladoPierna2 = -2.5;

float anguloBrazo1 = 0;
float ladoBrazo1 = 1;

float anguloBrazo2 = 0;
float ladoBrazo2 = -1;

//float desplazamiento = -50;
float desplazamiento = 0;


/*************************************************************************/


void loadTextureFromFile(const char* filename, int index) {//metodo para cargar imagenes
	RgbImage theTexMap(filename);
	glGenTextures(1, &texture[index]);
	glBindTexture(GL_TEXTURE_2D, texture[index]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, theTexMap.GetNumCols(), theTexMap.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE, theTexMap.ImageData());
}

void cargarImagenes() {
	loadTextureFromFile("texturas/marmolBMP.bmp",0);
	loadTextureFromFile("texturas/piso_.bmp", 1);
	loadTextureFromFile("texturas/piso_templo.bmp", 2);
	loadTextureFromFile("texturas/pared.bmp", 3);
	loadTextureFromFile("texturas/columna.bmp", 4);
	loadTextureFromFile("texturas/symbol.bmp", 5);
	loadTextureFromFile("texturas/puerta.bmp", 6);
	loadTextureFromFile("texturas/patio.bmp", 7);
}

void iniciarVentana(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);//modo
	glLoadIdentity();
	//gluPerspective(90, (float)w / (float)h, 1, 200);//perspectiva
	gluPerspective(100, (float)w / (float)h, 1, 800);//perspectiva	
}


void inicializarLuces() {

	GLfloat light_ambient[] = { 0.1,0.1,0.1,1 };
	//GLfloat light_diffuse[] = { 0.5,0.5,0.5,1 };
	GLfloat light_diffuse[] = { 0.2,0.2,0.2,1 };
	GLfloat light_specular[] = { 0.2,0.2,0.2,1 };

	float reflejo[] = { 0,0,0,1 };
	float posicionLuz[] = { posLuzX,posLuzY,posLuzZ,1 };
	int sombra = 128;

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);


	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glMaterialfv(GL_FRONT, GL_SPECULAR, reflejo);
	glMateriali(GL_FRONT, GL_SHININESS, sombra);
	glLightfv(GL_LIGHT0, GL_POSITION, posicionLuz);

	//Luces Piso
	GLfloat light_ambient1[] = { 0.1,0.1,0.1,1 };
	GLfloat light_diffuse1[] = { 0.4,0.4,0.4,1 };
	GLfloat light_specular1[] = { 0.3,0.3,0.3,1 };
	/*float posicionLuz1[] = {-50,0,0,1};
	float posicionLuz2[] = { 0,0,50,1 };
	float posicionLuz3[] = { 50,0,0,1 };
	float posicionLuz4[] = { 0,0,-50,1 };*/

	float posicionLuz1[] = { -599,1,0,1 };
	float posicionLuz2[] = { 0,1,599,1 };
	float posicionLuz3[] = { 599,1,0,1 };
	float posicionLuz4[] = { 0,1,-599,1 };

	glEnable(GL_LIGHT1);
	glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient1);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse1);
	glLightfv(GL_LIGHT1, GL_SPECULAR, light_specular1);
	glLightfv(GL_LIGHT1, GL_POSITION, posicionLuz1);

	glEnable(GL_LIGHT2);
	glLightfv(GL_LIGHT2, GL_AMBIENT, light_ambient1);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, light_diffuse1);
	glLightfv(GL_LIGHT2, GL_SPECULAR, light_specular1);
	glLightfv(GL_LIGHT2, GL_POSITION, posicionLuz2);

	glEnable(GL_LIGHT3);
	glLightfv(GL_LIGHT3, GL_AMBIENT, light_ambient1);
	glLightfv(GL_LIGHT3, GL_DIFFUSE, light_diffuse1);
	glLightfv(GL_LIGHT3, GL_SPECULAR, light_specular1);
	glLightfv(GL_LIGHT3, GL_POSITION, posicionLuz3);

	glEnable(GL_LIGHT4);
	glLightfv(GL_LIGHT4, GL_AMBIENT, light_ambient1);
	glLightfv(GL_LIGHT4, GL_DIFFUSE, light_diffuse1);
	glLightfv(GL_LIGHT4, GL_SPECULAR, light_specular1);
	glLightfv(GL_LIGHT4, GL_POSITION, posicionLuz4);
}


void dibujarEjes() {
	glLineWidth(5);
	glBegin(GL_LINES);
	glColor3ub(255, 0, 0);
	glVertex3d(0, 0, 0);
	glVertex3d(100, 0, 0);

	glColor3ub(0, 255, 0);
	glVertex3d(0, 0, 0);
	glVertex3d(0, 100, 0);

	glColor3ub(0, 0, 255);
	glVertex3d(0, 0, 0);
	glVertex3d(0, 0, 100);
	glEnd();
}

void piso() {
	glPushMatrix();
	glTranslated(0, -2, 0);
	glScaled(340, 1, 340);
	//glScaled(90,1,90);
	//glColor3ub(180, 180, 180);
	//46 121 165
	glColor3ub(128, 128, 128);
	//glColor3ub(46, 121, 165);
	glutSolidCube(2);
	glPopMatrix();
}
/*
/*COLORES*/
void color_0_interno_dorado() {
	glColor3ub(101, 83, 0);
}

void color_1() {
	glColor3ub(160, 141, 32);
}
void color_2() {
	glColor3ub(132, 116, 26);
}
void color_3() {
	glColor3ub(245, 151, 22);
}

void color_0_piel_clara() {
	glColor3ub(208, 160, 95);
}

void color_pelo() {
	glColor3ub(143, 121, 45);
}

void color_shiryu1() {
	glColor3ub(7,93,104);
}

void colorTrianguloTemplo(){
	glColor3ub(199,178,157);
}

/*EXTREMIDADES INFERIORES*/
void zapato() {
	//tacon
	glPushMatrix();
	color_2();
	glTranslated(0, 0, 0.15);
	//glColor3ub(0, 128, 128);
	//color_1();
	//glRotated(-90, 1, 0, 0);
	glScaled(0.85, 1, 1);
	glutSolidSphere(1, 10, 10);
	glPopMatrix();
	//parte arriba zapato
	glPushMatrix();
	color_2();
	glTranslated(0, 0, 1);
	glScaled(0.5, 0.5, 1.2);
	glutSolidDodecahedron();
	glPopMatrix();
	//suela		
	glPushMatrix();
	color_2();
	glTranslated(0, -0.5, 1);
	glRotated(-90, 1, 0, 0);
	glScaled(0.5, 1.5, 2.75);
	glutSolidTorus(0.2, 1, 20, 20);
	glPopMatrix();
}

void rodilla_pierna() {
	//despues de rodilla
	glPushMatrix();
	//glColor3ub(0, 128, 128);
	color_1();
	glTranslated(0, 3, 0);
	glRotated(90, 1, 0, 0);
	gluCylinder(gluNewQuadric(), 0.65, 0.72, 3, 20, 20);
	glPopMatrix();
	/*glPushMatrix();
		//glColor3ub(0, 128, 128);
		color_1();
		glTranslated(0, 7.65, 0);
		glRotated(-90, 1, 0, 0);
		gluDisk(gluNewQuadric(), 0, 1.13, 20, 20);
	glPopMatrix();*/
	//detalles ************************************************
	// rodilla
	glPushMatrix();
	color_2();
	glTranslated(0, 7.65, 0);
	//glScaled(0.80,1,0.5);
	glutSolidSphere(0.90, 20, 20);
	glPopMatrix();
	glPushMatrix();
	color_2();
	glTranslated(0, 7.65, 1);
	glScaled(0.80, 1, 0.5);
	glutSolidSphere(1, 20, 20);
	glPopMatrix();
	glPushMatrix();
	glColor3ub(0, 128, 128);
	color_2();
	glTranslated(0, 7, 1);
	glScaled(0.80, 1, 0.5);
	glutSolidSphere(1, 20, 20);
	glPopMatrix();
	//dejado de rodilla supuesto musculo
	glPushMatrix();
	color_1();
	glTranslated(0, 5, 0);
	glScaled(.8, 2.2, 0.89);
	glutSolidSphere(1.25, 20, 20);
	glPopMatrix();
	//detalle alto relieve 1
	glPushMatrix();
	//glColor3ub(0, 128, 128);	
	color_1();
	glTranslated(0, 4.5, 1.1);
	glRotated(-90, 1, 0, 0);
	glScaled(1, 0.5, 1);
	//glutSolidCube(1);
	glutSolidCone(0.5, 2, 5, 5);
	glPopMatrix();
	glPushMatrix();
	//glColor3ub(0, 128, 128);	
	color_1();
	glTranslated(0, 4.55, 1.1);
	glRotated(100, 1, 0, 0);
	glScaled(1, 0.5, 1);
	//glutSolidCube(1);
	glutSolidCone(0.5, 1, 5, 5);
	glPopMatrix();
	//detalle alto relieve 2
	glPushMatrix();
	//glColor3ub(0, 128, 128);	
	color_1();
	glTranslated(0, 4.5, -1.1);
	glRotated(-87, 1, 0, 0);
	glScaled(1, 0.5, 1);
	//glutSolidCube(1);
	glutSolidCone(0.5, 2, 5, 5);
	glPopMatrix();
	glPushMatrix();
	//glColor3ub(0, 128, 128);	
	color_1();
	glTranslated(0, 4.55, -1.1);
	glRotated(80, 1, 0, 0);
	glScaled(1, 0.5, 1);
	//glutSolidCube(1);
	glutSolidCone(0.5, 1, 5, 5);
	glPopMatrix();
}

void falda() {
	//cubo finta
	glPushMatrix();
	color_1();
	//color_0_interno_dorado();
	glTranslated(0, 13.3, 0);
	glScaled(0.95, 1, 0.95);
	glutSolidCube(2);
	glPopMatrix();

}

void muslo() {
	//silueta guia
	/*glPushMatrix();
		glColor3ub(0, 128, 128);
		glTranslated(0, 7, 0);
		glRotated(-90, 1, 0, 0);
		gluCylinder(gluNewQuadric(), 0.5, 0.5, 7.22,20,20);
	glPopMatrix();*/
	//parte interna con músculo
	glPushMatrix();
	glColor3ub(106, 35, 53);
	glTranslated(0, 10.5, 0);
	glScaled(1, 3.8, 1);
	gluSphere(gluNewQuadric(), 1.0, 20, 20);
	glPopMatrix();
	//adorno arriba de rodilla
	glPushMatrix();
	color_2();
	glTranslated(0, 8, 0);
	glRotated(-90, 1, 0, 0);
	gluCylinder(gluNewQuadric(), 0.95, 1.1, 1.7, 10, 10);
	glPopMatrix();
	glPushMatrix();
	//glColor3ub(0, 128, 128);
	color_2();
	glTranslated(0, 9.8, 1);
	glRotated(180, 1, 0, 0);
	glutSolidCone(0.7, 0.9, 20, 20);
	glPopMatrix();
	glPushMatrix();
	color_1();
	glTranslated(0, 9.8, 0.8);
	glScaled(0.5, 0.5, 0.5);
	glutSolidSphere(1, 20, 20);
	glPopMatrix();
	/************************************/
	falda();
}


void pierna_Completa() {
	glPushMatrix();
		muslo();
		rodilla_pierna();
		zapato();
	glPopMatrix();
}



/************* TRONCO **************/

void placa_plana() {
	glPushMatrix();
	color_0_interno_dorado();
	glScaled(0.5, 2.5, 1.5);
	glutSolidCube(1);
	glPopMatrix();
}


/**************BRAZO******************/

void brazo(float posX) {
	//hombrera
	glPushMatrix();
	color_0_interno_dorado();
	glTranslated(posX, 20, 0);
	glutSolidSphere(1, 20, 20);
	glPopMatrix();
	//carne
	glPushMatrix();
	color_0_piel_clara();
	glTranslated(posX, 14.9, 0);
	glRotated(-90, 1, 0, 0);
	gluCylinder(gluNewQuadric(), 0.65, 0.8, 4.45, 20, 20);
	glPopMatrix();
	//codo
	glPushMatrix();
	color_0_interno_dorado();
	glTranslated(posX, 15.3, 0);
	glutSolidSphere(0.77, 20, 20);
	glPopMatrix();
	//adorno
	glPushMatrix();
	color_1();
	glTranslated(posX, 14.9, 0);
	glRotated(-90, 1, 0, 0);
	gluCylinder(gluNewQuadric(), 0.65, 0.8, 3.2, 20, 20);
	glPopMatrix();
	//musculo
	glPushMatrix();
	//glColor3ub(255, 0, 0);
	color_1();
	glTranslated(posX, 17.5, 0.15);
	glScaled(0.8, 1.25, 1);
	glutSolidSphere(1, 20, 20);
	glPopMatrix();
}

void detalle_antebrazo(float posX, float ang) {
	//detalle por sacar braz izq
	glPushMatrix();
	//glColor3ub(255, 0, 0);
	color_1();
	glTranslated(posX, 14.6, 0);
	glRotated(ang, 0, 0, 1);
	glScaled(0.5, 2, 0.6);
	glutSolidIcosahedron();
	glPopMatrix();
}

void mano(float posX) {
	//palma
	glPushMatrix();
	//glColor3ub(255, 0, 0);
	color_2();
	glTranslated(posX, 12.5, 0);
	glutSolidSphere(0.55, 20, 20);
	glPopMatrix();
	glPushMatrix();
	//glColor3ub(255, 0, 0);
	color_2();
	glTranslated(posX, 12.35, 0);
	glutSolidSphere(0.55, 20, 20);
	glPopMatrix();
	//dedos
	glPushMatrix();
	color_0_piel_clara();
	glTranslated(posX, 12.5, 0);
	glRotated(90, 1, 0, 0);
	glScaled(0.5, 1, 1);
	gluCylinder(gluNewQuadric(), 0.5, 0.5, 1, 10, 10);
	glPopMatrix();
}

void antebrazo(float posX) {
	//parte recta
	glPushMatrix();
	color_1();
	glTranslated(posX, 12.6, 0);
	glRotated(-90, 1, 0, 0);
	gluCylinder(gluNewQuadric(), 0.5, 0.65, 2.5, 20, 20);
	glPopMatrix();
	//musculo
	glPushMatrix();
	//glColor3ub(255, 0, 0);
	glTranslated(posX, 14, 0);
	glScaled(0.8, 1.25, 0.9);
	glutSolidSphere(0.8, 20, 20);
	glPopMatrix();
	//musculo
	glPushMatrix();
	//glColor3ub(255, 0, 0);
	glTranslated(posX, 14.9, 0);
	glScaled(0.8, 1.25, 0.9);
	glutSolidSphere(0.9, 20, 20);
	glPopMatrix();
}

void brazoCompletoIzq() {
	glPushMatrix();
	glTranslated(14.5, 3.5, 0);
	glRotated(42.5, 0, 0, 1);
	brazo(3.2);
	antebrazo(3.2);
	mano(3.2);
	detalle_antebrazo(3.7, -14);
	glPopMatrix();
}

void brazoCompletoDer() {
	glPushMatrix();
	glTranslated(-14.5, 3.5, 0);
	glRotated(-42.5, 0, 0, 1);
	brazo(-3.2);
	antebrazo(-3.2);
	mano(-3.2);
	detalle_antebrazo(-3.7, 14);
	glPopMatrix();

}
void aros(float posY, float anchoX) {
	glPushMatrix();
	//glColor3ub(0, 128, 128);
	color_2();
	glTranslated(0, posY, 0);
	glRotated(-90, 1, 0, 0);
	glScaled(anchoX, 0.65, 0.52);
	glutSolidTorus(0.5, 1, 20, 20);
	glPopMatrix();
}


void tronco() {
	//guia
	glPushMatrix();
	//color_0_interno_dorado();		
	color_1();
	glTranslated(0, 14, 0);
	glRotated(-90, 1, 0, 0);
	glScaled(1.6, 1, 1);
	gluCylinder(gluNewQuadric(), 1, 1, 7.57, 20, 20);
	glPopMatrix();

	//tipo union correa
	glPushMatrix();
	//glColor3ub(0, 255, 0);
	color_0_interno_dorado();
	glTranslated(0, 14.95, 0);
	glRotated(-90, 1, 0, 0);
	glScaled(0.85, 0.59, 0.6);
	glutSolidTorus(1, 1.75, 10, 10);
	glPopMatrix();

	/*************************/
	glPushMatrix();
	//glColor3ub(255, 0, 0);
	color_0_interno_dorado();
	glTranslated(0, 15, 0);
	glRotated(-90, 1, 0, 0);
	glScaled(1.1, 0.59, 0.5);
	glutSolidCone(2, 6, 20, 20);
	glPopMatrix();
	glPushMatrix();
	color_2();
	glTranslated(0, 21.4, 0);
	glRotated(90, 1, 0, 0);
	glScaled(1.1, 0.5, 1);
	glutSolidCone(3.88, 5.2, 20, 20);
	glPopMatrix();
	//detalle
	glPushMatrix();
	color_2();
	glTranslated(0, 20, 1.2);
	glutSolidSphere(0.5, 10, 10);
	glPopMatrix();

	glPushMatrix();
	color_2();
	glTranslated(0, 21.5, 1.4);
	glRotated(90, 1, 0, 0);
	glScaled(1, 1, 1);
	glutSolidCone(1, 2, 10, 10);
	glPopMatrix();
	/*....aros*/
	glPushMatrix();
	aros(18.4, 1.7);
	aros(18.2, 1.7);
	aros(18.0, 1.6);
	aros(17.8, 1.6);
	aros(17.6, 1.5);
	aros(17.4, 1.5);
	aros(17.2, 1.4);
	aros(17.0, 1.4);
	aros(17.0, 1.4);
	aros(16.8, 1.3);
	aros(16.6, 1.3);
	aros(16.4, 1.2);
	aros(16.2, 1.2);
	aros(16.0, 1.1);
	aros(15.8, 1.1);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(226, 196, 108);
	//color_1();
	glTranslated(0, 15.6, 0.79);
	glScaled(1, 0.5, 0.5);
	glutSolidIcosahedron();
	glPopMatrix();

	glPushMatrix();
	glColor3ub(198, 103, 127);
	//color_1();
	glTranslated(0, 15.6, 0.74);
	//glScaled(1, 0.5, 0.5);
	gluSphere(gluNewQuadric(), 0.5, 20, 20);
	glPopMatrix();

	//triangulo
	glPushMatrix();
		color_0_interno_dorado();
		glBegin(GL_TRIANGLES);
		glVertex3d(-1.8, 15, 1);
		glVertex3d(1.8, 15, 1);
		glVertex3d(0, 12, 1);
		glEnd();
	glPopMatrix();
	glPushMatrix();
		color_0_interno_dorado();
		glBegin(GL_TRIANGLES);
		glVertex3d(-1.8, 15, -1);
		glVertex3d(1.8, 15, -1);
		glVertex3d(0, 12, -1);
	glEnd();
	glPopMatrix();

}

void cara_cuello() {
	//cuello
	glPushMatrix();
	color_0_piel_clara();
	glTranslated(0, 20.5, 0);
	glRotated(-90, 1, 0, 0);
	gluCylinder(gluNewQuadric(), 0.79, 0.79, 3.22, 20, 20);
	glPopMatrix();
	//cara
	glPushMatrix();
	color_0_piel_clara();
	glTranslated(0, 23.5, 0);
	glScaled(0.9, 1.2, 0.9);
	gluSphere(gluNewQuadric(), 1.24, 20, 20);
	glPopMatrix();
	//pelo
	glPushMatrix();
	//color_0_piel_clara();
	color_pelo();
	glTranslated(0, 23.55, 0);
	glScaled(0.9, 1.2, 0.9);
	gluSphere(gluNewQuadric(), 1.24, 20, 20);
	glPopMatrix();
	//menton
	glPushMatrix();
	color_0_piel_clara();
	glTranslated(0, 23.0, 0.25);
	glRotated(45, 1, 0, 0);
	glScaled(0.7, 0.5, 1);
	gluSphere(gluNewQuadric(), 1, 20, 20);
	glPopMatrix();
	//ojos
	/*glPushMatrix();
		glColor3ub(0, 0, 0);
		glTranslated(0.32, 23.7, 0.69);
		glRotated(-90, 1, 0, 0);
		glScaled(0.5, 0.5, 1);
		glutSolidCone(1, 0.5, 20, 20);
	glPopMatrix();
	glPushMatrix();
		glColor3ub(0, 0, 0);
		glTranslated(-0.32, 23.7, 0.69);
		glRotated(-90, 1, 0, 0);
		glScaled(0.5, 0.5, 1);
		glutSolidCone(1, 0.5, 20, 20);
	glPopMatrix();*/
	glPushMatrix();
	glColor3ub(0, 0, 0);
	glTranslated(-0.32, 23.45, 0.65);
	glRotated(-91, 1, 0, 0);
	glScaled(0.5, 0.5, 1);
	glutSolidCone(1, 0.5, 20, 20);
	glPopMatrix();
	glPushMatrix();
	glColor3ub(0, 0, 0);
	glTranslated(0.32, 23.45, 0.65);
	glRotated(-91, 1, 0, 0);
	glScaled(0.5, 0.5, 1);
	glutSolidCone(1, 0.5, 20, 20);
	glPopMatrix();

	//nariz
	/*glPushMatrix();
		color_0_piel_clara();
		glTranslated(0, 23.2, 0.80);
		glRotated(40, 1, 0, 0);
		glScaled(0.5, 0.7, 0.5);
		glutSolidOctahedron();
	glPopMatrix();*/

	//detallecasco
	glPushMatrix();
	//glColor3ub(0, 128, 128);
	color_1();
	glTranslated(0, 24.75, 0);
	glRotated(40, 1, 0, 0);
	glScaled(0.5, 1, 1);
	glutSolidIcosahedron();
	glPopMatrix();

	//detalle cuello
	glPushMatrix();
	color_2();
	glTranslated(0, 19.5, 0);
	glRotated(-90, 1, 0, 0);
	gluCylinder(gluNewQuadric(), 0.81, 0.81, 3.22, 20, 20);
	glPopMatrix();

	//detallecabeza
	glPushMatrix();
	//glColor3ub(0, 128, 128);
	color_1();
	glTranslated(0, 24.75, 1);
	glScaled(1, 0.8, 0.5);
	glutSolidIcosahedron();
	glPopMatrix();
	//cachos
	/*glPushMatrix();
		color_2();
		glColor3ub(255, 0, 0);
		glTranslated(0, 26.8, 1);
		glRotated(90, 1, 0, 0);
		//glRotated(45, 0, 1, 0);
		glScaled(0.5, 0.55, 0.5);
		glutSolidCone(1, 4, 20, 20);
	glPopMatrix();
	glPushMatrix();
		color_2();
		//glColor3ub(255, 0, 0);
		glTranslated(-2, 26.5, 1);
		glRotated(90, 1, 0, 0);
		glRotated(45, 0, 1, 0);
		//glRotated(45, 0, 1, 0);
		//glScaled(0.5, 0.5, 1);
		glutSolidCone(0.5, 2.5, 20, 20);
	glPopMatrix();
	glPushMatrix();
		//color_2();
		glColor3ub(255, 0, 0);
		glTranslated(-2, 27.5, 1);
		glRotated(-90, 1, 0, 0);
		glRotated(-25, 0, 1, 0);
		//glRotated(45, 0, 1, 0);
		//glScaled(0.5, 0.5, 1);
		glutSolidCone(0.5, 2.5, 20, 20);
	glPopMatrix();*/

	/*glPushMatrix();
		color_2();
		glTranslated(0, 27, 1);
		glScaled(0.5, 2, 0.5);
		glutSolidIcosahedron();
	glPopMatrix();*/

	glPushMatrix();
	color_2();
	glTranslated(1.1, 25, 1);
	glRotated(-45, 0, 0, 1);
	glScaled(0.5, 1, 0.5);
	glutSolidIcosahedron();
	glPopMatrix();

	glPushMatrix();
	color_2();
	glTranslated(-1.1, 25, 1);
	glRotated(45, 0, 0, 1);
	glScaled(0.5, 1, 0.5);
	glutSolidIcosahedron();
	glPopMatrix();
	glPushMatrix();
	color_2();
	glTranslated(1.6, 26.6, 1);
	glScaled(0.5, 1.5, 0.5);
	glutSolidIcosahedron();
	glPopMatrix();
	glPushMatrix();
	color_2();
	glTranslated(-1.6, 26.6, 1);
	glScaled(0.5, 1.5, 0.5);
	glutSolidIcosahedron();
	glPopMatrix();

	glPushMatrix();
	color_2();
	glTranslated(-0.7, 23.5, 0.4);
	glScaled(0.65, 1.5, 0.5);
	glutSolidIcosahedron();
	glPopMatrix();
	glPushMatrix();
	color_2();
	glTranslated(0.7, 23.5, 0.4);
	glScaled(0.65, 1.5, 0.5);
	glutSolidIcosahedron();
	glPopMatrix();
}

void cabeza() {
	cara_cuello();
}

void zapato_parado_der() {
	glPushMatrix();
	glTranslated(-3.5, 0, 0);
	zapato();
	glPopMatrix();
}
void zapato_parado_izq() {
	glPushMatrix();
	glTranslated(3.5, 0, 0);
	zapato();
	glPopMatrix();
}
void aro_arriba_pierna(float posX) {
	glPushMatrix();
	color_2();
	//color_0_interno_dorado();
	//glColor3ub(0, 128, 128);
	glTranslated(posX, 11, 0);
	glRotated(-90, 1, 0, 0);
	gluCylinder(gluNewQuadric(), 1.2, 1, 3.31, 20, 20);
	glPopMatrix();
}

void pierna_derecha_shura() {
	//derecha
	glPushMatrix();
		glTranslated(-3.5, 0.5, 0);
		glRotated(-11, 0, 0, 1);
		rodilla_pierna();
		muslo();
	glPopMatrix();
	
	//aros
	glPushMatrix();
		glRotated(-11, 0, 0, 1);
		aro_arriba_pierna(-4.2);
	glPopMatrix();

	zapato_parado_der();
}

void pierna_izquierda_shura() {	
	//izq
	glPushMatrix();
		glTranslated(3.5, 0.5, 0);
		glRotated(11, 0, 0, 1);
		rodilla_pierna();
		muslo();
	glPopMatrix();
	//aros
	glPushMatrix();
		glRotated(11, 0, 0, 1);
		aro_arriba_pierna(4.2);
	glPopMatrix();
	zapato_parado_izq();
}

void brazo_shura_final_derecho(){
	glPushMatrix();
		glTranslated(0, 20, 0);
		glRotated(-10, 1, 0, 0);
		glTranslated(0, -20, 0);
		brazoCompletoDer();
	glPopMatrix();	
}

void brazo_shura_final_derecho_f() {
	glPushMatrix();
		glTranslated(0, 20, 0);
		glRotated(10, 0, 0, 1);
		glTranslated(0, -20, 0);
		brazo_shura_final_derecho();
	glPopMatrix();	
}

void brazo_shura_final_izquierdo(){
	glPushMatrix();
		glTranslated(0, 20, 0);
		glRotated(-10, 1, 0, 0);
		glTranslated(0, -20, 0);
		brazoCompletoIzq();
	glPopMatrix();
}
void brazo_shura_final_izquierdo_f() {
	glPushMatrix();
		glTranslated(0, 20, 0);
		glRotated(-10, 0, 0, 1);
		glTranslated(0, -20, 0);
		brazo_shura_final_izquierdo();
	glPopMatrix();
}

void shura_parado(){
	glTranslated(0, 0, -10);
	glPushMatrix();
		/*anguloPierna1 += (velocidadMovimiento * ladoPierna1);
		if (anguloPierna1 >= 20) {
			ladoPierna1 = -0.5;
		}
		if (anguloPierna1 <= -20) {
			ladoPierna1 = 0.5;
		}
		glTranslated(0, 14.5, 0);
		glRotated(anguloPierna1, 1, 0, 0);
		glTranslated(0, -14.5, 0);*/
		pierna_derecha_shura();
	glPopMatrix();

	glPushMatrix();
		/*anguloPierna2 += (velocidadMovimiento * ladoPierna2);
		if (anguloPierna2 <= -20) {
			ladoPierna2 = 0.5;
		}
		if (anguloPierna2 >= 20) {
			ladoPierna2 = -0.5;
		}
		glTranslated(0, 14.5, 0);
		glRotated(anguloPierna2, 1, 0, 0);
		glTranslated(0, -14.5, 0);*/
		pierna_izquierda_shura();
	glPopMatrix();
	
	glPushMatrix();
		/*anguloBrazo1 += (velocidadMovimiento * ladoBrazo1);
		if (anguloBrazo1 >= 10) {
			ladoBrazo1 = -0.5;
		}

		if (anguloBrazo1 <= -10) {
			ladoBrazo1 = 0.5;
		}
		glTranslated(0, 20, 0);
		glRotated(anguloBrazo1, 1, 0, 0);
		glTranslated(0, -20, 0);*/
		brazo_shura_final_izquierdo_f();
	glPopMatrix();

	glPushMatrix();
		/*anguloBrazo2 += (velocidadMovimiento * ladoBrazo2);
		if (anguloBrazo2 <= -160) {
			ladoBrazo2 = 0.85;
		}
		if (anguloBrazo2 >= 110) {
			ladoBrazo2 = -0.85;
		}
		glTranslated(0, 20, 0);
		glRotated(anguloBrazo2, 1, 0, 0);
		glTranslated(0, -20, 0);*/
		brazo_shura_final_derecho_f();
	glPopMatrix();
	
	tronco();
	cabeza();
	
}

/*******************************************************/

/*piernas Shiryu*/

void cabeza_shiryu() {
	//cara
	glPushMatrix();
		color_0_piel_clara();
		glTranslated(0, 22.9, 0.1);
		glScaled(0.8, 1.1, 0.9);
		gluSphere(gluNewQuadric(), 1.24, 20, 20);
	glPopMatrix();
	//cuello
	glPushMatrix();
		color_0_piel_clara();
		glTranslated(0, 19.5, 0.1);
		glRotated(-90, 1, 0, 0);
		gluCylinder(gluNewQuadric(), 0.79, 0.7, 3.22, 20, 20);
	glPopMatrix();
	//cabello
	glPushMatrix();	
		glColor3ub(0, 0, 0);
		glTranslated(0, 23.2, -0.3);		
		glScaled(1.31, 1, 1);
		glutSolidIcosahedron();
	glPopMatrix();
	glPushMatrix();	
		glColor3ub(0, 0, 0);
		glTranslated(0, 23.7, 0.1);		
		glScaled(1.29, 1, 1);
		glutSolidIcosahedron();
	glPopMatrix();
	glPushMatrix();	
		glColor3ub(0, 0, 0);
		glTranslated(0, 24, 0.4);		
		glScaled(1.10, 1, 1.4);
		glutSolidIcosahedron();
	glPopMatrix();
	//tirones cabello 
	glPushMatrix();
		//glColor3ub(255, 0, 0);
		glTranslated(0, 21, -1);
		glRotated(20, 1, 0, 0);
		glScaled(0.5, 5, 0.5);
		glutSolidCube(1);
	glPopMatrix();
	glPushMatrix();		
		glTranslated(0, 21.5, -1.2);
		glRotated(22, 1, 0, 0);
		glScaled(1.5, 5, 0.8);
		glutSolidCube(1);
	glPopMatrix();
	glPushMatrix();					
		glTranslated(-0.7, 21, -1);
		glRotated(20, 1, 0, 0);
		glScaled(1, 5, 0.5);
		glutSolidCube(1);
	glPopMatrix();
	glPushMatrix();			
		glTranslated(0.7, 21, -1);
		glRotated(20, 1, 0, 0);
		glScaled(1, 5, 0.5);
		glutSolidCube(1);
	glPopMatrix();
	//tirones laterales
	glPushMatrix();		
		glTranslated(-1, 23, 0);
		glRotated(20, 1, 0, 0);
		glScaled(0.5, 1.5, 0.5);
		glutSolidCube(1);
	glPopMatrix();
	glPushMatrix();		
		glTranslated(1, 23, 0);
		glRotated(20, 1, 0, 0);
		glScaled(0.5, 1.5, 0.5);
		glutSolidCube(1);
	glPopMatrix();
	//tirones inferiores
}

void brazo_Shiryu(float posX) {
	//hombrera
	glPushMatrix();
		color_0_piel_clara();
		glTranslated(posX, 19, 0);
		glutSolidSphere(1, 20, 20);
	glPopMatrix();
	//carne
	glPushMatrix();
		color_0_piel_clara();
		glTranslated(posX, 14.9, 0);
		glRotated(-90, 1, 0, 0);
		gluCylinder(gluNewQuadric(), 0.65, 0.8, 4.45, 20, 20);
	glPopMatrix();
	//codo
	glPushMatrix();
		color_0_piel_clara();
		glTranslated(posX, 15.3, 0);
		glutSolidSphere(0.77, 20, 20);
	glPopMatrix();
	//adorno
	glPushMatrix();
		color_shiryu1();
		glTranslated(posX, 14.9, 0);
		glRotated(-90, 1, 0, 0);
		gluCylinder(gluNewQuadric(), 0.65, 0.8, 3.2, 20, 20);
	glPopMatrix();
	//musculo
	glPushMatrix();
		//glColor3ub(255, 0, 0);
		color_shiryu1();
		glTranslated(posX, 17.5, 0.15);
		glScaled(0.8, 1.25, 1);
		glutSolidSphere(1, 20, 20);
	glPopMatrix();
}

void antebrazo_Shiryu(float posX) {
	//parte recta
	glPushMatrix();
		color_shiryu1();
		glTranslated(posX, 12.6, 0);
		glRotated(-90, 1, 0, 0);
		gluCylinder(gluNewQuadric(), 0.5, 0.65, 2.5, 20, 20);
	glPopMatrix();
	//musculo
	glPushMatrix();		
		glTranslated(posX, 14, 0);
		glScaled(0.8, 1.25, 0.9);
		glutSolidSphere(0.8, 20, 20);
	glPopMatrix();
	//musculo
	glPushMatrix();	
		glTranslated(posX, 14.9, 0);
		glScaled(0.8, 1.25, 0.9);
		glutSolidSphere(0.9, 20, 20);
	glPopMatrix();
}

void mano_Shiryu(float posX) {
	//palma
	glPushMatrix();
	//glColor3ub(255, 0, 0);
		color_0_piel_clara();
		glTranslated(posX, 12.5, 0);
		glutSolidSphere(0.55, 20, 20);
	glPopMatrix();
	glPushMatrix();
		//glColor3ub(255, 0, 0);
		color_shiryu1();
		glTranslated(posX, 12.35, 0);
		glutSolidSphere(0.55, 20, 20);
	glPopMatrix();
	//dedos
	glPushMatrix();
		color_shiryu1();
		glTranslated(posX, 12.5, 0);
		glRotated(90, 1, 0, 0);
		glScaled(0.5, 1, 1);
		gluCylinder(gluNewQuadric(), 0.5, 0.5, 1, 10, 10);
	glPopMatrix();
}

void brazoCompletoIzq_Shiryu() {
	glPushMatrix();
			glTranslated(13.5, 3.5, 0);
			glRotated(42.5, 0, 0, 1);
			brazo_Shiryu(3.2);
			antebrazo_Shiryu(3.2);
			mano_Shiryu(3.2);
			//detalle_antebrazo(3.7, -14);
	glPopMatrix();
}

void brazoCompletoDer_Shiryu() {
	glPushMatrix();
			glTranslated(-13.5, 3.5, 0);
			glRotated(-42.5, 0, 0, 1);
			brazo_Shiryu(-3.2);
			antebrazo_Shiryu(-3.2);
			mano_Shiryu(-3.2);
			//detalle_antebrazo(-3.7, 14);
	glPopMatrix();
}


void aro_arriba_pierna_Shiryu(float posX) {
	glPushMatrix();
		color_shiryu1();
		//color_0_interno_dorado();
		//glColor3ub(0, 128, 128);
		glTranslated(posX, 11, 0);
		glRotated(-90, 1, 0, 0);
		gluCylinder(gluNewQuadric(), 1.2, 1, 3.31, 20, 20);
	glPopMatrix();
}
void zapatoShiryu() {
	//tacon
	glPushMatrix();
	color_shiryu1();
	glTranslated(0, 0, 0.15);
	//glColor3ub(0, 128, 128);
	//color_1();
	//glRotated(-90, 1, 0, 0);
	glScaled(0.85, 1, 1);
	glutSolidSphere(1, 10, 10);
	glPopMatrix();
	//parte arriba zapato
	glPushMatrix();
	color_shiryu1();
	glTranslated(0, 0, 1);
	glScaled(0.5, 0.5, 1.2);
	glutSolidDodecahedron();
	glPopMatrix();
	//suela		
	glPushMatrix();
	color_shiryu1();
	glTranslated(0, -0.5, 1);
	glRotated(-90, 1, 0, 0);
	glScaled(0.5, 1.5, 2.75);
	glutSolidTorus(0.2, 1, 20, 20);
	glPopMatrix();
}
void rodilla_pierna_Shiryu() {
	//despues de rodilla
	glPushMatrix();
	color_shiryu1();
	glTranslated(0, 3, 0);
	glRotated(90, 1, 0, 0);
	gluCylinder(gluNewQuadric(), 0.65, 0.72, 3, 20, 20);
	glPopMatrix();
	//detalles ************************************************
	// rodilla
	glPushMatrix();
	color_shiryu1();
	glTranslated(0, 7.65, 0);
	//glScaled(0.80,1,0.5);
	glutSolidSphere(0.90, 20, 20);
	glPopMatrix();
	glPushMatrix();
	color_shiryu1();
	glTranslated(0, 7.65, 1);
	glScaled(0.80, 1, 0.5);
	glutSolidSphere(1, 20, 20);
	glPopMatrix();
	glPushMatrix();
	color_shiryu1();
	glTranslated(0, 7, 1);
	glScaled(0.80, 1, 0.5);
	glutSolidSphere(1, 20, 20);
	glPopMatrix();
	//dejado de rodilla supuesto musculo
	glPushMatrix();
	color_shiryu1();
	glTranslated(0, 5, 0);
	glScaled(.8, 2.2, 0.89);
	glutSolidSphere(1.25, 20, 20);
	glPopMatrix();
	//detalle alto relieve 1
	glPushMatrix();
	//glColor3ub(0, 128, 128);	
	color_shiryu1();
	glTranslated(0, 4.5, 1.1);
	glRotated(-90, 1, 0, 0);
	glScaled(1, 0.5, 1);
	//glutSolidCube(1);
	glutSolidCone(0.5, 2, 5, 5);
	glPopMatrix();
	glPushMatrix();
	//glColor3ub(0, 128, 128);	
	color_shiryu1();
	glTranslated(0, 4.55, 1.1);
	glRotated(100, 1, 0, 0);
	glScaled(1, 0.5, 1);
	//glutSolidCube(1);
	glutSolidCone(0.5, 1, 5, 5);
	glPopMatrix();
	//detalle alto relieve 2
	glPushMatrix();
	//glColor3ub(0, 128, 128);	
	color_shiryu1();
	glTranslated(0, 4.5, -1.1);
	glRotated(-87, 1, 0, 0);
	glScaled(1, 0.5, 1);
	//glutSolidCube(1);
	glutSolidCone(0.5, 2, 5, 5);
	glPopMatrix();
	glPushMatrix();
	//glColor3ub(0, 128, 128);	
	color_shiryu1();
	glTranslated(0, 4.55, -1.1);
	glRotated(80, 1, 0, 0);
	glScaled(1, 0.5, 1);
	//glutSolidCube(1);
	glutSolidCone(0.5, 1, 5, 5);
	glPopMatrix();
}
void falda_Shiryu() {
	//cubo finta
	glPushMatrix();
		color_shiryu1();
		//color_0_interno_dorado();
		glTranslated(0, 13.3, 0);
		glScaled(1.15, 1.5, 1.2);
		glutSolidCube(2);
	glPopMatrix();
}
void musloShiryu() {
	//silueta guia
	/*glPushMatrix();
		glColor3ub(0, 128, 128);
		glTranslated(0, 7, 0);
		glRotated(-90, 1, 0, 0);
		gluCylinder(gluNewQuadric(), 0.5, 0.5, 7.22,20,20);
	glPopMatrix();*/
	//parte interna con músculo
	glPushMatrix();
		glColor3ub(0, 0, 0);
		glTranslated(0, 10.5, 0);
		glScaled(1, 3.8, 1);
		gluSphere(gluNewQuadric(), 1.0, 20, 20);
	glPopMatrix();
	//adorno arriba de rodilla
	glPushMatrix();
		color_shiryu1();
		glTranslated(0, 8, 0);
		glRotated(-90, 1, 0, 0);
		gluCylinder(gluNewQuadric(), 0.95, 1.1, 1.7, 10, 10);
	glPopMatrix();
	glPushMatrix();
	//glColor3ub(0, 128, 128);
		color_shiryu1();
		glTranslated(0, 9.8, 1);
		glRotated(180, 1, 0, 0);
		glutSolidCone(0.7, 0.9, 20, 20);
	glPopMatrix();
	/*glPushMatrix();
		color_shiryu1();
		glTranslated(0, 9.8, 0.8);
		glScaled(0.5, 0.5, 0.5);
		glutSolidSphere(1, 20, 20);
	glPopMatrix();*/
	/************************************/
	falda_Shiryu();
}

void piernasShiryu() { // igual a pierna completa
	zapatoShiryu();
	rodilla_pierna_Shiryu();
	musloShiryu();
}

void zapato_parado_der_Shiryu() {
	glPushMatrix();
		glTranslated(-3.5, 0, 0);
		zapatoShiryu();
	glPopMatrix();
}
void zapato_parado_izq_Shiryu() {
	glPushMatrix();
		glTranslated(3.5, 0, 0);
		zapatoShiryu();
	glPopMatrix();
}

/***********************************************/

void piernas_paradas_Shyriu() {
	//derecha
	glPushMatrix();
		glTranslated(-3.5, 0.5, 0);
		glRotated(-11, 0, 0, 1);
		rodilla_pierna_Shiryu();
		musloShiryu();
	glPopMatrix();
	//izq
	glPushMatrix();
		glTranslated(3.5, 0.5, 0);
		glRotated(11, 0, 0, 1);
		rodilla_pierna_Shiryu();
		musloShiryu();
	glPopMatrix();
	//aros falda
	glPushMatrix();
		glRotated(-11, 0, 0, 1);
		aro_arriba_pierna_Shiryu(-4.2);
	glPopMatrix();
	glPushMatrix();
		glRotated(11, 0, 0, 1);
		aro_arriba_pierna_Shiryu(4.2);
		glPopMatrix();
	//triangulo
	glPushMatrix();
		color_shiryu1();
		glBegin(GL_TRIANGLES);
			glVertex3d(-1.8, 15, 1);
			glVertex3d(1.8, 15, 1);
			glVertex3d(0, 12, 1);
		glEnd();
	glPopMatrix();
	glPushMatrix();
		color_shiryu1();
		glBegin(GL_TRIANGLES);
			glVertex3d(-1.8, 15, -1);
			glVertex3d(1.8, 15, -1);
			glVertex3d(0, 12, -1);
		glEnd();
	glPopMatrix();
	//llAMANDO a ZAPATOS
	zapato_parado_der_Shiryu();
	zapato_parado_izq_Shiryu();
}

void tronco_Shiryu() {
	//tipo union correa
	glPushMatrix();
		//glColor3ub(0, 255, 0);
		color_shiryu1();
		glTranslated(0, 14.95, 0);
		glRotated(-90, 1, 0, 0);
		glScaled(0.85, 0.59, 0.99);
		glutSolidTorus(1, 1.75, 10, 10);
	glPopMatrix();
	

	//guia/*CUELLO*/
	glPushMatrix();
	//color_0_interno_dorado();		
		color_0_piel_clara();
		//glColor3ub(255, 0, 0);
		glTranslated(0, 15.5, 0);
		glRotated(-90, 1, 0, 0);
		glScaled(0.7, 1, 0.7);
		gluCylinder(gluNewQuadric(), 1, 1, 7.57, 20, 20);
	glPopMatrix();
	//bajo
	glPushMatrix();
		color_0_piel_clara();
		glTranslated(0, 17.5, 0);
		glScaled(1.3, 2.7, .9);
		glutSolidSphere(1.6, 20, 20);
	glPopMatrix();
	//medio
	glPushMatrix();
		color_0_piel_clara();
		glTranslated(0, 18.8, 0.2);
		glScaled(1.45, 0.9, 1);
		glutSolidSphere(1.6, 20, 20);
	glPopMatrix();
	//arriba
	glPushMatrix();
		color_0_piel_clara();
		glTranslated(0, 20, 0.2);
		glScaled(1.95, 0.9, 1);
		glutSolidSphere(1.6, 20, 20);
	glPopMatrix();
	

	/*************************/
	/*glPushMatrix();
	//glColor3ub(255, 0, 0);
		color_0_interno_dorado();
		glTranslated(0, 15, 0);
		glRotated(-90, 1, 0, 0);
		glScaled(1.1, 0.59, 0.5);
		glutSolidCone(2, 6, 20, 20);
	glPopMatrix();
	glPushMatrix();
		color_2();
		glTranslated(0, 21.4, 0);
		glRotated(90, 1, 0, 0);
		glScaled(1.1, 0.5, 1);
		glutSolidCone(3.88, 5.2, 20, 20);
	glPopMatrix();
	//detalle
	glPushMatrix();
		color_2();
		glTranslated(0, 20, 1.2);
		glutSolidSphere(0.5, 10, 10);
	glPopMatrix();

	glPushMatrix();
		color_2();
		glTranslated(0, 21.5, 1.4);
		glRotated(90, 1, 0, 0);
		glScaled(1, 1, 1);
		glutSolidCone(1, 2, 10, 10);
	glPopMatrix();*/
	/*....aros*/
	/*glPushMatrix();
		aros(18.4, 1.7);
		aros(18.2, 1.7);
		aros(18.0, 1.6);
		aros(17.8, 1.6);
		aros(17.6, 1.5);
		aros(17.4, 1.5);
		aros(17.2, 1.4);
		aros(17.0, 1.4);
		aros(17.0, 1.4);
		aros(16.8, 1.3);
		aros(16.6, 1.3);
		aros(16.4, 1.2);
		aros(16.2, 1.2);
		aros(16.0, 1.1);
		aros(15.8, 1.1);
	glPopMatrix();*/

	/*glPushMatrix();
		glColor3ub(226, 196, 108);
		//color_1();
		glTranslated(0, 15.6, 0.79);
		glScaled(1, 0.5, 0.5);
		glutSolidIcosahedron();
	glPopMatrix();

	glPushMatrix();
		glColor3ub(198, 103, 127);
		//color_1();
		glTranslated(0, 15.6, 0.74);
		//glScaled(1, 0.5, 0.5);
		gluSphere(gluNewQuadric(), 0.5, 20, 20);
	glPopMatrix();*/
}
/***shiryu**/

/* SHIRU ORIGINAL*/

/*void shiryu() {
	piernas_paradas_Shyriu();
	tronco_Shiryu();
	glPushMatrix();
		//glTranslated(0, 10, 0);
		//glRotated(-20, 0, 0, 1);
		//glTranslated(0, 10, 0);
		//brazoCompletoIzq_Shiryu();
		
		glPushMatrix();
			//glTranslated(13.5, 3.5, 0);
			//glRotated(42.5, 0, 0, 1);
			brazo_Shiryu(3.2);
			antebrazo_Shiryu(3.2);
			mano_Shiryu(3.2);			
		glPopMatrix();

		brazoCompletoDer_Shiryu();
	glPopMatrix();	
	
	cabeza_shiryu();
}*/


/*nuevo brazos completos*/
void brazo_Shiryu_izq() {
	glPushMatrix();
		glTranslated(13.3, 3.5, 0);
		glRotated(42.5, 0, 0, 1);
		brazo_Shiryu(3.2);
	glPopMatrix();	
}

void antebrazo_Shiryu_izq() {
	glPushMatrix();
		glTranslated(13.3, 3.5, 0);
		glRotated(42.5, 0, 0, 1);
		antebrazo_Shiryu(3.2);		
		mano_Shiryu(3.2);
	glPopMatrix();	
}

void brazo_Shiryu_der() {
	glPushMatrix();
		glTranslated(-13.3, 3.5, 0);
		glRotated(-42.5, 0, 0, 1);
		brazo_Shiryu(-3.2);
	glPopMatrix();	
}

void antebrazo_Shiryu_der() {
	glPushMatrix();
		glTranslated(-13.3, 3.5, 0);
		glRotated(-42.5, 0, 0, 1);	
		antebrazo_Shiryu(-3.2);		
		mano_Shiryu(-3.2);
	glPopMatrix();
	
}

void brazo_derecho_posicion_2() {
	glPushMatrix();
	brazo_Shiryu(8);
	antebrazo_Shiryu(8);
	mano_Shiryu;
	glPopMatrix();
}


/*nuevas piernas*/
void rodilla_pierna_Shiryu_() {
	//despues de rodilla
	glPushMatrix();
		color_shiryu1();
		glTranslated(0, 3, 0);
		glRotated(90, 1, 0, 0);
		gluCylinder(gluNewQuadric(), 0.65, 0.72, 3, 20, 20);
	glPopMatrix();
	//detalles ************************************************
	// rodilla
	glPushMatrix();
		color_shiryu1();
		glTranslated(0, 7.65, 0);
		//glScaled(0.80,1,0.5);
		glutSolidSphere(0.90, 20, 20);
	glPopMatrix();
		glPushMatrix();
		color_shiryu1();
		glTranslated(0, 7.65, 1);
		glScaled(0.80, 1, 0.5);
		glutSolidSphere(1, 20, 20);
	glPopMatrix();
	glPushMatrix();
		color_shiryu1();
		glTranslated(0, 7, 1);
		glScaled(0.80, 1, 0.5);
		glutSolidSphere(1, 20, 20);
	glPopMatrix();
	//dejado de rodilla supuesto musculo
	glPushMatrix();
		color_shiryu1();
		glTranslated(0, 5, 0);
		glScaled(.8, 2.2, 0.89);
		glutSolidSphere(1.25, 20, 20);
	glPopMatrix();
	//detalle alto relieve 1
	glPushMatrix();
	//glColor3ub(0, 128, 128);	
		color_shiryu1();
		glTranslated(0, 4.5, 1.1);
		glRotated(-90, 1, 0, 0);
		glScaled(1, 0.5, 1);
		//glutSolidCube(1);
		glutSolidCone(0.5, 2, 5, 5);
	glPopMatrix();
	glPushMatrix();
	//glColor3ub(0, 128, 128);	
		color_shiryu1();
		glTranslated(0, 4.55, 1.1);
		glRotated(100, 1, 0, 0);
		glScaled(1, 0.5, 1);
		//glutSolidCube(1);
		glutSolidCone(0.5, 1, 5, 5);
	glPopMatrix();
	//detalle alto relieve 2
	glPushMatrix();
	//glColor3ub(0, 128, 128);	
		color_shiryu1();
		glTranslated(0, 4.5, -1.1);
		glRotated(-87, 1, 0, 0);
		glScaled(1, 0.5, 1);
		//glutSolidCube(1);
		glutSolidCone(0.5, 2, 5, 5);
	glPopMatrix();
	glPushMatrix();
	//glColor3ub(0, 128, 128);	
		color_shiryu1();
		glTranslated(0, 4.55, -1.1);
		glRotated(80, 1, 0, 0);
		glScaled(1, 0.5, 1);
		//glutSolidCube(1);
		glutSolidCone(0.5, 1, 5, 5);
	glPopMatrix();
}

void parte_pierna_abajo_rodilla(float distX, float ang, float distXzapato) {
	glPushMatrix();
		glTranslated(distX, 0.5, 0);
		glRotated(ang, 0, 0, 1);		
		rodilla_pierna_Shiryu_();
	glPopMatrix();
	glPushMatrix();
		glTranslated(distXzapato, 0, 0);
		zapato_parado_izq_Shiryu();
	glPopMatrix();
}

void muslo_rodilla_Shiryu_real(float ang, float distX){
	glPushMatrix();
		glTranslated(distX, 0.5, 0);
		glRotated(ang, 0, 0, 1);
		//rodilla_pierna_Shiryu_();
		musloShiryu();
	glPopMatrix();
}

void aro_falda(float angZ, float distX) {
	glPushMatrix();
		glRotated(angZ, 0, 0, 1);
		aro_arriba_pierna_Shiryu(distX);
	glPopMatrix();
}

void pierna_derecha_Shiryu() {
	muslo_rodilla_Shiryu_real(-11,-3.5);	
	//aro_falda(11, 4.2);
	parte_pierna_abajo_rodilla(-2.5, -3.5, -6);
	//zapato_parado_der_Shiryu();
}

void pierna_izquierda_Shiryu() {
	muslo_rodilla_Shiryu_real(11, 3.5);
	//aro_falda(-11, -4.2);
	parte_pierna_abajo_rodilla(2.5, 3.5,-1);	
}



void brazo_Shiryu_Final() {
	glPushMatrix();
		glTranslated(0, 0.8, 0);		
		brazo_Shiryu(3.29);
	glPopMatrix();
}

void antebrazo_Shiryu_Final() {
	glPushMatrix();
		glTranslated(0, 0.8, 0);
		antebrazo_Shiryu(3.29);
		mano_Shiryu(3.29);
	glPopMatrix();
}

void brazo_izq_completo_Shiryu_doblado() {
	glPushMatrix();
		glTranslated(6.3, 0, 0);
		glRotated(20, 0, 0, 1);		
		brazo_Shiryu_Final();
	glPopMatrix();

	glPushMatrix();
		glTranslated(0.6, 1.5, 7);
		glRotated(-25, 1, 0, 0);
		antebrazo_Shiryu_Final();
	glPopMatrix();
}
void brazo_der_completo_Shiryu_doblado() {
	glPushMatrix();
		glTranslated(-12.5, 2.3, 0);
		glRotated(-20, 0, 0, 1);		
		brazo_Shiryu_Final();
	glPopMatrix();

	glPushMatrix();
		glTranslated(-7.2, 1.5, 7);
		glRotated(-25, 1, 0, 0);
		antebrazo_Shiryu_Final();
	glPopMatrix();
 }

void casco_shiryu() {
	color_shiryu1();
	
	glPushMatrix();
		glutSolidDodecahedron();
	glPopMatrix();
	
	glPushMatrix();
		glColor3ub(222, 202, 116);
		glTranslated(-3, 0, 0.7);
		glRotated(90,0,1,0);
		gluCylinder(gluNewQuadric(), 0.5, 0.5, 6, 20, 20);
	glPopMatrix();

	glPushMatrix();
		glColor3ub(222, 202, 116);
		glTranslated(-2.7, 0, 0.7);
		glRotated(-70,1,0,0);
		gluCylinder(gluNewQuadric(), 0.5, 0.5, 3, 20, 20);
	glPopMatrix();

	glPushMatrix();
		glColor3ub(222, 202, 116);
		glTranslated(2.7, 0, 0.7);
		glRotated(-70,1,0,0);
		gluCylinder(gluNewQuadric(), 0.5, 0.5, 3, 20, 20);
	glPopMatrix();

	glPushMatrix();
		color_shiryu1();
		glTranslated(0.8, 0, 0);
		glRotated(-90,1,0,0);
		glutSolidCone(0.5, 4, 20, 20);
	glPopMatrix();

	glPushMatrix();
		color_shiryu1();
		glTranslated(-0.8, 0, 0);
		glRotated(-90,1,0,0);
		glutSolidCone(0.5, 4, 20, 20);
	glPopMatrix();

}

void casco_shiryu_final(){
	glPushMatrix();
		glTranslated(0, 24, 0);
		glScaled(0.8, 0.7, 1.2);
		casco_shiryu();
	glPopMatrix();
}

void armadura_tronco_Shiryu() {
	color_shiryu1();
	glPushMatrix();
		glTranslated(0, 20, 0);
		glutSolidSphere(2, 20, 20);
	glPopMatrix();
	glPushMatrix();
		glTranslated(0, 19.69, 0);
		glScaled(1.1, 0.5, 0.55);
		glutSolidSphere(4, 20, 20);
	glPopMatrix();

	glPushMatrix();
		glTranslated(0, 22, 0);		
		glScaled(1, 1, 0.7);
		glRotated(90,1,0,0);			
		gluCylinder(gluNewQuadric(), 2, 2.5, 6, 20, 20);	
	glPopMatrix();
}

void shiryu() {	
	
	//casco_shiryu_final();
	//armadura_tronco_Shiryu();
	//glPushMatrix
	
	/*              GUIA                */
	/*glPushMatrix();
		glColor3ub(255, 0, 0);
		glTranslated(-8, 7, 0);
		glScaled(2, 16, 2);
		glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
		glColor3ub(255, 255, 0);
		glTranslated(-8, 19, 0);
		glScaled(2, 5, 2);
		glutSolidCube(1);
	glPopMatrix();*/

	/*piernas estáticas*/
	glPushMatrix();
		pierna_derecha_Shiryu();
	glPopMatrix();
	
	glPushMatrix();
		pierna_izquierda_Shiryu();
	glPopMatrix();
	

	/*       piernas en movimiento    */
	/*glPushMatrix();
		anguloPierna1 += (velocidadMovimiento * ladoPierna1);
		if (anguloPierna1 >= 34) {
			ladoPierna1 = -1;
		}
		if (anguloPierna1 <= -34) {
			ladoPierna1 = 1;
		}
		glTranslated(0, 14, 0);
		glRotated(anguloPierna1, 1, 0, 0);
		glTranslated(0, -14, 0);
		pierna_derecha_Shiryu();
	glPopMatrix();

	glPushMatrix();
		anguloPierna2 += (velocidadMovimiento * ladoPierna2);
		if (anguloPierna2 <= -34) {
			ladoPierna2 = 1;
		}
		if (anguloPierna2 >= 34) {
			ladoPierna2 = -1;
		}
		glTranslated(0, 14, 0);
		glRotated(anguloPierna2, 1, 0, 0);
		glTranslated(0, -14, 0);
		pierna_izquierda_Shiryu();
	glPopMatrix();*/
	
	tronco_Shiryu();
		
		/*        BRAZO IZQUIERDO */
		/*glPushMatrix();
			/*glTranslated(0, 19, 0);
			glRotated(-70, 1, 0, 0);
			glTranslated(0, -19, 0);*/
			/*brazo_Shiryu_izq();
			antebrazo_Shiryu_izq();
		glPopMatrix();*/
		/*        BRAZO DERECHO    */		
		/*glPushMatrix();
			brazo_Shiryu_der();
			antebrazo_Shiryu_der();
		glPopMatrix();

		/*         BRAZOS POSICIÓN NORMAL          */
		
	/*         BRAZOS ESTATICOS POSICIÓN 2           */
	glPushMatrix();
		glTranslated(0, 20, 0);
		glRotated(-81, 1, 0, 0);
		glTranslated(0, -20, 0);
		brazo_izq_completo_Shiryu_doblado();
	glPopMatrix();

	glPushMatrix();
		glTranslated(0, 20, 0);
		glRotated(-81, 1, 0, 0);
		glTranslated(0, -20, 0);
		brazo_der_completo_Shiryu_doblado();
	glPopMatrix();	

	/*************** BRAZOS SHIRYU Q SE MUEVEN ********************/

	/*glPushMatrix();
		/*anguloBrazo2 += (velocidadMovimiento * ladoBrazo2);
		if (anguloBrazo2 <= -100) {
			ladoBrazo2 = 0.25;
		}
		if (anguloBrazo2 >= 0) {
			ladoBrazo2 = -0.25;
		}
		glTranslated(0, 20, 0);
		glRotated(anguloBrazo2, 1, 0, 0);
		glTranslated(0, -20, 0);*/
		/*brazo_der_completo_Shiryu_doblado();
		brazo_izq_completo_Shiryu_doblado();
	glPopMatrix();*/
	

	cabeza_shiryu();
}

/**********************/

void puerta() {
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[6]);

	glPushMatrix();	
		
		glBegin(GL_QUADS);						
			glTexCoord2d(0, 0); glVertex3d(-70, 0, 0);
			glTexCoord2d(1, 0); glVertex3d(70, 0, 0);
			glTexCoord2d(1, 1); glVertex3d(70, 40, 0);
			glTexCoord2d(0, 1); glVertex3d(-70, 40, 0);
		glEnd();
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
}

void escalon1() {
	/*int h = 0, z = 0;
	for ( int i = 0; i < escalones; i++)
	{
		glPushMatrix();
			glTranslated(0, h, z);
			glColor3ub(255, 255, 255);
			glScaled(90, 2, 10);
			glutSolidCube(1);
		glPopMatrix();
		h += 2;
		z -= 10;
	}*/
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[0]);

	glPushMatrix();
		glColor3ub(255, 255, 255);
		//glTranslated(0, 5, -44.9); 
		glBegin(GL_QUADS);						
			glTexCoord2d(0, 0); glVertex3d(-70, 0, 0);
			glTexCoord2d(1, 0); glVertex3d(70, 0, 0);
			glTexCoord2d(1, 1); glVertex3d(70, 2, 0);
			glTexCoord2d(0, 1); glVertex3d(-70, 2, 0);
		glEnd();
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
		
}


void escalon2() {

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[0]);

	glPushMatrix();
		glColor3ub(255, 255, 255);
		//glTranslated(0, 5, -44.9); 
		glRotated(90, 1, 0, 0);
		glBegin(GL_QUADS);						
			glTexCoord2d(0, 0); glVertex3d(-70, 0, -10);
			glTexCoord2d(1, 0); glVertex3d(70, 0, -10);
			glTexCoord2d(1, 1); glVertex3d(70, 10, -10);
			glTexCoord2d(0, 1); glVertex3d(-70, 10, -10);
		glEnd();
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
		
}

void escalera(int escalones) {
	int h = -8, z = -10;
	int h1 = 0, z1 = 0;

	for (int i = 0; i < escalones; i++) {
		glPushMatrix();
			glTranslated(0, h1, z1);
			escalon1();
		glPopMatrix();
		h1 += 2;
		z1 -= 10;
	}

	

	for (int i = 0; i < escalones; i++) {
		glPushMatrix();
			glTranslated(0, h, z);
			escalon2();
		glPopMatrix();
		h += 2;
		z -= 10;
	}
	
	
}

void costado_inferior() {
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[1]);	
	//izq
	glPushMatrix();
		glColor3ub(255, 255, 255);				
		glBegin(GL_QUADS);						
			glTexCoord2d(0, 0); glVertex3d(-70, 0, 0);
			glTexCoord2d(1, 0); glVertex3d(-70, 0, -70);
			glTexCoord2d(1, 1); glVertex3d(-70, 14, -70);
			glTexCoord2d(0, 1); glVertex3d(-70, 14, 0);
		glEnd();
	glPopMatrix();

	glPushMatrix();
		glColor3ub(255, 255, 255);				
		glBegin(GL_QUADS);						
			glTexCoord2d(0, 0); glVertex3d(-140, 0, 0);
			glTexCoord2d(1, 0); glVertex3d(-140, 0, -70);
			glTexCoord2d(1, 1); glVertex3d(-140, 14, -70);
			glTexCoord2d(0, 1); glVertex3d(-140, 14, 0);
		glEnd();
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
}

void detallesCostadoEscalera1() {glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[1]);
	//frontal
	glPushMatrix();
		glColor3ub(255, 255, 255);		
		glBegin(GL_QUADS);						
			glTexCoord2d(0, 0); glVertex3d(-140, 0, 0);
			glTexCoord2d(1, 0); glVertex3d(-70, 0, 0);
			glTexCoord2d(1, 1); glVertex3d(-70, 14, 0);
			glTexCoord2d(0, 1); glVertex3d(-140, 14, 0);
		glEnd();
	glPopMatrix();


	glDisable(GL_TEXTURE_2D);

		//inferior
	glPushMatrix();
		costado_inferior();
	glPopMatrix();
		
}

void detallesCostadoEscalera2() {
	
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[1]);

	glPushMatrix();
		glColor3ub(255, 255, 255);		
		glBegin(GL_QUADS);						
			glTexCoord2d(0, 0); glVertex3d(-140, 14, 0);
			glTexCoord2d(1, 0); glVertex3d(-70, 14, 0);
			glTexCoord2d(1, 1); glVertex3d(-70, 14, -70);
			glTexCoord2d(0, 1); glVertex3d(-140, 14, -70);
		glEnd();
	glPopMatrix();
	
	glDisable(GL_TEXTURE_2D);
		
}

void costadoEscalera_forma() {
	detallesCostadoEscalera1();
	detallesCostadoEscalera2();
}

void costadoEscalera_final() {
	glPushMatrix();
		costadoEscalera_forma();
	glPopMatrix();

	glPushMatrix();
		glTranslated(210, 0, 0);
		costadoEscalera_forma();
	glPopMatrix();
}

void piso_templo() {
	
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[2]);

	glPushMatrix();
		glColor3ub(255, 255, 255);		
		glBegin(GL_QUADS);						
			glTexCoord2d(0, 0); glVertex3d(140, 14, -70);
			glTexCoord2d(1, 0); glVertex3d(-140, 14, -70);
			glTexCoord2d(1, 1); glVertex3d(-140, 14, -300);
			glTexCoord2d(0, 1); glVertex3d(140, 14, -300);
		glEnd();
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
}

void paredes() {
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[3]);

	glPushMatrix();
		glColor3ub(255, 255, 255);		
		glBegin(GL_QUADS);						
			glTexCoord2d(0, 0); glVertex3d(-90, 0, 0);
			glTexCoord2d(1, 0); glVertex3d(90, 0, 0);
			glTexCoord2d(1, 1); glVertex3d(90, 60, 0);
			glTexCoord2d(0, 1); glVertex3d(-90, 60, 0);
		glEnd();
	glPopMatrix();
	
	glDisable(GL_TEXTURE_2D);
}

void paredesLaterales() {
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[3]);

	glPushMatrix();
		glColor3ub(255, 255, 255);		
		glBegin(GL_QUADS);						
			glTexCoord2d(0, 0); glVertex3d(0, 0, -65);
			glTexCoord2d(1, 0); glVertex3d(0, 0, 65);
			glTexCoord2d(1, 1); glVertex3d(0, 60, 65);
			glTexCoord2d(0, 1); glVertex3d(0, 60, -65);
		glEnd();
	glPopMatrix();
	
	glDisable(GL_TEXTURE_2D);
}

void techo() {
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[3]);

	glPushMatrix();
		glColor3ub(255, 255, 255);		
		glBegin(GL_QUADS);						
			glTexCoord2d(0, 0); glVertex3d(-90, 60, -65);
			glTexCoord2d(1, 0); glVertex3d(-90, 60, 65);
			glTexCoord2d(1, 1); glVertex3d(90, 60, 65);
			glTexCoord2d(0, 1); glVertex3d(90, 60, -65);
		glEnd();
	glPopMatrix();
	
	glDisable(GL_TEXTURE_2D);
}

void columnas() {
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[4]);

	glPushMatrix();		
		glColor3ub(255, 255, 255);
		glRotated(-90, 1, 0, 0);
		GLUquadric* quad = gluNewQuadric();
		gluQuadricTexture(quad, 1);
		gluCylinder(quad, 4, 4, 60, 30, 30);
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
}

void trianguloDecoracion2() {

	glPushMatrix();		
		glBegin(GL_QUADS);
			//glColor3ub(0, 255, 0);			
			colorTrianguloTemplo();
			glVertex3d(0, 25, 0);
			glVertex3d(70, 0, 0);
			glVertex3d(70, 0, 40);
			glVertex3d(0, 25, 40);
		glEnd();
	glPopMatrix();

	glPushMatrix();		
		glBegin(GL_QUADS);
			//glColor3ub(0, 255, 0);			
			colorTrianguloTemplo();
			glVertex3d(0, 25, 0);
			glVertex3d(-70, 0, 0);
			glVertex3d(-70, 0, 40);
			glVertex3d(0, 25, 40);
		glEnd();
	glPopMatrix();
}

void trianguloDecoracion() {
	
	glPushMatrix();	
		colorTrianguloTemplo();
		glTranslated(0, 34, 200);		
		glBegin(GL_TRIANGLES);
			glVertex3d(-70, 0, 0);
			glVertex3d(70, 0, 0);
			glVertex3d(0, 25, 0);
		glEnd();		
		glColor3ub(0, 0, 0);
		glBegin(GL_TRIANGLES);
			glVertex3d(-70, 0, 40);
			glVertex3d(70, 0, 40);
			glVertex3d(0, 25, 40);
		glEnd();
		trianguloDecoracion2();
	glPopMatrix();

	/*glPushMatrix();
		trianguloDecoracion2();
	glPopMatrix();*/
}
void baseColumna() {
	glPushMatrix();
		glColor3ub(100, 100, 100);
		glutSolidCube(13);
	glPopMatrix();

	/*glPushMatrix();
		glColor3ub(100, 100, 100);
		glTranslated(0, 60, 0);
		glutSolidCube(13);
	glPopMatrix();*/
}

void columnaLlamar() {	

	glPushMatrix();
		glTranslated(30, 16, 81);
		columnas();
		baseColumna();
	glPopMatrix();
	
	glPushMatrix();
		glTranslated(-30, 16, 81);
		columnas();
		baseColumna();
	glPopMatrix();

	glPushMatrix();
		glTranslated(-60, 16, 81);
		columnas();
		baseColumna();
	glPopMatrix();

	glPushMatrix();
		glTranslated(60, 16, 81);
		columnas();
		baseColumna();
	glPopMatrix();
	
}

void cuadroArriba() {


	glPushMatrix();
		glTranslated(0,0,65);
		paredes();
	glPopMatrix();

	glPushMatrix();
		glTranslated(0,0,-65);
		paredes();
	glPopMatrix();

	glPushMatrix();
		glTranslated(90, 0, 0);
		paredesLaterales();
	glPopMatrix();	
	
	glPushMatrix();
		glTranslated(-90, 0, 0);
		paredesLaterales();
	glPopMatrix();

	glPushMatrix();
		techo();
	glPopMatrix();	



}

void symbol() {
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[5]);

	glPushMatrix();
		glColor3ub(255, 255, 255);		
		glBegin(GL_QUADS);						
			glTexCoord2d(0, 0); glVertex3d(0, 0, 0);
			glTexCoord2d(1, 0); glVertex3d(20, 0, 0);
			glTexCoord2d(1, 1); glVertex3d(20, 20, 0);
			glTexCoord2d(0, 1); glVertex3d(0, 20, 0);
		glEnd();
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
}

void puertaR() {
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[6]);
	glPushMatrix();
		glColor3ub(255, 255, 255);		
		glBegin(GL_QUADS);						
			glTexCoord2d(0, 0); glVertex3d(0, 0, 0);
			glTexCoord2d(1, 0); glVertex3d(20, 0, 0);
			glTexCoord2d(1, 1); glVertex3d(20, 20, 0);
			glTexCoord2d(0, 1); glVertex3d(0, 20, 0);
		glEnd();
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
}

void patio() {
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[7]);

	glPushMatrix();
		glColor3ub(255, 255, 255);
			glBegin(GL_QUADS);
			glTexCoord2d(0, 0); glVertex3d(0, 0.1, 0);
			glTexCoord2d(8, 0); glVertex3d(280, 0.1, 0);
			glTexCoord2d(8, 8); glVertex3d(280, 0.1, 280);
			glTexCoord2d(0, 8); glVertex3d(0, 0.1, 280);
		glEnd();
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
	
}

void templo() {	

	glPushMatrix();
		glTranslated(-20,15,56);
		glScaled(2,2.5,1);
		puertaR();
	glPopMatrix();

	glPushMatrix();
		glTranslated(0,0,180);
		piso_templo();
	glPopMatrix();	

	glPushMatrix();
		glTranslated(0, 16, 0);
		glScaled(1.4, 1.2, .85);
		cuadroArriba();
	glPopMatrix();
	
	
	columnaLlamar();	
	
	glPushMatrix();
		glTranslated(-10,74,90);
		symbol();
	glPopMatrix();

	glPushMatrix();
		glTranslated(0, 40, -150.01);
		trianguloDecoracion();
	glPopMatrix();

	
	
}

void final() {
	glPushMatrix();
			//desplazamiento += 0.05;
			//glTranslated(0, 0.5, desplazamiento);	
			/* cuando va a atacar*/
			glTranslated(0, 2, 120);
			shura_parado();
		glPopMatrix();
		
		glPushMatrix();
			glTranslated(0, 2, 106);			
			//glRotated(180, 0, 1, 0);
			shiryu();
		glPopMatrix();
}

void dibujar() {
	
	inicializarLuces();
	//glLoadIdentity();//inicializa el lienzo
	//gluOrtho2D(0, 10, 0, 10);
	//glClear(GL_COLOR_BUFFER_BIT);//limpiar el buffer de colores
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//limpiar el buffer de colores
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//gluLookAt(camaraX, camaraY, camaraZ, 0, 0, 0, 0, 1, 0);
	gluLookAt(camaraX, camaraY, camaraZ, centroX, 0, centroZ,0,1,0);
	//-----------------------------------------------
	glPushMatrix();//engloba a lo q va a girar
		glRotated(angulo, 0, 1, 0);
		//dibujarEjes();
		//piso();		
		//cargarImagenes();		
		
		

		/*glPushMatrix();
			glTranslated(-140, -0.5, 0);
			patio();
		glPopMatrix();

		glPushMatrix();
			glTranslated(0, -3, -180);			
			templo();
		glPopMatrix();

		glPushMatrix();
			glTranslated(0, -1, 0);
			escalera(7);
			costadoEscalera_final();
		glPopMatrix();*/
		
		glPushMatrix();
			//desplazamiento += 0.05;
			//glTranslated(0, desplazamiento, 0);
			final();
		glPopMatrix();
		

		
		

	glPopMatrix();
	//-----------------------------------------------
	//glFlush();
	glutSwapBuffers();
}

void teclado_especial(int tecla, int x, int y) {
	//cout << tecla << endl;

	switch (tecla)
	{
	case 101:
		camaraY += 0.2;
		//camaraY += 5;
		//camaraY += 2.5;
		break;
	case 103:
		camaraY -= 0.2;
		//camaraY -= 5;
		//camaraY -= 2.5;
		
		break;
	case 100:
		angulo -= 1;
		//angulo -= 10;
		//angulo -= 2.5;
		break;
	case 102:
		angulo += 1;
		//angulo += 10;
		//angulo += 2.5;
		break;
	}

}

void timer(int t) {
	glutPostRedisplay();
	glutTimerFunc(20, timer, 0);
}

void teclado(unsigned char key, int x, int y) {
	//cout << key << endl;
	switch (key) {
	case 'o':
		camaraZ -= 5;
		break;
	case 'p':
		camaraZ += 5;
		break;
	
	case 'a':
		camaraX -= movimientoCamara;
		centroX -= movimientoCamara;
		break;

	case 'd':
		camaraX += movimientoCamara;
		centroX += movimientoCamara;
		break;
	case 'w':
		camaraZ -= movimientoCamara;
		centroZ -= movimientoCamara;
		break;
	case 's':
		camaraZ += movimientoCamara;
		centroZ += movimientoCamara;
		break;
	}

}

int main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	//glutInitDisplayMode(GLUT_SINGLE);//para 2d
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);//para 3d
	//glutInitWindowSize(1400, 900);//tamaño de ventana
	glutInitWindowSize(1282, 720);//tamaño de ventana
	glutInitWindowPosition(100, 0);//donde inicia la pantalla
	//glutInitWindowPosition(400, 0);//donde inicia la pantalla
	glutCreateWindow("Computacion Gráfica");//título
	//para 3d
	//46 121 165
	cargarImagenes();
	//glClearColor(0.70, 0.7, 0.7, 1);
	//glClearColor(0.56, 0.76, 0.89, 1);
	//glClearColor(0.39, 0.21, 0.62, 1);
	glClearColor(0, 1, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	//glFlush();

	glutReshapeFunc(iniciarVentana);
	glutDisplayFunc(dibujar);//llama a función q dibuja
	glutKeyboardFunc(teclado);
	glutSpecialFunc(teclado_especial);
	glutTimerFunc(0, timer, 0);
	glutMainLoop();

	return 0;
}