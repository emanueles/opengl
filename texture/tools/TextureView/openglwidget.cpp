#include "openglwidget.h"

#ifdef __APPLE__
    #include <GLUT/glut.h>
    #include <OpenGL/OpenGL.h>
#else
    #include <GL/glut.h>
#endif

extern "C"
{
    unsigned * read_texture(const char *name, int *width, int *height, int *components);
    GLubyte* readPPM(char* filename, int* width, int* height);
    unsigned * loadTGA(const char* filename, int* width, int* height, int* components);
}

OpenGLWidget::OpenGLWidget(QWidget *parent) :
    QGLWidget(parent)
{
    loadedtext = false;
    texture = NULL;
    texture_h = 0;
    texture_w = 0;
    texture_c = 0;
}

void OpenGLWidget::initializeGL(){
    glShadeModel(GL_FLAT);
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glEnable(GL_DEPTH_TEST);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

void OpenGLWidget::resizeGL(int w, int h){
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (GLfloat) w/(GLfloat) h, 1.0, 30.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0, 0.0, -3.6);
}

void OpenGLWidget::paintGL(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    if (loadedtext){
        glEnable(GL_TEXTURE_2D);
        glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
        glBindTexture(GL_TEXTURE_2D, texName);
        glBegin(GL_QUADS);
            glTexCoord2f(0.0, 0.0); glVertex3f(-2.0, -2.0, 0.0);
            glTexCoord2f(0.0, 1.0); glVertex3f(-2.0,  2.0, 0.0);
            glTexCoord2f(1.0, 1.0); glVertex3f( 2.0,  2.0, 0.0);
            glTexCoord2f(1.0, 0.0); glVertex3f( 2.0, -2.0, 0.0);
        glEnd();
        glFlush();
        glDisable(GL_TEXTURE_2D);
    } else{
        glBegin(GL_QUADS);
            glVertex3f(-2.0, -2.0, 0.0);
            glVertex3f(-2.0,  2.0, 0.0);
            glVertex3f( 2.0,  2.0, 0.0);
            glVertex3f( 2.0, -2.0, 0.0);
        glEnd();
        glFlush();
    }
}

void OpenGLWidget::setTexture(const char *name){
    texture = read_texture(name, &texture_w, &texture_h, &texture_c);
    glGenTextures(1, &texName);
    glBindTexture(GL_TEXTURE_2D, texName);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, texture_c, texture_w, texture_h, 0, GL_RGBA, GL_UNSIGNED_BYTE,
                  texture);
    this->loadedtext = true;
    this->updateGL();
}

void OpenGLWidget::setBumpMap(const char *name){
    texture = loadTGA(name, &texture_w, &texture_h, &texture_c);
    glGenTextures(1, &texName);
    glBindTexture(GL_TEXTURE_2D, texName);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, texture_c, texture_w, texture_h, 0, GL_RGB, GL_UNSIGNED_BYTE,
                  texture);
    this->loadedtext = true;
    this->updateGL();
}

