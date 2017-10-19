#include <math.h>
#include <stdlib.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include "imageloader.h"

GLuint _textureBrick, _textureDoor, _textureGrass, _textureRoof, _textureWindow,
    _textureSky, _textureWorld, _textureOlho, _textureOlho1;
GLUquadric *quad;

// actual vector representing the camera's direction
float lx=0.0f, lz=-1.0f;
// XZ position of the camera
float x=0.0f, z=5.0f;

// all variables initialized to 1.0, meaning
// the triangle will initially be white
float red=1.0f, blue=1.0f, green=1.0f;

// angle for rotating triangle
float angle = 0.0f, _angle = 1.0f;

static void resize(int width, int height){
    const float ar = (float) width / (float) height;
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    gluPerspective(45.0f, ar, 0.1f, 100.0f);
    glLoadIdentity();
    glFrustum(-ar, ar, -1.0, 1.0, 2.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void createCube(){
    glPushMatrix ();
        glBindTexture(GL_TEXTURE_2D, _textureSky);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        /*Lado multicolorido - Frente
        glBegin(GL_QUADS);
            glTexCoord3f(0.0,1.0,0.1);	glVertex3f(  1.0, -1.0, -1.0 );
            glTexCoord3f(1.0,1.0,0.1);	glVertex3f(  1.0,  1.0, -1.0 );
            glTexCoord3f(1.0,0.0,0.1);	glVertex3f( -1.0,  1.0, -1.0 );
            glTexCoord3f(0.0,0.0,0.1);	glVertex3f( -1.0, -1.0, -1.0 );
        glEnd();

        // Lado branco - TRASEIRA
        glBegin(GL_QUADS);
            glVertex3f(  1.0, -1.0, 1.0 );
            glVertex3f(  1.0,  1.0, 1.0 );
            glVertex3f( -1.0,  1.0, 1.0 );
            glVertex3f( -1.0, -1.0, 1.0 );
        glEnd();

        // Lado roxo - DIREITA
        glBegin(GL_QUADS);
            glVertex3f( 1.0, -1.0, -1.0 );
            glVertex3f( 1.0,  1.0, -1.0 );
            glVertex3f( 1.0,  1.0,  1.0 );
            glVertex3f( 1.0, -1.0,  1.0 );
        glEnd();

        // Lado verde - ESQUERDA
        glBegin(GL_QUADS);
            glVertex3f( -1.0, -1.0,  1.0 );
            glVertex3f( -1.0,  1.0,  1.0 );
            glVertex3f( -1.0,  1.0, -1.0 );
            glVertex3f( -1.0, -1.0, -1.0 );
        glEnd();

        // Lado azul - TOPO
        glBegin(GL_QUADS);
            glVertex3f(  1.0,  1.0,  1.0 );
            glVertex3f(  1.0,  1.0, -1.0 );
            glVertex3f( -1.0,  1.0, -1.0 );
            glVertex3f( -1.0,  1.0,  1.0 );
        glEnd();
        */

        // Lado vermelho - BASE
        glBegin(GL_QUADS);
            glVertex3f(  1.0, -1.0, -1.0 );
            glVertex3f(  1.0, -1.0,  1.0 );
            glVertex3f( -1.0, -1.0,  1.0 );
            glVertex3f( -1.0, -1.0, -1.0 );
        glEnd();
    glPopMatrix ();
}

void createWorld(){
    const double t = glutGet(GLUT_ELAPSED_TIME) / 1000.0; // glutGet(GLUT_ELAPSED_TIME) = Retorna o número de milissegundos desde que GlutInit foi chamado.
    const double a = t*90.0;

    // Draw Body
    glPushMatrix();
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, _textureWorld);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glTranslatef(0.0f, 25.0f, -45.0f);
        glRotated(180,1,0,0);
        glRotated(a,0,1,0);
        gluQuadricTexture(quad,1);
        gluSphere(quad, 5, 1024, 512);
    glPopMatrix();
}

void createHouse(){
    // Grass
    glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, _textureGrass);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTranslatef(0,0,-6);
        //glRotatef(_angle, 0.0, 1.0, 0.0);
        glBegin(GL_QUADS);
            glTexCoord3f(0.0,70.0,1);  glVertex3f(-50,-1.5,50);
            glTexCoord3f(0.0,0.0,-1);  glVertex3f(-50,-1.5,-50);
            glTexCoord3f(70.0,0.0,-1);  glVertex3f(50,-1.5,-50);
            glTexCoord3f(70.0,70.0,1);  glVertex3f(50,-1.5,50);
        glEnd();
    glPopMatrix();

    // Front side
    glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, _textureBrick);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTranslatef(0,0,-6);
        //glRotatef(_angle, 0.0, 1.0, 0.0);
        glBegin(GL_QUADS);  // Wall
            glTexCoord3f(0.0,2.0,0.1);  glVertex3f(-2,0,1);
            glTexCoord3f(4.0,2.0,0.1);  glVertex3f(2,0,1);
            glTexCoord3f(4.0,0.0,0.1);  glVertex3f(2,-1.5,1);
            glTexCoord3f(0.0,0.0,0.1);  glVertex3f(-2,-1.5,1);
        glEnd();

        glBindTexture(GL_TEXTURE_2D, _textureRoof);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glBegin(GL_QUADS);  // Roof
            glTexCoord3f(0.0,2.0,0); glVertex3f(-2.2,0.5,0);
            glTexCoord3f(4.0,2.0,0);glVertex3f(2.2,0.5,0);
            glTexCoord3f(4.0,0.0,1.25); glVertex3f(2.2,-0.1,1.25);
            glTexCoord3f(0.0,0.0,1.25); glVertex3f(-2.2,-0.1,1.25);
        glEnd();

        glBindTexture(GL_TEXTURE_2D, _textureDoor);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glBegin(GL_QUADS);  // Door
            glTexCoord3f(0.0,1.0,1.0001); glVertex3f(-0.3,-0.4,1.0001);
            glTexCoord3f(1.0,1.0,1.0001); glVertex3f(0.3,-0.4,1.0001);
            glTexCoord3f(1.0,0.0,1.0001); glVertex3f(0.3,-1.5,1.0001);
            glTexCoord3f(0.0,0.0,1.0001); glVertex3f(-0.3,-1.5,1.0001);
        glEnd();

        glBindTexture(GL_TEXTURE_2D, _textureWindow);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glBegin(GL_QUADS);  // Window Left
            glTexCoord3f(0.0,1.0,1.0001); glVertex3f(-1.5,-0.3,1.0001);
            glTexCoord3f(1.0,1.0,1.0001); glVertex3f(-0.75,-0.3,1.0001);
            glTexCoord3f(1.0,0.0,1.0001); glVertex3f(-0.75,-0.8,1.0001);
            glTexCoord3f(0.0,0.0,1.0001); glVertex3f(-1.5,-0.8,1.0001);
        glEnd();

        glBegin(GL_QUADS);  // Window Right
            glTexCoord3f(0.0,1.0,1.0001); glVertex3f(1.5,-0.3,1.0001);
            glTexCoord3f(1.0,1.0,1.0001); glVertex3f(0.75,-0.3,1.0001);
            glTexCoord3f(1.0,0.0,1.0001); glVertex3f(0.75,-0.8,1.0001);
            glTexCoord3f(0.0,0.0,1.0001); glVertex3f(1.5,-0.8,1.0001);
        glEnd();
    glPopMatrix();

    // Back side
    glPushMatrix();
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, _textureBrick);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTranslatef(0,0,-6);
        //glRotatef(_angle, 0.0, 1.0, 0.0);
        glBegin(GL_QUADS);  // Wall
            glTexCoord3f(0.0,2.0,-1);  glVertex3f(-2,0,-1);
            glTexCoord3f(4.0,2.0,-1);  glVertex3f(2,0,-1);
            glTexCoord3f(4.0,0.0,-1);  glVertex3f(2,-1.5,-1);
            glTexCoord3f(0.0,0.0,-1);  glVertex3f(-2,-1.5,-1);
        glEnd();

        glBindTexture(GL_TEXTURE_2D, _textureRoof);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glBegin(GL_QUADS);  // Roof
            glTexCoord3f(0.0,2.0,0); glVertex3f(-2.2,0.5,0);
            glTexCoord3f(4.0,2.0,0);glVertex3f(2.2,0.5,0);
            glTexCoord3f(4.0,0.0,-1.25); glVertex3f(2.2,-0.1,-1.25);
            glTexCoord3f(0.0,0.0,-1.25); glVertex3f(-2.2,-0.1,-1.25);
        glEnd();

        glBindTexture(GL_TEXTURE_2D, _textureWindow);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glBegin(GL_QUADS);  // Window Left
            glTexCoord3f(0.0,1.0,-1.0001); glVertex3f(-1.5,-0.3,-1.0001);
            glTexCoord3f(1.0,1.0,-1.0001); glVertex3f(-0.75,-0.3,-1.0001);
            glTexCoord3f(1.0,0.0,-1.0001); glVertex3f(-0.75,-0.8,-1.0001);
            glTexCoord3f(0.0,0.0,-1.0001); glVertex3f(-1.5,-0.8,-1.0001);
        glEnd();

        glBegin(GL_QUADS);  // Window Right
            glTexCoord3f(0.0,1.0,1.0001); glVertex3f(1.5,-0.3,-1.0001);
            glTexCoord3f(1.0,1.0,1.0001); glVertex3f(0.75,-0.3,-1.0001);
            glTexCoord3f(1.0,0.0,1.0001); glVertex3f(0.75,-0.8,-1.0001);
            glTexCoord3f(0.0,0.0,1.0001); glVertex3f(1.5,-0.8,-1.0001);
        glEnd();
    glPopMatrix();

    // Right side
    glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, _textureBrick);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTranslatef(0,0,-6);
        //glRotatef(_angle, 0.0, 1.0, 0.0);
        glBegin(GL_QUADS);  // Wall
            glTexCoord3f(0.0,2.0,1); glVertex3f(2,0,1);
            glTexCoord3f(2.0,2.0,-1); glVertex3f(2,0,-1);
            glTexCoord3f(2.0,0.0,-1); glVertex3f(2,-1.5,-1);
            glTexCoord3f(0.0,0.0,1); glVertex3f(2,-1.5,1);
        glEnd();

        glBegin(GL_TRIANGLES);  // Wall Upper
            glTexCoord3f(0.0,1.0,0); glVertex3f(2,0.5,0);
            glTexCoord3f(1.0,0.0,1); glVertex3f(2,0,1);
            glTexCoord3f(-1.0,0.0,-1); glVertex3f(2,0,-1);
        glEnd();
    glPopMatrix();

    // Left side
    glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, _textureBrick);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTranslatef(0,0,-6);
        //glRotatef(_angle, 0.0, 1.0, 0.0);
        glBegin(GL_QUADS);  // Wall
            glTexCoord3f(0.0,2.0,1);    glVertex3f(-2,0,1);
            glTexCoord3f(2.0,2.0,-1);    glVertex3f(-2,0,-1);
            glTexCoord3f(2.0,0.0,-1);    glVertex3f(-2,-1.5,-1);
            glTexCoord3f(0.0,0.0,1);    glVertex3f(-2,-1.5,1);
        glEnd();

        glBegin(GL_TRIANGLES);  // Wall Upper
            glTexCoord3f(0.0,1.0,0);    glVertex3f(-2,0.5,0);
            glTexCoord3f(1.0,0.0,1);    glVertex3f(-2,0,1);
            glTexCoord3f(-1.0,0.0,-1);    glVertex3f(-2,0,-1);
        glEnd();
    glPopMatrix();
}

void createSnowMan(){
    glScalef(5.0f, 5.0f, 5.0f);
    glTranslatef(5.0f, -3.0f, -8.0f);
    glPushMatrix();
        // Draw Head
        glTranslatef(0.0f, 1.0f, 0.0f);
        glutSolidSphere(0.4f, 20, 20);

        //Draw Body
        glTranslatef(0.0f, 1.0f, 0.0f);
        glTranslatef(0.0f, -2.3f, 0.0f);
        glutSolidSphere(1.0f, 40, 40);
    glPopMatrix();
}

void createBall(){

    int slices = 20;
    int stacks = 20;

    const double t = glutGet(GLUT_ELAPSED_TIME) / 1000.0; // glutGet(GLUT_ELAPSED_TIME) = Retorna o número de milissegundos desde que GlutInit foi chamado.
    const double a = t*90.0;

    //glColor3d(1,0,1);

    //Esfera
    glPushMatrix();
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, _textureOlho);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glTranslated(-15.0f,25.0f,-45.0f);
        glRotated(180,1,0,0);
        glRotated(a,0,1,0); //glRotated(a,0,0,1);
        gluSphere(quad, 4,slices,stacks);
    glPopMatrix();

    //Anel
    glPushMatrix();
        glTranslated(-15.0f,25.0f,-45.0f);
        glRotated(90,1,0,0);
        glutSolidTorus(0.8,5.5,slices,stacks);
    glPopMatrix();
}

void renderScene() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_TEXTURE_2D);

    // Reset transformations
    glLoadIdentity();

    // Set the camera
    gluLookAt( x, 1.0f, z,
               x+lx, _angle, z+lz,
               0.0f, 1.0f, 0.0f);

    /*SKY
    glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, _textureSky);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTranslatef(0, 0, -10);
        glBegin(GL_QUADS);
            glTexCoord3f(0.0,1.0,0.1);  glVertex3f(-10,10,0);
            glTexCoord3f(1.0,1.0,0.1);  glVertex3f(10,10,0);
            glTexCoord3f(1.0,0.0,0.1);  glVertex3f(10,-10,0);
            glTexCoord3f(0.0,0.0,0.1);  glVertex3f(-10,-10,0);
        glEnd();
    glPopMatrix();*/

    //Create SnowMan
    glPushMatrix();
        /*glScalef(5.0, 5.0, 5.0);
        glTranslatef(0.0f, -3.0f, 0.0f);*/
        createSnowMan();
    glPopMatrix();

    //Create Sky
    glPushMatrix();
        glScalef(80.0, 80.0, 80.0);
        createCube();
    glPopMatrix();

    //Create House
    glPushMatrix();
        glScalef(8.0, 10.0, 8.0);
        createHouse();
    glPopMatrix();

    //Create World
    glPushMatrix();
        createWorld();
    glPopMatrix();

    glPushMatrix();
        createBall();
    glPopMatrix();

    /*ILUMINAÇÃO
    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);*/

    glutSwapBuffers();
}

void processNormalKeys(unsigned char key, int x, int y){
    float fraction = 0.05f;

    switch(key){
        case 'w':
            _angle += fraction;
            break;
        case 's':
            _angle -= fraction;
            break;
        case 27:
            exit(0);
    }

    glutPostRedisplay();
}

void processSpecialKeys(int key, int xx, int yy){
    float fraction = 0.5f;
    float angleL = 0.05f;

    switch (key){
        case GLUT_KEY_LEFT :
            angle -= angleL;
            lx = sin(angle);
            lz = -cos(angle);
            break;
        case GLUT_KEY_RIGHT :
            angle += angleL;
            lx = sin(angle);
            lz = -cos(angle);
            break;
        case GLUT_KEY_UP :
            x += lx * fraction;
            z += lz * fraction;
            break;
        case GLUT_KEY_DOWN :
            x -= lx * fraction;
            z -= lz * fraction;
            break;
    }
}

GLuint loadTexture(Image* image) {
	GLuint textureId;
	glGenTextures(1, &textureId); //Make room for our texture
	glBindTexture(GL_TEXTURE_2D, textureId); //Tell OpenGL which texture to edit
	//Map the image to the texture
	glTexImage2D(GL_TEXTURE_2D,                //Always GL_TEXTURE_2D
				 0,                            //0 for now
				 GL_RGB,                       //Format OpenGL uses for image
				 image->width, image->height,  //Width and height
				 0,                            //The border of the image
				 GL_RGB, //GL_RGB, because pixels are stored in RGB format
				 GL_UNSIGNED_BYTE, //GL_UNSIGNED_BYTE, because pixels are stored
				                   //as unsigned numbers
				 image->pixels);               //The actual pixel data
	return textureId; //Returns the id of the texture
}

void Initialize() {
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);

	quad = gluNewQuadric();

	Image* image = loadBMP("C:\\Users\\hayness\\Documents\\OpenGL\\3D-House-using-OpenGL-and-C--master\\bricks.bmp");
	_textureBrick = loadTexture(image);
	image = loadBMP("C:\\Users\\hayness\\Documents\\OpenGL\\3D-House-using-OpenGL-and-C--master\\door.bmp");
	_textureDoor = loadTexture(image);
	image = loadBMP("C:\\Users\\hayness\\Documents\\OpenGL\\3D-House-using-OpenGL-and-C--master\\grass.bmp");
	_textureGrass = loadTexture(image);
	image = loadBMP("C:\\Users\\hayness\\Documents\\OpenGL\\3D-House-using-OpenGL-and-C--master\\roof.bmp");
	_textureRoof = loadTexture(image);
	image = loadBMP("C:\\Users\\hayness\\Documents\\OpenGL\\3D-House-using-OpenGL-and-C--master\\window.bmp");
	_textureWindow = loadTexture(image);
	image = loadBMP("C:\\Users\\hayness\\Documents\\OpenGL\\3D-House-using-OpenGL-and-C--master\\sky.bmp");
	_textureSky = loadTexture(image);
	image = loadBMP("C:\\Users\\hayness\\Documents\\OpenGL\\3D-House-using-OpenGL-and-C--master\\worldtex.bmp");
	_textureWorld = loadTexture(image);

	image = loadBMP("C:\\Users\\hayness\\Documents\\OpenGL\\3D-House-using-OpenGL-and-C--master\\saturnmap.bmp");
	_textureOlho = loadTexture(image);
	image = loadBMP("C:\\Users\\hayness\\Documents\\OpenGL\\3D-House-using-OpenGL-and-C--master\\saturnringmap.bmp");
	_textureOlho1 = loadTexture(image);




	delete image;
}

const GLfloat light_ambient[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_position[] = { 2.0f, 5.0f, 5.0f, 0.0f };

const GLfloat mat_ambient[]    = { 0.7f, 0.7f, 0.7f, 1.0f };
const GLfloat mat_diffuse[]    = { 0.8f, 0.8f, 0.8f, 1.0f };
const GLfloat mat_specular[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat high_shininess[] = { 100.0f };


int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(50,50);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Trabalho Lucio");
	glEnable(GL_DEPTH_TEST);

	glutDisplayFunc(renderScene);
	glutReshapeFunc(resize);
	glutIdleFunc(renderScene);
	glutKeyboardFunc(processNormalKeys);
    glutSpecialFunc(processSpecialKeys);
    glEnable(GL_DEPTH_TEST);

    /*ILUMINAÇÃO
    glDepthFunc(GL_LESS);

    glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);*/

	Initialize();

	glutMainLoop();

	return 0;
}
