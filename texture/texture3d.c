/*  texture3d.c
 *  This program demonstrates using a three-dimensional texture.
 *  It creates a 3D texture and then renders two rectangles
 *  with different texture coordinates to obtain different
 *  "slices" of the 3D texture.
 *
 * cc -o texture3d texture3d.c -lGLU -lGL -lglut -lXext -lX11 -lm
 * On a Mac:
 * cc -o texture3d texture3d.c -framework GLUT -framework OpenGL
 */
#include <stdlib.h>
#include <stdio.h>
#ifdef __APPLE__
    #include <GLUT/glut.h>
    #include <OpenGL/OpenGL.h>
#else
    #include <GL/glut.h>
#endif

#ifdef GL_VERSION_1_2
#define iWidth 16
#define iHeight 16
#define iDepth 16
static GLubyte image[iDepth][iHeight][iWidth][3];

static GLuint texName;
/* Create a 16x16x16x3 array with different color values in
 * each array element [r, g, b]. Values range from 0 to 255. 
*/ 
void makeImage(void){
	int s, t, r;
	for(s=0; s < iWidth; s++) {
		for(t=0; t < iHeight; t++) {
			for(r=0; r < iDepth; r++) {
				image[r][t][s][0] = s * 17;
				image[r][t][s][1] = t * 17;
				image[r][t][s][2] = r * 17;
			}
		}
	}
}

/* Initialize state: 3D texture object and its image */
void init(void){
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_FLAT);
	
	makeImage();
	
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	
	glGenTextures(1, &texName);
	glBindTexture(GL_TEXTURE_3D, texName);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_R, GL_CLAMP);
	
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glTexImage3D(GL_TEXTURE_3D, 0, GL_RGB, iWidth, iHeight, iDepth,
				 0, GL_RGB, GL_UNSIGNED_BYTE, image);
				  		
	glEnable(GL_TEXTURE_3D);
}

void display(void){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glBegin(GL_QUADS);
	   glTexCoord3f(0.0, 0.0, 0.0); glVertex3f(-2.25, -1.0, 0.0);
	   glTexCoord3f(0.0, 1.0, 0.0); glVertex3f(-2.25, 1.0, 0.0);
	   glTexCoord3f(1.0, 1.0, 1.0); glVertex3f(-0.25, 1.0, 0.0);
	   glTexCoord3f(1.0, 0.0, 1.0); glVertex3f(-0.25, -1.0, 0.0);

	   glTexCoord3f(0.0, 0.0, 1.0); glVertex3f(0.25, -1.0, 0.0);
	   glTexCoord3f(0.0, 1.0, 1.0); glVertex3f(0.25, 1.0, 0.0);
	   glTexCoord3f(1.0, 1.0, 0.0); glVertex3f(2.25, 1.0, 0.0);
	   glTexCoord3f(1.0, 0.0, 0.0); glVertex3f(2.25, -1.0, 0.0);
	glEnd();
	glFlush();

}

void reshape(int w, int h){
	glViewport(0, 0, (GLsizei) w, (GLsizei) h);
	glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
	gluPerspective(60.0, (GLfloat) w/(GLfloat) h, 1.0, 30.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0, 0.0, -4.0);
}

void keyboard (unsigned char key, int x, int y){
	switch (key) {
       case 27:
         exit(0);
         break;
      default:
         break;
   }
}

int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
   glutInitWindowSize(250, 250);
   glutInitWindowPosition(100, 100);
   glutCreateWindow(argv[0]);
   init();
   glutDisplayFunc(display);
   glutReshapeFunc(reshape);
   glutKeyboardFunc(keyboard);
   glutMainLoop();
   return 0; 
}
#else
int main(int argc, char** argv)
{
    fprintf (stderr, "This program demonstrates a feature which is not in OpenGL Version 1.0 or 1.1.\n");
    fprintf (stderr, "If your implementation of OpenGL has the right extensions,\n");
    fprintf (stderr, "you may be able to modify this program to make it run.\n");
    return 0;
}
#endif
