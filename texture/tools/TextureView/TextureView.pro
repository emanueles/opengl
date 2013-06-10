#-------------------------------------------------
#
# Project created by QtCreator 2013-06-05T17:05:12
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TextureView
TEMPLATE = app


SOURCES += texture.c \
        tga.c\
        main.cpp\
        mainwindow.cpp \
        openglwidget.cpp


HEADERS  += mainwindow.h \
    openglwidget.h \
    texture.h \
    tga.h

FORMS    += mainwindow.ui

mac: LIBS += -framework GLUT
else:unix|win32: LIBS += -lGLUT

mac: LIBS += -framework OpenGL
else:unix|win32: LIBS += -lGLU
