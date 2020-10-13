#include <math.h>
#include <GL/gl.h>
#include <GL/glut.h>

GLUquadric* a;
GLfloat xRotaded, yRotaded = 0.0;

//----------------------Rasterização (Bresenham)

void RasterizaDxMaior(float x1, float y1, float x2, float y2){

    float x, y, Dx, Dy, e, m, i;
 
    x = x1;
    y = y1;
    Dx = x2-x1;
    Dy = y2-y1;
    m = Dy/Dx;
    e = m - 1/2;
    glPushMatrix();
    glPointSize(2);
    glColor3f(255,255,255);
    glRotatef(xRotaded,1,0,0);
    glRotatef(yRotaded,0,1,0);
    glTranslatef(-1.125,-0.02,0);
    glScalef(2.55,2.55,3.0);
    glBegin(GL_POINTS);
    for (i = 0.01; i < Dx ; i+=0.01){
     
		glVertex3f(x/102,y,0.39);
	
	while (e>0){
    	    y = y + 1;
  	    e = e - 1;
        }
        x = x + 1;
        e = e + m;
    }
    glEnd();
    glPopMatrix();
}


void RasterizaDyMaior(float x1, float y1, float x2, float y2){

    float x, y, Dx, Dy, e, m, i;
 
    y = y1;
    x = x1;
    Dy = y2-y1;
    Dx = x2-x1;
    m = Dx/Dy;
    e = m - 1/2;
    glPushMatrix();
    glPointSize(1);
    glColor3f(255,255,255);
    glRotatef(xRotaded,1,0,0);
    glRotatef(yRotaded,0,1,0);
    glScalef(2.55,2.55,3.0);
    glTranslatef(-0.3878,-1.125,0.0);
    glBegin(GL_POINTS);
    for (i = 0.01; i < Dy ; i+=0.01){
     
		glVertex3f(x/350,y/250,0.39);
	
	while (e>0){
    	    x = x + 1;
  	    e = e - 1;
        }
        y = y + 1;
        e = e + m;
    }
    glEnd();
    glPopMatrix();
}

//-----------------------Círculos

void Circulo(GLfloat x, GLfloat y, GLfloat z, GLfloat radius) {
	int i;
	int triangleAmount = 80;
	
	GLfloat twicePi = 2.0f * 3.1415926;
	
	glBegin(GL_TRIANGLE_FAN);
	for(i = 0; i <= triangleAmount; i++) { 
		glVertex3f(
	        x + (radius * cos(i *  twicePi / triangleAmount)), 
		    y + (radius * sin(i * twicePi / triangleAmount)),
            z
		);
	}
	glEnd();
}
//-------------------------Espaço

void reshape(int x, int y) {
    if (y == 0 || x == 0) return;   
    glMatrixMode(GL_PROJECTION);  
    glLoadIdentity(); 
    gluPerspective(42,(GLdouble)x/(GLdouble)y,1,50);
    glMatrixMode(GL_MODELVIEW);
    glViewport(0,0,x,y);
}

//----------------------------------Inicialização

void init(void) {
    
    //-------------------------------iluminação
    
    GLfloat luz_ambiente[4]={1.0, 1.0, 1.0, 1.0}; //Luz ambiente
    GLfloat luz_difusa[4]={1.0,1.0,1.0,1.0}; // Luz difusa
    GLfloat luz_especular[4] = {0.0,0.0,0.01,1.0}; //Especular
    GLfloat luz_posicao[4] = {0.0,-10.0,-10.0,0.0}; //Posição da luz
    GLfloat brilho[1] = {2.5}; //Brilho    

    glClearColor (0.0, 0.0, 0.0, 0.0);
    glShadeModel (GL_SMOOTH);

    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, luz_especular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, brilho);
    glLightfv(GL_LIGHT0, GL_POSITION, luz_posicao);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, luz_difusa);
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luz_ambiente);    

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    glEnable(GL_DEPTH_TEST); //Z-buffer

    a = gluNewQuadric();
    gluQuadricNormals(a, GLU_SMOOTH);
}
 
//------------------------ Rotação

void RotateUP(void) {
    xRotaded -= 1.5;  //Velocidade
    if (xRotaded < -360.0) {
        xRotaded += 360.0;
    }
    glutPostRedisplay();
}
void RotateDOWN(void) {
    xRotaded += 1.5;
    if (xRotaded > 360.0) {
        xRotaded -= 360.0;
    }
    glutPostRedisplay();
}
void RotateRIGHT(void) {
    yRotaded += 1.5;
    if (yRotaded > 360.0) {
        yRotaded -= 360.0;
    }
    glutPostRedisplay();
}
void RotateLEFT(void) {
    yRotaded -= 1.5;
    if (yRotaded < -360.0) {
        yRotaded += 360.0;
    }
    glutPostRedisplay();
}

//---------------------- Entrada de dados rotação

void teclado(int key, int x, int y) {
    switch(key) {
        case GLUT_KEY_UP:
            RotateUP();
            break;
        case GLUT_KEY_DOWN:
            RotateDOWN();
            break;
        case GLUT_KEY_RIGHT:
            RotateRIGHT();
            break;
        case GLUT_KEY_LEFT:
            RotateLEFT();
            break;
        case GLUT_KEY_END:
            xRotaded = 0;
            yRotaded = 0;
    }
}

//---------------------------- Geometria

void display() {
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
  
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Limpeza Z-buffer

    glClearColor(0,0,0.15,0);
    glEnable(GL_COLOR_MATERIAL);
    glLoadIdentity();
    glTranslatef(0.0,0.5,-15.0);

    //------------------------------------ Cilindro branco externo
    glPushMatrix(); 
    glRotatef(xRotaded,1,0,0);
    glRotatef(yRotaded,0,1,0);
    glColor3f(100,100,100); //(vermelho,verde,azul)
    glTranslatef(0.0,-1.2,-0.8);
    gluCylinder(a,4.0,4,1.68,80,10); //(*gluNewQuadric, base, top, height, slices)
    glTranslatef(0.0,1.2,0.8);
    Circulo(0,-1.2,0.8,4); //frente
    Circulo(0,-1.2,-0.8,4); //verso
    glPopMatrix();

    //----------------------------------Cilindro azul externo
    glPushMatrix(); 
    glRotatef(xRotaded,1,0,0);
    glRotatef(yRotaded,0,1,0);
    glColor3f(0,0,0.15);
    glTranslatef(0.0,-1.2,-0.8);
    gluCylinder(a,3,3,1.6,50,10);
    glTranslatef(0.0,1.2,0.8);
    Circulo(0,-1.2,0.9,3.6); //frente
    Circulo(0,-1.2,-0.9,3.6);//verso
    glPopMatrix();

    //----------------------------------Cilindro branco interno
    glPushMatrix(); 
    glRotatef(xRotaded,1,0,0);
    glRotatef(yRotaded,0,1,0);
    glColor3f(255,255,255);
    glTranslatef(0.0,-1.2,-0.7);
    gluCylinder(a,3,3,1.6,50,10);
    glTranslatef(0.0,1.2,0.8);
    Circulo(0,-1.2,0.9,3.2); //frente
    Circulo(0,-1.2,-0.9,3.2);//verso
    glPopMatrix();

    //----------------------------------Cilindro azul interno
    glPushMatrix(); 
    glRotatef(xRotaded,1,0,0);
    glRotatef(yRotaded,0,1,0);
    glColor3f(0,0,0.15);
    glTranslatef(0.0,-1.2,-0.6);
    gluCylinder(a,3,3,1.6,50,10);
    glTranslatef(0.0,1.2,0.8);
    Circulo(0,-1.2,0.9,2.9); //frente
    Circulo(0,-1.2,-0.9,2.9); //verso
    glPopMatrix();


    //---------------------------------------amarelo esquerda
    glPushMatrix();
    glRotatef(xRotaded,1,0,0);
    glRotatef(yRotaded,0,1,0);
    glColor3f(255,255,255);
    glScalef(3,3,3);
    glTranslatef(-1.45,0.1,0.0);
    glRotatef(-17,0,0,1);
    glutSolidCube(0.6);
    glPopMatrix();

    //---------------------------------------amarelo esquerda dentro
    glPushMatrix();
    glRotatef(xRotaded,1,0,0);
    glRotatef(yRotaded,0,1,0);
    glColor3f(0,0,0.15);
    glScalef(3,3,4.1);
    glTranslatef(-1.33,0.05,0.0);
    glRotatef(-17,0,0,1);
    glutSolidCube(0.45);
    glPopMatrix();


    //---------------------------------------roxo esquerda
    glPushMatrix();
    glRotatef(xRotaded,1,0,0);
    glRotatef(yRotaded,0,1,0);
    glColor3f(255,255,255);
    glScalef(3.0,3.0,3.0);
    glTranslatef(-1.42,-0.95,0.0);
    glRotatef(21,0,0,1);
    glutSolidCube(0.6);
   
    glPopMatrix();

    //---------------------------------------roxo esquerda dentro
    glPushMatrix();
    glRotatef(xRotaded,1,0,0);
    glRotatef(yRotaded,0,1,0);
    glColor3f(0,0,0.15);
    glScalef(3.0,3.0,4.1);
    glTranslatef(-1.31,-0.92,0);
    glRotatef(21,0,0,1);
    glutSolidCube(0.45);
   
    glPopMatrix();


    //---------------------------------------azul esverdeado esquerda embaixo
    glPushMatrix();
    glRotatef(xRotaded,1,0,0);
    glRotatef(yRotaded,0,1,0);
    glColor3f(255,255,255);
    glScalef(3.0,3.0,3.0);
    glTranslatef(-0.60,-1.80,0.0);
    glRotatef(68,0,0,1);
    glutSolidCube(0.6);
    
    glPopMatrix();

    //---------------------------------------azul esverdeado esquerda embaixo dentro
    glPushMatrix();
    glRotatef(xRotaded,1,0,0);
    glRotatef(yRotaded,0,1,0);
    glColor3f(0,0,0.15);
    glScalef(3.0,3.0,4.1);
    glTranslatef(-0.55,-1.69,0);
    glRotatef(68,0,0,1);
    glutSolidCube(0.45);
    
    glPopMatrix();


    //---------------------------------------verde esquerda em cima
    glPushMatrix();
    glRotatef(xRotaded,1,0,0);
    glRotatef(yRotaded,0,1,0);
    glColor3f(255,255,255);
    glScalef(3.0,3.0,3.0);
    glTranslatef(-0.65,0.94,0.0);
    glRotatef(-62,0,0,1);
    glutSolidCube(0.6);
   
    glPopMatrix();

    //---------------------------------------verde esquerda em cima dentro
    glPushMatrix();
    glRotatef(xRotaded,1,0,0);
    glRotatef(yRotaded,0,1,0);
    glColor3f(0,0,0.15);
    glScalef(3.0,3.0,4.1);
    glTranslatef(-0.61,0.86,0);
    glRotatef(-62,0,0,1);
    glutSolidCube(0.45);
   
    glPopMatrix();


    //---------------------------------------azul direita embaixo
    glPushMatrix();
    glRotatef(xRotaded,1,0,0);
    glRotatef(yRotaded,0,1,0);
    glColor3f(255,255,255);
    glScalef(3.0,3.0,3.0);
    glTranslatef(1.43,-0.91,0.0);
    glRotatef(-20,0,0,1);
    glutSolidCube(0.6);
   
    glPopMatrix();

    //---------------------------------------azul direita embaixo dentro
    glPushMatrix();
    glRotatef(xRotaded,1,0,0);
    glRotatef(yRotaded,0,1,0);
    glColor3f(0,0,0.15);
    glScalef(3.0,3.0,4.1);
    glTranslatef(1.32,-0.875,0);
    glRotatef(-20,0,0,1);
    glutSolidCube(0.45);
   
    glPopMatrix();

    //---------------------------------------roxo direita embaixo
    glPushMatrix();
    glRotatef(xRotaded,1,0,0);
    glRotatef(yRotaded,0,1,0);
    glColor3f(255,255,255);
    glScalef(3.0,3.0,3.0);
    glTranslatef(0.7,-1.75,0.0);
    glRotatef(28,0,0,1);
    glutSolidCube(0.6);
    
    glPopMatrix();

    //---------------------------------------roxo direita embaixo dentro
    glPushMatrix();
    glRotatef(xRotaded,1,0,0);
    glRotatef(yRotaded,0,1,0);
    glColor3f(0,0,0.15);
    glScalef(3.0,3.0,4.1);
    glTranslatef(0.65,-1.64,0);
    glRotatef(28,0,0,1);
    glutSolidCube(0.45);
    
    glPopMatrix();

    //---------------------------------------cinza direita em cima
    glPushMatrix();
    glRotatef(xRotaded,1,0,0);
    glRotatef(yRotaded,0,1,0);
    glColor3f(255,255,255);
    glScalef(3.0,3.0,3.0);
    glTranslatef(1.38,0.2,0.0);
    glRotatef(24,0,0,1);
    glutSolidCube(0.6);
   
    glPopMatrix();

    //---------------------------------------cinza direita em cima dentro
    glPushMatrix();
    glRotatef(xRotaded,1,0,0);
    glRotatef(yRotaded,0,1,0);
    glColor3f(0,0,0.15);
    glScalef(3.0,3.0,4.1);
    glTranslatef(1.28,0.15,0);
    glRotatef(24,0,0,1);
    glutSolidCube(0.45);
   
    glPopMatrix();


    //---------------------------------------amarelo direita em cima
    glPushMatrix();
    glRotatef(xRotaded,1,0,0);
    glRotatef(yRotaded,0,1,0);
    glColor3f(255,255,255);
    glScalef(3.0,3.0,3.0);
    glTranslatef(0.65,0.94,0.0);
    glRotatef(64,0,0,1);
    glutSolidCube(0.6);
   
    glPopMatrix();

    //---------------------------------------amarelo direita em cima dentro
    glPushMatrix();
    glRotatef(xRotaded,1,0,0);
    glRotatef(yRotaded,0,1,0);
    glColor3f(0,0,0.15);
    glScalef(3.0,3.0,4.1);
    glTranslatef(0.63,0.86,0);
    glRotatef(64,0,0,1);
    glutSolidCube(0.45);
   
    glPopMatrix();

    //---------------------------------------base somatório

    glPushMatrix();
    glRotatef(xRotaded,1,0,0);
    glRotatef(yRotaded,0,1,0);
    glColor3f(255,255,255);
    glScalef(2.55,2.55,3.0);
    glRotatef(0,0,0,1);
    glBegin(GL_QUADS);
        glVertex3f(0.4,-1.25,0.37); //(y,x,z)
        glVertex3f(0.4,-1.15,0.37); 
        glVertex3f(-0.4,-1.15,0.37);
        glVertex3f(-0.46,-1.25,0.37);
    glEnd();
  
    glPopMatrix();

    //---------------------------------------baixo direita somatório

    glPushMatrix();
    glRotatef(xRotaded,1,0,0);
    glRotatef(yRotaded,0,1,0);
    glColor3f(255,255,255);
    glScalef(2.55,2.55,3.0);
    glRotatef(0,0,0,1);
    glBegin(GL_POLYGON);
        glVertex3f(0.25,-1.25,0.37);
        glVertex3f(0.4,-1.25,0.37); 
        glVertex3f(0.5,-0.9,0.37);
    glEnd();
  
    glPopMatrix();


    //---------------------------------------diagonal baixo somatório

    glPushMatrix();
    glRotatef(xRotaded,1,0,0);
    glRotatef(yRotaded,0,1,0);
    glColor3f(255,255,255);
    glScalef(2.55,2.55,3.0);
    glRotatef(0,0,0,1);
    glBegin(GL_QUADS);
        glVertex3f(0.15,-0.53,0.38); //(y,x,z)
        glVertex3f(-0.25,-1.15,0.38); //FIXO
        glVertex3f(-0.4,-1.15,0.38); //FIXO
        glVertex3f(0,-0.48,0.38);
    glEnd();
  
    glPopMatrix();
    
    RasterizaDyMaior(-1.05,-1.95,0.15,-0.53);

    //---------------------------------------cima somatório

    glPushMatrix();
    glRotatef(xRotaded,1,0,0);
    glRotatef(yRotaded,0,1,0);
    glColor3f(255,255,255);
    glScalef(2.55,2.55,3.0);
    glRotatef(0,0,0,1);
    glBegin(GL_QUADS);
        glVertex3f(0.4,0.05,0.37); //(y,x,z)
        glVertex3f(0.4,0.15,0.37); 
        glVertex3f(-0.46,0.15,0.37);
        glVertex3f(-0.4,0.05,0.37);
    glEnd();
  
    glPopMatrix();

    RasterizaDxMaior(-0.46,0.15,0.4,0.15);

    //---------------------------------------cima direita somatório

    glPushMatrix();
    glRotatef(xRotaded,1,0,0);
    glRotatef(yRotaded,0,1,0);
    glColor3f(255,255,255);
    glScalef(2.55,2.55,3.0);
    glRotatef(0,0,0,1);
    glBegin(GL_POLYGON);
        glVertex3f(0.4,0.05,0.38); //(y,x,z)
        glVertex3f(0.30,0.05,0.38); 
        glVertex3f(0.4,-0.15,0.38);
    glEnd();
  
    glPopMatrix();


    //---------------------------------------diagonal cima somatório

    glPushMatrix();
    glRotatef(xRotaded,1,0,0);
    glRotatef(yRotaded,0,1,0);
    glColor3f(255,255,255);
    glScalef(2.55,2.55,3.0);
    glRotatef(0,0,0,1);
    glBegin(GL_POLYGON);
        glVertex3f(-0.25,0.05,0.38); //FIXO
        glVertex3f(0.15,-0.53,0.38); 
        glVertex3f(0,-0.58,0.38);
        glVertex3f(-0.4,0.05,0.38);//FIXO
    glEnd();
  
    glPopMatrix();

    //FURG

    //---------------------------------------F (barra)

    glPushMatrix();
    glRotatef(xRotaded,1,0,0);
    glRotatef(yRotaded,0,1,0);
    glColor3f(255,255,255);
    glScalef(1.0,0.8,3.0);
    glRotatef(0,0,0,1);
    glBegin(GL_QUADS);
    	glVertex3f(-0.8,-4.1,0.37);
        glVertex3f(-0.8,-4.8,0.37); 
        glVertex3f(-0.7,-4.8,0.37); 
        glVertex3f(-0.7,-4.1,0.37);  
  
	
    glEnd();
  
    glPopMatrix();
 
    //---------------------------------------F (cima)

    glPushMatrix();
    glRotatef(xRotaded,1,0,0);
    glRotatef(yRotaded,0,1,0);
    glColor3f(255,255,255);
    glScalef(1.0,0.8,3.0);
    glRotatef(0,0,0,1);
    glBegin(GL_QUADS);
	glVertex3f(-0.7,-4.1,0.37);
        glVertex3f(-0.45,-4.1,0.37); 
        glVertex3f(-0.45,-4.2,0.37); 
        glVertex3f(-0.7,-4.2,0.37);  
	
    glEnd();
  
    glPopMatrix();
 
    //---------------------------------------F (meio)

    glPushMatrix();
    glRotatef(xRotaded,1,0,0);
    glRotatef(yRotaded,0,1,0);
    glColor3f(255,255,255);
    glScalef(1.0,0.8,3.0);
    glRotatef(0,0,0,1);
    glBegin(GL_QUADS);
	glVertex3f(-0.7,-4.5,0.37);
        glVertex3f(-0.7,-4.4,0.37); 
        glVertex3f(-0.55,-4.4,0.37); 
        glVertex3f(-0.55,-4.5,0.37);  
	
    glEnd();
  
    glPopMatrix();

    //---------------------------------------U (barra)

    glPushMatrix();
    glRotatef(xRotaded,1,0,0);
    glRotatef(yRotaded,0,1,0);
    glColor3f(255,255,255);
    glScalef(1.0,0.8,3.0);
    glRotatef(0,0,0,1);
    glBegin(GL_QUADS);
    	glVertex3f(-0.3,-4.1,0.37);
        glVertex3f(-0.3,-4.8,0.37); 
        glVertex3f(-0.4,-4.8,0.37); 
        glVertex3f(-0.4,-4.1,0.37);   
	
    glEnd();
  
    glPopMatrix();
 
    //---------------------------------------U (baixo)

    glPushMatrix();
    glRotatef(xRotaded,1,0,0);
    glRotatef(yRotaded,0,1,0);
    glColor3f(255,255,255);
    glScalef(1.0,0.8,3.0);
    glRotatef(0,0,0,1);
    glBegin(GL_QUADS);
	glVertex3f(-0.3,-4.7,0.37);
        glVertex3f(-0.05,-4.7,0.37); 
        glVertex3f(-0.05,-4.8,0.37); 
        glVertex3f(-0.3,-4.8,0.37);
	
    glEnd();
  
    glPopMatrix();
 
    //---------------------------------------U (direita)

    glPushMatrix();
    glRotatef(xRotaded,1,0,0);
    glRotatef(yRotaded,0,1,0);
    glColor3f(255,255,255);
    glScalef(1.0,0.8,3.0);
    glRotatef(0,0,0,1);
    glBegin(GL_QUADS);
	glVertex3f(-0.15,-4.1,0.37);
        glVertex3f(-0.05,-4.1,0.37); 
        glVertex3f(-0.05,-4.8,0.37); 
        glVertex3f(-0.15,-4.8,0.37);  
		
    glEnd();
  
    glPopMatrix();

    //---------------------------------------R (barra)

    glPushMatrix();
    glRotatef(xRotaded,1,0,0);
    glRotatef(yRotaded,0,1,0);
    glColor3f(255,255,255);
    glScalef(1.0,0.8,3.0);
    glRotatef(0,0,0,1);
    glBegin(GL_QUADS);
    	glVertex3f(0.1,-4.1,0.37);
        glVertex3f(0.1,-4.8,0.37); 
        glVertex3f(0,-4.8,0.37); 
        glVertex3f(0,-4.1,0.37);  
  
	
    glEnd();
  
    glPopMatrix();
 
    //---------------------------------------R (cima)

    glPushMatrix();
    glRotatef(xRotaded,1,0,0);
    glRotatef(yRotaded,0,1,0);
    glColor3f(255,255,255);
    glScalef(1.0,0.8,3.0);
    glRotatef(0,0,0,1);
    glBegin(GL_QUADS);
	glVertex3f(0.1,-4.1,0.37);
        glVertex3f(0.35,-4.1,0.37); 
        glVertex3f(0.35,-4.2,0.37); 
        glVertex3f(0.1,-4.2,0.37);  
	
    glEnd();
  
    glPopMatrix();
 
    //---------------------------------------R (meio)

    glPushMatrix();
    glRotatef(xRotaded,1,0,0);
    glRotatef(yRotaded,0,1,0);
    glColor3f(255,255,255);
    glScalef(1.0,0.8,3.0);
    glRotatef(0,0,0,1);
    glBegin(GL_QUADS);
	glVertex3f(0.1,-4.5,0.37);
        glVertex3f(0.1,-4.4,0.37); 
        glVertex3f(0.35,-4.4,0.37); 
        glVertex3f(0.35,-4.5,0.37);  
	
    glEnd();
  
    glPopMatrix();

    //---------------------------------------R (direita)

    glPushMatrix();
    glRotatef(xRotaded,1,0,0);
    glRotatef(yRotaded,0,1,0);
    glColor3f(255,255,255);
    glScalef(1.0,0.8,3.0);
    glRotatef(0,0,0,1);
    glBegin(GL_QUADS);
	glVertex3f(0.25,-4.5,0.37);
        glVertex3f(0.25,-4.1,0.37); 
        glVertex3f(0.35,-4.1,0.37); 
        glVertex3f(0.35,-4.5,0.37);  
	
    glEnd();
  
    glPopMatrix();

    //---------------------------------------R (diagonal)

    glPushMatrix();
    glRotatef(xRotaded,1,0,0);
    glRotatef(yRotaded,0,1,0);
    glColor3f(255,255,255);
    glScalef(1.0,0.8,3.0);
    glRotatef(0,0,0,1);
    glBegin(GL_QUADS);
	glVertex3f(0.10,-4.5,0.37);
        glVertex3f(0.15,-4.4,0.37); 
        glVertex3f(0.35,-4.8,0.37); 
        glVertex3f(0.25,-4.8,0.37);  
	
    glEnd();
  
    glPopMatrix();
 
    //---------------------------------------G (barra)

    glPushMatrix();
    glRotatef(xRotaded,1,0,0);
    glRotatef(yRotaded,0,1,0);
    glColor3f(255,255,255);
    glScalef(1.0,0.8,3.0);
    glRotatef(0,0,0,1);
    glBegin(GL_QUADS);
    	glVertex3f(0.5,-4.1,0.37);
        glVertex3f(0.5,-4.8,0.37); 
        glVertex3f(0.4,-4.8,0.37); 
        glVertex3f(0.4,-4.1,0.37);  
  
	
    glEnd();
  
    glPopMatrix();
 
    //---------------------------------------G (cima)

    glPushMatrix();
    glRotatef(xRotaded,1,0,0);
    glRotatef(yRotaded,0,1,0);
    glColor3f(255,255,255);
    glScalef(1.0,0.8,3.0);
    glRotatef(0,0,0,1);
    glBegin(GL_QUADS);
	glVertex3f(0.4,-4.1,0.37);
        glVertex3f(0.75,-4.1,0.37); 
        glVertex3f(0.75,-4.2,0.37); 
        glVertex3f(0.4,-4.2,0.37);  
	
    glEnd();
  
    glPopMatrix();
 
    //---------------------------------------G (baixo)

    glPushMatrix();
    glRotatef(xRotaded,1,0,0);
    glRotatef(yRotaded,0,1,0);
    glColor3f(255,255,255);
    glScalef(1.0,0.8,3.0);
    glRotatef(0,0,0,1);
    glBegin(GL_QUADS);
	glVertex3f(0.4,-4.7,0.37);
        glVertex3f(0.75,-4.7,0.37); 
        glVertex3f(0.75,-4.8,0.37); 
        glVertex3f(0.4,-4.8,0.37);  
	
    glEnd();
  
    glPopMatrix();

    //---------------------------------------G (direita)

    glPushMatrix();
    glRotatef(xRotaded,1,0,0);
    glRotatef(yRotaded,0,1,0);
    glColor3f(255,255,255);
    glScalef(1.0,0.8,3.0);
    glRotatef(0,0,0,1);
    glBegin(GL_QUADS);
	glVertex3f(0.65,-4.35,0.37);
        glVertex3f(0.75,-4.35,0.37); 
        glVertex3f(0.75,-4.8,0.37); 
        glVertex3f(0.65,-4.8,0.37);  
	
    glEnd();
  
    glPopMatrix();

    //ECOMP

    //---------------------------------------E (barra)

    glPushMatrix();
    glRotatef(xRotaded,1,0,0);
    glRotatef(yRotaded,0,1,0);
    glColor3f(255,255,255);
    glScalef(1.0,0.8,3.0);
    glRotatef(0,0,0,1);
    glBegin(GL_QUADS);
    	glVertex3f(-1,1.75,0.37);
        glVertex3f(-1,0.95,0.37); 
        glVertex3f(-1.1,0.95,0.37); 
        glVertex3f(-1.1,1.75,0.37);  
    glEnd();
  
    glPopMatrix();

    //---------------------------------------E (cima)

    glPushMatrix();
    glRotatef(xRotaded,1,0,0);
    glRotatef(yRotaded,0,1,0);
    glColor3f(255,255,255);
    glScalef(1.0,0.8,3.0);
    glRotatef(0,0,0,1);
    glBegin(GL_QUADS);
    	glVertex3f(-1.1,1.75,0.37);
        glVertex3f(-1.1,1.65,0.37); 
        glVertex3f(-0.7,1.65,0.37); 
        glVertex3f(-0.7,1.75,0.37);  
    glEnd();
  
    glPopMatrix();

    //---------------------------------------E (baixo)

    glPushMatrix();
    glRotatef(xRotaded,1,0,0);
    glRotatef(yRotaded,0,1,0);
    glColor3f(255,255,255);
    glScalef(1.0,0.8,3.0);
    glRotatef(0,0,0,1);
    glBegin(GL_QUADS);
    	glVertex3f(-1.1,1.05,0.37);
        glVertex3f(-1.1,0.95,0.37); 
        glVertex3f(-0.7,0.95,0.37); 
        glVertex3f(-0.7,1.05,0.37);  
    glEnd();
  
    glPopMatrix();
 
    //---------------------------------------E (centro)

    glPushMatrix();
    glRotatef(xRotaded,1,0,0);
    glRotatef(yRotaded,0,1,0);
    glColor3f(255,255,255);
    glScalef(1.0,0.8,3.0);
    glRotatef(0,0,0,1);
    glBegin(GL_QUADS);
    	glVertex3f(-1.1,1.4,0.37);
        glVertex3f(-1.1,1.3,0.37); 
        glVertex3f(-0.8,1.3,0.37); 
        glVertex3f(-0.8,1.4,0.37);  
    glEnd();
  
    glPopMatrix();
  
    //---------------------------------------C (barra)

    glPushMatrix();
    glRotatef(xRotaded,1,0,0);
    glRotatef(yRotaded,0,1,0);
    glColor3f(255,255,255);
    glScalef(1.0,0.8,3.0);
    glRotatef(0,0,0,1);
    glBegin(GL_QUADS);
    	glVertex3f(-0.55,1.75,0.37);
        glVertex3f(-0.55,0.95,0.37); 
        glVertex3f(-0.65,0.95,0.37); 
        glVertex3f(-0.65,1.75,0.37);  
    glEnd();
  
    glPopMatrix();

    //---------------------------------------C (cima)

    glPushMatrix();
    glRotatef(xRotaded,1,0,0);
    glRotatef(yRotaded,0,1,0);
    glColor3f(255,255,255);
    glScalef(1.0,0.8,3.0);
    glRotatef(0,0,0,1);
    glBegin(GL_QUADS);
    	glVertex3f(-0.55,1.75,0.37);
        glVertex3f(-0.55,1.65,0.37); 
        glVertex3f(-0.25,1.65,0.37); 
        glVertex3f(-0.25,1.75,0.37);  
    glEnd();
  
    glPopMatrix();

    //---------------------------------------C (baixo)

    glPushMatrix();
    glRotatef(xRotaded,1,0,0);
    glRotatef(yRotaded,0,1,0);
    glColor3f(255,255,255);
    glScalef(1.0,0.8,3.0);
    glRotatef(0,0,0,1);
    glBegin(GL_QUADS);
    	glVertex3f(-0.55,1.05,0.37);
        glVertex3f(-0.55,0.95,0.37); 
        glVertex3f(-0.25,0.95,0.37); 
        glVertex3f(-0.25,1.05,0.37);  
    glEnd();
  
    glPopMatrix();

    //---------------------------------------O (barra)

    glPushMatrix();
    glRotatef(xRotaded,1,0,0);
    glRotatef(yRotaded,0,1,0);
    glColor3f(255,255,255);
    glScalef(1.0,0.8,3.0);
    glRotatef(0,0,0,1);
    glBegin(GL_QUADS);
    	glVertex3f(-0.1,1.75,0.37);
        glVertex3f(-0.1,0.95,0.37); 
        glVertex3f(-0.2,0.95,0.37); 
        glVertex3f(-0.2,1.75,0.37);  
    glEnd();
  
    glPopMatrix();

    //---------------------------------------O (cima)

    glPushMatrix();
    glRotatef(xRotaded,1,0,0);
    glRotatef(yRotaded,0,1,0);
    glColor3f(255,255,255);
    glScalef(1.0,0.8,3.0);
    glRotatef(0,0,0,1);
    glBegin(GL_QUADS);
    	glVertex3f(0.2,1.75,0.37);
        glVertex3f(0.2,1.65,0.37); 
        glVertex3f(-0.2,1.65,0.37); 
        glVertex3f(-0.2,1.75,0.37);  
    glEnd();
  
    glPopMatrix();

    //---------------------------------------O (baixo)

    glPushMatrix();
    glRotatef(xRotaded,1,0,0);
    glRotatef(yRotaded,0,1,0);
    glColor3f(255,255,255);
    glScalef(1.0,0.8,3.0);
    glRotatef(0,0,0,1);
    glBegin(GL_QUADS);
    	glVertex3f(-0.2,1.05,0.37);
        glVertex3f(-0.2,0.95,0.37); 
        glVertex3f(0.2,0.95,0.37); 
        glVertex3f(0.2,1.05,0.37);  
    glEnd();
  
    glPopMatrix();

    //---------------------------------------O (direita)

    glPushMatrix();
    glRotatef(xRotaded,1,0,0);
    glRotatef(yRotaded,0,1,0);
    glColor3f(255,255,255);
    glScalef(1.0,0.8,3.0);
    glRotatef(0,0,0,1);
    glBegin(GL_QUADS);
    	glVertex3f(0.2,1.75,0.37);
        glVertex3f(0.2,0.95,0.37); 
        glVertex3f(0.1,0.95,0.37); 
        glVertex3f(0.1,1.75,0.37);  
    glEnd();
  
    glPopMatrix();

    //---------------------------------------M (barra)

    glPushMatrix();
    glRotatef(xRotaded,1,0,0);
    glRotatef(yRotaded,0,1,0);
    glColor3f(255,255,255);
    glScalef(1.0,0.8,3.0);
    glRotatef(0,0,0,1);
    glBegin(GL_QUADS);
    	glVertex3f(0.25,1.75,0.37);
        glVertex3f(0.25,0.95,0.37); 
        glVertex3f(0.35,0.95,0.37); 
        glVertex3f(0.35,1.75,0.37);  
    glEnd();
  
    glPopMatrix();

    //---------------------------------------M (diagonal esquerda)

    glPushMatrix();
    glRotatef(xRotaded,1,0,0);
    glRotatef(yRotaded,0,1,0);
    glColor3f(255,255,255);
    glScalef(1.0,0.8,3.0);
    glRotatef(0,0,0,1);
    glBegin(GL_QUADS);
    	glVertex3f(0.25,1.75,0.37);
        glVertex3f(0.35,1.75,0.37); 
        glVertex3f(0.5,1.25,0.37); 
        glVertex3f(0.5,0.95,0.37);  
    glEnd();
  
    glPopMatrix();

    //---------------------------------------M (diagonal direita)

    glPushMatrix();
    glRotatef(xRotaded,1,0,0);
    glRotatef(yRotaded,0,1,0);
    glColor3f(255,255,255);
    glScalef(1.0,0.8,3.0);
    glRotatef(0,0,0,1);
    glBegin(GL_QUADS);
    	glVertex3f(0.65,1.75,0.37);
        glVertex3f(0.75,1.75,0.37); 
        glVertex3f(0.5,0.95,0.37); 
        glVertex3f(0.5,1.25,0.37);  
    glEnd();
  
    glPopMatrix();

    //---------------------------------------M (direita)

    glPushMatrix();
    glRotatef(xRotaded,1,0,0);
    glRotatef(yRotaded,0,1,0);
    glColor3f(255,255,255);
    glScalef(1.0,0.8,3.0);
    glRotatef(0,0,0,1);
    glBegin(GL_QUADS);
    	glVertex3f(0.75,1.75,0.37);
        glVertex3f(0.75,0.95,0.37); 
        glVertex3f(0.65,0.95,0.37); 
        glVertex3f(0.65,1.75,0.37);  
    glEnd();
  
    glPopMatrix();

    //---------------------------------------P (barra)

    glPushMatrix();
    glRotatef(xRotaded,1,0,0);
    glRotatef(yRotaded,0,1,0);
    glColor3f(255,255,255);
    glScalef(1.0,0.8,3.0);
    glRotatef(0,0,0,1);
    glBegin(GL_QUADS);
    	glVertex3f(0.9,1.75,0.37);
        glVertex3f(0.9,0.95,0.37); 
        glVertex3f(0.8,0.95,0.37); 
        glVertex3f(0.8,1.75,0.37);  
    glEnd();
  
    glPopMatrix();

    //---------------------------------------P (cima)

    glPushMatrix();
    glRotatef(xRotaded,1,0,0);
    glRotatef(yRotaded,0,1,0);
    glColor3f(255,255,255);
    glScalef(1.0,0.8,3.0);
    glRotatef(0,0,0,1);
    glBegin(GL_QUADS);
    	glVertex3f(0.8,1.75,0.37);
        glVertex3f(1.2,1.75,0.37); 
        glVertex3f(1.2,1.65,0.37); 
        glVertex3f(0.8,1.65,0.37);  
    glEnd();
  
    glPopMatrix();

    //---------------------------------------P (centro)

    glPushMatrix();
    glRotatef(xRotaded,1,0,0);
    glRotatef(yRotaded,0,1,0);
    glColor3f(255,255,255);
    glScalef(1.0,0.8,3.0);
    glRotatef(0,0,0,1);
    glBegin(GL_QUADS);
    	glVertex3f(0.8,1.4,0.37);
        glVertex3f(1.2,1.4,0.37); 
        glVertex3f(1.2,1.3,0.37); 
        glVertex3f(0.8,1.3,0.37);  
    glEnd();
  
    glPopMatrix();

    //---------------------------------------P (direita)

    glPushMatrix();
    glRotatef(xRotaded,1,0,0);
    glRotatef(yRotaded,0,1,0);
    glColor3f(255,255,255);
    glScalef(1.0,0.8,3.0);
    glRotatef(0,0,0,1);
    glBegin(GL_QUADS);
    	glVertex3f(1.1,1.75,0.37);
        glVertex3f(1.2,1.75,0.37); 
        glVertex3f(1.2,1.3,0.37); 
        glVertex3f(1.1,1.3,0.37);  
    glEnd();
  
    glPopMatrix();

    //USB

    //---------------------------------------triângulo superior

    glPushMatrix();
    glRotatef(xRotaded,1,0,0);
    glRotatef(yRotaded,0,1,0);
    glColor3f(0,0,0);
    glScalef(2.55,2.55,3.0);
    glRotatef(0,0,0,1);
    glBegin(GL_POLYGON);
        glVertex3f(-0.03,0.20,0.4);
        glVertex3f(-0.13,0.05,0.4);
	glVertex3f(0.07,0.05,0.4);
    glEnd();
  
    glPopMatrix();

    //---------------------------------------quadrado direita

    glPushMatrix();
    glRotatef(xRotaded,1,0,0);
    glRotatef(yRotaded,0,1,0);
    glColor3f(0,0,0);
    glScalef(2.55,2.55,3.0);
    glRotatef(0,0,0,1);
    glBegin(GL_QUADS);
        glVertex3f(0.25,-0.12,0.38);
        glVertex3f(0.25,-0.27,0.38);
	glVertex3f(0.4,-0.27,0.38);
	glVertex3f(0.4,-0.12,0.38);
    glEnd();
  
    glPopMatrix();

    //---------------------------------------circulo esquerda

    glPushMatrix();
    glRotatef(xRotaded,1,0,0);
    glRotatef(yRotaded,0,1,0);
    glColor3f(0,0,0);
    glScalef(2.55,2.55,3.0);
    glRotatef(0,0,0,1);
 
    Circulo(-0.388, -0.45, 0.38, 0.08);    

    glEnd();
  
    glPopMatrix();

    //---------------------------------------circulo baixo

    glPushMatrix();
    glRotatef(xRotaded,1,0,0);
    glRotatef(yRotaded,0,1,0);
    glColor3f(0,0,0);
    glScalef(2.55,2.55,3.0);
    glRotatef(0,0,0,1);
 
    Circulo(-0.03, -1.17, 0.38, 0.09);    

    glEnd();
  
    glPopMatrix();

    //---------------------------------------cabo central

    glPushMatrix();
    glRotatef(xRotaded,1,0,0);
    glRotatef(yRotaded,0,1,0);
    glColor3f(0,0,0);
    glScalef(2.55,2.55,3.0);
    glRotatef(0,0,0,1);
    glBegin(GL_QUADS);
        glVertex3f(0.0,0.12,0.4);
        glVertex3f(0.0,-1.2,0.4);
	glVertex3f(-0.06,-1.2,0.4);
	glVertex3f(-0.06,0.12,0.4);
    glEnd();
  
    glPopMatrix();

    //---------------------------------------cabo direita cima

    glPushMatrix();
    glRotatef(xRotaded,1,0,0);
    glRotatef(yRotaded,0,1,0);
    glColor3f(0,0,0);
    glScalef(2.55,2.55,3.0);
    glRotatef(0,0,0,1);
    glBegin(GL_QUADS);
        glVertex3f(0.295,-0.195,0.39);
        glVertex3f(0.355,-0.195,0.39);
	glVertex3f(0.355,-0.45,0.39);
	glVertex3f(0.295,-0.42,0.39);
    glEnd();
  
    glPopMatrix();

    //---------------------------------------cabo direita diagonal

    glPushMatrix();
    glRotatef(xRotaded,1,0,0);
    glRotatef(yRotaded,0,1,0);
    glColor3f(0,0,0);
    glScalef(2.55,2.55,3.0);
    glRotatef(0,0,0,1);
    glBegin(GL_QUADS);
        glVertex3f(0.0,-0.575,0.39);
        glVertex3f(0.0,-0.645,0.39);
	glVertex3f(0.355,-0.45,0.39);
	glVertex3f(0.295,-0.42,0.39);
    glEnd();
  
    glPopMatrix();

    //---------------------------------------cabo esquerda cima

    glPushMatrix();
    glRotatef(xRotaded,1,0,0);
    glRotatef(yRotaded,0,1,0);
    glColor3f(0,0,0);
    glScalef(2.55,2.55,3.0);
    glRotatef(0,0,0,1);
    glBegin(GL_QUADS);
        glVertex3f(-0.418,-0.47,0.39);
        glVertex3f(-0.358,-0.47,0.39);
	glVertex3f(-0.358,-0.685,0.39);
	glVertex3f(-0.418,-0.715,0.39);
    glEnd();
  
    glPopMatrix();

    //---------------------------------------cabo esquerda diagonal

    glPushMatrix();
    glRotatef(xRotaded,1,0,0);
    glRotatef(yRotaded,0,1,0);
    glColor3f(0,0,0);
    glScalef(2.55,2.55,3.0);
    glRotatef(0,0,0,1);
    glBegin(GL_QUADS);
        glVertex3f(-0.06,-0.795,0.4);
	glVertex3f(-0.06,-0.855,0.4);
	glVertex3f(-0.418,-0.715,0.4);
	glVertex3f(-0.358,-0.685,0.4);
    glEnd();
  
    glPopMatrix();

    glFlush();
    glutPostRedisplay();
    glutSwapBuffers();

}

//-----------------Função principal

int main(int argc, char **argv) {
    glutInit(&argc, argv); 
    glutInitWindowSize(800,600);
    glutCreateWindow("Logo Moletom");
    glutSpecialFunc(teclado);
    glutDisplayFunc(display);
    init();
    glutReshapeFunc(reshape);
    glutMainLoop();
    return 0;
}
