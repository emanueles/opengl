#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include <QGLWidget>

class OpenGLWidget : public QGLWidget
{
    Q_OBJECT
public:
    explicit OpenGLWidget(QWidget *parent = 0);
    void setTexture(const char *name);
    void setBumpMap(const char *name);
protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

signals:
    
public slots:
    
private:
    bool loadedtext;
    GLuint texName;
    unsigned *texture;
    int texture_h;
    int texture_w;
    int texture_c;
};

#endif // OPENGLWIDGET_H
